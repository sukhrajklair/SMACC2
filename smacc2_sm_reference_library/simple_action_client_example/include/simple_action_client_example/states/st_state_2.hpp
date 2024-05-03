#ifndef ROBOT_STATE_MACHINE__STATES__ST_STATE_2_HPP_
#define ROBOT_STATE_MACHINE__STATES__ST_STATE_2_HPP_

#include "smacc2/smacc.hpp"

namespace robot_state_machine
{
//STATE DECLARATION
struct StState2 : smacc2::SmaccState<StState2, SimpleSM>
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