#include "testHarness.h"
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include "tinyxml2.h"
#include "../Comm/MsgPassingComm/Comm.h"
#include "../Comm/Message/Message.h"
#include "../Comm/Sockets/Sockets.h"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

using namespace tinyxml2;
using namespace std;
using namespace MsgPassingCommunication;

typedef void(*funcITest)();

//EndPoint ep("localhost", 9890);
//Comm comm(ep, "Comm");
//BlockingQueue<string> queue;
//thread t;

//testHarness::comm : comm(EndPoint("localhost", 9890), "Comm") {}

Comm comm(EndPoint("localhost", 9890), "NewComm");

testHarness::testHarness()
{

}

/*void testHarness::testFunction(string xmlPath)
{

	tinyxml2::XMLDocument doc;

	doc.LoadFile( xmlPath.c_str() );

	const char* test = doc.FirstChildElement( "TestElement" )->GetText();

	if (strcmp(test, "TestDriver") == 0) {

		LPCWSTR libName = L"../TestDriver/Debug/TestDriver.dll";

		HINSTANCE hDLL = LoadLibrary(libName);

		if (hDLL != NULL) {

			funcITest ITest = (funcITest)GetProcAddress(hDLL, "ITest");

			ITest();

			FreeLibrary(hDLL);

		}

	}

}*/

void testHarness::start()
{
	comm.start();
	t = thread([this] { runThread(); });
}

void testHarness::end()
{
	t.join();
	comm.stop();
}

void testHarness::testFunction(Message msg)
{
	comm.postMessage(msg);

	{
		lock_guard<mutex> l(lock);
	}

	queue.enQ("Ready");

}

void testHarness::runThread()
{
	cout << "Yes" << endl;

	string msg;

	do {
		msg = queue.deQ();
		{
			lock_guard<mutex> l(lock);

			Message message = comm.getMessage();

			this->runFunction(message);
		}
	} while (msg != "Stop");
}

void testHarness::runFunction(Message msg)
{
	string xmlPath = msg.file();

	tinyxml2::XMLDocument doc;

	doc.LoadFile(xmlPath.c_str());

	const char* test = doc.FirstChildElement("TestElement")->GetText();

	if (strcmp(test, "TestDriver") == 0) {

		LPCWSTR libName = L"../TestDriver/Debug/TestDriver.dll";

		HINSTANCE hDLL = LoadLibrary(libName);

		if (hDLL != NULL) {

			funcITest ITest = (funcITest)GetProcAddress(hDLL, "ITest");

			ITest();

			FreeLibrary(hDLL);

		}

	}
}

testHarness::~testHarness()
{
	t.join();

	comm.stop();
}