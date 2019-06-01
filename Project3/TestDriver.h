#pragma once
#include "number.h"

class ITest
{
public:
	virtual ~ITest(){}
	virtual bool runTest();
};

class TestDriver
{
public:
	TestDriver();
	bool test();
	~TestDriver();
};