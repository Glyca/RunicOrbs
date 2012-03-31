#include "Log.h"

Log::Log()
{
}

void Log::print(const std::string& string)
{
	std::list<std::ostream>::iterator it(instance().m_ostreams.begin()), eit(instance().m_ostreams.end());
	for(; it != eit; ++it) {
		it->write(string.c_str(), string.size());
	}
}
