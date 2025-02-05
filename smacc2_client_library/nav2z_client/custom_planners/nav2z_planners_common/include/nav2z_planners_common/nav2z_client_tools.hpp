// Copyright 2021 RobosoftAI Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*****************************************************************************************************************
 *
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#pragma once

#include <vector>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>

namespace cl_nav2z
{
geometry_msgs::msg::PoseStamped makePureSpinningSubPlan(
  const geometry_msgs::msg::PoseStamped & start, double dstRads,
  std::vector<geometry_msgs::msg::PoseStamped> & plan, double radstep = 0.005);

geometry_msgs::msg::PoseStamped makePureStraightSubPlan(
  const geometry_msgs::msg::PoseStamped & startOrientedPose, const geometry_msgs::msg::Point & goal,
  double length, std::vector<geometry_msgs::msg::PoseStamped> & plan);

}  // namespace cl_nav2z
