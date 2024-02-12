
#include "ConsoleApp.h"
#include "StarsModel.h"

void PutStarsToDisplay(ConsoleGraphics::Display &display, Stars::StarsModel &starModel);

int	main()
{
	ConsoleGraphics::ConsoleApp	application;
	Stars::StarsModel 			starsModel;
	double						baseStep = 1.0;
	double						textPos = (double)application.GetDisplay().GetWidth();
	std::string					message = "Press Ctrl + C for exit...";

	return application.Run([&](double k, ConsoleGraphics::Display& display)
	{
		starsModel.MoveStars(baseStep * k);

		PutStarsToDisplay(display, starsModel);

		display.SetStringAt(int(textPos), 1, message, F_WHITE);

		textPos -= 0.25;

		if (textPos + message.size() < 0)
			textPos = (double)application.GetDisplay().GetWidth();
	});
}

Stars::StarDescription SetPerspective(const Stars::StarDescription &star)
{
	Stars::StarDescription perspectStar = star;
	double z = perspectStar.z;

	perspectStar.x = perspectStar.x / z;
	perspectStar.y = perspectStar.y / z;

	return perspectStar;
}

void PutStarsToDisplay(ConsoleGraphics::Display &display, Stars::StarsModel &starModel)
{
	const auto &starList = starModel.GetStars();
	double halfWidth = (double)display.GetWidth() / 2.0;
	double halfHeight = (double)display.GetHeight() / 2.0;
	double distancePart = starModel.GetMaxZ() / 5.0;

	for (auto &star : starList)
	{
		Stars::StarDescription curStar = SetPerspective(star);
		char	starShape = '.';
		int		color = F_GREEN;		

		if (curStar.z > distancePart * 3.0)
		{
			starShape = '*';
			color = F_WHITE;
		}
		else if (curStar.z > (distancePart * 4.0))
		{
			starShape = '+';
			color = F_CYAN;
		}

		display.SetCharAt(curStar.x + halfWidth,
						  curStar.y + halfHeight,
						  curStar.z,
						  starShape,
						  color,
						  1);
	}
}
