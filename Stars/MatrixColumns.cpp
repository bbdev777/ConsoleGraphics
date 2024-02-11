#include "ConsoleApp.h"
//#include "StarsModel.h"

int	main()
{
	ConsoleGraphics::ConsoleApp	application;
	double						baseStep = 1.0;
	double						textPos = (double)application.GetDisplay().GetWidth();
	std::string					message = "Press Ctrl + C for exit...";

	return application.Run([&](double k, ConsoleGraphics::Display& display)
	{
		display.SetStringAt(int(textPos), 1, message, F_WHITE);

		textPos -= 0.25;

		if (textPos + message.size() < 0)
			textPos = (double)application.GetDisplay().GetWidth();
	});
}
