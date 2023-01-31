#include <chrono>
#include <iostream>
#include <Windows.h>

#include <conio.h>
#include <stdio.h>

/**
 * Todo
 * 1. add mouse movement detection
 * 2. add another sound for beeping
 * 3. add option for sound if break time is also over
 * 4. (future improvement) computer vision to make sure a person walked and not still sitting (for example watching a video case)
 */
int main(int argc, char* argv[])
{
	int workTimeMin, breakTimeMin;

	// 3 = program name, first parameter, second parameter
	if(argc > 3)
	{
		std::cout << "Program args: [Work Time in Min] [Break Time in Min]\n";
		exit(0);
	}
	else if(argc != 3)
	{
		std::cout << "Using default values for unspecifed parameters!\n";
	}

	if (argc == 1)
	{
		workTimeMin = 25;
		breakTimeMin = 5;
	}
	else if (argc == 2)
	{
		workTimeMin = atoi(argv[1]);
		breakTimeMin = 5;
	}
	else // argc == 3
	{
		workTimeMin = atoi(argv[1]);
		breakTimeMin = atoi(argv[2]);
	}

	std::cout << "Work Time in Min: " << workTimeMin << "\n";
	std::cout << "Break Time in Min: " << breakTimeMin << "\n";

	float continuousWorkTime = 0;

	bool keyIsPressed = false;
	auto start = std::chrono::steady_clock::now();

	while (true)
	{

		// taken from https://github.com/MinhasKamal/TrojanCockroach/blob/master/com/minhaskamal/trojanCockroach/TrojanCockroach.cpp
		unsigned short ch = 1;
		int i;
		while (ch < 250) {
			for (i = 0; i < 50; i++, ch++) {
				if (GetAsyncKeyState(ch) == -32767) { ///key is stroke
					keyIsPressed = true;
				}
			}
			Sleep(1); ///take rest
		}


		if(keyIsPressed)
		{
			auto now = std::chrono::steady_clock::now();
			auto timePassed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
			start = now;
#ifdef _DEBUG
			std::cout << "Since last key stroke in minutes " << timePassed/60.f << "\n";
			std::cout << "Since last key stroke in seconds " << timePassed << "\n";
#endif
			if (timePassed < breakTimeMin * 60)
			{
				continuousWorkTime += timePassed / 60.f;
			}
			else
			{
				continuousWorkTime = 0.f;
			}

			// if you work more than worktime and still using the computer, beep on every keystroke
			if(continuousWorkTime >= workTimeMin)
				std::cout << '\a'; // beep
		}

		keyIsPressed = false;
	}
}
