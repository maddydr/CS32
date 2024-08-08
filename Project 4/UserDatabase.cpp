#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>

#include <iostream> // !!!!! DELETE THIS BEFORE TURNING IN
using namespace std;

void UserDatabase::makeLower(string &input) const
{
    string lowercaseInput = "";
    for (int i = 0; i < input.size(); i++)
    {
        char c = input[i];
        lowercaseInput += (tolower(c));
    }
    input = lowercaseInput;
    return;
}


UserDatabase::UserDatabase()
{
  
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
        return false;
    
    string name;
    while (getline(infile,name))
    {
        vector<string> movieHist;
        
        string email;
        string nMovies;
        string movie;
        
        
       // getline(infile, name); // get the name, email, num movies, and next line if they have seen a movie
        //cout << "this is the name " << name << endl;
        getline(infile, email);
        getline(infile, nMovies);
        getline(infile, movie);
        
        int numMovies = stoi(nMovies);
        
        for (int i = 0; i < numMovies; i++)
        {
            makeLower(movie);
            movieHist.push_back(movie);
            getline(infile, movie);
        }

        userTree.insert(email, User(name, email, movieHist));
    }
    
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    return &userTree.find(email).get_value();
}
