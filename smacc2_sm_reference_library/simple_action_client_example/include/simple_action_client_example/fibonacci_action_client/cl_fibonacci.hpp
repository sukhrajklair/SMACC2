#ifndef ROBOT_STATE_MACHINE__CLIENTS__CL_FIBONACCI_HPP_
#define ROBOT_STATE_MACHINE__CLIENTS__CL_FIBONACCI_HPP_

#include "smacc2/client_bases/smacc_action_client_base.hpp"
#include "smacc2/smacc.hpp"
#include "action_tutorials_interfaces/action/fibonacci.hpp"


namespace robot_state_machine
{
class ClFibonacci : public smacc2::client_bases::SmaccActionClientBase<action_tutorials_interfaces::action::Fibonacci>
{
public:
    using smacc2::client_bases::SmaccActionClientBase<action_tutorials_interfaces::action::Fibonacci>::GoalHandle;
    using smacc2::client_bases::SmaccActionClientBase<action_tutorials_interfaces::action::Fibonacci>::ResultCallback;

    typedef smacc2::SmaccSignal<void(const WrappedResult &)> FibonacciResultSignal;

    ClFibonacci(std::string action_name = "/fibonacci")
    : smacc2::client_bases::SmaccActionClientBase<action_tutorials_interfaces::action::Fibonacci>(action_name)
    {
    }

    virtual ~ClFibonacci(){}


};
} // namespace robot_state_machine

#endif // ROBOT_STATE_MACHINE__CLIENTS__CL_FIBONACCI_HPP_