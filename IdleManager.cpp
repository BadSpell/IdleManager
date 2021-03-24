#include <windows.h>
#include <powersetting.h>
#pragma comment(lib, "PowrProf.lib")
const GUID GUID_RYZEN_POWER = { 0x9897998c, 0x92de, 0x4669, 0x85, 0x3f, 0xb7, 0xcd, 0x3e, 0xcb, 0x27, 0x90 };

void IMain()
{
	LASTINPUTINFO lastInput;
	DWORD prevTime = -1;
	DWORD tick = 0;
	int currentState = -1;
	const int IdleTime = 360;

	lastInput.dwTime = 0;
	lastInput.cbSize = sizeof(LASTINPUTINFO);
	while (1)
	{
		if (!GetLastInputInfo(&lastInput))
			lastInput.dwTime = -1;
		
		if (prevTime == lastInput.dwTime)
		{
			if (tick < IdleTime)
				tick++;
		}
		else
		{
			prevTime = lastInput.dwTime;
			tick = 0;
		}
		if (tick < IdleTime)
		{
			if (currentState != 0)
			{
				currentState = 0;
				PowerSetActiveScheme(0, &GUID_RYZEN_POWER);
			}
		}
		else
		{
			if (currentState != 1)
			{
				currentState = 1;
				PowerSetActiveScheme(0, &GUID_MAX_POWER_SAVINGS);
			}
		}
		Sleep(1000);
	}
}