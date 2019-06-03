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

EndPoint ep("localhost", 9890);
Comm comm(ep, "Comm");
//BlockingQueue<string> queue;
thread t;

testHarness::testHarness()
{
	//EndPoint ep("localhost", 9890);
	//Comm comm(ep, "Comm");
	//this->comm = Comm(ep, "Comm");
	comm.start();

	//thread t1, t2, t3, t4;

	//queue.enQ(t1);
	//queue.enQ(t2);
	//queue.enQ(t3);
	//queue.enQ(t4);

	//t1([this] { runThread(); });

	//t1 = thread([this] { runThread(); });
	//t2 = thread([this] { runThread(); });
	//t3 = thread([this] { runThread(); });
	//t4 = thread([this] { runThread(); });

	//thread t(runThread);

	//thread t([this] { runThread(); });

	t = thread([this] { runThread(); });

	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();
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
	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();

	t.join();

	comm.stop();
}