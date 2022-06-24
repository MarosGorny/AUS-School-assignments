#include "file_log_consumer.h"

structures::FileLogConsumer::FileLogConsumer(const std::string& path)
	:fileStream_(path)
{
	if (!this->fileStream_.is_open()) {
		throw std::invalid_argument("FileLogConsumer::FileLogConsumer: Failed to open file " + path);
	}
}

void structures::FileLogConsumer::logMessage(structures::LogType type, const std::string& message)
{
	this->fileStream_ << logTypeToString(type) << ";"  << message << std::endl;
}

void structures::FileLogConsumer::logDuration(size_t size, std::chrono::nanoseconds duration, const std::string& message)
{
	this->fileStream_ << size << ";" << duration.count() << ";" << message << std::endl;
}

void structures::FileLogConsumer::matrixDuration(size_t rows, size_t columns, std::chrono::nanoseconds duration, const std::string& message)
{
	this->fileStream_ << rows << ";" << columns << ";" << duration.count() << ";" << message << std::endl;
}

void structures::FileLogConsumer::matrixTitle()
{
	this->fileStream_ << "Rows;Columns;Time[ns];Method" << std::endl;
}

void structures::FileLogConsumer::SizeTimeNsMethodTitle()
{
	this->fileStream_ << "Size;Time[ns];Method" << std::endl;
}

void structures::FileLogConsumer::csvCELL(const std::string& message, bool bodkoCiarka , bool novyRiadok ) 
{
	this->fileStream_ << message << ((bodkoCiarka) ? ";" : "");
	if (novyRiadok)
		this->fileStream_ << std::endl;
}

void structures::FileLogConsumer::csvCELL(long long duration, bool bodkoCiarka, bool novyRiadok)
{
	this->fileStream_ << duration << ((bodkoCiarka) ? ";" : "");
	if (novyRiadok)
		this->fileStream_ << std::endl;
}
