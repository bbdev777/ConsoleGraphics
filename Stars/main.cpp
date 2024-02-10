#include <iostream>
#include <signal.h>
#include <memory.h>
#include <atomic>
#include <chrono>
#include <thread>

#include "Display.h"
#include "StarsModel.h"

std::atomic_bool run = true;

void SetSigTerm();
void PutStarsToDisplay(ConsoleGraphics::Display &display, Stars::StarsModel &starModel);

int AppCycle()
{
   	ConsoleGraphics::Display	display;
	Stars::StarsModel 			starsModel;
	double						baseStep = 1.0, k = 1.0;

	while(run)
    {
		display.Resize();

		std::chrono::time_point<std::chrono::system_clock>  startTime = std::chrono::system_clock::now();
		starsModel.MoveStars(baseStep * k);

		display.FillIn(' ');

		PutStarsToDisplay(display, starsModel);
        
        display.RenderColored();
        usleep(10 * 1000);
		
		std::chrono::time_point<std::chrono::system_clock>  endTime = std::chrono::system_clock::now();
		std::chrono::duration<double> delta = endTime - startTime;

		k = delta.count() / (1.0 / 60.0);
	}

	return 0;
}

int	main()
{
	SetSigTerm();
	return AppCycle();
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
		char starModel = '.';

		if (curStar.z > distancePart * 3.0)
			starModel = '*';
		else if (curStar.z > (distancePart * 4.0))
			starModel = '+';

		display.SetCharAt(curStar.x + halfWidth,
						  curStar.y + halfHeight,
						  curStar.z,
						  starModel);
	}
}

void SetSigTerm()
{
	struct sigaction action;
	memset(&action, 0, sizeof(action));

	action.sa_handler = [](int signum)
	{
		run = false;
	};

	sigaction(SIGTERM, &action, NULL);

	signal(SIGINT, action.sa_handler);
	signal(SIGABRT, action.sa_handler);
}
