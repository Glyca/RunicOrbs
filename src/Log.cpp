#include "Log.h"
#include <cstdlib> // abort()

void qtMessageOutput(QtMsgType type, const char* msg)
{
	switch (type) {
	case QtDebugMsg:
		ldebug(Channel_Qt, std::string(msg));
		break;
	case QtWarningMsg:
		lwarning(Channel_Qt, std::string(msg));
		break;
	case QtCriticalMsg:
		lerror(Channel_Qt, std::string(msg));
		break;
	case QtFatalMsg:
		lerror(Channel_Qt, std::string(msg));
		lwarning(Channel_Global, std::string("The error is unrecoverable, program will abort! :("));
		abort();
	}
}

Log::Log()
{
	qInstallMsgHandler(qtMessageOutput);
}

Log::~Log()
{

}

void Log::printLine(const std::string& string)
{
	// Print on ostreams
	std::list<std::ostream*>::iterator it(instance().m_ostreams.begin()), eit(instance().m_ostreams.end());
	for(; it != eit; ++it) {
		(*it)->write(string.c_str(), string.size());
		(*it)->put('\n');
		(*it)->flush();
	}
	// Print on slots
	emit instance().print(QString::fromStdString(string));
}

void Log::debugLine(const std::string& string, const LogChannel channel)
{
	printLine(std::string("[Debug/") + std::string(channelString(channel)) + std::string("] ") + string);
}
void Log::debugLine(const QString& string, const LogChannel channel)
{
	debugLine(string.toStdString(), channel);
}
void Log::debugLine(const char* string, const LogChannel channel)
{
	debugLine(std::string(string), channel);
}

void Log::infoLine(const std::string& string, const LogChannel channel)
{
	printLine(std::string("[Info/") + std::string(channelString(channel)) + std::string("] ") + string);
}
void Log::infoLine(const QString& string, const LogChannel channel)
{
	infoLine(string.toStdString(), channel);
}
void Log::infoLine(const char* string, const LogChannel channel)
{
	infoLine(std::string(string), channel);
}

void Log::warningLine(const std::string& string, const LogChannel channel)
{
	printLine(std::string("[WARNING/") + std::string(channelString(channel)) + std::string("] ") + string);
}
void Log::warningLine(const QString& string, const LogChannel channel)
{
	warningLine(string.toStdString(), channel);
}
void Log::warningLine(const char* string, const LogChannel channel)
{
	warningLine(std::string(string), channel);
}

void Log::errorLine(const std::string& string, const LogChannel channel)
{
	printLine(std::string("[ERROR/") + std::string(channelString(channel)) + std::string("] ") + string);
}
void Log::errorLine(const QString& string, const LogChannel channel)
{
	errorLine(string.toStdString(), channel);
}
void Log::errorLine(const char* string, const LogChannel channel)
{
	errorLine(std::string(string), channel);
}

void Log::plugOutputStream(std::ostream* stream)
{
	instance().m_ostreams.push_back(stream);
}

const char* Log::channelString(const LogChannel channel)
{
	switch(channel) {
	case Channel_Global:
		return "Global";
	case Channel_Qt:
		return "Qt";
	case Channel_Server:
		return "Server";
	case Channel_Physic:
		return "Physic";
	case Channel_Textures:
		return "Textures";
	case Channel_OpenGL:
		return "OpenGL";
	case Channel_Blocks:
		return "Blocks";
	default:
		return "Global";
	}
}
