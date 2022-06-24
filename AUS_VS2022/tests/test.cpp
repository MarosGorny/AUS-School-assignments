#include "test.h"
#include "../structures/_logger/logger.h"
#include <chrono>
#ifdef AUS_CATCH_EXCEPTIONS
#include <exception>
#endif

namespace tests
{
// TestLog:

    TestLog::TestLog(TestLogType logType, std::string message) :
        logType_(logType),
        message_(std::move(message))
    {
    }

    TestLogType TestLog::getType() const
    {
        return logType_;
    }

    const std::string& TestLog::getMessage() const
    {
        return message_;
    }

// Test:

    Test::Test(std::string name) :
        name_(std::move(name))
    {
    }

    const std::string& Test::getName() const
    {
        return name_;
    }

	void Test::run()
	{
#ifdef AUS_CATCH_EXCEPTIONS
		try
		{
#endif
		beforeTest();
		test();
		afterTest();

#ifdef AUS_CATCH_EXCEPTIONS
		}
		catch (const std::exception& e)
		{
			structures::Logger::getInstance().logError(e.what());
			this->fail(e.what());
		}
#endif
	}

    void Test::beforeTest()
    {
    }

    void Test::afterTest()
    {
    }

	void Test::fail(const std::string&)
	{
	}

// SimpleTest:

	SimpleTest::SimpleTest(std::string name) :
		Test(std::move(name)),
		elapsedTime_(0)
	{
	}

	TestResult SimpleTest::getResult() const
	{
		return result_;
	}

	const std::vector<TestLog>& SimpleTest::getOutput() const
	{
		return output_;
	}

	void SimpleTest::reset()
	{
		result_ = TestResult::NotEvaluated;
		output_.clear();
	}

	void SimpleTest::beforeTest()
	{
		Test::beforeTest();
		result_ = TestResult::Passed;
	}

	void SimpleTest::assertTrue(bool expression)
	{
		assertTrue(expression, "");
	}

	void SimpleTest::assertFalse(bool expression)
	{
		assertFalse(expression, "");
	}

	void SimpleTest::assertTrue(bool expression, const std::string& message)
	{
		if (!expression)
		{
			fail("Assert true failed. " + message);
		}
		else
		{
			logPass("Assert true passed. " + message);
		}
	}

	void SimpleTest::assertFalse(bool expression, const std::string& message)
	{
		if (expression)
		{
			fail("Assert false failed. " + message);
		}
		else
		{
			logPass("Assert false passed. " + message);
		}
	}

	void SimpleTest::fail(const std::string& message)
	{
		result_ = TestResult::Failed;
		logError(message);
	}

	void SimpleTest::succeed(const std::string& message)
	{
		logPass(message);
	}

	void SimpleTest::logInfo(std::string str)
	{
		output_.emplace_back(TestLogType::Info, std::move(str));
	}

	void SimpleTest::logPass(std::string str)
	{
		output_.emplace_back(TestLogType::Pass, std::move(str));
	}

	void SimpleTest::logError(std::string str)
	{
		output_.emplace_back(TestLogType::Error, std::move(str));
	}

	void SimpleTest::startStopwatch()
	{
		timeZero_ = Clock::now();
	}

	void SimpleTest::stopStopwatch()
	{
		namespace ch = std::chrono;
		auto elapsedTime = Clock::now() - timeZero_;
		elapsedTime_ = ch::duration_cast<DurationType>(elapsedTime);
	}

	DurationType SimpleTest::getElapsedTime() const
	{
		return elapsedTime_;
	}

// ComplexTest:

	ComplexTest::ComplexTest(std::string name) :
		Test(std::move(name))
	{
	}

	ComplexTest::~ComplexTest()
	{
		for (Test* subTest : tests_)
		{
			delete subTest;
		}
	}

	TestResult ComplexTest::getResult() const
	{
		std::size_t failCount = 0;
		std::size_t passCount = 0;
		std::size_t partialCount = 0;

		for (Test* test : tests_)
		{
			switch (test->getResult())
			{
			case TestResult::Failed:
				++failCount;
				break;

			case TestResult::Passed:
				++passCount;
				break;

			case TestResult::Partial:
				++partialCount;
				break;

			default:
				break;
			}
		}

		if (failCount + passCount + partialCount != tests_.size() || tests_.size() == 0)
		{
			return TestResult::NotEvaluated;
		}
		else if (passCount == tests_.size())
		{
			return TestResult::Passed;
		}
		else if (failCount == tests_.size())
		{
			return TestResult::Failed;
		}
		else
		{
			return TestResult::Partial;
		}
	}

	void ComplexTest::test()
	{
		for (Test* subTest : tests_)
		{
			subTest->run();
		}
	}

	void ComplexTest::addTest(Test* test)
	{
		tests_.emplace_back(test);
	}

	const std::vector<Test*>& ComplexTest::getSubTests() const
	{
		return tests_;
	}

	void ComplexTest::reset()
	{
		for (Test* subTest : tests_)
		{
			subTest->reset();
		}
	}

	std::string testLogTypeToString(TestLogType type)
	{
		switch (type)
		{
		case tests::TestLogType::Error:
			return "Error";

		case tests::TestLogType::Warning:
			return "Warning";

		case tests::TestLogType::Pass:
			return "Pass";

		case tests::TestLogType::Info:
			return "Info";

		case tests::TestLogType::Elapsed:
			return "Elapsed";

		default:
			return "<unknown>";
		}
	}
}