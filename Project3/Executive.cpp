// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include "testHarness.h"
#include "../Comm/Message/Message.h"

using namespace std;
using namespace MsgPassingCommunication;

int main()
{

	//string xmlPath = "../testing.xml";

	//testHarness harness;

	//harness.testFunction(xmlPath);

	//STARTUPINFO si;
	//PROCESS_INFORMATION pi1;
	//PROCESS_INFORMATION pi2;

	//ZeroMemory(&si, sizeof(si));
	//si.cb = sizeof(si);
	//ZeroMemory(&pi1, sizeof(pi1));
	//ZeroMemory(&pi2, sizeof(pi2));

	Message msg1;
	msg1.file("../testing.xml");

	Message msg2;
	msg1.file("../testing.xml");

	Message msg3;
	msg1.file("../testing.xml");

	Message msg4;
	msg1.file("../testing.xml");

	testHarness harness;

	harness.testFunction()
}
