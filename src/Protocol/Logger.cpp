#include "Logger.h"
Logger::Logger() : out(std::cout){
	Logger(std::cout, LogLevel::INFO);
}

Logger::Logger(std::ostream& out, LogLevel level) : out(out){
	out << MSG_LOGGING_BEGIN << std::endl;
	Logger::level = level;
	out << "LOG LEVEL IS: " << level << std::endl;
}

void Logger::erro(std::string msg){
	if(level >= LogLevel::ERROR){
		out << BRED << "[ERROR]  " << reset << msg << std::endl;
	}
}
void Logger::warn(std::string msg){
	if(level >= LogLevel::WARN){
		out << YEL << "[WARN]    " << reset << msg << std::endl;
	}
}
void Logger::info(std::string msg){
	if(level >= LogLevel::INFO){
		out << reset << "[Info]    "  << msg << std::endl;
	}
}
void Logger::verb(std::string msg){
	if(level >= LogLevel::VERBOSE){
		out << GRY << "[verbose]  " << msg << std::endl;
	}
}

void Logger::exit(std::string msg){
	out << BRED << "[FATAL]  " << msg << std::endl;
	std::exit(1);
}