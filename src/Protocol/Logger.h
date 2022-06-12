
#pragma once

#include <iostream>

/** @file Logger.h
 * @brief defines Logger, a class used for printing nice looking logs.
 * Provides the ability to log to any output stream, and pretty colors!
 * @note including this file will #define quite a few terminal color codes
 * @note also #defines terminal color codes (if on linux)
 * @author Christen Spadavecchia
 * @date 6/10/2022
*/

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

/** @brief enumerates possible log levels */
enum LogLevel {
	VERBOSE,
	INFO,
	WARN,
	ERROR,
	FATAL,
};


/** @brief Logger is a class that provides visually pleasing logging capabilities
 * @note allows logs to be sent to an ostream and for debug levels to be set
*/

class Logger {
	private:
		//the ostream to write debug messages to
		std::ostream& out;
		//the current log level
		LogLevel level;
	public:
	/** @brief constructs a new logger
	 * @param out the stream to output logs to (defaults to std::cout)
	 * @param level the minimum level for logs to be reported (defaults to verbose)
	 */
	Logger(std::ostream& out = std::cout, LogLevel level = LogLevel::VERBOSE);
	/** @brief print an error to the log
	 * @param msg the message string to log
	 */
	void erro(std::string msg);
	/** @brief print a warning to the log
	 * @param msg the message string to log
	 */
	void warn(std::string msg);
	/** @brief print info to the log
	 * @param msg the message string to log
	 */
	void info(std::string msg);
	/** @brief print extra information to the log
	 * @param msg the message string to log
	 */
	void verb(std::string msg);
	/** @brief print an error that is considered fatal and then exit with code 1
	 * @param msg the message string to log
	 */
	void exit(std::string msg);
};