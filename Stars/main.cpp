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

void	ProcessTimers(std::vector<Common::Timer>& timers)
{
	for (auto& item : timers)
	{
		item.Tick();
	}
}

int main ()
{
    ConsoleGraphics::Display	display;
	Stars::StarsModel 			starsModel;
	std::vector<Common::Timer>	timers;
    
	timers.push_back(Common::Timer(100.0, [&]()
	{
		starsModel.GenerateStars();
	}));

	while(run)
    { 
		ProcessTimers(timers);

        display.FillIn(' ');
        
        display.Render();
        usleep(16 * 1000);
	}
 
    return 0;
}

void Display()
{
    home();
	//clrscr();
	printf("Home + clrscr\n");
	gotoxy(20,7);
	printf("gotoxy(20,7)");
	
	gotoxy(1,10);
	printf("gotoxy(1,10)  \n\n");
	
	set_display_atrib(BRIGHT);
	printf("Formatting text:\n");
	resetcolor();
	
	set_display_atrib(BRIGHT);
	printf("Bold\n");
	resetcolor();
	
	set_display_atrib(DIM);
	printf("Dim\n");
	resetcolor();

	set_display_atrib(BLINK);
	printf("Blink\n");
	resetcolor();

	set_display_atrib(REVERSE);
	printf("Reverse\n");
	printf("\n");
	

	set_display_atrib(BRIGHT);
	printf("Text color example:\n");
	resetcolor();
	
	set_display_atrib(F_RED);
	printf("Red\n");
	resetcolor();
	
	set_display_atrib(F_GREEN);
	printf("Green\n");
	resetcolor();

	set_display_atrib(F_BLUE);
	printf("Blue\n");
	resetcolor();

	set_display_atrib(F_CYAN);
	printf("Cyan\n");
	resetcolor();

	set_display_atrib(BRIGHT);
	printf("\nBottom color example:\n");
	resetcolor();	
	
	set_display_atrib(B_RED);
	printf("Red\n");
	resetcolor();
	
	set_display_atrib(B_GREEN);
	printf("Green\n");
	resetcolor();

	set_display_atrib(B_BLUE);
	printf("Blue\n");
	resetcolor();

	set_display_atrib(B_CYAN);
	printf("Cyan\n");
	printf("\n");
	resetcolor();
}
