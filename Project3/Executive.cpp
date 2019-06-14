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

	//EndPoint serverEP("localhost", 9890);
	//EndPoint clientEP("localhost", 9891);

	//EndPoint ep("localhost", 9890);
	// EndPoint ep("localhost", 9191);

	//EndPoint ep1("localhost", 9190);
	//EndPoint ep2("localhost", 9890);

	//Comm server(ep1, "server");

	//server.start();

	testHarness harness;

	harness.start();

	Message msg1;
	msg1.file("../testing.xml");
	msg1.name("Message 1");
	//msg1.to(ep);
	//msg1.from(ep);
	//msg1.to(ep2);
	msg1.from(harness.publicEP1);
	//msg1.to(ep2);
	msg1.to(harness.publicEP2);

	Message msg2;
	msg2.file("../testing.xml");
	msg2.name("Message 2");

	Message msg3;
	msg3.file("../testing.xml");
	msg3.name("Message 3");

	Message msg4;
	msg4.file("../testing.xml");
	msg4.name("Message 4");

	//testHarness harness;

	//harness.start();

	cout << "Sending messages now" << endl;

	//server.postMessage(msg1);

	harness.sendMessage(msg1);
	//harness.sendMessage(msg2);
	//harness.sendMessage(msg3);
	//harness.sendMessage(msg4);

	harness.end();

	//server.stop();

}
