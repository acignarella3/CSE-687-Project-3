#include "stdafx.h"
#include "number.h"
#include <iostream>
#include <string>

using namespace std;

int _inputOne;
int _inputTwo;

number::number()
{
	_inputOne = -1;
	_inputTwo = -1;
}

number::number(int inputOne, int inputTwo)
{
	_inputOne = inputOne;
	_inputTwo = inputTwo;
}

int number::operator()()
{
	//throw string("No inputs were used");
	if (_inputOne < 0 && _inputTwo < 0) {
		throw string("No inputs detected");
	}
	else if (_inputOne < 0) {
		throw string("The first input must be a positive number");
	}
	else if (_inputTwo < 0) {
		throw string("The second input must be a positive number");
	}
	else if (_inputTwo == 0) {
		throw string("The second input cannot be zero");
	}

	int results = _inputOne / _inputTwo;

	return results;
}

number::~number()
{
}