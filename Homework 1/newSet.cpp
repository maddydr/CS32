//
//  newSet.cpp
//  homework1_newset
//
//  Created by Maddy Delos Reyes on 1/22/23.



#include "newSet.h"
#include <iostream>
using namespace std;

Set::Set()
{
    m_array = new ItemType[DEFAULT_MAX_ITEMS];
    m_size = 0;
    m_maxsize = 160;
}

Set::Set(int num)
{
    m_array = new ItemType[num];
    m_size = 0;
    m_maxsize = num;
    
}

// MAKE COPY CONST AND ASSN OPP
Set::Set(const Set& other) // copy constructor
{
    m_size = other.m_size;
    m_maxsize = other.m_maxsize;
    m_array = new ItemType[other.m_maxsize];
}

Set& Set::operator=(const Set& rhs) // OPERATOR EQUALS
{
    if (this != &rhs)
    {
        Set temp = rhs;
        swap(temp);
    }
    return *this;
}

Set::~Set()
{
    delete [] m_array;
}

bool Set::empty() const
{
    if (m_size == 0)
        return true;
    
    return false;
}

int Set::size() const
{
    return m_size;
}


bool Set::insert(const ItemType &value)
{
    
    if (m_size >= DEFAULT_MAX_ITEMS || m_size >= m_maxsize) // can't insert another value, already at max
        return false;
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i] == value)
            return false;
    }
    
    m_array[m_size] = value;
    m_size++;
    return true;
}

bool Set::erase(const ItemType &value)
{
    int index = 0;
    bool present = false;
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i] == value)
        {
            index = i;
            present = true;
        }
    }
    
    if (present == false)
        return false; // if value is not in array set, return now
    
    for (int j = index; j < (m_size - 1); j++)
    {
        m_array[j] = m_array[j + 1];
    }
    m_size--;
    return true;
}


bool Set::contains(const ItemType &value) const
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType &value) const
{
    ItemType temp;
    if (0 <= i && i < size())
    {
        for (int j = 0; j < m_size; j++)
        {
            temp = m_array[j];
            int greaterCount = 0;
            for (int k = 0; k < m_size; k++)
            {
                if(temp > m_array[k] && k != j)
                {
                    greaterCount++;
                }
            }
            if (greaterCount == i)
            {
                value = temp;
                return true;
            }
        }
    }
    return false;
}

void Set::swap(Set &other)
{
    ItemType* temp = this->m_array;
    this->m_array = other.m_array;
    other.m_array = temp;
    
    int temp1 = this->m_size;
    int temp2 = this->m_maxsize;
    
    this->m_size =  other.m_size;
    this->m_maxsize = other.m_maxsize;
    
    other.m_size = temp1;
    other.m_maxsize = temp2;
    
}


