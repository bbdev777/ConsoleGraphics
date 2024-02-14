#pragma once

#include <math.h>
#include <vector>
#include <random>

#include "FlameModel.h"

namespace Blur
{
    class FireballModel : public BlurModel
    {
    public:
        FireballModel()
        {
            blurDirection = 0;
            blurCoefficient = 5;
        }

        void Animate() final
        {
            //int     offset = (int)round(sin(iterationCount) * 40.0);

            if (iterationCount > 0)
                std::swap(fromBufferNum, toBufferNum);

            for (int i = 0, c = buffers[0].size(); i < c; i++)
            {
               buffers[toBufferNum][i] = 0;
            }
            

            PutFireball((int)round(x), (int)round(y) + (sin(iterationCount) * 2.0), 6, 3);

            SpreadData();

            x += 6.0;

            if (x > rightBound)
                x = 0.0;

            iterationCount++;
        }

    protected:

        double      x = 10.0;
        double      y = 10.0;

        void PutFireball(int x, int y, int w, int h)
        {
            int bufferSize = buffers[fromBufferNum].size();

            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < w; j++)
                {
                    int index = (i + y) * rightBound + j + x;

                    if (index < 0 || index >= bufferSize)
                        continue;

                    buffers[fromBufferNum][index] = 11;
                }
            }
        }
    };
}
