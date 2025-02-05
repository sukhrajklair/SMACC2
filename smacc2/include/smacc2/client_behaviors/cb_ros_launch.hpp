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

#include <smacc2/client_bases/smacc_ros_launch_client.hpp>
#include <smacc2/smacc_asynchronous_client_behavior.hpp>

namespace smacc2
{
namespace client_behaviors
{
enum class RosLaunchMode
{
  LAUNCH_DETTACHED,
  LAUNCH_CLIENT_BEHAVIOR_LIFETIME
};

class CbRosLaunch : public smacc2::SmaccAsyncClientBehavior
{
private:
  static std::vector<std::future<std::string>> detached_futures_;

public:
  CbRosLaunch();

  CbRosLaunch(std::string package, std::string launchfile, RosLaunchMode);

  // CbRosLaunch(std::string packageName, std::string launchFileName);

  virtual ~CbRosLaunch();

  template <typename TOrthogonal, typename TSourceObject>
  void onOrthogonalAllocation()
  {
    smacc2::SmaccAsyncClientBehavior::onOrthogonalAllocation<TOrthogonal, TSourceObject>();
  }

  void onEntry() override;

  std::optional<std::string> packageName_;
  std::optional<std::string> launchFileName_;

  RosLaunchMode launchMode_;

protected:
  std::string result_;

  smacc2::client_bases::ClRosLaunch * client_;

  std::future<std::string> future_;
};
}  // namespace client_behaviors
}  // namespace smacc2
