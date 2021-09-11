#include "progress.hpp"

ProgressHandler::ProgressHandler()
{
    total_step_count = 0;
    processed_steps = 0;
    fraction = 0;
}

void ProgressHandler::subscribe(ProgressSubscriber* subscriber_)
{
    if (subscriber_ == nullptr)
        throw std::runtime_error("ERROR: trying to subscribe a null pointer");

    subscribers.push_back(subscriber_);
}

void ProgressHandler::initialize_new_process(Psteps total_steps)
{
    total_step_count = total_steps;
    processed_steps = 0;
    fraction = total_steps / 100;

    for (int i = 0; i < subscribers.size(); i++)
        subscribers[i]->start();
}

void ProgressHandler::update()
{
    if (processed_steps >= total_step_count)
        return;

    processed_steps += 1;
    if (fraction == 0)
    {
        if (processed_steps == total_step_count)
            for (int i = 0; i < subscribers.size(); i++)
                subscribers[i]->update(100);
    }
    else
    {
        if (processed_steps % fraction == 0)
            for (int i = 0; i < subscribers.size(); i++)
                subscribers[i]->update(processed_steps/fraction);
    }
}