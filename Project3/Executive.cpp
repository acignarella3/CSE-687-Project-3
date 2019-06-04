// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//#include <iostream>
//#include <windows.h>
#include "testHarness.h"
#include "../Comm/Message/Message.h"
//#include "../Comm/Sockets/Sockets.h"
#include <winsock2.h>
#include <thread>

//using namespace std;
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
	msg1.name("Message 1");

	/*Message msg2;
	msg2.file("../testing.xml");
	msg2.name("Message 2");

	Message msg3;
	msg3.file("../testing.xml");
	msg3.name("Message 3");

	Message msg4;
	msg4.file("../testing.xml");
	msg4.name("Message 4");*/

	testHarness harness;

	harness.start();

	harness.end();

	//harness.testFunction()
}
