#include "Blocks.h"
#include "BlockDescriptor.h"

const bool B_BREAKABLE = true, B_UNBREAKABLE = false;

BlockDescriptor Blocks::AIR(0, "air", B_UNBREAKABLE);
BlockDescriptor Blocks::STONE(1, "stone", B_BREAKABLE);
BlockDescriptor Blocks::DIRT(2, "dirt", B_BREAKABLE);
BlockDescriptor Blocks::GRASS(3, "grass", B_BREAKABLE);

Blocks::Blocks()
{
	// We put nulls for all block ids.
	for(int i = 0; i < MAX_BLOCKID; ++i) {
		m_blockDescriptors[i] = NULL;
	}
	// Then we fill the internal array
	m_blockDescriptors[0] = &Blocks::AIR;
	m_blockDescriptors[1] = &Blocks::STONE;
	m_blockDescriptors[2] = &Blocks::DIRT;
	m_blockDescriptors[3] = &Blocks::GRASS;
	qDebug() << QObject::tr("Blocks catalog created, having %1 blocks.").arg(MAX_BLOCKID).toStdString().c_str();
}

BlockDescriptor& Blocks::byId(const int id)
{
	if(id < MAX_BLOCKID) {
		if(instance().m_blockDescriptors[id] != NULL) {
			return *instance().m_blockDescriptors[id];
		}
		else {
			return *instance().m_blockDescriptors[0];
		}
	}
	else {
		return *instance().m_blockDescriptors[0];
	}
}
