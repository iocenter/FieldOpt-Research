#include "Simulation/tests/test_fixture_adgprs.h"
#include "Simulation/simulator_interfaces/adgprssimulator.h"

namespace {

class AdgprsDriverFileWriterTest : public AdgprsTestFixture {
protected:
    AdgprsDriverFileWriterTest() {
        simulator_ = new Simulation::SimulatorInterfaces::AdgprsSimulator(settings_, model_);
    }
    virtual ~AdgprsDriverFileWriterTest() {}
    virtual void SetUp() {}
    Simulation::SimulatorInterfaces::AdgprsSimulator *simulator_;
};

TEST_F(AdgprsDriverFileWriterTest, Initialization) {
}

}


