#ifndef _PROGRESS_H_
#define _PROGRESS_H_

#include <vector>
#include <stdexcept>

typedef unsigned long long int Psteps;

class ProgressSubscriber
{
public:
    virtual void start() = 0;
    virtual void update(int percentage) = 0; 
};

typedef std::vector<ProgressSubscriber*> Subscribers;

class ProgressHandler
{
public:
    ProgressHandler();
    void subscribe(ProgressSubscriber* subscriber_);
    void initialize_new_process(Psteps total_steps);
    void update();

private:
    Subscribers subscribers;
    Psteps total_step_count;
    Psteps processed_steps;
    Psteps fraction;
};

#endif