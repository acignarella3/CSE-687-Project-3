// TestDriver.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include "TestDriver.h"
#include "number.h"
#include "Logger.h"
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
using namespace Logging;

TESTDRIVER_API void ITest()
{

	Logger ITestLog;
	ITestLog.attach(&cout);

	ITestLog.start();

	ITestLog.write("Begin testing\n");

	ITestLog.title("Test 1", '=');
	ITestLog.write("\n");
	bool test1Result = test(20, 10);
	string test1 = "Test 1 " + string(test1Result ? "passed" : "failed");
	ITestLog.write(test1 + "\n");
	time_t now1 = time(0);
	string timer1 = "Test 1 run at " + string(ctime(&now1));
	ITestLog.write(timer1 + "\n\n");

	ITestLog.title("Test 2", '=');
	ITestLog.write("\n");
	bool test2Result = test(10, 0);
	string test2 = "Test 2 " + string(test2Result ? "passed" : "failed");
	ITestLog.write(test2 + "\n");
	time_t now2 = time(0);
	string timer2 = "Test 2 run at " + string(ctime(&now2));
	ITestLog.write(timer2 + "\n\n");

	ITestLog.title("Test 3", '=');
	ITestLog.write("\n");
	bool test3Result = test(-20, 10);
	string test3 = "Test 3 " + string(test3Result ? "passed" : "failed");
	ITestLog.write(test3 + "\n");
	time_t now3 = time(0);
	string timer3 = "Test 3 run at " + string(ctime(&now3));
	ITestLog.write(timer3 + "\n\n");

	ITestLog.write("Testing complete\n");
	ITestLog.stop();
}

TESTDRIVER_API bool test(int input1, int input2)
{
	number num = number(input1, input2);
	Logger log;
	bool ans = false;

	log.attach(&cout);
	log.start();

	string start = "The inputs are " + to_string(input1) +
		" and " + to_string(input2);

	log.write(start + "\n");

	try
	{

		int res = num();

		string result = "The result is " + to_string(res);

		log.write(result + "\n");

		ans = true;
	}
	catch (string e)
	{

		string error = "Error: " + e;

		log.write(error + "\n");

		ans = false;
	}

	log.stop();

	return ans;
	
}
