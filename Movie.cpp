#include "Movie.h"


#include <cmath>
#include <iostream>
#include <iomanip>



using namespace std;
/**
 * @brief Construct a new Movie:: Movie object
 * 
 */
Movie::Movie(){
    _id = 0;
    _name = "Unknown";
    _rating = 0.0;
    _genre = "Unknown";
    _ratingCount = 0;

}
/**
 * @brief Construct a new Movie:: Movie object
 * 
 * @param id 
 * @param name 
 * @param genre 
 * @param rating 
 */
Movie::Movie(int id, const std::string& name, const std::string& genre, double rating ){
    _id = id;
    _name = name;
    _rating = rating;
    _genre = genre;

   if (rating > 0) {
    _ratingCount = 1;   // one initial rating exists
    } else {
    _ratingCount = 0;   // no ratings yet
    }

}
/**
 * @brief Gets the Movie name
 * 
 * @return std::string 
 */
std::string Movie::getName()const {
    return _name;
}
/**
 * @brief Gets the movie rating
 * 
 * @return double 
 */
double Movie::getRating()const {
    return _rating;
}
/**
 * @brief gets the ID of the movie
 * 
 * @return int 
 */
int Movie::getID()const {
    return _id;
}
/**
 * @brief Gets the genre of the movie
 * 
 * @return std::string 
 */
std::string Movie::getGenre()const {
    return _genre;
}
/**
 * @brief Shows the information of the movie including the id, name , rating and genre.
 * 
 */
void Movie::displayInfo() const {
    cout << left << "ID: " << setw(4) << _id  << " | Name: " << setw(40) << _name  << " | Genre: " << setw(12) << _genre << " | Rating: " << fixed << setprecision(1) << _rating << endl;
}

/**
 * @brief When a user adds rating to a Movie. Average rating is updated of that movie.
 * 
 * @param rating 
 */
void Movie::addUserRating(double rating){
    //The rating cannot go out bounds so clamping to the bounderies.
    if(rating < 0.0){
        rating = 0.0;
    }
    if(rating > 10.0){
        rating = 10.0;
    }
    //Calculate the average rating
    double total = _rating * _ratingCount;
    total += rating;
    _ratingCount++;
    _rating = total/ _ratingCount;

}
/**
 * @brief It calculates a similarity score between this movie and another movie based on genre and rating.
 * 
 * @param other 
 * @return double 
 */
double Movie::similarityTo(const Movie& other) const{
    //Score is from 0 to 2 is the similarity score for movies.
    double score = 0.0;

    //if the genre is the same it will be similar
    if(_genre == other._genre){
        score += 1;
    }

    //Compares ratings of movies and similiar ratings will be similar movies.
    double diffRating = fabs(_rating -  other._rating);
    //Based on a 0-1 scale of similarity 
    double similarRating = 1.0 - (diffRating/10.0);
    //if the similarRating is negative number clamp to 0.
    if(similarRating < 0.0){
        similarRating = 0.0;
    }
    score += similarRating;
    return score;
    
}