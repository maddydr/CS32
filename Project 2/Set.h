//
//  Set.hpp
//  CS32 Proj2
//
//  Created by Maddy Delos Reyes on 1/28/23.
//

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <iostream>


using ItemType = std::string; 

class Set
{
  public:
    Set(); // create an empty list with head pointing to null
    
    Set(const Set& other);
    
    Set& operator=(const Set& rhs);
    
    bool empty() const; // Return true if the set is empty, otherwise false.
    
    int size() const; // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    
    // Insert value into the set if it is not already present.  Return
    // true if the value is actually inserted.  Leave the set unchanged
    // and return false if value is not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    

    
    
    bool erase(const ItemType& value);
    
    // Remove the value from the set if it is present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
   
    bool contains(const ItemType& value) const;  // Return true if the value is in the set, otherwise false.
    
    bool get(int pos, ItemType& value) const;
    
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.

    void swap(Set& other);  // Exchange the contents of this set with the other one.
    
    ~Set();
    
  private:
    struct Node
    {
        ItemType value;
        Node* next;
        Node* prev;
    };
    
    Node dummy;
    Node* head;
    int m_counter;
    
   
    
};
#endif /* Set_hpp */


void unite(const Set& s1, const Set& s2, Set& result);
void butNot(const Set& s1, const Set& s2, Set& result);
