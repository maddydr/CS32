//
//  Set.cpp
//  CS32 Proj2
//
//  Created by Maddy Delos Reyes on 1/28/23.
//

#include "Set.h"

#include <iostream>
using namespace std;

Set::Set()
{
    dummy.next = nullptr; //initialize private members
    dummy.prev = nullptr;
    head = &dummy;
    m_counter = 0;
}

Set::Set(const Set& other) // copy const ---- refers to the set it is copying from as OTHER
{
    dummy.next = nullptr;
    dummy.prev = nullptr;
    m_counter = other.m_counter; //copy over counters to the new Set
    head = &dummy;
    
    Node* original = other.head;
    Node* newest = head;
    
    while (original->next != nullptr) // travese though the original set until no items left to insert
    {
        Node* brandNew = new Node;
        brandNew->value = original->next->value;
        brandNew->prev = newest;
        brandNew->next = nullptr;
        newest->next = brandNew;
        newest = newest->next;
        original = original->next;
    }
        
}

Set& Set::operator=(const Set &rhs) //operator equals function
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
        m_counter = rhs.m_counter;
    }
    return *this;
}

Set::~Set()
{
    
    if (dummy.next != nullptr)
    {
        Node* toBeDeleted = dummy.next; // ensures at least 1 nodes in the list
        
        while(toBeDeleted != nullptr) // while there are still values in the list, must delete
        {
            Node* temp = toBeDeleted->next;
            delete toBeDeleted;
            toBeDeleted = temp;
        }
    }
}

bool Set::empty() const
{
    if (dummy.next == nullptr)
        return true;
    return false;
}

int Set::size() const
{
    return m_counter;
}

bool Set::insert(const ItemType& value)
{
    // find correct position new value should go into
    // upate its previous's next pointer
    // update the new nodes pointer to point to following node
    // update the following node's previous pointer
    
    Node* p = &dummy;
    while(p->next != nullptr)
    {
        if (p->next->value == value) // if item is already in the list
            return false;
        if (p->next->value < value) //want the pointer to stop right before the next node is inserted to late initialize next and prev pointers
            p = p->next;
        else
            break;
    }
    

    Node* latest = new Node;
    latest->value = value; //add all values to new node
    latest->prev = p;
    latest->next = p -> next;
    if (p->next != nullptr) // only need to update the following node if there even is one
        p->next->prev = latest;
    p->next = latest;
    m_counter++;
    return true;

}

bool Set::erase(const ItemType& value)
{
    Node* p = &dummy;
    
    
    while (p->next != nullptr)
    {
        if (p->next != nullptr && p->next->value == value) // want to stop the pointer right before the one that must be deleted
            break;
        p = p->next; //keep incrementing the pointer until we find the value to delete
    }
    
    if (p->next == nullptr && p->value != value) // at the end of the list, value not present, return now
        return false;
    
    if (p->next->value == value)
    {
        Node* deleteme = p->next; // a temporary pointer to point at the node that must be deleted
        p->next = deleteme->next; // reassign the next pointer to point to whatever is after the node that is being deleted
        if (deleteme->next != nullptr) // only update the following's previous pointer if there even is one
            deleteme->next->prev = p;
        else
            p->next = nullptr;

        delete deleteme;
        m_counter--;
        return true;
    
    }
    return false;
}

bool Set::contains(const ItemType &value) const
{
    Node* p = dummy.next;
    if (p == nullptr) // empty list
        return false;
    
    while (p != nullptr) // traverse through entire list
    {
        if(p ->value == value)
            return true;
        p = p->next;
    }
    return false;
    
}
bool Set::get(int pos, ItemType &value) const
{
    if (pos >= m_counter || pos < 0) // check for valid position
        return false;
    Node* p = dummy.next;
    int counter = 0;
    // make a counter and traverse through list
    while (p != nullptr)
    {
        if(counter < pos) // need to find item that is 'pos' bigger than other items
        {
            p = p->next;
            counter++;
        }
        else
            break;
    }
    if (counter == pos) // must check is it matches because could have broken from loop if it was a nullptr
    {
        value = p->value;
        return true;
    }
    return false;
}

void Set::swap(Set &other)
{
    // swapping the sizes of each array
    int size = other.m_counter; // swap private variables
    other.m_counter = this->m_counter;
    this->m_counter = size;
    
    Node* temp = this->dummy.next; // swapping the node's next pointers
    this->dummy.next = other.dummy.next;
    other.dummy.next = temp;
}




void unite(const Set& s1, const Set& s2, Set& result)
{
    ItemType value;
    
    // empty the result list if there is items in there
    int k = 0;
    while (result.get(k,value))
    {
        result.erase(value);
    }
    
    for (int i = 0; ; i++) // infinitely traverses through the sets until there are no values left
    {
        if (s1.get(i, value))
        {
            result.insert(value); // insert already handles duplicates

        }
        if (s2.get(i, value))
            result.insert(value);
        if (!s1.get(i,value) && !s2.get(i,value)) // break once you have gone through both sets entirely
            break;
    }
    
}



void butNot(const Set& s1, const Set& s2, Set& result)
{
    ItemType value;
    
    // empty the result list if there is items in there
    
    int k = 0;
    while (result.get(k,value))
    {
        result.erase(value);
    }
    
    
    
    
    result = s1; // pass in all values from s1
    
    Set copied = s2; //makes a copy of all of set2 values so we don't actually modify them
    
    ItemType value2;
    
    int i = 0; //never need to increment this because we erase values in the set 
    
    while (copied.get(i,value2)) // while there are values in the set 2
    {
        copied.get(i,value2);
        if (result.contains(value2)) // check if result contains this value, if so must delete it
            result.erase(value2);
        copied.erase(value2); // erase the value to traverse to next value
    }
    
    
}




