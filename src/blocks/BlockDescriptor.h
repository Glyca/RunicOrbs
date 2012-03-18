#ifndef BLOCKDESCRIPTOR_H
#define BLOCKDESCRIPTOR_H

#include <QColor>
#include <QString>

#include "BlockInfo.h"
#include "Vector.h"
#include "gui/TextureManager.h" // TextureCoordinates

class BlockDescriptor
{
public:
	BlockDescriptor() : i_id(0), s_name("undefined"), b_breakable(true), m_color(QColor(255, 255, 255)) {}
	BlockDescriptor(const int id, const QString& name, const bool breakable, const QColor& color)
		: i_id(id), s_name(name), b_breakable(breakable), m_color(color) {}

	inline int id() const {return i_id;}

	/*! Set the texture coordinates of the block */
	inline void setTexture(const TexCoords& texture1, const TexCoords& texture2, const TexCoords& texture3, const TexCoords& texture4) {
		m_texturePos[0] = texture1; m_texturePos[1] = texture2; m_texturePos[2] = texture3; m_texturePos[3] = texture4;
	}

	inline TexCoords* getTexture() {return m_texturePos;}

private:
	// General
	int i_id;
	QString s_name;

	// Properties
	bool b_breakable;

	// Apparence
	QColor m_color;
	TexCoords m_texturePos[4];
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
