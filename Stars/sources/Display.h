#pragma once

#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

namespace ConsoleGraphics
{
    class Display
    {
    public:
        Display()
        {
            size.ws_col = -1;
            size.ws_row = -1;
            size.ws_xpixel = -1;
            size.ws_ypixel = -1;
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

        void    RenderColored()
        {
            gotoxy(0, 0);
            
            for (auto& item : displayBuffer)
            {
                if (item == '.')
                    set_display_atrib(F_GREEN);
                else if (item == '+')
                    set_display_atrib(F_CYAN);
                else
                    set_display_atrib(F_WHITE);

                fprintf(stdout, "%c", item);
            }

            resetcolor();
            fflush(stdout);
        }
        
        void    Resize()
        {
            winsize localSize;

            ioctl(STDOUT_FILENO, TIOCGWINSZ, &localSize); // Получение размеров консоли

            if (memcmp(&localSize, &size, sizeof(winsize)) == 0)
                return;

            size = localSize;
            displayBuffer.clear();
            displayBuffer.resize(size.ws_col * size.ws_row);

            zBuffer.clear();
            zBuffer.resize(displayBuffer.size());

            clrscr();
            hide_cursor();
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

        std::vector<double> zBuffer;
        std::vector<char> displayBuffer;
        
        winsize size;
    };
}