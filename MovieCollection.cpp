#include "MovieCollection.hpp"

std::map<char, std::vector<Movie<double>>>& MovieCollection::getMoviesByLetter(){
    return this->moviesByLetter;
}

std::vector<Movie<double>> MovieCollection::getAllMovies(){
    std::vector<Movie<double>> w;
    for(auto letter : this->moviesByLetter){
        w.insert(w.end(), letter.second.begin(), letter.second.end());
    }
    return w;
}

void MovieCollection::addMovie(const Movie<double>& movie){
    char letter = movie.getTitle()[0];
    this->moviesByLetter[letter].push_back(movie);
}

std::ostream& operator<<(std::ostream& os, MovieCollection& collection){
    for(auto letter : collection.getMoviesByLetter()){
        os << "=== " << letter.first << " ===" << std::endl;
        for(auto movie : letter.second){
            os << movie << std::endl;
        }
        os << std::endl;
    }
    return os;
}