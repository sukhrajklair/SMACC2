#include <ros_timer_client/cl_ros_timer.h>

namespace cl_ros_timer
{

ClRosTimer::ClRosTimer(std::chrono::seconds duration, bool oneshot)
    : duration_(duration),
    oneshot_ (oneshot)
{
}

ClRosTimer::~ClRosTimer()
{
    timer_->cancel();
}

void ClRosTimer::initialize()
{
    timer_ = this->getNode()->create_wall_timer(duration_, std::bind(&ClRosTimer::timerCallback, this));
}

void ClRosTimer::timerCallback()
{
    if (!onTimerTick_.empty())
    {
        this->onTimerTick_();
    }
    postTimerEvent_();

    if(oneshot_)
    {
        this->timer_->cancel();
    }
}

} // namespace cl_ros_timer
