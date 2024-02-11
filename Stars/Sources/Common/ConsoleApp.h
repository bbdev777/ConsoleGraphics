#pragma once

#include <memory.h>
#include <signal.h>
#include <functional>
#include <chrono>
#include <atomic>

#include "Display.h"

namespace ConsoleGraphics
{
    size_t SetSigTerm(std::function<void()> handler);
    void RemoveSigTerm(size_t id);

    class ConsoleApp
    {
        size_t terminationId = 0;
        std::atomic_bool run = true;

    public:
        ConsoleApp()
        {
            terminationId = SetSigTerm([this]()
                                       { run = false; });
            display.Resize();
        }

        int Run(std::function<void(double interFrameCoefficient, ConsoleGraphics::Display& display)> onFrame)
        {
            double k = 1.0;

            while (run)
            {
                display.Resize();

		        hide_cursor();
                
                std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
                display.FillIn(' ');

                onFrame(k, display);

                display.RenderColored();
                usleep(10 * 1000);
                std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();
                std::chrono::duration<double> delta = endTime - startTime;

                k = delta.count() / (1.0 / 60.0);
            }
            
            return 0;
        }

        virtual ~ConsoleApp()
        {
            RemoveSigTerm(terminationId);
        }

        const ConsoleGraphics::Display GetDisplay() const
        {
            return display;
        }
    protected:
        ConsoleGraphics::Display display;
    };
}
