#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include<cctype>
using namespace std;

//HELPER FUNCTIONS FOR MOVIEDATABASE
void MovieDatabase::makeLower(string &input) const
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

vector<Movie*> MovieDatabase::getVector(TreeMultimap<string, Movie>::Iterator treeIterator) const
{
    vector<Movie*> moviePtrs;
    while (treeIterator.is_valid())
    {
        moviePtrs.push_back(&treeIterator.get_value());
        treeIterator.advance();
    }
    return moviePtrs;
    
}


MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    // load movie ID
    //load movie name
    //load release year
    //load entire director line
    //helper function: make a empty string, if not a comma, += to empty string go until null char? '\0'
    
    ifstream infile(filename);
    
    if (!infile)
        return false;
    
    string movieId;
    while (getline(infile, movieId))
    {
        string movieName;
        string releaseYr;
        string directors;
        string actors;
        string genres;
        string rating; // need to cast this to a bool?
        
        getline(infile, movieName);
        getline(infile, releaseYr);
        getline(infile, directors);
        getline(infile, actors);
        getline(infile, genres);
        getline(infile, rating);
        
        // MUST BE A CASE INSENSITIVE SEARCH !!! CHANGE
        makeLower(movieId);
        makeLower(directors);
        makeLower(actors);
        makeLower(genres);
        
        vector<string> dataDirs = parseCommas(directors); // create vectors without commas
        vector<string> dataActors = parseCommas(actors);
        vector<string> dataGenre = parseCommas(genres);
        // same movie object inserted every time
        Movie movieObj = Movie(movieId, movieName, releaseYr, dataDirs, dataActors, dataGenre, stof(rating));
        
        // tree based on ID's
        MovieTree_ID.insert(movieId, movieObj);
        
        //tree based on director
        for (int i = 0; i < dataDirs.size(); i++)
        {
            MovieTree_directors.insert(dataDirs[i], movieObj);
        }
        
        //tree based on actors
        for (int i = 0; i < dataActors.size(); i++)
        {
            MovieTree_actors.insert(dataActors[i], movieObj);
        }
        
        //tree based on genres
        for (int i = 0; i < dataGenre.size(); i++)
        {
            MovieTree_genres.insert(dataGenre[i], movieObj);
        }
        //    }
        
        string extraLine;
        getline(infile, extraLine); // CHECK THIS???? SPEC SAYS THERE MIGHT OR MIGHT NOT BE EMPTY LINE AFTER LAST MOVIE
        
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string currID = id;
    makeLower(currID);
    return &MovieTree_ID.find(currID).get_value();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    //user iterator and go through entire vector don't keep making a new iterator by calling find
    vector<Movie*> moviePtrs;
    string currDirector = director;
    makeLower(currDirector);
    moviePtrs = getVector(MovieTree_directors.find(currDirector)); // passing an iterator to helper function to return a vector of pointers to all the movies
    return moviePtrs;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector <Movie*> moviePtrs;
    string currActor = actor;
    makeLower(currActor);
    moviePtrs = getVector(MovieTree_actors.find(currActor));
    return moviePtrs;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector <Movie*> moviePtrs;
    string currGenre = genre;
    makeLower(currGenre);
    moviePtrs = getVector(MovieTree_genres.find(currGenre));
    return moviePtrs;
}


vector<string> MovieDatabase::parseCommas(std::string entireLine) // helper function to return a vector with all the actors in a vector
{
    string pushString = "";
    vector<string> entireList;
    
    for (int i = 0; i < entireLine.size(); i++)
    {
        if (entireLine[i] != ',')
            pushString += entireLine[i];
        else if (entireLine[i] == ',' || entireLine[i] == '\n')// must have encountered a comma or end of director string
        {
            entireList.push_back(pushString);
            pushString = ""; // initialize string back to empty
        }
    }
    entireList.push_back(pushString); // pushback the last one without a comma after it
    return entireList;
    
    
}

