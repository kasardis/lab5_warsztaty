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

void MovieCollection::sortMovies(){
    for(auto& letter : moviesByLetter){
        std::sort(letter.second.begin(), letter.second.end());
    }
}

void MovieCollection::removeMoviesOlderThan(char letter, int year){
    struct OlderThan{
        int year;
        explicit OlderThan(int year) : year(year) {}

        bool operator()(const Movie<double>& movie) const {
            return movie.getYear() < this->year;
        }
    };

    auto rem = std::remove_if(this->moviesByLetter[letter].begin(), this->moviesByLetter[letter].end(), OlderThan(year));
    this->moviesByLetter[letter].erase(rem, this->moviesByLetter[letter].end());
}

double MovieCollection::getAverageTopRating(){
    struct SumMovies{
        double operator()(double current, const Movie<double>& movie) const{
            return current + movie.getTopRating();
        }
    };
    auto allMovies = this->getAllMovies();
    if(allMovies.size() == 0){
        return 0;
    }
    return std::accumulate(allMovies.begin(), allMovies.end(), 0.0, SumMovies()) / allMovies.size();
}

std::vector<Movie<double>> MovieCollection::getMoviesByDirector(const std::string& director){
    struct IfDirector{
        std::string director;
        explicit IfDirector(std::string director) : director(director) {}

        bool operator()(const Movie<double>& movie){
            if(std::holds_alternative<std::string>(movie.getDirector())){
                return director == std::get<std::string>(movie.getDirector());
            } else {
                return director == std::get<Movie<double>::Director>(movie.getDirector()).name;
            }
        }
    };

    std::vector<Movie<double>> directorMovies;
    std::vector<Movie<double>> allMovies = this->getAllMovies();
    std::copy_if(allMovies.begin(), allMovies.end(), std::back_inserter(directorMovies), IfDirector(director));
    return directorMovies;
}

std::optional<Movie<double>> MovieCollection::findMovieWithAverageAbove(double threshold){
    
    struct OverThreshold{
        double rating;
        explicit OverThreshold(double rating) : rating(rating) {}

        bool operator()(const Movie<double>& movie) const{
            return movie.getAverageRating() > rating;
        }
    };

    auto allMovies = this->getAllMovies();
    auto moviePtr = std::find_if(allMovies.begin(), allMovies.end(), OverThreshold(threshold));
    if(moviePtr != allMovies.end()){
        return *moviePtr;
    }
    return std::nullopt;
}