#include "AbstractConfiguration.h"

AbstractConfiguration::AbstractConfiguration()
{
}

AbstractConfiguration::AbstractConfiguration(const QString& filename) : s_filename(filename)
{
	Q_UNUSED(filename);
}

void AbstractConfiguration::setFilename(const QString& filename)
{
	s_filename = filename;
}
