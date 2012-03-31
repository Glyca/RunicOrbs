#ifndef BLOCKS_H
#define BLOCKS_H

class BlockDescriptor;

const int MAX_BLOCKID = 3;

/*! The Blocks class holds all informations about any blocks (such as resistance, breakability...) stored in BlockDescriptor s */
class Blocks
{
public:
	Blocks();

	static BlockDescriptor AIR;
	static BlockDescriptor STONE;
	static BlockDescriptor DIRT;

	/*! Give the BlockDescriptor of the given block ID */
	static BlockDescriptor& byId(const int id);

private:
	inline static Blocks& instance() {
		static Blocks blocks;
		return blocks;
	}
	BlockDescriptor* m_blockDescriptors[MAX_BLOCKID];
};

#endif // BLOCKS_H
