
#pragma once

#include <functional>
#include <chrono>
#include <ctime>

namespace Common
{
    class Timer
    {
        std::function<void()>   onTimer;
        double                  interval = 100.0;
        std::chrono::time_point<std::chrono::system_clock>  startTime = std::chrono::system_clock::now();

        public:
            Timer()
            {
            }

            Timer(double intervalMiliseconds, std::function<void()> onTimerCallback)
            {
                interval = intervalMiliseconds;
                onTimer = onTimerCallback;
            }

            void    Tick()
            {
                std::chrono::time_point<std::chrono::system_clock>  curTime = std::chrono::system_clock::now();
                std::chrono::duration<double> delta = curTime - startTime;

                if (delta.count() >= interval)
                {
                    startTime = curTime;

                    if (onTimer)
                        onTimer();
                }
            }
    };
}
