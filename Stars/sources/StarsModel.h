
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

        static StarDescription Randomize(double defaultZ)
        {
            int maxX = 6000;
            int maxY = maxX / 2;
            int maxZ = (int)fabs(defaultZ);
            int signX = rand() % 2 == 1 ? -1 : 1;
            int signY = rand() % 2 == 1 ? 1 : -1;
            StarDescription description {(double)(signX * rand() % maxX), (double)(signY * rand() % maxY), -(double)(rand() % maxZ)};

            //double k = 1.0 / sqrt(description.x * description.x + description.y * description.y);


            return description;
        }
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
                {
                    item = StarDescription::Randomize(defaultZ);
                    item.z = defaultZ;
                }
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
            for (int i = 0; i < 400; i++)
            {               
                starList.push_back(StarDescription::Randomize(defaultZ));
            }
        }

    protected:
        double defaultZ = -120.0;

        std::vector<StarDescription> starList;
    };
}
