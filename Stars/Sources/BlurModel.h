#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace Blur
{
    class BlurModel
    {
    public:
        BlurModel()
        {
        }

        virtual void SetBounds(int rightBound, int lowerBound)
        {
            this->rightBound = rightBound;
            this->lowerBound = lowerBound - blurDirection;

            kernel = LoadKernel();

            int size =  this->rightBound * this->lowerBound;

            buffers[0].resize(size);
            buffers[1].resize(size);
        }

        const std::vector<int>& GetData() const
        {
            return buffers[toBufferNum];
        }

        virtual void Animate() = 0;
    protected:

        struct KernelItem
        {
            int x = 0;
            int y = 0;
        };

        std::vector<KernelItem>     kernel;

        std::vector<KernelItem>    LoadKernel()
        {
             std::vector<KernelItem> temp = {
                { 1,  1},
                { 0,  1},
                {-1,  1},

                {-1,  0},
                { 0,  0},
                { 1,  0},

                { 1, -1},
                { 0, -1},
                {-1, -1},
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

                    count += blurCoefficient;
                    sum = (int)(round(sum / count));

                    int index = (i + blurDirection) * rightBound + j;
                    if (index >= 0 && index < bufferSize)
                        buffers[toBufferNum][index] = sum;
                }
            }
        }

        int blurDirection = 0;
        int blurCoefficient = 1;

        int iterationCount = 0;
        int rightBound = 0;
        int lowerBound = 0;

        int fromBufferNum = 0;
        int toBufferNum = 1;

        std::vector<int> buffers[2];
    };
}
