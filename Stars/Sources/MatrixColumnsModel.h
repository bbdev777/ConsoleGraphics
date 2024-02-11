#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace MatrixColumns
{
    struct ColumnDescription
    {
        char firs = '*';
        char second = '#';
        char terminal = ' ';

        double x = 0.0;
        double y = -1.0;
        int length = 5;
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
                column.second = column.firs;
                column.firs = symbols[rand() % symbols.length() - 1];
                column.y += 0.25;

                if (column.y - column.length > lowerBound)
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
        MatrixColumns::ColumnDescription   GenerateColumn()
        {
            MatrixColumns::ColumnDescription   column;
            column.x = rand() % rightBound;
            column.y = - rand() % (lowerBound / 4);
            column.length = rand() % (lowerBound / 3) + 3;
            column.terminal = ' ';

            return column;
        }

        void    GenerateColumns()
        {
            columns.clear();
            
            int     maxColumn = rightBound / 2; 
            
            for (int i = 0; i < maxColumn; i++)
            {
                columns.emplace_back(GenerateColumn());
            }
        }

        int             rightBound = 0; 
        int             lowerBound = 0;
        std::string    symbols = "1234567890qwertyuiopasdfghjklzxcvbnm";
        std::vector<ColumnDescription> columns;
    };
}
