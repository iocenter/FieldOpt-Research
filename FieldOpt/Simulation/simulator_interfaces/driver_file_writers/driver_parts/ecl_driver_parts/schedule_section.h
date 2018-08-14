/******************************************************************************
 *
 *
 *
 * Created: 18.11.2015 2015 by einar
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

#ifndef SCHEDULE_SECTION_H
#define SCHEDULE_SECTION_H

#include "ecldriverpart.h"
#include "Model/wells/well.h"
#include "welspecs.h"
#include "compdat.h"
#include "wellcontrols.h"
#include <QStringList>

namespace Simulation {
namespace SimulatorInterfaces {
namespace DriverFileWriters {
namespace DriverParts {
namespace ECLDriverParts {

class Schedule : public ECLDriverPart
{
public:
    Schedule(QList<Model::Wells::Well *> *wells, QList<int> control_times);
    QString GetPartString() const;

private:

  struct ScheduleTimeEntry {
    ScheduleTimeEntry(ECLDriverParts::Welspecs welspecs,
                      ECLDriverParts::Compdat compdat,
                      ECLDriverParts::WellControls well_controls);
    Welspecs welspecs;
    Compdat compdat;
    WellControls well_controls;
  };

  /*!
   * WELSPECS, COMPDAT and control entries for each timestep.
   */
  QList<ScheduleTimeEntry> schedule_time_entries_;

  QString schedule_;
};

}
}
}
}
}

#endif // SCHEDULE_SECTION_H
