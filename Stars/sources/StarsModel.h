
#pragma once

#include <list>

namespace Stars
{
    struct StarDescription
    {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    class StarsModel
    {
    public:
        StarsModel()
        {
        }

        void    MoveStars(double step)
        {
            auto iter = starList.begin();

            while (iter != starList.end())
            {
                auto current = iter;
                iter++;
                
                current->z += step;
                if (current->z >= 0.0)
                    starList.erase(current);
            }
        }
    
        void    GenerateStars()
        {
            starList.push_back({-1.0, 1.0, defaultZ});
            starList.push_back({1.0, 1.0, defaultZ});
            starList.push_back({-1.0, 1.0, defaultZ});
            starList.push_back({-1.0, -1.0, defaultZ});
        }

protected:
        double      defaultZ = -100.0;

        std::list<StarDescription> starList;
    };
}
