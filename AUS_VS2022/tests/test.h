#pragma once

#include "../structures/heap_monitor.h"
#include "../structures/_logger/logger.h"
#include <chrono>
#include <string>
#include <vector>

namespace tests
{
	using DurationType = structures::DurationType;

	/// <summary>
	/// Typ spravy o priebehu testu.
	/// </summary>
	enum class TestLogType
	{
		Error,
		Warning,
		Pass,
		Info,
		Elapsed
	};

	/// <summary>
	/// Prevedie enum na string.
	/// </summary>
	/// <param name="type">Typ logu testu.</param>
	/// <returns>Retazcova reprezentacia enumu.</returns>
	std::string testLogTypeToString(TestLogType type);

	/// <summary>
	/// Typ vysledku testu.
	/// </summary>
	enum class TestResult
	{
		Passed,
		Failed,
		Partial,
		NotEvaluated
	};

	/// <summary>
	/// Sprava o priebehu testu. Obsahuje typ a obsah spravy.
	/// </summary>
	class TestLog
	{
	public:
		TestLog(TestLogType logType, std::string message);

		TestLogType getType() const;
		const std::string& getMessage() const;

	private:
		TestLogType logType_;
		std::string message_;
	};

	/// <summary>
	/// Spolocny predok pre vsetky testy.
	/// </summary>
	class Test
	{
	public:
		Test(std::string name);
		virtual ~Test() = default;

		const std::string& getName() const;
		virtual TestResult getResult() const = 0;
		virtual void reset() = 0;
		void run();

	protected:
		virtual void beforeTest();
		virtual void test() = 0;
		virtual void afterTest();
		virtual void fail(const std::string& message);

	private:
		std::string name_;
	};

	/// <summary>
	/// Jednouduchy test, ktory sluzi ako predok pre konkretne testy.
	/// </summary>
	class SimpleTest
		: public Test
	{
	public:
		SimpleTest(std::string name);

		TestResult getResult() const override;
		const std::vector<TestLog>& getOutput() const;
		void reset() override;

	protected:
		void beforeTest() override;

		void assertTrue(bool expression);
		void assertFalse(bool expression);

		void assertTrue(bool expression, const std::string& message);
		void assertFalse(bool expression, const std::string& message);

		void fail(const std::string& message) override;
		void succeed(const std::string& message);

		void logInfo(std::string str);
		void logPass(std::string str);
		void logError(std::string str);

		void startStopwatch();
		void stopStopwatch();
		DurationType getElapsedTime() const;

	private:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

	private:
		TestResult result_;
		std::vector<TestLog> output_;
		TimePoint timeZero_;
		DurationType elapsedTime_;
	};

	/// <summary>
	///	Predok pre testy, ktore sa skladaju z viacerych testov.
	/// </summary>
	class ComplexTest
		: public Test
	{
	public:
		ComplexTest(std::string name);
		~ComplexTest();

		TestResult getResult() const override;
		const std::vector<Test*>& getSubTests() const;
		void reset() override;

	protected:
		void test() override;
		void addTest(Test* test);

	private:
		std::vector<Test*> tests_;
	};
}