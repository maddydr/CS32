#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"


class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    std::vector<std::string> parseCommas(std::string entireLine);
    // 4 different trees to search by ID, directors, actors, or genre
    TreeMultimap<std::string, Movie> MovieTree_ID;
    TreeMultimap <std::string, Movie> MovieTree_directors;
    TreeMultimap <std::string, Movie> MovieTree_actors;
    TreeMultimap <std::string, Movie> MovieTree_genres;
    void makeLower(std::string &input) const;
    std::vector<Movie*> getVector(TreeMultimap<std::string, Movie>::Iterator) const;
};

#endif // MOVIEDATABASE_INCLUDED
