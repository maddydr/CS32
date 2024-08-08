//
//  CardSet.cpp
//  homework1
//
//  Created by Maddy Delos Reyes on 1/22/23.
//

#include "CardSet.h"
#include <iostream>

using namespace std;


CardSet::CardSet()
{

}

bool CardSet::add(unsigned long cardNumber)
{
    bool inserted = cardset.insert(cardNumber);
    return inserted;
}


int CardSet::size() const
{
    return cardset.size();
}

void CardSet::print() const
{
    for (int i = 0; i < cardset.size(); i++)
    {
        ItemType temp;
        cardset.get(i, temp);
        cout << temp << endl;

    }
}
