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

        int     GetHeight()
        {
            return size.ws_row;
        }

        void    SetCharAt(int x, int y, char c)
        {
            if (IsOutOfScreen(x, y))
                return;
                
            displayBuffer[y * size.ws_col + x] = c;
        }

        void    SetCharAt(int x, int y, double z, char c)
        {
            if (IsOutOfScreen(x, y))
                return;
                
            int index = y * size.ws_col + x;

            if (zBuffer[index] >= z)
                return;

             displayBuffer[index] = c;
             zBuffer[index] = z;   
        }

        void    FillIn(char symbol)
        {
            for (size_t i = 0; i < displayBuffer.size(); i++)
            {
                zBuffer[i] = -99999.0; 
                displayBuffer[i] = symbol;
            }
        }

        void    Render()
        {
            gotoxy(0, 0);
            fwrite(displayBuffer.data(), displayBuffer.size(), 1, stdout);
      
            fflush(stdout);
        }
    protected:
        bool    IsOutOfScreen(int x, int y)
        {
            if (x <= 0)
                return true;

            if (y <= 0)
                return  true;

            if (y >= size.ws_row)
                return  true;

            if (x >= size.ws_col)
                return true;

            return false;
        }

        void    Resize()
        {
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); // Получение размеров консоли
            displayBuffer.clear();
            displayBuffer.resize(size.ws_col * size.ws_row);

            zBuffer.clear();
            zBuffer.resize(displayBuffer.size());
        }

        std::vector<double> zBuffer;
        std::vector<char> displayBuffer;
        
        winsize size;
    };
}