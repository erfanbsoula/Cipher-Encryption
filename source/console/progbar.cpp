#include "progbar.hpp"
#include <iostream>

const int ConsoleProgressBar::PERCENTAGE_OF_A_BAR = 
    100 / ConsoleProgressBar::TOTAL_BAR_COUNT;

void ConsoleProgressBar::start()
{
    std::string out = "\rprogress: |";
    for (int space = 0; space < TOTAL_BAR_COUNT; space++)
        out += " ";
    
    out += "| 0%";
    std::cout << out << std::flush;
}

void ConsoleProgressBar::update(int percentage)
{
    std::string out = "\rprogress: |";
    int bar_count = percentage / PERCENTAGE_OF_A_BAR;

    for (int bar = 0; bar < bar_count; bar++)
        out += "|";
    for (int space = 0; space < (TOTAL_BAR_COUNT-bar_count); space++)
        out += " ";

    out += "| " + std::to_string(percentage) + "%";
    std::cout << out << std::flush;
}