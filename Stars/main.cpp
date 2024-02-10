#include <iostream>
#include <signal.h>
#include <memory.h>
#include <atomic>
#include <chrono>

#include "Display.h"
#include "Timer.h"
#include "StarsModel.h"

void Display();

std::atomic_bool	run = true;

void	SetSigTerm();
void	PutStarsToDisplay(ConsoleGraphics::Display& display, Stars::StarsModel& starModel);

int main ()
{
    ConsoleGraphics::Display	display;
	Stars::StarsModel 			starsModel;

	while(run)
    { 
		display.Resize();

		starsModel.MoveStars(2.0);

		display.FillIn(' ');

		PutStarsToDisplay(display, starsModel);
        
        display.RenderColored();
        usleep(16 * 1000);
	}
 
    return 0;
}

Stars::StarDescription	SetPerspective(const Stars::StarDescription& star)
{
	Stars::StarDescription	perspectStar = star;
	double	k = 1.0;
	double	z = perspectStar.z;

	if (z == 0.0)
		z = 1.0;

	perspectStar.x = (perspectStar.x * k) / (z + k);
	perspectStar.y = (perspectStar.y * k) / (z + k);

	return 	perspectStar;
}

void	PutStarsToDisplay(ConsoleGraphics::Display& display, Stars::StarsModel& starModel)
{
		const auto& starList = starModel.GetStars();
		double	halfWidth = (double)display.GetWidth() / 2.0;
		double	halfHeight = (double)display.GetHeight() / 2.0;
		double	distancePart = starModel.GetMaxZ() / 5.0;

		for (auto& star : starList)
		{
			Stars::StarDescription	curStar = SetPerspective(star);
			char 	starModel = '.';

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
