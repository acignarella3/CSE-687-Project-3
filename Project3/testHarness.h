#pragma once
#include <string>
#include <vector>
#include "../Comm/MsgPassingComm/Comm.h"
#include "../Comm/Message/Message.h"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

using namespace std;
using namespace MsgPassingCommunication;

class testHarness
{
public:
	testHarness();
	//void testFunction(string xmlPath);
	void testFunction(Message msg);
	~testHarness();
	EndPoint ep;
	Comm comm;
	BlockingQueue<string> queue;
};

