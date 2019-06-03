#pragma once
#include <string>
#include <vector>
#include "../Comm/MsgPassingComm/Comm.h"
#include "../Comm/Message/Message.h"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../Comm/Sockets/Sockets.h"

using namespace std;
using namespace MsgPassingCommunication;

class testHarness
{
public:
	testHarness();
	//void testFunction(string xmlPath);
	void testFunction(Message msg);
	void runThread();
	void runFunction(Message msg);
	~testHarness();
	//EndPoint ep;
	//Comm comm;
	BlockingQueue<string> queue;
	//thread t1, t2, t3, t4;
	mutex lock;
};