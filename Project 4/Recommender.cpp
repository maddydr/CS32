#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <unordered_map>
#include <algorithm>

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database)
{
    m_userDataBase = &user_database;
    m_movieDataBase = &movie_database;
    // Replace this line with correct code.
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if (movie_count <= 0) //can't request movies for negative or 0 amount
        return vector<MovieAndRank>();
    
    unordered_map<string, int> compatibilityScoreMap; // create one big hash map to hold ID's and scores
    unordered_map<string, int>::iterator compatibilityItr = compatibilityScoreMap.begin(); // used to iterate through large hash table to check if movie already in table

    vector<string> watchHist;
    watchHist = m_userDataBase->get_user_from_email(user_email)->get_watch_history(); // gets the string of movieId's
    
    vector<Movie*> movieObjPtrs; // holds a pointer to the user's actual movie objects
    for (int i = 0; i < watchHist.size(); i++)
    {
        movieObjPtrs.push_back(m_movieDataBase->get_movie_from_id(watchHist[i])); // gets entire history of movie object pointers
    }
    
                                                                          ////////////////////DIRECTORS //////////////
    
    unordered_map<string, int> mapOfDirectors; // create a map of just directors as keys, and scores correlated with that director
    unordered_map<string, int>::iterator DirectorItr; //iterator for the director map
    for(int i = 0; i < movieObjPtrs.size(); i++)
    {
        vector<string> directors = movieObjPtrs[i]->get_directors(); // get directors from a single movie object
        for (int j = 0; j < directors.size(); j++)
        {
//            DirectorItr = mapOfDirectors.find(directors[j]);
//            if (DirectorItr == mapOfDirectors.end())
                mapOfDirectors[directors[j]] += 20;
//            else
//                DirectorItr->second += 20;
        }
    }


    //goal: put instances of entire movie database with same director into hash table
    DirectorItr = mapOfDirectors.begin();
    compatibilityItr = compatibilityScoreMap.begin();
    for (; DirectorItr != mapOfDirectors.end(); DirectorItr++)
    {
        vector<Movie*> moviesWithCommoneDirector = m_movieDataBase->get_movies_with_director(DirectorItr->first);
        for (int i = 0; i < moviesWithCommoneDirector.size(); i++)
        {
            compatibilityItr = compatibilityScoreMap.find(moviesWithCommoneDirector[i]->get_id()); // get the ID of the movie to check if already in hash map
            // checks if the movie ID is already been watched by User
            if (find(watchHist.begin(), watchHist.end(), moviesWithCommoneDirector[i]->get_id()) == watchHist.end())
            {
                if (compatibilityItr == compatibilityScoreMap.end()) // director not found in map yet
                    compatibilityScoreMap[moviesWithCommoneDirector[i]->get_id()] = DirectorItr->second;
                else
                    compatibilityItr->second += DirectorItr->second;
            }
        }
    }

                                                                      ////////////////////ACTORS /////////////////

    unordered_map<string, int> mapOfActors;
    unordered_map<string, int>::iterator actorItr;
    for(int i = 0; i < movieObjPtrs.size(); i++)
    {
        vector<string> actors = movieObjPtrs[i]->get_actors();
        for (int j = 0; j < actors.size(); j++)
        {
            actorItr = mapOfActors.find(actors[j]);
            if (actorItr == mapOfActors.end())
                mapOfActors[actors[j]] = 30;
            else
                actorItr->second += 30;
        }
    }

    actorItr = mapOfActors.begin();
    compatibilityItr = compatibilityScoreMap.begin();
    for(; actorItr != mapOfActors.end(); actorItr++)
    {
        vector<Movie*> moviesWithCommonActor = m_movieDataBase->get_movies_with_actor(actorItr->first);
        for (int i = 0; i < moviesWithCommonActor.size(); i++)
        {
            compatibilityItr = compatibilityScoreMap.find(moviesWithCommonActor[i]->get_id());
            if (find(watchHist.begin(), watchHist.end(), moviesWithCommonActor[i]->get_id()) == watchHist.end())
            {
                if (compatibilityItr == compatibilityScoreMap.end())
                    compatibilityScoreMap[moviesWithCommonActor[i]->get_id()] = actorItr->second;
                else
                    compatibilityItr->second += actorItr->second;
            }
        }
    }
    
    
    
    
                                                                          ////////////////////GENRES //////////////

    unordered_map<string, int> mapOfGenres;
    unordered_map<string, int>::iterator itr; // iterator to iterate map of GENRES
    for (int i = 0; i < movieObjPtrs.size(); i++)
    {
        vector<string>genres = movieObjPtrs[i]->get_genres(); // create a vector of all the genres of a single movie
        for (int j = 0; j < genres.size(); j++)
        {
            itr = mapOfGenres.find(genres[j]);
                if (itr == mapOfGenres.end()) // does the genre already exist in the genre hash table?
                    mapOfGenres[genres[j]] = 1;
                else
                    itr->second++;
        }
    }
    

    
    
    // goal: put all instances of the movie with the same genre into the large hash table
    itr = mapOfGenres.begin();
    compatibilityItr = compatibilityScoreMap.begin(); // used to iterate through large hash table to check if movie already in table
    for (; itr != mapOfGenres.end(); itr++)
    {
        vector<Movie*> moviesWithCommonGenre = m_movieDataBase->get_movies_with_genre(itr->first);
        for (int i = 0; i < moviesWithCommonGenre.size(); i++)
        {
            compatibilityItr = compatibilityScoreMap.find(moviesWithCommonGenre[i]->get_id()); // does the movie already exist in the hash table?
            if (find(watchHist.begin(), watchHist.end(), moviesWithCommonGenre[i]->get_id()) == watchHist.end())
            {
                if (compatibilityItr == compatibilityScoreMap.end()) // not in map yet, so make instance of it
                    compatibilityScoreMap[moviesWithCommonGenre[i]->get_id()] += itr->second; //putting in big hash table all the movies that share some common genre with user's history
                
                else
                    compatibilityItr->second += itr->second; // else its already in the compatibility map, so add points to it
            }
        }
        
    }
    
    
    
    // creating MovieRank objects to create a vector to be able to return all correctly sorted information
    vector<MovieAndRank> finalCompatibilityScores;
    compatibilityItr = compatibilityScoreMap.begin();
    for (; compatibilityItr != compatibilityScoreMap.end(); compatibilityItr++)
    {
        MovieAndRank movieRankobj(compatibilityItr->first, compatibilityItr->second); // pass in movie and score
        finalCompatibilityScores.push_back(movieRankobj);
    }
    sort(finalCompatibilityScores.begin(), finalCompatibilityScores.end(), [this](const MovieAndRank& a, const MovieAndRank& b) -> bool
    {
        if (a.compatibility_score != b.compatibility_score)
            return a.compatibility_score > b.compatibility_score;
        
        if (a.compatibility_score == b.compatibility_score && m_movieDataBase->get_movie_from_id(a.movie_id)->get_rating() == m_movieDataBase->get_movie_from_id(b.movie_id)->get_rating())
        {
            return (m_movieDataBase->get_movie_from_id(a.movie_id)->get_title() < m_movieDataBase->get_movie_from_id(b.movie_id)->get_title());
        }
        else
            return (m_movieDataBase->get_movie_from_id(a.movie_id)->get_rating() > m_movieDataBase->get_movie_from_id(b.movie_id)->get_rating());
        
            
    });
    
    if (movie_count > finalCompatibilityScores.size()) // requested too many movies, only return as many as in database
        return finalCompatibilityScores;
    
    
    for (int i = finalCompatibilityScores.size() - 1; i > movie_count; i--)
    {
        finalCompatibilityScores.pop_back(); // only want to return the correct # of movies they request
    }
    

    
    return finalCompatibilityScores;
}


    
    
    
    // retrieve actual movie from ID ----> must do
    
    // use the director tree to find the director and all the movies that returned
    //use the actor tree, find all the movies some actor has done
    //use genre tree to find all movies with associated genre

