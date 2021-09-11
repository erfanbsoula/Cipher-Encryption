// simple progress-bar for console application

#ifndef _PROGBAR_H_
#define _PROGBAR_H_

#include "../progress.hpp"

class ConsoleProgressBar : public ProgressSubscriber
{
private:
    static const int TOTAL_BAR_COUNT = 20;
    static const int PERCENTAGE_OF_A_BAR;

public:
    void start();
    void update(int percentage);
};

#endif