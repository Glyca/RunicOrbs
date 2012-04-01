#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H

/*! A slot of an inventory */
class InventorySlot
{
public:
	InventorySlot();

	inline int id() const {return i_id;}
	inline int amount() const {return i_amount;}

	inline void setId(const int id) {i_id = id;}
	inline void setAmount(const int quantity) {i_amount = quantity;}

	/*! Try to remove an item of this slot */
	bool removeOne();
	/*! Try to remove an item of the specified id to this slot */
	bool removeOne(const int id);
	/*! Try to add an item to this slot */
	bool addOne();
	/*! Try to add an item of the specified id to this slot */
	bool addOne(const int id);

private:
	int i_id; //! The item id
	int i_amount; //! The quantity
};

#endif // INVENTORYSLOT_H
