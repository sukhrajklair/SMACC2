#ifndef ROBOT_STATE_MACHINE__CLIENTS__CB_FIBONACCI_HPP_
#define ROBOT_STATE_MACHINE__CLIENTS__CB_FIBONACCI_HPP_

#include <smacc2/smacc_asynchronous_client_behavior.hpp>
#include "simple_action_client_example/fibonacci_action_client/cl_fibonacci.hpp"

namespace robot_state_machine
{
class CbFibonacci : public smacc2::SmaccAsyncClientBehavior
{
public:
    CbFibonacci()
    {

    }
    // virtual ~CbFibonacci();
    
    template <typename TOrthogonal, typename TSourceObject>
    void onOrthogonalAllocation()
    {
        this->requiresClient(cl_fibonacci_);
        smacc2::SmaccAsyncClientBehavior::onOrthogonalAllocation<TOrthogonal, TSourceObject>();
    }

    void onEntry() override
    {
        ClFibonacci::Goal goal;
        goal.order = 100;

        fibonacciCallback_ = std::make_shared<ClFibonacci::FibonacciResultSignal>();
        this->getStateMachine()->createSignalConnection(*fibonacciCallback_, &CbFibonacci::onFibonacciResult, this);
        goalHandleFuture_ = cl_fibonacci_->sendGoal(goal, fibonacciCallback_);
        
    }
    void onExit() override
    {
        cl_fibonacci_->cancelGoal();
    }

private:

    void onFibonacciResult(const ClFibonacci::WrappedResult & result)
    {
        if (result.code == rclcpp_action::ResultCode::SUCCEEDED)
            onFibonacciActionSuccess();
        else 
            onFibonacciActionAbort();
    }
    void onFibonacciActionSuccess()
    {
        this->postSuccessEvent();
    }
    void onFibonacciActionAbort()
    {
        this->postFailureEvent();
    }

    ClFibonacci * cl_fibonacci_;
    ClFibonacci::FibonacciResultSignal::SharedPtr fibonacciCallback_;
    rclcpp_action::ResultCode fibonacciResult_;
    std::shared_future<
    std::shared_ptr<rclcpp_action::ClientGoalHandle<action_tutorials_interfaces::action::Fibonacci> > >
    goalHandleFuture_;
    
};
} // namespace robot_state_machine

#endif // ROBOT_STATE_MACHINE__CLIENTS__CB_FIBONACCI_HPP_