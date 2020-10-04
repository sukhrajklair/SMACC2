/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#pragma once

#include <smacc/client_bases/smacc_action_client.h>
#include <smacc/smacc_signal.h>

#include <optional>

namespace smacc
{
namespace client_bases
{
using namespace smacc::default_events;

template <typename ActionType>
class SmaccActionClientBase : public ISmaccActionClient
{
public:
    // Inside this macro you can find the typedefs for Goal and other types
    // ACTION_DEFINITION(ActionType);
    typedef rclcpp_action::Client<ActionType> ActionClient;
    // typedef actionlib::SimpleActionClient<ActionType> GoalHandle;

    // typedef typename ActionClient::SimpleDoneCallback SimpleDoneCallback;
    // typedef typename ActionClient::SimpleActiveCallback SimpleActiveCallback;
    // typedef typename ActionClient::SimpleFeedbackCallback SimpleFeedbackCallback;


    using Goal = typename ActionClient::Goal;
    using Feedback = typename ActionClient::Feedback;
    using GoalHandle = rclcpp_action::ClientGoalHandle<ActionType>;
    typedef typename GoalHandle::WrappedResult WrappedResult;

    using SendGoalOptions = typename GoalHandle::SendGoalOptions;
    using GoalResponseCallback =
        std::function<void (std::shared_future<typename GoalHandle::SharedPtr>)>;
    using FeedbackCallback = typename GoalHandle::FeedbackCallback;
    using ResultCallback = typename GoalHandle::ResultCallback;
    using CancelRequest = typename ActionType::Impl::CancelGoalService::Request;
    using CancelResponse = typename ActionType::Impl::CancelGoalService::Response;
    using CancelCallback = std::function<void (typename CancelResponse::SharedPtr)>;


    SmaccActionClientBase(std::string actionServerName)
        : ISmaccActionClient(),
          name_(actionServerName)
    {
    }

    SmaccActionClientBase()
        : ISmaccActionClient(),
          name_("")
    {
    }

    virtual ~SmaccActionClientBase()
    {
    }

    virtual void initialize() override
    {
        client_ = std::make_shared<ActionClient>(name_);
    }

    static std::string getEventLabel()
    {
        auto type = TypeInfo::getTypeInfoFromType<ActionType>();
        return type->getNonTemplatedTypeName();
    }

    /// rosnamespace path
    std::string name_;

    smacc::SmaccSignal<void(const WrappedResult &)> onSucceeded_;
    smacc::SmaccSignal<void(const WrappedResult &)> onAborted_;
    //smacc::SmaccSignal<void(const WrappedResult &)> onPreempted_;
    //smacc::SmaccSignal<void(const WrappedResult &)> onRejected_;
    smacc::SmaccSignal<void(const WrappedResult &)> onCancelled_;

    // event creation/posting factory functions
    std::function<void(WrappedResult)> postSuccessEvent;
    std::function<void(WrappedResult)> postAbortedEvent;
    //std::function<void(WrappedResult)> postPreemptedEvent;
    //std::function<void(WrappedResult)> postRejectedEvent;
    std::function<void(WrappedResult)> postCancelledEvent;

    std::function<void(const typename Feedback::SharedPtr)> postFeedbackEvent;

    ResultCallback done_cb;
    //SimpleActiveCallback active_cb;
    FeedbackCallback feedback_cb;

    template <typename EvType>
    void postResultEvent(WrappedResult result)
    {
        auto *ev = new EvType();
        //ev->client = this;
        ev->resultMessage = *result;
        RCLCPP_INFO(getNode()->get_logger(),"Posting EVENT %s", demangleSymbol(typeid(ev).name()).c_str());
        this->postEvent(ev);
    }

    template <typename TOrthogonal, typename TSourceObject>
    void onOrthogonalAllocation()
    {
        // we create here all the event factory functions capturing the TOrthogonal
        postSuccessEvent = [=](auto msg) { this->postResultEvent<EvActionSucceeded<TSourceObject, TOrthogonal>>(msg); };
        postAbortedEvent = [=](auto msg) { this->postResultEvent<EvActionAborted<TSourceObject, TOrthogonal>>(msg); };
        //postPreemptedEvent = [=](auto msg) { this->postResultEvent<EvActionPreempted<TSourceObject, TOrthogonal>>(msg); };
        //postRejectedEvent = [=](auto msg) { this->postResultEvent<EvActionRejected<TSourceObject, TOrthogonal>>(msg); };
        postCancelledEvent = [=](auto msg) { this->postResultEvent<EvActionCancelled<TSourceObject, TOrthogonal>>(msg); };
        postFeedbackEvent = [=](auto msg) {
            auto actionFeedbackEvent = new EvActionFeedback<Feedback, TOrthogonal>();
            actionFeedbackEvent->client = this;
            actionFeedbackEvent->feedbackMessage = *msg;
            this->postEvent(actionFeedbackEvent);
            RCLCPP_DEBUG(getNode()->get_logger(),"[%s] FEEDBACK EVENT", demangleType(typeid(*this)).c_str());
        };

        done_cb = boost::bind(&SmaccActionClientBase<ActionType>::onResult, this, _1, _2);
        //active_cb;
        feedback_cb = boost::bind(&SmaccActionClientBase<ActionType>::onFeedback, this, _1);
    }

    template <typename T>
    boost::signals2::connection onSucceeded(void (T::*callback)(WrappedResult &), T *object)
    {
        return this->getStateMachine()->createSignalConnection(onSucceeded_, callback, object);
    }

