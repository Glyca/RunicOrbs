#ifndef LOG_H
#define LOG_H

#include <list>
#include <ostream>

/*! Static singloton class for logging */
class Log
{
public:
	Log();

	/*! Channels available */
	enum Channel {
		Channel_Debug,
		Channel_Warning
	};

	static void print(const std::string& string);

	/*! Plug an ostream on which the log will print */
	static void plugOutputStream(const std::ostream& stream);

private:
	static Log& instance() {
		static Log log;
		return log;
	}

	std::list<std::ostream> m_ostreams; //!< All ostreams we have to print on
};

#endif // LOG_H
