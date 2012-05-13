#ifndef LOG_H
#define LOG_H

#include <list>
#include <ostream>
#include <QObject>
#include <QString>

/*! Channels available */
enum LogChannel {
	Channel_Global,
	Channel_Qt,
	Channel_Server,
	Channel_Physic,
	Channel_Textures,
	Channel_OpenGL,
	Channel_Blocks
};

/*! Singloton class for logging */
class Log : public QObject
{
	Q_OBJECT

public:
	Log();
	~Log();

	inline static Log& instance() {
		static Log log;
		return log;
	}

	static void printLine(const std::string& string);

	static void debugLine(const std::string& string, const LogChannel channel = Channel_Global);
	static void debugLine(const QString& string, const LogChannel channel = Channel_Global);
	static void debugLine(const char* string, const LogChannel channel = Channel_Global);

	static void infoLine(const std::string& string, const LogChannel channel = Channel_Global);
	static void infoLine(const QString& string, const LogChannel channel = Channel_Global);
	static void infoLine(const char* string, const LogChannel channel = Channel_Global);

	static void warningLine(const std::string& string, const LogChannel channel = Channel_Global);
	static void warningLine(const QString& string, const LogChannel channel = Channel_Global);
	static void warningLine(const char* string, const LogChannel channel = Channel_Global);

	static void errorLine(const std::string& string, const LogChannel channel = Channel_Global);
	static void errorLine(const QString& string, const LogChannel channel = Channel_Global);
	static void errorLine(const char* string, const LogChannel channel = Channel_Global);

	/*! Plug an ostream on which the log will print */
	static void plugOutputStream(std::ostream* stream);

signals:
	void print(const std::string& string);

private:

	static const char* channelString(const LogChannel channel);

	std::list<std::ostream*> m_ostreams; //!< All ostreams we have to print on
};

template<typename T>
inline std::basic_ostream<T>& operator<<(std::basic_ostream<T>& os, const QString& str) {
	return os << qPrintable(str);
}

#ifndef QT_NO_DEBUG
#define ldebug(channel, string) (Log::debugLine(string, channel))
#else
#define ldebug(channel, string)
#endif

#define linfo(channel, string) (Log::infoLine(string, channel))
#define lwarning(channel, string) (Log::warningLine(string, channel))
#define lerror(channel, string) (Log::errorLine(string, channel))

#endif // LOG_H
