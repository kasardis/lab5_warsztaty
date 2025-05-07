#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Movie.hpp"

class MovieCollection{

    private:

        std::map<char, std::vector<Movie<double>>> moviesByLetter;

    public:

        std::map<char, std::vector<Movie<double>>>& getMoviesByLetter();
        std::vector<Movie<double>> getAllMovies();
        void addMovie(const Movie<double>& movie);

        void sortMovies();
        void removeMoviesOlderThan(char letter, int year);
        double getAverageTopRating();
        std::vector<Movie<double>> getMoviesByDirector(const std::string& director);
        std::optional<Movie<double>> findMovieWithAverageAbove(double threshold);

};

std::ostream& operator<<(std::ostream& os, MovieCollection& collection);