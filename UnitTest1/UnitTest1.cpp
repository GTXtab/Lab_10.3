#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.3/Lab_10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            int N = 3;
            Bill bills[3] = {
                {"PayerC", "RecipientC", 300.0},
                {"PayerA", "RecipientA", 100.0},
                {"PayerB", "RecipientB", 200.0}
            };

            SortBillsByPayerAccount(bills, N);

            Assert::AreEqual(string("PayerA"), bills[0].payerAccount);
            Assert::AreEqual(string("PayerB"), bills[1].payerAccount);
            Assert::AreEqual(string("PayerC"), bills[2].payerAccount);
		}
	};
}
