#ifndef _HASHED_DICTIONARY
#define _HASHED_DICTIONARY

#include "DictionaryInterface.h"
#include "HashedEntry.h"

//#include "NotFoundException.h"

const int TABLE_SIZE = 13;

template <class KeyType, class ItemType>
class HashedDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
   // Binary search tree of dictionary entries
   HashedEntry<KeyType, ItemType> *hashTable[TABLE_SIZE];
   
   //void traversalHelper(Entry<KeyType, ItemType>& theEntry);
    int getHashIndex(const KeyType&) const;
   
public:
   HashedDictionary();
   //HashedDictionary(const HashedDictionary<KeyType, ItemType>& dict);
   virtual ~HashedDictionary();
   
   // The declarations of the public methods appear here and are the
   // same as given in Listing 18-3 for the class ArrayDictionary.
   
    bool isEmpty() const;
    int getNumberOfItems() const;
    bool add(const KeyType& searchKey, const ItemType& newItem);
    bool remove(const KeyType& searchKey);
    void clear();
    ItemType getItem(const KeyType& searchKey) const; // throw (NotFoundException);
    bool contains(const KeyType& searchKey) const;
    void print();
    void printToFile();
   /** Traverses the items in this dictionary in sorted search-key order
    and calls a given client function once for each item. */
   void traverse(void visit(ItemType&)) const;
}; // end HashedDictionary

#include "HashedDictionary.cpp"
#endif