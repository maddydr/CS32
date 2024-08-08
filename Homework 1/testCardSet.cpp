//
//  testCardSet.cpp
//  homework1
//
//  Created by Maddy Delos Reyes on 1/23/23.
//

#include "CardSet.h"
#include "Set.h"
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
    CardSet s;
    s.add(690);
    s.add(4);
    s.add(2900000);
    s.print();
    assert(s.size() == 3);
    
    
    
    cout << "Passed all tests" << endl;
}
