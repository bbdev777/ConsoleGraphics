
#include "ConsoleApp.h"
#include "MatrixColumnsModel.h"

void PutColumnsToDisplay(ConsoleGraphics::Display &display, MatrixColumns::MatrixColumnsModel &model);

int	main()
{
	ConsoleGraphics::ConsoleApp         application;
    MatrixColumns::MatrixColumnsModel   matrixColumnModel;
	double						        textPos = (double)application.GetDisplay().GetWidth();
	std::string					        message = "Press Ctrl + C for exit... ";


    matrixColumnModel.SetBounds(application.GetDisplay().GetWidth(), application.GetDisplay().GetHeight());

	return application.Run([&](double k, ConsoleGraphics::Display& display)
	{
        matrixColumnModel.Animate();

        PutColumnsToDisplay(display, matrixColumnModel);

		display.SetStringAt(int(textPos), 1, message, F_WHITE);

		textPos -= 0.25;

		if (textPos + message.size() < 0)
			textPos = (double)application.GetDisplay().GetWidth();
	},
    10,
    false);
}

void PutColumnsToDisplay(ConsoleGraphics::Display &display, MatrixColumns::MatrixColumnsModel &model)
{
    auto&   columns = model.GetColumns();
    
    for (auto& column : columns)
    {
        display.SetCharAt(column.x, column.y, column.firs, F_WHITE, 0);
        display.SetCharAt(column.x, column.y - 1, column.second, F_GREEN, 1);
        display.SetCharAt(column.x, column.y - column.length, column.terminal, F_GREEN, 2);
    }
}
