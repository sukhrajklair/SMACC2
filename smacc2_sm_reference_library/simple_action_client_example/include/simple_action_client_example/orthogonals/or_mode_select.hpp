#ifndef ROBOT_STATE_MACHINE__ORTHOGONALS__OR_MODE_SELECT_HPP_
#define ROBOT_STATE_MACHINE__ORTHOGONALS__OR_MODE_SELECT_HPP_

#include <smacc2/smacc_orthogonal.hpp>
#include <simple_action_client_example/mode_selection_client/cl_mode_select.hpp>

namespace robot_state_machine
{
class OrModeSelect : public smacc2::Orthogonal<OrModeSelect>
{
public:
    void onInitialize() override
    {
        auto client = this->createClient<ClModeSelect>();
    }
};
}

#endif  // ROBOT_STATE_MACHINE__ORTHOGONALS__OR_MODE_SELECT_HPP_