/***********************************************************
 Created by Mathias C. Bellout on 27.11.18
 Copyright (C) 2018-2019 Mathias Bellout
 <mathias.bellout@petroleumcyberneticsgroup.no>
 <chakibbb-pcg@gmail.com>

 Modified 2018-2019 Thiago Lima Silva
 <thiagolims@gmail.com>

 This file is part of the FieldOpt project.

 FieldOpt is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation, either version
 3 of the License, or (at your option) any later version.

 FieldOpt is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty
 of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 the GNU General Public License for more details.

 You should have received a copy of the
 GNU General Public License along with FieldOpt.
 If not, see <http://www.gnu.org/licenses/>.
***********************************************************/

#include <gtest/gtest.h>

// Define settings for tr-dfo
#include "Optimization/tests/test_resource_optimizer.h"
#include "Optimization/tests/test_resource_cases.h"

#include "Runner/tests/test_resource_runner.hpp"
#include "Reservoir/tests/test_resource_grids.h"
#include "Optimization/tests/test_resource_test_functions.h"

#include "Optimization/optimizers/trust_region/TrustRegionOptimization.h"

#include <Eigen/Core>
#include <Eigen/Dense>
#include "Utilities/math.hpp"
#include "Utilities/colors.hpp"
#include "Utilities/stringhelpers.hpp"

