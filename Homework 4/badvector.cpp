
  // Remove the movies in v with a rating below 50 and destroy them.
  // It is acceptable if the order of the remaining movies is not
  // the same as in the original vector.
void removeBad(vector<Movie*>& v)
{
    vector<Movie*>::iterator it;
    it = v.begin();
    
    while (it != v.end())
    {
        if ((*it)->rating() < 50)
        {
            delete *it;
            it = v.erase(it);
        }
        else
            it++;
    }
}

