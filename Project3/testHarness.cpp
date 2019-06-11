#include "testHarness.h"
//#include <string>
//#include <iostream>
//#include <vector>
//#include <windows.h>
#include "tinyxml2.h"
#include "../Comm/MsgPassingComm/Comm.h"
#include "../Comm/Message/Message.h"
#include "../Comm/Sockets/Sockets.h"
//#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../Comm/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../Comm/Logger/Logger.h"
//#include "../Comm/Utilities/Utilities.h"
#include <iostream>
#include <functional>
#include <conio.h>
//#include <thread>
//#include <winsock2.h>

using namespace tinyxml2;
using namespace std;
using namespace MsgPassingCommunication;
using namespace Sockets;

typedef void(*funcITest)();

/*
This Comm is established here due to the lack of a default
constructor.
*/

//EndPoint serverEP("localhost", 9891);
//EndPoint clientEP("localhost", 9891);

//Comm commTest(EndPoint("localhost", 9891), "commTest");
//thread t(runThread, &(this.queue));

testHarness::testHarness()
{

}

/*
This function starts the Comm and the thread
*/
void testHarness::start()
{
	//commTest.start();
	//t = thread([this] { runThread(); });
	//t = thread (runThread, &(this->queue));
	//t = thread([this] { runThread(&(this->queue)); });
}

/*
This function joins the thread and stops the Comm
*/
void testHarness::end()
{
	queue.enQ("Stop");
	//t.join();
	//commTest.stop();
}

void testHarness::sendMessage(Message msg, EndPoint ep)
{

	Comm commTest(EndPoint("localhost", 9191), "commTest");

	commTest.start();

	cout << "Message sending" << endl;

	//Post the message
	//comm.postMessage(msg);

	//cout << "Message posted" << endl;

	//Lock here to stop races to enqueue
	/*{
		lock_guard<mutex> l(lock);

		comm.postMessage(msg);
	}*/

	StaticLogger<1>::flush();

	commTest.postMessage(msg);

	StaticLogger<1>::stop();

	cout << "Message posted" << endl;

	msg = commTest.getMessage();

	//cout << commTest.getMessage() << endl;

	//Message newMsg = commTest.getMessage();

	//Message newMsg;

	//newMsg.to(ep);
	//newMsg.from(ep);

	//newMsg = commTest.getMessage();

	cout << "Message received: " << msg.name() << endl;

	//cout << "Message posted" << endl;

	//cout << "Going to enqueue" << endl;

	//Enqueue
	//this->queue.enQ("Ready");

	cout << "Enqueued" << endl;

	commTest.stop();

	//std::this_thread::sleep_for(std::chrono::milliseconds(20));

}

/*void testHarness::runThread(BlockingQueue<string>* pQ)
{
	string msg;

	cout << "Preparing to dequeue" << endl;

	//Run so long as msg isn't "Stop"
	do {
		//Dequeue 
		msg = pQ->deQ();

		cout << "Dequeued" << endl;

		//Lock to allow for runFunction to run 
		{
			lock_guard<mutex> l(lock);

			cout << "Evaluating dequeued msg " << msg << endl;

			if (msg == "Ready") {
				cout << "Getting message" << endl;

				Message message = commTest.getMessage();

				cout << "Got message " << message.name() << endl;

				this->testFunction(message);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	} while (msg != "Stop");
}
*/
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