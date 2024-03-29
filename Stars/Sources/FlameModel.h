#pragma once

#include <math.h>
#include <vector>
#include <random>

#include "BlurModel.h"

namespace Blur
{
    class FlameModel : public BlurModel
    {
    public:
        FlameModel()
        {
            blurDirection = -3;
            blurCoefficient = 6;
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
            
            for (int i = 0; i < rightBound / 6; i++)
            {
                int     offset = rand() % rightBound;
                int     w = rand() % 5 + rightBound / 70;
                int     h = rand() % 10 + lowerBound / 35;
                PutFlameBasement(offset - w / 2, lowerBound - h, w, h);
            }

            SpreadData();

            iterationCount++;
        }

    protected:

        void PutFlameBasement(int x, int y, int w, int h)
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
