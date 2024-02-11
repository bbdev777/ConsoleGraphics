
#include <map>
#include <mutex>
#include "ConsoleApp.h"


namespace ConsoleGraphics
{
    std::map<int, std::function<void()>> terminationHandlers;
    std::mutex terminationHandlerMutex;

    size_t  handlerId = 0;

    size_t SetSigTerm(std::function<void()> handler)
    {
        std::lock_guard locler(terminationHandlerMutex);

        handlerId++;

        if (terminationHandlers.size() == 0)
        {
            struct sigaction action;
            memset(&action, 0, sizeof(action));

            action.sa_handler = [](int signum)
            {
                for (auto handler : terminationHandlers)
                {
                    if (handler.second)
                        handler.second();
                }
            };

            sigaction(SIGTERM, &action, NULL);

            signal(SIGINT, action.sa_handler);
            signal(SIGABRT, action.sa_handler);
        }

        terminationHandlers[handlerId] = handler;

        return handlerId;
    }

    void RemoveSigTerm(size_t id)
    {
        terminationHandlers.erase(id);
    }
}
