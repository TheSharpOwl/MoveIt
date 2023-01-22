#include <chrono>
#include <iostream>
#include <Windows.h>

#include <conio.h>
#include <stdio.h>

int main()
{
	auto const breakTimeMin = 5;
	auto const workTimeMin = 25;
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
			auto timePassed = std::chrono::duration_cast<std::chrono::minutes>(now - start).count();
			start = now;
			std::cout << '\a';
			std::cout << "Since last key stroke in minutes " << timePassed << "\n";
		}

		keyIsPressed = false;
	}
}
