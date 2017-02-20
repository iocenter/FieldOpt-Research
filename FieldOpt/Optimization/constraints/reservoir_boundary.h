/******************************************************************************
   Copyright (C) 2015-2016 Einar J.M. Baumann <einar.baumann@gmail.com>

   This file is part of the FieldOpt project.

   FieldOpt is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   FieldOpt is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with FieldOpt.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef FIELDOPT_RESERVOIRBOUNDARY_H
#define FIELDOPT_RESERVOIRBOUNDARY_H

#include "constraint.h"
#include "well_spline_constraint.h"
#include "Reservoir/grid/grid.h"

namespace Optimization {
namespace Constraints {

/*!
 * \brief The ReservoirBoundary class deals with
 * imposing and checking reservoir boundary constraints
 *
 *  The class takes a boundary as input in the form of
 *  i,j and k min,max, i.e. a 'box' in the grid i,j,k
 *  coordinates. It can check wether or not a single
 *  well is inside the given box domain and, if needed,
 *  project the well onto the domain.
 *
 *  \todo Figure out a more effective way to enforce
 *  the box constraints (TASK A), then figure out way
 *  boundary constraints for non-box (parallelogram)
 *  shapes (TASK B); finally, define this constraint
 *  (out of ReservoirBoundary) as a standalone
 *  constraint (call it Box) (TASK C)
 *
 *  Steps for (A):
 *  1. find the edge cells of the box [x] + unit test [],
 *
 *  2. get the corner points for each of the cells [] + unit test [],
 *
 *  3. find the corner points of the entire box (assuming the box is a
 *  parallelogram, which may not be true for the top and bottom planes
 *  -> figure out how to deal with this later) [] + unit test [],
 *
 *  4. print the box data to log for external visualization
 *
 *  5. figure out if the current point is inside or outside
 *  the box, e.g., create a BoxEnvelopsPoint function
 *
 *  6. if outside, project point onto nearest point on plane
 *
 *  Steps for (B):
 */
class ReservoirBoundary : public Constraint, WellSplineConstraint
{
 public:
  ReservoirBoundary(const Settings::Optimizer::Constraint &settings,
                    Model::Properties::VariablePropertyContainer *variables,
                    Reservoir::Grid::Grid *grid);

  // Constraint interface
 public:
  bool CaseSatisfiesConstraint(Case *c);
  void SnapCaseToConstraints(Case *c);

  /* \brief Function getListOfBoxEdgeCellIndices uses the limits
   * defining the box constraint to find the cells that constitute
   * the edges of the box
   */
  QList<int> returnListOfBoxEdgeCellIndices() const { return index_list_edge_; }

 private:
  int imin_, imax_, jmin_, jmax_, kmin_, kmax_;
  QList<int> index_list_;
  Reservoir::Grid::Grid *grid_;
  Well affected_well_;
  QList<int> getListOfCellIndices();

  QList<int> getListOfBoxEdgeCellIndices();
  QList<int> index_list_edge_;

};
}
}

#endif //FIELDOPT_RESERVOIRBOUNDARY_H
