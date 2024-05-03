#ifndef ROBOT__STATE_MACHINE__ORTHOGONALS__OR_FIBONACCI_HPP_
#define ROBOT__STATE_MACHINE__ORTHOGONALS__OR_FIBONACCI_HPP_

#include "smacc2/smacc_orthogonal.hpp"
#include "simple_action_client_example/fibonacci_action_client/cl_fibonacci.hpp"

namespace robot_state_machine
{

class OrFibonacci : public smacc2::Orthogonal<OrFibonacci>
{
public:
  void onInitialize() override
  {
    auto fibonacci_action_client = this->createClient<ClFibonacci>();
  }
};
} // namespace robot_state_machine

#endif // ROBOT__STATE_MACHINE__ORTHOGONALS__OR_FIBONACCI_HPP_