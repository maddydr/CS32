//
//  Set.cpp
//  homework1
//
//  Created by Maddy Delos Reyes on 1/21/23.
//



#include "Set.h"
#include <iostream>
using namespace std;

Set::Set()
{
    m_size = 0;
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
    
    if (m_size >= 160) // can't insert another value, already at max
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
    int largerSize;
    bool larger = false;
    if (this->size() > other.size())
        largerSize = this->size();
    else
    {
        largerSize = other.size();
        larger = true;
    }
    
    if (larger == false)
    {
        for (int j = 0; j < largerSize; j++)
        {
            ItemType temp = this->m_array[j];
            this->m_array[j] = other.m_array[j];
            other.m_array[j] = temp;
        }
    }
    if (larger == true)
    {
        for (int k = 0; k < largerSize; k++)
        {
            ItemType temp = other.m_array[k];
            other.m_array[k] = this->m_array[k];
            this->m_array[k] = temp;
        }
    }
    
    int temp = this->m_size;
    this->m_size = other.m_size;
    other.m_size = temp;
    
}

