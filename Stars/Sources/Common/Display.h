#pragma once

#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <string>
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

        int     GetWidth() const
        {
            return size.ws_col;
        }

        int     GetHeight() const
        {
            return size.ws_row;
        }

        void    SetCharAt(int x, int y, char symbol, int color)
        {
            if (IsOutOfScreen(x, y))
                return;
                
            int index = y * size.ws_col + x;    
            displayBuffer[index] = symbol;
            shadowBuffer[index].color = color;
        }

        void    SetCharAt(int x, int y, double z, char symbol, int color)
        {
            if (IsOutOfScreen(x, y))
                return;
                
            int index = y * size.ws_col + x;

            if (shadowBuffer[index].z >= z)
                return;

             displayBuffer[index] = symbol;
             shadowBuffer[index].z = z;
             shadowBuffer[index].color = color;
        }

        void    SetStringAt(int x, int y, const std::string& text, int color)
        {
            set_display_atrib(color);

            for (int i = 0, c = text.length(); i < c; i++)
            {
                SetCharAt(x + i, y, text[i], color);
            }

            resetcolor();
        }

        void    FillIn(char symbol)
        {
            for (size_t i = 0, c = displayBuffer.size(); i < c; i++)
            {
                shadowBuffer[i].z = -99999.0; 
                shadowBuffer[i].color = 0;
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
            gotoxy(1, 1);

            for (int i = 0; i < size.ws_row - 1; i++)
            {
                gotoxy(1, i + 1);
                for (int j = 0; j < size.ws_col - 1; j++)
                {
                    int index = i * size.ws_col + j;
                    set_display_atrib(shadowBuffer[index].color);
                    fprintf(stdout, "%c", displayBuffer[index]);
                }
            }    
            /*
            for (size_t i = 0, c = displayBuffer.size(); i < c; i++)
            {
                set_display_atrib(shadowBuffer[i].color);
                fprintf(stdout, "%c", displayBuffer[i]);
            }
        */
            fflush(stdout);
            resetcolor();
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

            shadowBuffer.clear();
            shadowBuffer.resize(displayBuffer.size());

            clrscr();
            hide_cursor();
        }

    protected:
        bool    IsOutOfScreen(int x, int y)
        {
            if (x < 1)
                return true;

            if (y < 1)
                return  true;

            if (y >= size.ws_row - 1)
                return  true;

            if (x >= size.ws_col - 1)
                return true;

            return false;
        }

        struct ShadowBufferItem
        {
            double  z = -99999.0;
            int     color = 0;
        };

        std::vector<ShadowBufferItem> shadowBuffer;
        std::vector<char> displayBuffer;
        
        winsize size;
    };
}