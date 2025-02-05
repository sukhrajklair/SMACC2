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
#include <smacc2/introspection/introspection.hpp>
#include <smacc2/smacc_event_generator.hpp>

namespace smacc2
{
template <typename EventType>
void SmaccEventGenerator::postEvent(const EventType & ev)
{
  ownerState_->postEvent(ev);
}

template <typename EventType>
void SmaccEventGenerator::postEvent()
{
  ownerState_->postEvent<EventType>();
}

template <typename TState, typename TSource>
void SmaccEventGenerator::onStateAllocation()
{
}
}  // namespace smacc2
