#include "Logger.h"

Logger::Logger(std::ostream& out, LogLevel level) : out(out), level(level){}

void Logger::erro(std::string msg){
	if(level >= LogLevel::ERROR){
		out << BRED << "[ERROR]  " << reset << msg << std::endl;
	}
}
void Logger::warn(std::string msg){
	if(level >= LogLevel::WARN){
		out << YEL << "[WARN]\t\t" << reset << msg << std::endl;
	}
}
void Logger::info(std::string msg){
	if(level >= LogLevel::INFO){
		out << WHT << "[Info]\t\t"  << msg << std::endl;
	}
}
void Logger::verb(std::string msg){
	if(level >= LogLevel::VERBOSE){
		out << GRY << "[verbose]\t" << msg << reset << std::endl;
	}
}

void Logger::exit(std::string msg){
	out << BRED << "[FATAL]\t\t" << msg << reset<< std::endl;
	std::exit(1);
}