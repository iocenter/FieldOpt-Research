/******************************************************************************
 *
 *
 *
 * Created: 16.12.2015 2015 by einar
 *
 * This file is part of the FieldOpt project.
 *
 * Copyright (C) 2015-2015 Einar J.M. Baumann <einar.baumann@ntnu.no>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *****************************************************************************/

#include "runtime_settings.h"

namespace Runner {

RuntimeSettings::RuntimeSettings(boost::program_options::variables_map vm)
{
    if (vm.count("input-file")) {
        driver_file_ = QString::fromStdString(vm["input-file"].as<std::string>());
        if (!Utilities::FileHandling::FileExists(driver_file_))
            throw std::runtime_error("The specified driver file does not exist.");
    } else throw std::runtime_error("An input file must be specified.");

    if (vm.count("output-dir")) {
        output_dir_ = QString::fromStdString(vm["output-dir"].as<std::string>());
        if (!Utilities::FileHandling::DirectoryExists(output_dir_))
            throw std::runtime_error("The specified output directory does not exist.");
    } else throw std::runtime_error("An output directory must be specified.");

    verbose_ = vm.count("verbose") ? true : false;

    overwrite_existing_ = vm.count("force") ? true : false;
    if (!overwrite_existing_ && !Utilities::FileHandling::DirectoryIsEmpty(output_dir_))
        throw std::runtime_error("Output directory is not empty. Use the --force flag to overwrite existing content.");

    if (vm.count("max-parallel-simulations")) {
        max_parallel_sims_ = vm["max-parallel-simulations"].as<int>();
    } else max_parallel_sims_ = 0;

    if (vm.count("runner-type")) {
        QString runner_str = QString::fromStdString(vm["runner-type"].as<std::string>());
        if (QString::compare(runner_str, "serial") == 0)
            runner_type_ = RunnerType::SERIAL;
        else if (QString::compare(runner_str, "oneoff") == 0)
            runner_type_ = RunnerType::ONEOFF;
    } else runner_type_ = RunnerType::SERIAL;

    if (vm.count("sim-drv-path")) {
        QString sim_drv_path = QString::fromStdString(vm["sim-drv-path"].as<std::string>());
        if (!Utilities::FileHandling::FileExists(sim_drv_path))
            throw std::runtime_error("Simulation driver file specified as argument does not exist.");
        else simulator_driver_path_ = sim_drv_path;
    } else simulator_driver_path_ = "";

    if (vm.count("grid-path")) {
        QString grid_path = QString::fromStdString(vm["grid-path"].as<std::string>());
        if (!Utilities::FileHandling::FileExists(grid_path))
            throw std::runtime_error("Grid file path specified as argument does not exist.");
        else grid_file_path_ = grid_path;
    } else grid_file_path_ = "";

    if (vm.count("well-prod-points")) {
        if (vm["well-prod-points"].as<std::vector<double>>().size() != 6)
            throw std::runtime_error("Exactly six coordinates must be provided for the production well position.");
        std::vector<double> coords = vm["well-prod-points"].as<std::vector<double>>();
        prod_coords_.first = QVector<double>() << coords[0] << coords[1] << coords[2];
        prod_coords_.second = QVector<double>() << coords[3] << coords[4] << coords[5];
    }
    if (vm.count("well-inj-points")) {
        if (vm["well-inj-points"].as<std::vector<double>>().size() != 6)
            throw std::runtime_error("Exactly six coordinates must be provided for the injection well position.");
        std::vector<double> coords = vm["well-inj-points"].as<std::vector<double>>();
        inje_coords_.first = QVector<double>() << coords[0] << coords[1] << coords[2];
        inje_coords_.second = QVector<double>() << coords[3] << coords[4] << coords[5];
    }


    if (verbose_) {
        std::cout << "FieldOpt runtime settings: " << std::endl;
        std::cout << "Input file:     " << driver_file_.toStdString() << std::endl;
        std::cout << "Output dir:     " << output_dir().toStdString() << std::endl;
        std::cout << "Sim driver file:" << (simulator_driver_path_.length() > 0 ? simulator_driver_path_.toStdString() : "from FieldOpt driver file") << std::endl;
        std::cout << "Grid file path: " << (grid_file_path_.length() > 0 ? grid_file_path_.toStdString() : "from FieldOpt driver file") << std::endl;
        std::cout << "Runner type:    " << runnerTypeString().toStdString() << std::endl;
        std::cout << "Verbose output: " << verbose_ << std::endl;
        std::cout << "Overwr. existing out files: " << overwrite_existing_ << std::endl;
        std::cout << "Max parallel simulations:   " << (max_parallel_sims_ > 0 ? std::to_string(max_parallel_sims_) : "default") << std::endl;
        std::cout << "Producer coordinates:       " << "(" << prod_coords_.first[0]  << ", " << prod_coords_.first[1]  << ", " << prod_coords_.first[2]  << "), "
                                                    << "(" << prod_coords_.second[0] << ", " << prod_coords_.second[1] << ", " << prod_coords_.second[2] << ")" << std::endl;
        std::cout << "Injector coordinates:       " << "(" << inje_coords_.first[0]  << ", " << prod_coords_.first[1]  << ", " << inje_coords_.first[2]  << "), "
                                                    << "(" << inje_coords_.second[0] << ", " << prod_coords_.second[1] << ", " << inje_coords_.second[2] << ")" << std::endl;
    }
}



QString RuntimeSettings::runnerTypeString() {
    if (runner_type_ == RunnerType::SERIAL)
        return "serial";
    else return "NOT SET";
}

}
