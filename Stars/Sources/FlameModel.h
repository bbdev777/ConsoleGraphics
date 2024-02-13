#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace Flame
{
    struct FlameDescription
    {
        char first = '*';
        char second = '#';
        char terminal = ' ';

        double x = 0.0;
        double y = -1.0;
        double oldY = 0.0;
        double speed = 0.25;
        int length = 5;

        bool isBlack = false;
    };

    class FlaneModel
    {
    public:
        FlaneModel()
        {
        }

        void SetBounds(int rightBound, int lowerBound)
        {
            this->rightBound = rightBound;
            this->lowerBound = lowerBound;

            kernel = LoadKernel();

            int size = rightBound * lowerBound;

            buffers[0].resize(size);
            buffers[1].resize(size);
        }

        const std::vector<int> GetData() const
        {
            return buffers[toBufferNum];
        }

        void Animate()
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

        struct KernelItem
        {
            int x = 0;
            int y = 0;
        };

        std::vector<KernelItem>     kernel;

        std::vector<KernelItem>    LoadKernel()
        {
            std::vector<KernelItem> temp = {
                { 0,  0},
                {-1,  0},
                { 1,  0},

                { 1, -1},
                {-1, -1},

                //{ 0, -4},
                { 0, -3},
                { 0, -2}
            };

            return temp;
        }

        void    SpreadData()
        {
            int bufferSize = buffers[fromBufferNum].size();

            for (int i = 0; i < lowerBound; i++)
            {
                for (int j = 0; j < rightBound; j++)
                {
                    double sum = 0.0;
                    double count = 0.0;

                    for (int k = 0, c = kernel.size(); k < c; k++)
                    {
                        int index = (i + kernel[k].y) * rightBound + (j + kernel[k].x);
                        
                        if (index >= 0 && index < bufferSize)
                        {
                            sum += buffers[fromBufferNum][index];
                            count ++;
                        }
                    }                 

                    count += 5;
                    sum = (int)(round(sum / count));

                    int index = (i - 3) * rightBound + j;
                    if (index >= 0 && index < bufferSize)
                        buffers[toBufferNum][index] = sum;
                }
            }
        }

        int iterationCount = 0;
        int rightBound = 0;
        int lowerBound = 0;

        int fromBufferNum = 0;
        int toBufferNum = 1;

        std::vector<int> buffers[2];
    };
}
