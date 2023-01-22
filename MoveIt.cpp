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
 */
int main()
{
	auto const breakTimeMin = 5;
	auto const workTimeMin = 25;

	float continuousWorkTime = 0;

	bool isBreak = false;
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
			std::cout << "Since last key stroke in minutes " << timePassed << "\n";

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
