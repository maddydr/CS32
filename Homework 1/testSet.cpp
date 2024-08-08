//
//  main.cpp
//  homework1
//
//  Created by Maddy Delos Reyes on 1/21/23.
//
#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;



int main()
{
    Set s;
    assert(s.empty());
    assert(s.insert("Walter"));
    assert(!s.empty());
    assert(s.insert("maddy"));
    assert(s.insert("Jacob"));
    assert(s.insert("lola"));
    assert(!s.insert("Walter"));
    assert(s.insert(""));
    assert(s.insert("john"));
    assert(s.erase(""));

}




