
#pragma once

#include <math.h>
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
            GenerateStars();
        }

        void MoveStars(double step)
        {
            for (auto &item : starList)
            {
                item.z += step;

                if(item.z >= 0.0)
                    item.z = defaultZ;
            }
        }

        const std::vector<StarDescription> &GetStars() const
        {
            return starList;
        }

        double  GetMaxZ() const
        {
            return defaultZ;
        }

        void GenerateStars()
        {
            int     maxX = 6000;
            int     maxY = maxX / 2;
            int     maxZ = (int)fabs(defaultZ);

            for (int i = 0; i < 100; i++)
            {
                starList.push_back({-(double)(rand() % maxX), (double)(rand() % maxY), -(double)(rand() % maxZ)});
                starList.push_back({(double)(rand() % maxX), (double)(rand() % maxY), -(double)(rand() % maxZ)});
                starList.push_back({(double)(rand() % maxX), -(double)(rand() % maxY), -(double)(rand() % maxZ)});
                starList.push_back({-(double)(rand() % maxX), -(double)(rand() % maxY), -(double)(rand() % maxZ)});
            }
        }

    protected:
        double defaultZ = -100.0;

        std::vector<StarDescription> starList;
    };
}
