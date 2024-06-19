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

#ifndef ROBOT_STATE_MACHINE__STATES__ST_STATE_2_HPP_
#define ROBOT_STATE_MACHINE__STATES__ST_STATE_2_HPP_

#include "smacc2/smacc.hpp"

namespace robot_state_machine
{
//STATE DECLARATION
struct StState2 : smacc2::SmaccState<StState2, SmSimpleActionClient>
{
    using SmaccState::SmaccState;

    //Declare custom object tags
    struct MANUAL_MODE: SUCCESS{};
    struct START_PATROL: SUCCESS{};
    struct STOP_PATROL: ABORT{};

    //TRANSITION TABLE
    typedef mpl::list<
    smacc2::Transition<EvManualMode<ClModeSelect, OrModeSelect>, StState1, MANUAL_MODE>,
    smacc2::Transition<smacc2::EvCbSuccess<CbFibonacci, OrFibonacci>, StState2>,
    smacc2::Transition<smacc2::EvCbFailure<CbFibonacci, OrFibonacci>, StState2>
    > reactions;

    //state functions
    static void staticConfigure()
    {
        configure_orthogonal<OrModeSelect, CbModeSelect>();
        configure_orthogonal<OrFibonacci, CbFibonacci>();
    }

    void runtimeConfigure()
    {

    }

    void onEntry()
    {   
    }
};

} // namespace robot_state_machine

#endif  // ROBOT_STATE_MACHINE__STATES__ST_STATE_2_HPP_
