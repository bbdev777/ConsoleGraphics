#pragma once

#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

#define home() printf(ESC "[H")    // Move cursor to the indicated row, column (origin at 1,1)
#define clrscr() printf(ESC "[2J") // clear the screen, move to (1,1)
#define gotoxy(x, y) printf(ESC "[%d;%dH", y, x);
#define hide_cursor() printf(ESC "[?25l");
#define show_cursor() printf(ESC "[?25h");
// Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color) printf(ESC "[%dm", color)

namespace ConsoleGraphics
{
    class Display
    {
    public:
        Display()
        {
            Resize();
            clrscr();
            hide_cursor();
        }

        ~Display()
        {
            show_cursor();
        }

        int     GetWidth()
        {
            return size.ws_col;
        }

        int     GetHeigth()
        {
            return size.ws_row;
        }

        void    SetCharAt(int x, int y, char c)
        {
            if (x < 0)
                return;

            if (y < 0)
                return;

            if (y >= (int)displayBuffer.size())
                return;

            if (x >= (int)displayBuffer[y].size())
                return;
                
            displayBuffer[y][x] = c;
        }

        void    FillIn(char symbol)
        {
            for (size_t r = 0; r < displayBuffer.size(); r++)
            {
                for (size_t c = 0; c < displayBuffer[r].size(); c++)
                {
                    displayBuffer[r][c] = symbol;
                }
            }
        }

        void    Render()
        {
            gotoxy(0, (int)displayBuffer.size());
            for (size_t r = 0; r < displayBuffer.size(); r++)
            {
                gotoxy(0, (int)r);
                fwrite(displayBuffer[r].data(), displayBuffer[r].size(), 1, stdout);
            }
            gotoxy(1, (int)displayBuffer.size());

            fflush(stdout);
        }
    protected:
        void Resize()
        {
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); // Получение размеров консоли
            displayBuffer.clear();

            for (int i = 0; i < size.ws_row; i++)
            {
                std::vector<char> row;
                row.resize(size.ws_col);
                displayBuffer.emplace_back(row);
            }
        }

        std::vector<std::vector<char>> displayBuffer;
        
        winsize size;
    };
}