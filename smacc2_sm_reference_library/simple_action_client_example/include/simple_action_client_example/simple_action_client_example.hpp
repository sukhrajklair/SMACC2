// Copyright 2021 MyName/MyCompany Inc.
// Copyright 2021 RobosoftAI Inc. (template)
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

#pragma once

#include <memory>
#include <string>

#include "smacc2/smacc.hpp"

//CLIENTS AND BEHAVIORS
#include "simple_action_client_example/mode_selection_client/cl_mode_select.hpp"
#include "simple_action_client_example/fibonacci_action_client/cl_fibonacci.hpp"
#include "simple_action_client_example/mode_selection_client/client_behaviors/cb_mode_select.hpp"
#include "simple_action_client_example/fibonacci_action_client/client_behaviors/cb_fibonacci.hpp"

// ORTHOGONALS
#include "simple_action_client_example/orthogonals/or_mode_select.hpp"
#include "simple_action_client_example/orthogonals/or_fibonacci.hpp"

namespace robot_state_machine
{
// SMACC2 clases

//STATES
struct StState1;
struct StState2;

//--------------------------------------------------------------------
//STATE_MACHINE
struct SimpleSM
: public smacc2::SmaccStateMachineBase<SimpleSM, StState1>
{
  using SmaccStateMachineBase::SmaccStateMachineBase;

  void onInitialize() override
  {
    this->createOrthogonal<OrModeSelect>();
    this->createOrthogonal<OrFibonacci>();
  }
};

}  // namespace simple_action_client_example

//STATES
#include "states/st_state_1.hpp"
#include "states/st_state_2.hpp"
