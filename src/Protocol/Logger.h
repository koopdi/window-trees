#pragma once

#include <iostream>

#ifdef __linux__
	//Regular text
	const char BLK[] = "\e[0;30m";
	const char RED[] = "\e[0;31m";
	const char GRN[] = "\e[0;32m";
	const char YEL[] = "\e[0;33m";
	const char BLU[] = "\e[0;34m";
	const char MAG[] = "\e[0;35m";
	const char CYN[] = "\e[0;36m";
	const char WHT[] = "\e[0;37m";
	const char GRY[] = "\e[1;30m";
	//Regular bold text
	const char BBLK[] = "\e[1;30m";
	const char BRED[] = "\e[1;31m";
	const char BGRN[] = "\e[1;32m";
	const char BYEL[] = "\e[1;33m";
	const char BBLU[] = "\e[1;34m";
	const char BMAG[] = "\e[1;35m";
	const char BCYN[] = "\e[1;36m";
	const char BWHT[] = "\e[1;37m";
	//Reset
	const char reset[] = "\e[0m";
	const char CRESET[] = "\e[0m";
	const char COLOR_RESET[] = "\e[0m";

	const char MSG_LOGGING_BEGIN[] = "BEGIN LOGGING:";
#elif _WIN32
//Regular text
	const char BLK[] = "";
	const char RED[] = "";
	const char GRN[] = "";
	const char YEL[] = "";
	const char BLU[] = "";
	const char MAG[] = "";
	const char CYN[] = "";
	const char WHT[] = "";
	const char GRY[] = "";
	//Regular bold text
	const char BBLK[] = "";
	const char BRED[] = "";
	const char BGRN[] = "";
	const char BYEL[] = "";
	const char BBLU[] = "";
	const char BMAG[] = "";
	const char BCYN[] = "";
	const char BWHT[] = "";
	//Reset
	const char reset[] = "";
	const char CRESET[] = "";
	const char COLOR_RESET[] = "";

	const char MSG_LOGGING_BEGIN[] = "BEGIN LOGGING: [Notice]: Colored output is not supported on your platform.";
#endif

enum LogLevel {
	VERBOSE,
	INFO,
	WARN,
	ERROR,
	FATAL,
};

class Logger {
	private:
		std::ostream& out;
		LogLevel level;
	public:
	Logger(std::ostream& out = std::cout, LogLevel level = LogLevel::INFO);
	void erro(std::string msg);
	void warn(std::string msg);
	void info(std::string msg);
	void verb(std::string msg);
	void exit(std::string msg);
};