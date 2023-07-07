#include <iostream>
#include "Application.h"

using namespace std;

void Application::ReadAndPrint(int startAddr, int endAddr)
{
	for (int addr = startAddr; addr <= endAddr; addr++)
	{
		int readResult = m_pstDriver->read(addr);

		cout << readResult << " ";
	}
	cout << endl;
}

void Application::WriteAll(int value)
{
}