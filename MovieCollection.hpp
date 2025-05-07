#pragma once

#include <map>
#include <vector>
#include "Movie.hpp"

class MovieCollection{

    private:

        std::map<char, std::vector<Movie<double>>> moviesByLetter;

    public:

        std::map<char, std::vector<Movie<double>>>& getMoviesByLetter();
        std::vector<Movie<double>> getAllMovies();
        void addMovie(const Movie<double>& movie);

};

std::ostream& operator<<(std::ostream& os, MovieCollection& collection);