#include "test_tr-model-data.hpp"
#include "test_tr-support.hpp"

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

        TrustRegionOptimization *tr_dfo_;
        Optimization::Case *test_case_tr_dfo_probs_;
        VariablePropertyContainer *varcont_tr_dfo_probs_;
        TestResources::TrustRegionModelData tr_mdata;

        void SetUpOptimizer(TestResources::TrustRegionModelData::prob &prob,
                            double (*tr_dfo_prob)(VectorXd xs)){

            VectorXd x0 = prob.xm.col(0);

            // Dummy var container based on initial point
            varcont_tr_dfo_probs_ = new VariablePropertyContainer();
            QString base_varname = "BHP#PRODUCER#"; // dummy var name

            for (int i = 0; i < x0.rows(); ++i) {
                // Use initial point values to construct container
                auto *prop = new ContinousProperty(x0(i));
                prop->setName(base_varname + QString::number(i));
                varcont_tr_dfo_probs_->AddVariable(prop);
            }

            // Set up base case using dummy var containter
            test_case_tr_dfo_probs_ = new Optimization::Case(
                    QHash<QUuid, bool>(), QHash<QUuid, int>(),
                    varcont_tr_dfo_probs_->GetContinousVariableValues());

            TestResources::FindVarSequence(prob,
                                           *test_case_tr_dfo_probs_);

            VectorXd ordered_vec(test_case_tr_dfo_probs_->GetRealVarVector().size());
            auto vec =test_case_tr_dfo_probs_->GetRealVarVector();
            for (int i=0; i <prob.idx.size(); i++) {
                ordered_vec(i) = vec(prob.idx[i]);
            }
            test_case_tr_dfo_probs_->SetRealVarValues(ordered_vec);

            // Use initial point from Matlab data
            test_case_tr_dfo_probs_->set_objective_function_value(tr_dfo_prob(x0));

            cout << "SetUpOptimizer" << endl;
            tr_dfo_ = new TrustRegionOptimization(
                    settings_tr_opt_max_,
                    test_case_tr_dfo_probs_,
                    varcont_tr_dfo_probs_,
                    grid_5spot_,
                    logger_);

        }

        void RunnerSubs(TestResources::TrustRegionModelData::prob prob,
                        double (*tr_dfo_prob)(VectorXd xs)){

            stringstream ss; ss << "[          ] " << FMAGENTA;
            double tol = 1e-06;
            int p_count = 0;

            while (tr_dfo_->IsFinished()
            == Optimization::Optimizer::TerminationCondition::NOT_FINISHED) {

                cout << "Runner@start: Call GetCaseForEvaluation()" << endl;
                auto next_case = tr_dfo_->GetCaseForEvaluation();

                // Compute obj.function value for case
                next_case->set_objective_function_value(
                        tr_dfo_prob(next_case->GetRealVarVector()));

                // Override 2nd point
                if (p_count == 1) {
                    TestResources::OverrideSecondPoint(prob, *next_case);
                }

                // Print case data (id, x, f)
                TestResources::PrintCaseData(*next_case);

                // Test if current point is equal to matlab data
                if (p_count < 2) {

                    string msg = "Checking point " + to_string(p_count+1) + " is equal";
                    TestResources::CheckSameVector(
                            next_case->GetRealVarVector(),
                            prob.xm.col(p_count), tol, msg);
                }

                // Finish Runner
                cout << "Runner@end: Call SubmitEvaluatedCase()" << endl;
                tr_dfo_->SubmitEvaluatedCase(next_case);

                if (tr_dfo_->getTrustRegionModel()->isInitialized() && (p_count < 2)) {

                    // Test pivot values (vector) are equal
                    TestResources::CheckSameVector(
                            tr_dfo_->getTrustRegionModel()->getPivotValues().transpose(),
                            prob.vm.col(0), tol, "Check pivot values are equal", true);

                    // Test polynomial values (column matrix) are equal
                    TestResources::CheckSamePolynomials(
                            tr_dfo_->getTrustRegionModel()->getPivotPolynomials(),
                            prob.pcm, tol, "Check pivot coeff. vector #");

                }

                p_count++;

            }

            cout << ss.str() << "----------------------" << END << endl;
            auto best_case = tr_dfo_->GetTentativeBestCase();
            cout << best_case->objective_function_value() << endl;
        }

    };

    TEST_F(TrustRegionTest, tr_dfo_prob1) {
        cout << endl << FMAGENTA << "[          ] =============="
             << "=========================================== " << endl
             << "[ CG.prob1 ] "
             << " f = @(x) (1 - x(1))^2; x0=[-1.2 2.0]" << END << endl;

        SetUpOptimizer(tr_mdata.prob1, tr_dfo_prob1);
        RunnerSubs(tr_mdata.prob1, tr_dfo_prob1);
    }

    TEST_F(TrustRegionTest, tr_dfo_prob2) {
        cout << endl << FMAGENTA << "[          ] =============="
             << "=========================================== " << endl
             << "[ CG.prob2 ] "
             << "f = @(x) log1p(x(1)^2) + x(2)^2; x0=[2.0 2.0]"
             << END << endl;

        SetUpOptimizer(tr_mdata.prob2, tr_dfo_prob2);
        RunnerSubs(tr_mdata.prob2, tr_dfo_prob2);
    }

    TEST_F(TrustRegionTest, tr_dfo_prob3) {
        cout << endl << FMAGENTA << "[          ] =============="
             << "=========================================== " << endl
             << "[ CG.prob3 ] "
             << "f = @(x) sin(pi*x(1)/12) * cos(pi*x(2)/16); x0=[0.0 0.0]"
             << END << endl;

        SetUpOptimizer(tr_mdata.prob3, tr_dfo_prob3);
        RunnerSubs(tr_mdata.prob3, tr_dfo_prob3);
    }

