/*
 * OmplPlanner.cpp
 *
 *  Created on: Apr 1, 2020
 *      Author: jelavice
 */

#include "se2_planning/OmplPlanner.hpp"

#include <functional>

namespace se2_planning {

void OmplPlanner::setStartingState(const State& startingState) {
  startState_ = convert(startingState);
}
void OmplPlanner::setGoalState(const State& goalState) {
  goalState_ = convert(goalState);
}

void OmplPlanner::getPath(Path* path) const {
  convert(*path_, path);
}

bool OmplPlanner::plan() {
  bool status = planConcreteImpl();
  simpleSetup_->setStartAndGoalStates(*startState_, *goalState_);

  if (!simpleSetup_->solve(maxPlanningDuration_)) {
    return false;
  }

  // simplify solution
  simpleSetup_->simplifySolution();

  return status;
}
bool OmplPlanner::reset() {
  simpleSetup_->clear();
  return true;
}
bool OmplPlanner::initialize() {
  bool status = initializeConcreteImpl();

  ompl::base::SpaceInformationPtr si_ = simpleSetup_->getSpaceInformation();
  simpleSetup_->setStateValidityChecker(std::bind(&OmplPlanner::isStateValid, this, si_.get(), std::placeholders::_1));

  return status;
}

void OmplPlanner::setMaxPlanningDuration(double T) {
  maxPlanningDuration_ = T;
}

} /*namespace se2_planning */
