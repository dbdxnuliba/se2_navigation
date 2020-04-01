/*
 * OmplPlanner.hpp
 *
 *  Created on: Apr 1, 2020
 *      Author: jelavice
 */

#pragma once

#include "ompl/base/SpaceInformation.h"
#include "ompl/geometric/SimpleSetup.h"
#include "se2_planning/Planner.hpp"

namespace se2_planning {

class OmplPlanner : public Planner {
 public:
  OmplPlanner() = default;
  ~OmplPlanner() override = default;

  bool reset() override;
  bool plan() final;
  bool initialize() final;
  void setStartingState(const State& startingState) final;
  void setGoalState(const State& goalState) final;
  void getPath(Path* path) const final;
  void setMaxPlanningDuration(double T);

 protected:
  virtual bool initializeConcreteImpl() = 0;
  virtual bool planConcreteImpl() = 0;
  virtual void setStateSpaceBoundaries() = 0;
  virtual bool isStateValid(const ompl::base::SpaceInformation* si, const ompl::base::State* state) = 0;
  virtual ompl::base::ScopedStatePtr convert(const State& state) const = 0;
  virtual void convert(const ompl::geometric::PathGeometric& pathOmpl, Path* path) const = 0;

  ompl::base::StateSpacePtr stateSpace_;
  ompl::geometric::SimpleSetupPtr simpleSetup_;
  ompl::base::RealVectorBounds stateSpaceBounds_;
  ompl::base::ScopedStatePtr startState_, goalState_;
  std::shared_ptr<ompl::geometric::PathGeometric> path_;
  double maxPlanningDuration_ = 1.0;
};

}  // namespace se2_planning
