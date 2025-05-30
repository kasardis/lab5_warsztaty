#pragma once

#include <string>
#include <variant>
#include <optional>
#include <list>
#include <iostream>

template<typename RatingType>
class Movie{

    public:

        struct Director{
            std::string name;
            int numberOfOscars;
            Director(std::string name, int numberOfOscars) : name{name}, numberOfOscars{numberOfOscars}{}
        };

    private:

        std::string title;
        int year;
        std::variant<Director, std::string> director;
        std::optional<std::string> description;
        std::list<RatingType> ratings;

    public:

        Movie(std::string title, int year, std::variant<Director, std::string> director, std::optional<std::string> description = std::nullopt) : 
            title{title}, year{year}, director{director}, description{description} {}

        std::string getTitle() const{
            return this->title;
        }

        int getYear() const{
            return this->year;
        }

        std::optional<std::string> getDescription() const{
            return this->description;
        }

        std::variant<Director, std::string> getDirector() const{
            return this->director;
        }

        std::list<RatingType> getRatings() const{
            return this->ratings;
        }

        RatingType getAverageRating() const{
            RatingType sum = 0;
            int counter = 0;
            for(RatingType rating : this->ratings){
                sum += rating;
                counter++;
            }
            if(counter == 0){
                return RatingType(0);
            }
            return sum/RatingType(counter);
        }

        RatingType getTopRating() const{
            RatingType max = RatingType(0);
            for(RatingType rating : this->ratings){
                if(rating > max){
                    max = rating;
                }
            }
            return max;
        }

        bool operator<(const Movie& other) const{
            if(this->title == other.getTitle()){
                return this->year < other.getYear();
            }
            return this->title < other.getTitle();
        }

        bool operator==(const Movie& other) const{
            return this->title == other.getTitle() && this->year == other.getYear();
        }

        Movie& operator+(RatingType rating){
            this->ratings.emplace_back(rating);
            return *this;
        }

};

template<typename RatingType>
std::ostream& operator<<(std::ostream& os, const Movie<RatingType>& movie){
    os << movie.getTitle() << " (" << movie.getYear() << "), Director: ";
    if(std::holds_alternative<std::string>(movie.getDirector())){
        os << std::get<std::string>(movie.getDirector());
    } else {
        os << std::get<typename Movie<RatingType>::Director>(movie.getDirector()).name << " (Oscars: " << std::get<typename Movie<RatingType>::Director>(movie.getDirector()).numberOfOscars << ")";
    }
    os << ", Avg: " << movie.getAverageRating() << ", Top: " << movie.getTopRating();
    if(movie.getDescription().has_value()){
        os << ", Description: " << movie.getDescription().value();
    }
    return os;
}