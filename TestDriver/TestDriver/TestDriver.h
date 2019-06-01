#pragma once
#ifdef TESTDRIVER_EXPORTS
#define TESTDRIVER_API __declspec(dllexport)
#else
#define TESTDRIVER_API __declspec(dllimport)
#endif // TESTDRIVER_EXPORTS

extern "C" TESTDRIVER_API void ITest();

extern "C" TESTDRIVER_API bool test(int input1, int input2);