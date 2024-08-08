
  // Remove the odd integers from v.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original vector.
void removeOdd(vector<int>& v)
{
    vector<int>::iterator li;
    li = v.begin();
    while (li != v.end())
    {
        if (*li % 2 != 0)
            li = v.erase(li);
        else
            li++;
    }
    
}

