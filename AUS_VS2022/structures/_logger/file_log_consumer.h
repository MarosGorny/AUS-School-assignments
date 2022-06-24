#pragma once
#include "logger.h"
#include <fstream>

namespace structures
{
	class FileLogConsumer
		:public structures::ILogConsumer
	{
	public:
		FileLogConsumer(const std::string& path);
		void logMessage(structures::LogType type, const std::string& message) override;
		void logDuration(size_t size, std::chrono::nanoseconds duration, const std::string& message) override;
		void matrixDuration(size_t rows, size_t columns, std::chrono::nanoseconds duration, const std::string& message);
		void matrixTitle();
		void SizeTimeNsMethodTitle();
		void csvCELL(const std::string& message, bool bodkoCiarka = true, bool novyRiadok = false);
		void csvCELL(long long duration, bool bodkoCiarka = true, bool novyRiadok = false);
	private:
		std::ofstream fileStream_;
	};

}
