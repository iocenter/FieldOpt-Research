//
// Created by bellout on 11/27/18.
//

#include <gtest/gtest.h>

// Define settings for tr-dfo
#include "Optimization/tests/test_resource_optimizer.h"
#include "Optimization/tests/test_resource_cases.h"

#include "Runner/tests/test_resource_runner.hpp"
#include "Reservoir/tests/test_resource_grids.h"
#include "Optimization/tests/test_resource_test_functions.h"

#include "Optimization/optimizers/trust_region/TrustRegionOptimization.h"

#include <Eigen/Core>
#include "Utilities/math.hpp"
#include "Utilities/colors.hpp"
#include "Utilities/stringhelpers.hpp"

using namespace TestResources::TestFunctions;
using namespace Optimization::Optimizers;
using namespace std;

namespace {

    class TrustRegionTest : public ::testing::Test,
                            public TestResources::TestResourceOptimizer,
                            public TestResources::TestResourceGrids {

    protected:
        TrustRegionTest() {}

        virtual ~TrustRegionTest() {}
        virtual void SetUp() {}

        Optimization::Optimizer *tr_dfo_;
        Optimization::Case *test_case_tr_dfo_probs_;
        VariablePropertyContainer *varcont_tr_dfo_probs_;

        void SetUpVarCont(int nvars){
            // Make 'synthetic' variable container (sz:10) for tr-dfo test functions
            varcont_tr_dfo_probs_ = new VariablePropertyContainer();
            QString base_varname = "BHP#PRODUCER#"; // dummy var name
            for (int i = 0; i < nvars; ++i) {
                ContinousProperty *prop = new ContinousProperty(0.0);
                prop->setName(base_varname + QString::number(i));
                varcont_tr_dfo_probs_->AddVariable(prop);
            }
        }

        void SetUpCase(){
            // Trust region problems from C.Guliani
            // Make 'synthetic' case using tr-dfo variable container
            test_case_tr_dfo_probs_ = new Optimization::Case(
                    QHash<QUuid, bool>(), QHash<QUuid, int>(),
                    varcont_tr_dfo_probs_->GetContinousVariableValues());

            test_case_tr_dfo_probs_->set_objective_function_value(0.0);
        }

        void SetUpOptimizer(){
            tr_dfo_ = new TrustRegionOptimization(
                    settings_tr_opt_max_,
                    test_case_tr_dfo_probs_,
                    varcont_tr_dfo_probs_,
                    grid_5spot_,
                    logger_);
        }

        void SolveProb(){
            while (!tr_dfo_->IsFinished()) {
                cout << "[          ] " << FMAGENTA
                     << "Getting new case (i.e., x_{k+1}) from tr-dfo algo"
                     << END << endl;
                auto next_case = tr_dfo_->GetCaseForEvaluation();
                next_case->set_objective_function_value(
                        tr_dfo_prob1(next_case->GetRealVarVector()));
                tr_dfo_->SubmitEvaluatedCase(next_case);
            }

            auto best_case = tr_dfo_->GetTentativeBestCase();
            cout << best_case->objective_function_value() << endl;
        }

    };

    //  auto values = variables->GetContinousVariableValues();
    //  VectorXd test_vec = VectorXd::Zero(values.size());
    //  Case * init_case = new Case(base_case);
    //  init_case->SetRealVarValues(test_vec);
    //  case_handler_->AddNewCase(init_case);

    TEST_F(TrustRegionTest, tr_dfo_prob1) {
        cout << FMAGENTA
             << "[CG.prob1  ] f = @(x) (1 - x(1))^2; x0=[-1.2 2.0]"
             << END << endl;

        VectorXd x0(2);
        x0 << -1.2, -2.0;
        SetUpVarCont(x0.rows());
        SetUpCase();

        test_case_tr_dfo_probs_->set_objective_function_value(tr_dfo_prob1(x0));
        SetUpOptimizer();
        SolveProb();
    }

    TEST_F(TrustRegionTest, tr_dfo_prob2) {
        cout << FMAGENTA
             << "[CG.prob2  ] f = @(x) log1p(x(1)^2) + x(2)^2; x0=[2.0 2.0]"
             << END << endl;

        VectorXd x0(2);
        x0 << -2.0, -2.0;
        SetUpVarCont(x0.rows());
        SetUpCase();

        test_case_tr_dfo_probs_->set_objective_function_value(tr_dfo_prob2(x0));
        SetUpOptimizer();
        SolveProb();
    }

    TEST_F(TrustRegionTest, tr_dfo_prob3) {
        cout << FMAGENTA
             << "[CG.prob3  ] f = @(x) sin(pi*x(1)/12) * cos(pi*x(2)/16); x0=[0.0 0.0]"
             << END << endl;

        VectorXd x0(2);
        x0 << -0.0, -0.0;
        SetUpVarCont(x0.rows());
        SetUpCase();

        test_case_tr_dfo_probs_->set_objective_function_value(tr_dfo_prob3(x0));
        SetUpOptimizer();
        SolveProb();
    }

}