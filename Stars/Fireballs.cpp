
#include "ConsoleApp.h"
#include "FireballModel.h"


 void PutModelToDisplay(ConsoleGraphics::Display &display, const Blur::FireballModel &model)
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
    Blur::FireballModel   fireballModel;

    fireballModel.SetBounds(application.GetDisplay().GetWidth(), application.GetDisplay().GetHeight());

    application.GetDisplay().SetOnScreenSizeChanged([&](int width, int height)
    {
         fireballModel.SetBounds(width, height); 
    });

    return application.Run([&](double k, ConsoleGraphics::Display &display)
    {
        fireballModel.Animate();

       PutModelToDisplay(display, fireballModel);
    },    
    20,
    false);
}

