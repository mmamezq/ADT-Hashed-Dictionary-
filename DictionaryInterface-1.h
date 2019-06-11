

#ifndef _DICTIONARY_INTERFACE
#define _DICTIONARY_INTERFACE

//#include "NotFoundException.h"

template<class KeyType, class ItemType>
class DictionaryInterface 
{
public:   
   /** Boolean function to determine whether dictionary is empty */
   virtual bool isEmpty() const = 0;
   
   /** Provides number of entries in dictionary. */
   virtual int getNumberOfItems() const = 0;
   
   /** Insert item to dictionary.
    Pre-condition: Entry is different from entries in dictionary - no duplicates.
    Post-condition: If successful, entry will be placed in correct alphabetical location.
   
   Parameters: 
   searchKey:  Search key correlated to dictionary entry.
   newItem:  The item to add to the dictionary.
   
   Boolean return:
   return  True if item was successfully added, or false if not. */
   virtual bool add(const KeyType& searchKey, const ItemType& newItem) = 0;
   
   /** Removes item from dictionary
   
    Parameter: searchKey  The search key of the item to be removed.
    @return  True if the item was successfully removed, or false if not. */
   virtual bool remove(const KeyType& searchKey) = 0;
   
   /** Removes all entries from this dictionary. */
   virtual void clear() = 0;
   
   /** Retrieves an item with a given search key from a dictionary.
  
    @param searchKey  The search key of the item to be retrieved.
    @return  The information associated with the search key.
    @throw  NotFoundException if the item does not exist. */
   virtual ItemType getItem(const KeyType& searchKey) const /*throw (NotFoundException)*/ = 0;
   
   /** Verifies whether the dictionary contains the element in question.
    @post  The dictionary is unchanged.
    @param searchKey  The search key of the item to be retrieved.
    @return  True if an item with the given search key exists in the dictionary. */
   virtual bool contains(const KeyType& searchKey) const = 0;
   
   /** Traverses this dictionary and calls a given client function once for each item.
    @post  The given function’s action occurs once for each item in the
       dictionary and possibly alters the item.
    @param visit A client function. */
   virtual void traverse(void visit(ItemType&)) const = 0;
}; // end DictionaryInterface

#endif