//    TEST_F(TrustRegionTest, tr_dfo_prob4) {
//        cout << FMAGENTA
//             << "[ CG.prob4 ] f = @(x) "
//             << END << endl;
//        SetUpOptimizer(tr_mdata.prob4, tr_dfo_prob4);
//        RunnerSubs(tr_mdata.prob4, tr_dfo_prob4);
//    }

    TEST_F(TrustRegionTest, tr_dfo_initial_model_created) {
        bool is_model_present = false;
        SetUpOptimizer(tr_mdata.prob1, tr_dfo_prob1);

        // Compute obj.function value for case
        auto next_case = tr_dfo_->GetCaseForEvaluation();
        next_case->set_objective_function_value(
                tr_dfo_prob1(next_case->GetRealVarVector()));

        cout << "----------------------" << END << endl;
        cout << "Case id:" << next_case << END << endl;
        cout << "x:" << next_case->GetRealVarVector().transpose() << END << endl;
        cout << "f:" << next_case->objective_function_value() << END << endl;

        // Finish Runner
        tr_dfo_->SubmitEvaluatedCase(next_case);

        // Compute obj.function value for case
        auto scnd_case = tr_dfo_->GetCaseForEvaluation();
        TestResources::OverrideSecondPoint(tr_mdata.prob1, *next_case);
        scnd_case->set_objective_function_value(
                tr_dfo_prob1(scnd_case->GetRealVarVector()));

        cout << "----------------------" << END << endl;
        cout << "Case id:" << scnd_case << END << endl;
        cout << "x:" << scnd_case->GetRealVarVector().transpose() << END << endl;
        cout << "f:" << scnd_case->objective_function_value() << END << endl;

        // Finish Runner
        tr_dfo_->SubmitEvaluatedCase(scnd_case);

        auto tr_model = tr_dfo_->getTrustRegionModel();

        if (tr_model) {
            if (tr_model->getNumPts() >=2) { //<!at least 2 points are needed in the
                is_model_present = true;
            } else {
                cout << "Not enough points in the model." << endl;
            }
        } else {
            cout << "model not created" << endl;
        }
        EXPECT_TRUE(is_model_present);
    }

    TEST_F(TrustRegionTest, tr_dfo_initial_rebuild_model) {
        bool is_model_present = false;
        SetUpOptimizer(tr_mdata.prob1, tr_dfo_prob1);

        // RUNNER CALL (START)
        auto next_case = tr_dfo_->GetCaseForEvaluation();

        // COMPUTE OBJ.FUNCTION VALUE FOR CASE
        next_case->set_objective_function_value(
                tr_dfo_prob1(next_case->GetRealVarVector()));

        if (tr_dfo_->GetNumInitPoints() == 1 ) {
            TestResources::OverrideSecondPoint(tr_mdata.prob1, *next_case);
        }

        // RUNNER CALL (FINISH)
        tr_dfo_->SubmitEvaluatedCase(next_case);

        auto tr_model = tr_dfo_->getTrustRegionModel();
        auto pivot_polynomials = tr_model->getPivotPolynomials();
        auto pivot_values = tr_model->getPivotValues();
        double tol = 1e-06;

        auto same_pivot_values =  true;
        for (int i=0; i<pivot_values.size(); i++) {
            if (abs(pivot_values(i) - tr_mdata.prob1.vm(i,0)) > tol) {
                same_pivot_values = false;
            }
        }
        auto same_pivot_coeff = true;
        for (int i=0; i<pivot_polynomials.size(); i++) {
            if (pivot_polynomials[i].dimension != tr_mdata.prob1.pdm(i)) {
                same_pivot_coeff = false;
            }

            for (int j=0; j<pivot_polynomials.size(); j++) {
                if (abs(pivot_polynomials[i].coefficients(j) -  tr_mdata.prob1.pcm(j,i)) > tol) {
                    same_pivot_coeff = false;
                }
            }
        }
        EXPECT_TRUE(same_pivot_values &&  same_pivot_coeff);
    }


    TEST_F(TrustRegionTest, tr_dfo_initial_compute_polynomial_models) {
        bool is_model_present = false;
        SetUpOptimizer(tr_mdata.prob1, tr_dfo_prob1);

        // RUNNER CALL (START)
        auto next_case = tr_dfo_->GetCaseForEvaluation();

        // COMPUTE OBJ.FUNCTION VALUE FOR CASE
        next_case->set_objective_function_value(
                tr_dfo_prob1(next_case->GetRealVarVector()));

        if (tr_dfo_->GetNumInitPoints() == 1 ) {
            TestResources::OverrideSecondPoint(tr_mdata.prob1, *next_case);
        }

        // RUNNER CALL (FINISH)
        tr_dfo_->SubmitEvaluatedCase(next_case);

        auto tr_model = tr_dfo_->getTrustRegionModel();
        auto modeling_polynomials = tr_model->getModelingPolynomials();

        double tol = 1e-06;
        auto same_modeling_polynomials = true;

        for (int i=0; i<modeling_polynomials.size(); i++)  {
            if (modeling_polynomials[i].dimension != tr_mdata.prob1.mdm(i)) {
                same_modeling_polynomials = false;
            }

            for (int j=0; j<modeling_polynomials[i].coefficients.size(); j++) {
                if (abs(modeling_polynomials[i].coefficients(j) - tr_mdata.prob1.mcm(j,i)) > tol) {
                    same_modeling_polynomials = false;
                }
            }
        }
        EXPECT_TRUE(same_modeling_polynomials);
    }

}
