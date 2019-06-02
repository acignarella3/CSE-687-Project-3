#include "testHarness.h"
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include "tinyxml2.h"
#include "../Comm/MsgPassingComm/Comm.h"
#include "../Comm/Message/Message.h"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

using namespace tinyxml2;
using namespace std;
using namespace MsgPassingCommunication;

typedef void(*funcITest)();

EndPoint ep("localhost", 9890);
Comm comm(ep, "Comm");
BlockingQueue<thread> queue;

testHarness::testHarness()
{
	//EndPoint ep("localhost", 9890);
	//Comm comm(ep, "Comm");
	this->comm.start();

	//thread t1, t2, t3, t4;

	//queue.enQ(t1);
	//queue.enQ(t2);
	//queue.enQ(t3);
	//queue.enQ(t4);
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
	this->comm.postMessage(msg);
}

testHarness::~testHarness()
{
	this->comm.stop();
}
