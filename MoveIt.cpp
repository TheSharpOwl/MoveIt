// MoveIt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

int main()
{
    while(true)
    {
        SHORT keyState = GetKeyState(VK_CAPITAL); // capslock
        bool isToggled = keyState & 1;
        bool isDown = keyState & 0x8000;
        if(isDown)
        {
            std::cout << "Pressed Caps Lock\n";
        }
    }
}
