#include "wellcontrols.h"

namespace Simulation {
    namespace SimulatorInterfaces {
        namespace DriverFileWriters {
            namespace DriverParts {
                namespace ECLDriverParts {

                    WellControls::WellControls(QList<Model::Wells::Well *> *wells)
                    {
                        initializeBaseEntryLine(12);
                        initializeTimeEntries(wells);
                    }

                    QString WellControls::GetPartString()
                    {
                        QString part = "";
                        for (int time : time_entries_.keys()) {
                            part.append(createTimeEntry(time));
                            for (WellSetting *setting : time_entries_.value(time)->well_settings) {
                                if (setting->is_injector)
                                    part.append(createInjectorEntry(setting));
                                else
                                    part.append(createProducerEntry(setting));
                            }
                        }
                        return part;
                    }

                    void WellControls::initializeTimeEntries(QList<Model::Wells::Well *> *wells)
                    {
                        time_entries_ = QMap<int, TimeEntry *>();
                        for (int i = 0; i < wells->size(); ++i) {
                            if (wells->at(i)->trajectory()->GetWellBlocks()->size() > 0) {
                                for (int j = 0; j < wells->at(i)->controls()->size(); ++j) {
                                    int current_time_step = wells->at(i)->controls()->at(j)->time_step();
                                    WellSetting *well_setting = new WellSetting();
                                    well_setting->well_name = wells->at(i)->name();
                                    well_setting->is_injector = wells->at(i)->type() == ::Utilities::Settings::Model::WellType::Injector;
                                    well_setting->control = wells->at(i)->controls()->at(j);
                                    if (time_entries_.keys().contains(current_time_step)) {
                                        // Adding to existing time step
                                        time_entries_.value(current_time_step)->well_settings.append(well_setting);
                                    }
                                    else {
                                        // Adding new time step
                                        TimeEntry *time_entry = new TimeEntry();
                                        time_entry->time = current_time_step;
                                        time_entry->well_settings = QList<WellSetting *>({well_setting});
                                        time_entries_.insert(time_entry->time, time_entry);
                                    }

                                }
                            }
                        }
                    }

                    QString WellControls::createTimeEntry(int time)
                    {
                        if (time == 0) {
                            return QString(""); // A Time entry should not be created for the initial step
                        }
                        return QString("TIME\n   %1/\n\n").arg(time);
                    }

                    QString WellControls::createProducerEntry(WellControls::WellSetting *setting)
                    {
                        initializeBaseEntryLine(9);
                        QStringList producer_entry_line = QStringList(base_entry_line_);
                        producer_entry_line[0] = setting->well_name;

                        if (setting->control->open()) producer_entry_line[1] = "OPEN";
                        else producer_entry_line[1] = "SHUT";

                        switch (setting->control->mode()) {
                            case ::Utilities::Settings::Model::ControlMode::BHPControl:
                                producer_entry_line[2] = "BHP";
                                producer_entry_line[8] = QString::number(setting->control->bhp());
                                break;
                            case ::Utilities::Settings::Model::ControlMode::RateControl:
                                producer_entry_line[2] = "LRAT";
                                producer_entry_line[6] = QString::number(setting->control->rate());
                                break;
                            default:
                                throw std::runtime_error("Producer control mode not recognized.");
                        }
                        return "WCONPROD\n   " + producer_entry_line.join(" ") + "/\n/\n\n";
                    }

                    QString WellControls::createInjectorEntry(WellControls::WellSetting *setting)
                    {
                        initializeBaseEntryLine(7);
                        QStringList injector_entry_line = QStringList(base_entry_line_);
                        injector_entry_line[0] = setting->well_name;

                        switch (setting->control->injection_fluid()) {
                            case ::Utilities::Settings::Model::InjectionType::WaterInjection:
                                injector_entry_line[1] = "WATER";
                                break;
                            case ::Utilities::Settings::Model::InjectionType::GasInjection:
                                injector_entry_line[1] = "GAS";
                                break;
                            default:
                                throw std::runtime_error("Injector type not recognized.");
                        }

                        if (setting->control->open()) injector_entry_line[2] = "OPEN";
                        else injector_entry_line[2] = "SHUT";

                        switch (setting->control->mode()) {
                            case ::Utilities::Settings::Model::ControlMode::BHPControl:
                                injector_entry_line[3] = "BHP";
                                injector_entry_line[6] = QString::number(setting->control->bhp());
                                break;
                            case ::Utilities::Settings::Model::ControlMode::RateControl:
                                injector_entry_line[3] = "RATE";
                                injector_entry_line[4] = QString::number(setting->control->rate());
                                break;
                            default:
                                throw std::runtime_error("Producer control mode not recognized.");
                        }
                        return "WCONINJE\n   " + injector_entry_line.join(" ") + "/\n/\n\n";
                    }



                }
            }
        }
    }
}
