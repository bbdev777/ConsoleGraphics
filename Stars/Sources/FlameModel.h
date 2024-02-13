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
                int     w = rand() % 6;
                int     h = rand() % 10;
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

        void SpreadData()
        {
            int bufferSize = buffers[fromBufferNum].size();

            for (int i = 0; i < lowerBound; i++)
            {
                for (int j = 0; j < rightBound; j++)
                {
                    int index0 = i * rightBound + j;
                    int index1 = i * rightBound + j - 1;
                    int index2 = i * rightBound + j + 1;
                    int index3 = (i - 3) * rightBound + j;
                    int index4 = (i - 1) * rightBound + j - 1;
                    int index5 = (i - 1) * rightBound + j + 1;
                                       
                    int index6 = (i - 2) * rightBound + j;
                    double sum = 0.0;
                    double count = 0.0;

                    if (index0 >= 0 && index0 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index0];
                        count ++;
                    }

                    if (index1 >= 0 && index1 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index1];
                        count ++;
                    }

                    if (index2 >= 0 && index2 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index2];
                        count ++;
                    }

                    if (index3 >= 0 && index3 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index3];
                        count ++;
                    }

                    if (index4 >= 0 && index4 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index4];
                        count ++;
                    }

                    if (index5 >= 0 && index5 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index5];
                        count ++;
                    }

                    if (index6 >= 0 && index6 < bufferSize)
                    {
                        sum += buffers[fromBufferNum][index6];
                        count ++;
                    }

                    count += 4;
                    sum = (int)(round(sum / count));

                    if (index3 >= 0 && index3 < bufferSize)
                        buffers[toBufferNum][index3] = sum;
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
