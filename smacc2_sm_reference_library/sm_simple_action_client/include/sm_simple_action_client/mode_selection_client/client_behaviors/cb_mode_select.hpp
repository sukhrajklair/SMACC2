#ifndef ROBOT_STATE_MACHINE__CLIENTS__CB_MODE_SELECT_HPP_
#define ROBOT_STATE_MACHINE__CLIENTS__CB_MODE_SELECT_HPP_

#include "smacc2/client_behaviors/cb_subscription_callback_base.hpp"
#include "sm_simple_action_client/mode_selection_client/cl_mode_select.hpp"
namespace robot_state_machine
{

using namespace smacc2::client_behaviors;

class CbModeSelect : public CbSubscriptionCallbackBase<example_interfaces::msg::Int32>{
public:
    CbModeSelect(){}
    void onEntry() override
    {
        RCLCPP_INFO(getLogger(), "CbModeSelect::onEntry()");
        this->requiresClient(mode_select_client_);
        mode_select_client_->onFirstMessageReceived(&CbModeSelect::onFirstMessageReceived, this);
        mode_select_client_->onMessageReceived(&CbModeSelect::onMessageReceived, this);
    }
    void onFirstMessageReceived(const example_interfaces::msg::Int32 & msg)  
    {
        RCLCPP_INFO(getLogger(), "CbModeSelect::onFirstMessageReceived()");
    }
    void onMessageReceived(const example_interfaces::msg::Int32 & msg) override
    {
        if(msg.data == 0){
            mode_select_client_->post_manual_mode_event_();
            RCLCPP_INFO(getLogger(), "CbModeSelect::onMessageReceived() - MANUAL");
        }
        else if(msg.data == 1){
            mode_select_client_->post_autonomous_mode_event_();
            RCLCPP_INFO(getLogger(), "CbModeSelect::onMessageReceived() - AUTONOMOUS");
        }
    }
private:
    ClModeSelect * mode_select_client_;
};
}
#endif  // ROBOT_STATE_MACHINE__CLIENTS__CB_MODE_SELECT_HPP_