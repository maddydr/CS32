
  // Remove the odd integers from li.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original list.
void removeOdd(list<int>& li)
{
    list <int>::iterator it;
    it = li.begin();
    
    while (it != li.end())
    {
        if (*it % 2 != 0)
        {
            // list<int>::iterator temp = it;
            it = li.erase(it);
        }
        else
            it++;
    }
}

