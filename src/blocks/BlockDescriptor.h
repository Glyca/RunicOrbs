#ifndef BLOCKDESCRIPTOR_H
#define BLOCKDESCRIPTOR_H

#include <QColor>
#include <QString>

#include "BlockInfo.h"

class BlockDescriptor
{
public:
	BlockDescriptor() : i_id(0), s_name("undefined"), b_breakable(true), m_color(QColor(255, 255, 255)) {}
	BlockDescriptor(const int id, const QString& name, const bool breakable, const QColor& color)
		: i_id(id), s_name(name), b_breakable(breakable), m_color(color) {}

	inline int id() const {return i_id;}

private:
	// General
	int i_id;
	QString s_name;

	// Properties
	bool b_breakable;

	// Apparence
	QColor m_color;
};


inline bool operator==(const BlockDescriptor& blockDescriptor, const BlockInfo& blockInfo) {
	return (blockInfo.id() == blockDescriptor.id());
}

inline bool operator==(const BlockInfo& blockInfo, const BlockDescriptor& blockDescriptor) {
	return (blockInfo.id() == blockDescriptor.id());
}

inline bool operator!=(const BlockDescriptor& blockDescriptor, const BlockInfo& blockInfo) {
	return !(blockDescriptor == blockInfo);
}

inline bool operator!=(const BlockInfo& blockInfo, const BlockDescriptor& blockDescriptor) {
	return !(blockDescriptor == blockInfo);
}


#endif // BLOCKDESCRIPTOR_H
