
#include "ConsoleApp.h"
#include "FlameModel.h"


void PutFlameToDisplay(ConsoleGraphics::Display &display, const Flame::FlaneModel &model)
{
    auto&   data = model.GetData();
    int     palette[] = {F_BLACK, F_ORANGE, F_RED, F_RED, F_RED, F_YELLOW, F_YELLOW, F_YELLOW, F_WHITE, F_WHITE, F_WHITE, F_WHITE};
    //int     offset = display.GetWidth() * 3;

    for (size_t i = 0, c = data.size(); i < c; i++)
    {
        display.SetCharAt(i, ' ', palette[data[i]], 0);
    }
}

int main()
{
    ConsoleGraphics::ConsoleApp application;
    Flame::FlaneModel   flameModel;

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
    20,
    false);
}

