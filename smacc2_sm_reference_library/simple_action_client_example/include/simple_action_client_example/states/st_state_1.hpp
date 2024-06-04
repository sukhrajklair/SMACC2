#ifndef ROBOT_STATE_MACHINE__STATES__ST_STATE_1_HPP_
#define ROBOT_STATE_MACHINE__STATES__ST_STATE_1_HPP_

#include "smacc2/smacc.hpp"


namespace robot_state_machine
{

//STATE DECLARATION
struct StState1 : smacc2::SmaccState<StState1, SimpleSM>
{
    using SmaccState::SmaccState;

    //Declare custom object tags
    struct AUTONOMOUS_MODE: SUCCESS{};
    struct MANUAL_MODE: SUCCESS{};

    //TRANSITION TABLE
    typedef mpl::list<
        smacc2::Transition<EvAutonomousMode<ClModeSelect, OrModeSelect>, StState2, AUTONOMOUS_MODE>
    > reactions;

    //state functions
    static void staticConfigure()
    {
        configure_orthogonal<OrModeSelect, CbModeSelect>();
    }

    void runtimeConfigure()
    {
        
    }
};
} // namespace robot_state_machine

#endif  // ROBOT_STATE_MACHINE__STATES__ST_STATE_1_HPP_