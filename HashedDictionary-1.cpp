/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

#include "HashedDictionary.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#ifndef HASHED_DICTIONARY_CPP
#define HASHED_DICTIONARY_CPP

//

using namespace std;

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	for (int index = 0; index < TABLE_SIZE; index++)
		hashTable[index] = nullptr;
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary()
{
	clear();
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &sKey) const
{
    unordered_map<KeyType, ItemType> mapper;
    typename std::unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(sKey) % TABLE_SIZE );
}

 template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
   // Create entry to add to dictionary
   HashedEntry<KeyType, ItemType>* entryToAddPtr =
                  new HashedEntry<KeyType, ItemType>(newItem, searchKey);
   
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   
   // Add the entry to the chain at itemHashIndex
   if (hashTable[itemHashIndex] == nullptr)
   {
      hashTable[itemHashIndex] = entryToAddPtr;
   }
   else
   {
      entryToAddPtr->setNext(hashTable[itemHashIndex]);
      hashTable[itemHashIndex] = entryToAddPtr;
   } // end if
   
   return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
   bool itemFound = false;
   
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   if (hashTable[itemHashIndex] != nullptr)
   {
      // Special case - first node has target
      if (searchKey == hashTable[itemHashIndex]->getKey())
      {
         HashedEntry<KeyType, ItemType>* entryToRemovePtr =
         hashTable[itemHashIndex];
         hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
         delete entryToRemovePtr;
         entryToRemovePtr = nullptr; // For safety
         itemFound = true;
      }
      else      {
         HashedEntry<KeyType, ItemType>* prevPtr = hashTable[itemHashIndex];
         HashedEntry<KeyType, ItemType>* curPtr = prevPtr->getNext();
         while ((curPtr != nullptr) && !itemFound )
         {
            // Found item in chain so remove that node
            if (searchKey == curPtr->getKey())
            {
               prevPtr->setNext(curPtr->getNext());
               delete curPtr;
               curPtr = nullptr; // For safety
               itemFound = true;
            }
            else // Look at next entry in chain
            {
               prevPtr = curPtr;
               curPtr = curPtr->getNext();
            } // end if
         } // end while
      } // end if
   } // end if
   
   return itemFound;
} // end remove

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const
{
    bool isempty = true;
    for (int index = 0; index < TABLE_SIZE; index++){
        if(hashTable[index] != nullptr)
            return false;
    }
    
    return isempty;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const
{
    int items = 0;
    HashedEntry<KeyType, ItemType>* entry;
    for (int index = 0; index < TABLE_SIZE; index++){
        entry = hashTable[index] -> getNext();
        while(entry != nullptr){
            items++;
            entry = entry -> getNext();
        }
    }
    return items;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	for (int x = 0; x < TABLE_SIZE; x++)
	{
		HashedEntry<KeyType, ItemType>* ptr = hashTable[x];
		while (ptr != nullptr)
		{
			hashTable[x] = ptr->getNext();
			ptr->setNext(nullptr);
			delete ptr;
			ptr = hashTable[x];
		}
	}
}

template <class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType& searchKey) const
{
    
    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType>* ptr = hashTable[itemHashIndex];
    while(ptr != nullptr && (ptr -> getKey() != searchKey )){
        ptr = ptr -> getNext();
    }
    
    return ptr -> getItem();
   
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType& searchKey) const
{
    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType>* ptr = hashTable[itemHashIndex];
    while(ptr != nullptr && ptr->getKey() != searchKey){
        ptr = ptr -> getNext();
    }
    
    if(ptr == nullptr)
        return false;
    else{
        if (ptr -> getKey() == searchKey)
            return true;
        else
            return false;
    }

}

template <class KeyType, class ItemType>
void  HashedDictionary<KeyType, ItemType>::print(){
    
    int average_age=0, total_values = 0;
    ItemType item;
    KeyType key;
    HashedEntry<KeyType, ItemType>* ptr;
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hashTable[i] != nullptr){
            ptr = hashTable[i];
            while(ptr != nullptr){
                item = ptr -> getItem();
                key = ptr -> getKey();
                cout << "Slot #" << i << ", ";
                cout << key << ", "
                << item << endl;
                average_age += ptr -> getItem();
                total_values++;
                ptr = ptr -> getNext();
            }
        }
    }
    cout << "Average Age is " << average_age / total_values;
}


template <class KeyType, class ItemType>
void  HashedDictionary<KeyType, ItemType>:: printToFile(){
    HashedEntry<KeyType, ItemType>* ptr;
    string file_name;
    int total_values = 0, average_age = 0;
    ItemType item;
    KeyType key;
    cout << "Enter filename to save to: ";
    cin >> file_name;
    ofstream myfile;
    myfile.open (file_name);
    
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hashTable[i] != nullptr){
            ptr = hashTable[i];
            while(ptr != nullptr){
                item = ptr -> getItem();
                key = ptr -> getKey();
                myfile << "Slot #" << i << ", ";
                myfile << key << ", "
                << item << endl;
                average_age += ptr -> getItem();
                ptr = ptr -> getNext();
                total_values++;
            }
        }
    }
    myfile << "Average Age is " << average_age / total_values;
    myfile.close();
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(ItemType&)) const
{
    int x = 0;
}

//HashedDictionary<std::string, int> xyz;


#endif