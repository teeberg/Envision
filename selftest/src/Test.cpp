/***********************************************************************************************************************
 * Test.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "Test.h"
#include "TestManager.h"

namespace SelfTest {

Test::Test(const QString &name_) :
	name(name_)
{
}

Test::~Test()
{
}

const QString& Test::getName() const
{
	return name;
}

void Test::run(TestResults& testResults)
{
	try
	{
		runCustom(testResults);
	}
	catch (...)
	{
		testResults.addFailed(getName() +": Uncaught exception outside of check.");
	}
}

}
