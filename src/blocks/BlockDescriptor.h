#ifndef BLOCKDESCRIPTOR_H
#define BLOCKDESCRIPTOR_H

#include <QColor>
#include <QString>

#include "Vector.h"
#include "gui/TextureManager.h" // TextureCoordinates

class BlockInfo;

/*! Holds informations about a type of block such as texture, resistance, name... */
class BlockDescriptor
{
public:
	BlockDescriptor() : i_id(0), s_name("undefined"), b_breakable(true) {}
	BlockDescriptor(const int id, const char* name, const bool breakable)
		: i_id(id), s_name(name), b_breakable(breakable) {}

	inline int id() const {return i_id;}

	/*! Set the texture coordinates of the block */
	inline void setTexture(const TexCoords& texture1, const TexCoords& texture2, const TexCoords& texture3, const TexCoords& texture4) {
		m_texturePos[0] = texture1; m_texturePos[1] = texture2; m_texturePos[2] = texture3; m_texturePos[3] = texture4;
	}

	inline TexCoords* getTexture() {return m_texturePos;}

private:
	// General
	int i_id;
	const char* s_name;

	// Properties
	bool b_breakable;

	// Apparence
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
