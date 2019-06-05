#include "testHarness.h"
//#include <string>
//#include <iostream>
//#include <vector>
//#include <windows.h>
#include "tinyxml2.h"
#include "../Comm/MsgPassingComm/Comm.h"
#include "../Comm/Message/Message.h"
#include "../Comm/Sockets/Sockets.h"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include <thread>
#include <winsock2.h>

using namespace tinyxml2;
using namespace std;
using namespace MsgPassingCommunication;

typedef void(*funcITest)();

/*
This Comm is established here due to the lack of a default
constructor.
*/
Comm comm(EndPoint("localhost", 9890), "NewComm");

testHarness::testHarness()
{

}

/*
This function starts the Comm and the thread
*/
void testHarness::start()
{
	comm.start();
	t = thread([this] { runThread(); });
}

/*
This function joins the thread and stops the Comm
*/
void testHarness::end()
{
	queue.enQ("Stop");
	t.join();
	comm.stop();
}

void testHarness::sendMessage(Message msg)
{
	//Post the message
	comm.postMessage(msg);

	//Lock here to stop races to enqueue
	{
		lock_guard<mutex> l(lock);
	}

	//Enqueue
	queue.enQ("Ready");

}

void testHarness::runThread()
{
	string msg;

	//Run so long as msg isn't "Stop"
	do {
		//Dequeue 
		msg = queue.deQ();

		//Lock to allow for runFunction to run 
		{
			lock_guard<mutex> l(lock);

			Message message = comm.getMessage();

			this->testFunction(message);
		}
	} while (msg != "Stop");
}

/*
This function goes through the process of explicitly linking the DLL
and running its test function.
*/
void testHarness::testFunction(Message msg)
{
	string xmlPath = msg.file();
	string name = msg.name();

	cout << name << " received, beginning tests" << endl;

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

}