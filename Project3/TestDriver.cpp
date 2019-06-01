#include "TestDriver.h"
#include <string>
#include <iostream>
#include "testHarness.h"

using namespace std;

TestDriver::TestDriver()
{

}

bool ITest::runTest()
{
	
}

bool TestDriver::test()
{
	ITest testing;

	testing.runTest();
}

TestDriver::~TestDriver()
{

}