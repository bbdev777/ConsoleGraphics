
#include "ConsoleApp.h"
#include "FlameModel.h"


void PutFlameToDisplay(ConsoleGraphics::Display &display, const Blur::FlameModel &model)
{
    auto&   data = model.GetData();
    int     palette[] = {F_BLACK, F_ORANGE, F_RED, F_RED, F_RED, F_YELLOW, F_YELLOW, F_YELLOW, F_WHITE, F_WHITE, F_WHITE, F_WHITE};

    for (size_t i = 0, c = data.size(); i < c; i++)
    {
        display.SetCharAt(i, ' ', palette[data[i]], 3);
    }
}

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
    20,
    false);
}
