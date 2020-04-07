/*
 * PriusControllerRos.hpp
 *
 *  Created on: Apr 6, 2020
 *      Author: jelavice
 */

#pragma once
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include "se2_navigation_msgs/RequestCurrentStateSrv.h"
#include "se2_navigation_msgs/SendControllerCommandSrv.h"

namespace car_demo {

class PriusControllerRos {

  using CurrentStateService = se2_navigation_msgs::RequestCurrentStateSrv;
  using ControllerCommandService = se2_navigation_msgs::SendControllerCommandSrv;
 public:
  PriusControllerRos(ros::NodeHandlePtr nh);
  virtual ~PriusControllerRos() = default;
  void initialize(double dt);
  void advance();

 private:

  void publishControl() const;
  void initRos();
  void priusStateCallback(const nav_msgs::Odometry &odometry);

  bool currentStateRequestService(CurrentStateService::Request &req, CurrentStateService::Response &res );
  bool controllerCommandService(ControllerCommandService::Request &req, ControllerCommandService::Response &res );

  void processStartTrackingCommand();
  void processAbortTrackingCommand();

  ros::NodeHandlePtr nh_;
  double dt_ = 0.01;
  ros::Publisher priusControlPub_;
  ros::Subscriber priusStateSub_;
  ros::ServiceServer priusCurrentStateService_;
  ros::ServiceServer controllerCommandService_;
  nav_msgs::Odometry priusState_;

  /*state machine variables*/
  bool planReceived_ = false;
  bool currentlyExecutingPlan_ = false;
  bool receivedStartTrackingCommand_ = false;
  bool doneFollowingPrev_ = false;
  bool publishTrackingStatus_ = false;

};


} /* namespace car_demo*/