    template <typename T>
    boost::signals2::connection onSucceeded(std::function<void(WrappedResult &)> callback)
    {
        return this->getStateMachine()->createSignalConnection(onSucceeded_, callback);
    }

    template <typename T>
    boost::signals2::connection onAborted(void (T::*callback)(WrappedResult &), T *object)
    {
        return this->getStateMachine()->createSignalConnection(onAborted_, callback, object);
    }

    template <typename T>
    boost::signals2::connection onAborted(std::function<void(WrappedResult &)> callback)
    {
        return this->getStateMachine()->createSignalConnection(onAborted_, callback);
    }

    template <typename T>
    boost::signals2::connection onCancelled(void (T::*callback)(WrappedResult &), T *object)
    {
        return this->getStateMachine()->createSignalConnection(onCancelled_, callback, object);
    }

    template <typename T>
    boost::signals2::connection onCancelled(std::function<void(WrappedResult &)> callback)
    {
        return this->getStateMachine()->createSignalConnection(onCancelled_, callback);
    }

    /*
    template <typename T>
    boost::signals2::connection onPreempted(void (T::*callback)(WrappedResult &), T *object)
    {
        return this->getStateMachine()->createSignalConnection(onPreempted_, callback, object);
    }

    template <typename T>
    boost::signals2::connection onPreempted(std::function<void(WrappedResult &)> callback)
    {
        return this->getStateMachine()->createSignalConnection(onPreempted_, callback);
    }

    template <typename T>
    boost::signals2::connection onRejected(void (T::*callback)(WrappedResult &), T *object)
    {
        return this->getStateMachine()->createSignalConnection(onRejected_, callback, object);
    }

    template <typename T>
    boost::signals2::connection onRejected(std::function<void(WrappedResult &)> callback)
    {
        return this->getStateMachine()->createSignalConnection(onRejected_, callback);
    }
    */

    virtual void cancelGoal() override
    {
        if (client_->isServerConnected())
        {
            RCLCPP_INFO(getNode()->get_logger(),"Cancelling goal of %s", this->getName().c_str());
            client_->cancelGoal();
        }
        else
        {
            RCLCPP_ERROR(getNode()->get_logger(),"%s [at %s]: not connected with actionserver, skipping cancel goal ...", getName().c_str(), getNamespace().c_str());
        }
    }

/*
    virtual SimpleClientGoalState getState() override
    {
        return client_->getState();
    }*/

    void sendGoal(Goal &goal)
    {
        RCLCPP_INFO_STREAM(getNode()->get_logger(),"Sending goal to actionserver located in " << this->name_ << "\"");

        if (client_->isServerConnected())
        {
            RCLCPP_INFO_STREAM(getNode()->get_logger(),getName() << ": Goal Value: " << std::endl
                                      << goal);
            //client_->sendGoal(goal, done_cb, active_cb, feedback_cb);
            //std::shared_future<typename GoalHandle::SharedPtr>

            SendGoalOptions options;
            //GoalResponseCallback 
            //options.goal_response_callback;

            /// Function called whenever feedback is received for the goal.
            //FeedbackCallback
            options.feedback_callback = feedback_cb;

            /// Function called when the result for the goal is received.
            //ResultCallback result_callback;
            options.result_callback = done_cb;


            auto resfut =  this->client_->async_send_goal(goal, options);
            
  
        }
        else
        {
            RCLCPP_ERROR(getNode()->get_logger(),"%s [at %s]: not connected with actionserver, skipping goal request ...", getName().c_str(), getNamespace().c_str());
            //client_->waitForServer();
        }
    }

protected:
    std::shared_ptr<ActionClient> client_;

    void onFeedback(typename GoalHandle::SharedPtr client, const typename Feedback::SharedPtr &feedback_msg)
    {
        postFeedbackEvent(feedback_msg);
    }
  

    void onResult(const WrappedResult &result_msg)
    {
        // auto *actionResultEvent = new EvActionResult<TDerived>();
        // actionResultEvent->client = this;
        // actionResultEvent->resultMessage = *result_msg;

        
        //const auto &resultType = this->getState();
        const auto& resultType = result_msg.code;

        RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: %s", this->getName().c_str(), resultType.toString().c_str());

        if (resultType == WrappedResult::SUCCEEDED)
        {
            RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: Success", this->getName().c_str());
            onSucceeded_(result_msg);
            postSuccessEvent(result_msg);
        }
        else if (resultType == WrappedResult::ABORTED)
        {
            RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: Aborted", this->getName().c_str());
            onAborted_(result_msg);
            postAbortedEvent(result_msg);
        }
        else if (resultType == WrappedResult::CANCELLED)
        {
            RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: Rejected", this->getName().c_str());
            onCancelled_(result_msg);
            postCancelledEvent(result_msg);
        }
        /*
        else if (resultType == actionlib::SimpleClientGoalState::REJECTED)
        {
            RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: Rejected", this->getName().c_str());
            onRejected_(result_msg);
            postRejectedEvent(result_msg);
        }
        else if (resultType == actionlib::SimpleClientGoalState::PREEMPTED)
        {
            RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: Preempted", this->getName().c_str());
            onPreempted_(result_msg);
            postPreemptedEvent(result_msg);
        }*/
        else
        {
            RCLCPP_INFO(getNode()->get_logger(),"[%s] request result: NOT HANDLED TYPE: %s", this->getName().c_str(), resultType.toString().c_str());
        }
    }
};

#define SMACC_ACTION_CLIENT_DEFINITION(ActionType) ACTION_DEFINITION(ActionType); typedef smacc::client_bases::SmaccActionClientBase<ActionType> Base;
} // namespace client_bases

} // namespace smacc