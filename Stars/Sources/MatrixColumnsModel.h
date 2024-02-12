#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace MatrixColumns
{
    struct ColumnDescription
    {
        char    first = '*';
        char    second = '#';
        char    terminal = ' ';

        double  x = 0.0;
        double  y = -1.0;
        double  oldY = 0.0;
        double  speed = 0.25;
        int     length = 5;

        bool    isBlack = false;
    };

    class MatrixColumnsModel
    {
    public:
        MatrixColumnsModel()
        {
        }

        void    SetBounds(int rightBound, int lowerBound)
        {
            this->rightBound = rightBound;
            this->lowerBound = lowerBound;

            GenerateColumns();
        }
        void    Animate()
        {
            for (auto& column : columns)
            {
                column.first = column.isBlack ? ' ' : symbols[rand() % symbols.length() - 1];
                column.y += column.speed;

                if (column.y - column.oldY >= 1.0)
                {
                    column.oldY = column.y;
                    column.second = column.first;
                    column.terminal = column.first;//symbols[rand() % symbols.length() - 1];
                }

                if ((column.y  - column.length) > lowerBound)
                {
                    column = GenerateColumn();
                }
            }
        }

        const std::vector<ColumnDescription>&   GetColumns() const
        {
            return columns;
        }

    protected:
        int     entryNumber = 0;
        MatrixColumns::ColumnDescription   GenerateColumn()
        {
            MatrixColumns::ColumnDescription   column;
            column.x = rand() % rightBound;
            column.y = -(rand() % lowerBound);
            column.length = rand() % (lowerBound / 2) + 7;
            column.terminal = symbols[rand() % symbols.length() - 1];
            column.speed = std::max(0.05, double(rand() % 250) / 1000.0);
            //column.isBlack = entryNumber % 3 == 0;

            entryNumber++;

            return column;
        }

        void    GenerateColumns()
        {
            columns.clear();
            
            int     maxColumn = rightBound;// / 2; 
            
            for (int i = 0; i < maxColumn; i++)
            {
                columns.emplace_back(GenerateColumn());
            }
        }

        int             rightBound = 0; 
        int             lowerBound = 0;
        std::string     symbols = "!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKLqwertyuiopasdfghjklzxcvbnm:|ZXCVBNM<>1234567890";
        std::vector<ColumnDescription> columns;
    };
}
