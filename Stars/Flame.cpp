
#include "ConsoleApp.h"
#include "FlameModel.h"


int     palette[] = {F_BLACK, F_ORANGE, F_RED, F_RED, F_RED, F_YELLOW, F_YELLOW, F_YELLOW, F_WHITE, F_WHITE, F_WHITE, F_WHITE};

struct KernelOffsets
{
    int     x = 0;
    int     y = 0;
};

std::vector<KernelOffsets>  kernel
{
    {
        {-1, 1},
        { 0, 1},
        { 1, 1},
        {-1, 0},
        //{ 0, 0},
        { 1, 0},
        {-1,-1},
        { 0,-1},
        { 1,-1},
    }
};

int     GetColor(int offset, ConsoleGraphics::Display &display, const std::vector<int>& data, bool markupBorders);
void    PutFlameToDisplay(ConsoleGraphics::Display &display, const Blur::FlameModel &model);

int main()
{
    ConsoleGraphics::ConsoleApp application;
    Blur::FlameModel   flameModel;

    flameModel.SetBounds(application.GetDisplay().GetWidth(), application.GetDisplay().GetHeight());

    application.GetDisplay().SetOnScreenSizeChanged([&](int width, int height)
    {
         flameModel.SetBounds(width, height); 
    });

    return application.Run([&](double k, ConsoleGraphics::Display &display)
    {
        flameModel.Animate();

        PutFlameToDisplay(display, flameModel);
    },    
    30,
    false);
}

int     GetColor(int offset, ConsoleGraphics::Display &display, const std::vector<int>& data, bool markupBorders)
{
    if (!markupBorders)   
        return palette[data[offset]];

    int     width = display.GetWidth();
    int     height = display.GetHeight();
    int     dispSize = width * height;
    int     flags = 0;
    
    for (auto& kernelItem: kernel)
    {
        int     index = kernelItem.y * width + kernelItem.x + offset;

        if (index < 0 || index >= dispSize)
            continue;

        if (data[index] > 0)
            flags |= 2;
        else if (data[index] == 0)
            flags |= 1;
    }

    return flags == 3 ? F_BLUE : palette[data[offset]];
}

void PutFlameToDisplay(ConsoleGraphics::Display &display, const Blur::FlameModel &model)
{
    const std::vector<int>&   data = model.GetData();
        
    for (size_t i = 0, c = data.size(); i < c; i++)
    {
        display.SetCharAt(i, ' ', GetColor(i, display, data, true), 3);
    }
}
