/******************************************************************************
 *
 *
 *
 * Created: 17.11.2015 2015 by einar
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

#include "Model/tests/test_fixture_model_base.h"
#include "Simulation/simulator_interfaces/driver_file_writers/driver_parts/ecl_driver_parts/solution_section.h"

using namespace ::Simulation::SimulatorInterfaces::DriverFileWriters::DriverParts::ECLDriverParts;

namespace {

class DriverPartSolutionTest : public ModelBaseTest {
protected:
    DriverPartSolutionTest(){
        QStringList *driver_file_contents = Utilities::FileHandling::ReadFileToStringList(settings_->simulator()->driver_file_path());
        solution_ = new Solution(driver_file_contents);
    }
    virtual ~DriverPartSolutionTest(){}

    Solution *solution_;
};

TEST_F(DriverPartSolutionTest, Constructor) {
    //std::cout << solution_->GetPartString().toStdString() << std::endl;
}

}
