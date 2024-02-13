#pragma once

#include <memory.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#define F_WHITE     1
#define F_CYAN      2
#define F_GREEN     3
#define F_BLACK     4
#define F_RED       5
#define F_BLUE      6
#define F_YELLOW    7
#define F_ORANGE    8

namespace ConsoleGraphics
{
    struct  ScreenSize
    {
        int     ws_col;
        int     ws_row;
    };

    class Display
    {            
    public:
        Display()
        {
            size.ws_col = -1;
            size.ws_row = -1;

            initscr();            
	        start_color();

            init_color(COLOR_RED, 1000, 0, 0);
            init_color(COLOR_GREEN, 0, 1000, 0);
            init_color(COLOR_BLUE, 0, 0, 1000);
            init_color(COLOR_YELLOW, 1000, 1000, 0);
            init_color(COLOR_CYAN, 0, 1000, 1000);
            init_color(COLOR_MAGENTA, 1000, 500, 0);

            init_pair(F_WHITE, COLOR_WHITE, COLOR_BLACK);
	        init_pair(F_CYAN, COLOR_CYAN, COLOR_BLACK);
	        init_pair(F_GREEN, COLOR_GREEN, COLOR_BLACK);
            init_pair(F_BLACK, COLOR_BLACK, COLOR_BLACK);
            init_pair(F_RED, COLOR_RED, COLOR_BLACK);
            init_pair(F_BLUE, COLOR_BLUE, COLOR_BLACK);
            init_pair(F_YELLOW, COLOR_YELLOW, COLOR_BLACK);
            init_pair(F_ORANGE, COLOR_MAGENTA, COLOR_BLACK);

	        curs_set(0);

            Resize();
        }

        ~Display()
        {
            curs_set(1);
            endwin();
        }

        int     GetWidth() const
        {
            return size.ws_col;
        }

        int     GetHeight() const
        {
            return size.ws_row;
        }

        void    SetCharAt(size_t index, char symbol, int color, int intensity)
        {
            if (index >= displayBuffer.size())
                return;

            displayBuffer[index] = symbol;
            shadowBuffer[index].color = color;
            shadowBuffer[index].intensity = intensity;
        }

        void    SetCharAt(int x, int y, char symbol, int color, int intensity)
        {
            if (IsOutOfScreen(x, y))
                return;
                
            int index = y * size.ws_col + x;    
            displayBuffer[index] = symbol;
            shadowBuffer[index].color = color;
            shadowBuffer[index].intensity = intensity;
        }

        void    SetCharAt(int x, int y, double z, char symbol, int color, int intensity)
        {
            if (IsOutOfScreen(x, y))
                return;
                
            int index = y * size.ws_col + x;

            if (shadowBuffer[index].z >= z)
                return;

             displayBuffer[index] = symbol;
             shadowBuffer[index].z = z;
             shadowBuffer[index].color = color;
             shadowBuffer[index].intensity = intensity;
        }

        void    SetStringAt(int x, int y, const std::string& text, int color)
        {
            for (int i = 0, c = text.length(); i < c; i++)
            {
                SetCharAt(x + i, y, text[i], color, 1);
            }
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
            for (int i = 0; i < size.ws_row; i++)
            {
                for (int j = 0; j < size.ws_col; j++)
                {
                    int index = i * size.ws_col + j;
                    int intensity = A_NORMAL;

                    if (shadowBuffer[index].intensity == 1)
                        intensity = A_BOLD;
                    else if (shadowBuffer[index].intensity == 2)
                        intensity = A_DIM;
                        
                    attron(COLOR_PAIR(shadowBuffer[index].color));
                    mvaddch(i, j, displayBuffer[index] | intensity | A_STANDOUT);
                }
            }

            refresh(); 
        }
        
        void    Resize()
        {
            ScreenSize localSize;

            getmaxyx(stdscr, localSize.ws_row, localSize.ws_col);

            if (memcmp(&localSize, &size, sizeof(ScreenSize)) == 0)
                return;

            size = localSize;
            displayBuffer.clear();
            displayBuffer.resize(size.ws_col * size.ws_row);

            shadowBuffer.clear();
            shadowBuffer.resize(displayBuffer.size());

            FillIn(' ');

            if (onScreenSizeChanged)
                onScreenSizeChanged(size.ws_col, size.ws_row);
        }

        void    SetOnScreenSizeChanged(std::function<void(int width, int height)> callback) const
        {
            onScreenSizeChanged = callback;
        }

    protected:
        bool    IsOutOfScreen(int x, int y)
        {
            if (x < 0)
                return true;

            if (y < 0)
                return  true;

            if (y >= size.ws_row)
                return  true;

            if (x >= size.ws_col)
                return true;

            return false;
        }

        struct ShadowBufferItem
        {
            double  z = -99999.0;
            int     color = 0;
            int     intensity = 1;
        };

        std::vector<ShadowBufferItem> shadowBuffer;
        std::vector<char> displayBuffer;
        mutable std::function<void(int, int)>    onScreenSizeChanged;  

        ScreenSize  size;
    };
}