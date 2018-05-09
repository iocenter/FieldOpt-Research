/******************************************************************************
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

#ifndef FIELDOPT_ENSEMBLE_HELPER_H
#define FIELDOPT_ENSEMBLE_HELPER_H

#include <boost/random.hpp>
#include "Settings/ensemble.h"
#include "Optimization/case.h"
#include <chrono>

namespace Runner {

/*!
 * The EnsembleHelper class contains facilities that helps the
 * Runner classes deal with ensembles (multiple realizations).
 */
class EnsembleHelper {

 public:
  EnsembleHelper();
  EnsembleHelper(const Settings::Ensemble &ensemble);

  /*!
   * Set a new active case and populate the realization queue
   * for it. You will not be able to set a new active case
   * until all the realizations selected for this one have been
   * evaluated.
   */
  void SetActiveCase(Optimization::Case *c);

  /*!
   * Check whether all the realizations selected for the currently
   * active case have been evaluated.
   */
  bool IsCaseDone() const;

  /*!
   * Chech whether there are any cases available for evaluation.
   */
  bool IsCaseAvailableForEval() const;

  /*!
   * Get a copy of the currently active case, with the realization
   * tag properly set.
   */
  Optimization::Case *GetCaseForEval();

  /*!
   * Return a case for a specific realization to the handler.
   * The objective function for it will be added to the array
   * in the original case object.
   */
  void SubmitEvaluatedRealization(Optimization::Case *c);

  /*!
   * Get a case that has had all the selected realizations evaluated.
   * This case will have a filled realization-ofv map.
   * @return
   */
  Optimization::Case *GetEvaluatedCase();

  /*!
   * Get the realization object refereincing the alias string.
   */
  Settings::Ensemble::Realization GetRealization(const std::string &alias) const;

  /*!
   * Get the base realization, to be used for evaluating the base model for initialization.
   * @param alias
   * @return
   */
  Settings::Ensemble::Realization GetBaseRealization() const;

 private:

  /*!
   * Pick a set of realizations from the ensemble and add
   * them to the queue.
   */
  void selectRealizations();

  /*!
   * Ensemble object containing paths for all realizations.
   */
  Settings::Ensemble ensemble_;

  /*!
   * The case that is currently being considered.
   */
  Optimization::Case *current_case_;

  /*!
   * Realization queue, containing the alias' of all realizatons
   * that should still be evaluated for the current case.
   */
  std::vector<std::string> rzn_queue_;

  /*!
   * List of alias' for realizations currently being evaluated.
   */
  std::vector<std::string> rzn_busy_;

  /*!
   * The number of realizations that will be selected for evaluation.
   */
  int n_select_;

  /*!
   * RNG that will be used when selecting which realizations to evaluate.
   */
  boost::random::mt19937 rng_;

  /*!
   * Time at which the currently active case was first added to the handler.
   */
  std::chrono::high_resolution_clock::time_point eval_start_time_;

};

}

#endif //FIELDOPT_ENSEMBLE_HELPER_H