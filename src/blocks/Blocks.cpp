#include "Blocks.h"
#include "BlockDescriptor.h"
#include "CubeBlock.h"
#include "Log.h"
#include "TorchBlock.h"

const bool B_BREAKABLE = true, B_UNBREAKABLE = false;
const bool B_CANPASSTROUGH = true, B_CANNOTPASSTROUGH = false;

BlockDescriptor Blocks::AIR(0, "air", B_UNBREAKABLE, B_CANPASSTROUGH, 0);
CubeBlock Blocks::STONE(1, "stone", B_BREAKABLE, B_CANNOTPASSTROUGH, 10);
CubeBlock Blocks::DIRT(2, "dirt", B_BREAKABLE, B_CANNOTPASSTROUGH, 5);
CubeBlock Blocks::GRASS(3, "grass", B_BREAKABLE, B_CANNOTPASSTROUGH, 6);
TorchBlock Blocks::TORCH(4, "torch", B_BREAKABLE, B_CANPASSTROUGH, 2);

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
	m_blockDescriptors[4] = &Blocks::TORCH;
	linfo(Channel_Blocks, QObject::tr("Blocks catalog created, having %1 blocks.").arg(MAX_BLOCKID));
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
