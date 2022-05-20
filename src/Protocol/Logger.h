#include <iostream>

#ifdef __linux__
	//Regular text
	#define BLK "\e[0;30m"
	#define RED "\e[0;31m"
	#define GRN "\e[0;32m"
	#define YEL "\e[0;33m"
	#define BLU "\e[0;34m"
	#define MAG "\e[0;35m"
	#define CYN "\e[0;36m"
	#define WHT "\e[0;37m"
	#define GRY "\e[1;30m"
	//Regular bold text
	#define BBLK "\e[1;30m"
	#define BRED "\e[1;31m"
	#define BGRN "\e[1;32m"
	#define BYEL "\e[1;33m"
	#define BBLU "\e[1;34m"
	#define BMAG "\e[1;35m"
	#define BCYN "\e[1;36m"
	#define BWHT "\e[1;37m"
	//Reset
	#define reset "\e[0m"
	#define CRESET "\e[0m"
	#define COLOR_RESET "\e[0m"

	#define MSG_LOGGING_BEGIN "BEGIN LOGGING:"
#elif _WIN32
//Regular text
	#define BLK ""
	#define RED ""
	#define GRN ""
	#define YEL ""
	#define BLU ""
	#define MAG ""
	#define CYN ""
	#define WHT ""
	//Regular bold text
	#define BBLK ""
	#define BRED ""
	#define BGRN ""
	#define BYEL ""
	#define BBLU ""
	#define BMAG ""
	#define BCYN ""
	#define BWHT ""
	//Reset
	#define reset ""
	#define CRESET ""
	#define COLOR_RESET ""

	#define MSG_LOGGING_BEGIN "BEGIN LOGGING: [Notice]: Colored output is not supported on your platform."
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
		static LogLevel level;
	public:
	Logger(std::ostream& out, LogLevel level = LogLevel::INFO);
	Logger();
	void erro(std::string msg);
	void warn(std::string msg);
	void info(std::string msg);
	void verb(std::string msg);
	void exit(std::string msg);
};