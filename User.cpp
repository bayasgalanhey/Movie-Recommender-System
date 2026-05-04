#include "User.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * @brief Construct a new User:: User object
 * Default constructor.
 */
User::User(){
    _userName = "Unknown";
    _userID = 0;

}
/**
 * @brief Construct a new User:: User object 
 * Parameterized constructor setting the user id and the name 
 * 
 * @param userName 
 * @param userID 
 */
User::User(const std::string& userName, int userID){
    _userName = userName;
    _userID = userID;
}
/**
 * @brief Gets the user's name
 * 
 * @return std::string 
 */
std::string User::getName() const {
   
    return _userName;
}
/**
 * @brief Gets the users id
 * 
 * @return int 
 */
int User::getID() const {
    
    return _userID;
}
/**
 * @brief Rates the movie based on the id on a scale of 0-10.
 * 
 * @param movieId 
 * @param rating 
 */
void User::rateMovie(int movieId, double rating){
    //Check if the rating is within the boundary of the scale 0-10.
    if(rating < 0.0){
        cout << "Enter valid rating from 0.0 to 10" << endl;
        return;
    }else if (rating > 10.0){
        cout << "Enter valid rating from 0.0 to 10" << endl;
        return;
    }
    //Look if there is a existing rating of the movie
    for(size_t i = 0; i < _ratedMovies.size(); i++){
        if(movieId ==_ratedMovies[i].first){
            _ratedMovies[i].second = rating;
            return;
        }
    }
    //There is no existing rating for the movie
    _ratedMovies.push_back({movieId, rating});
}
/**
 * @brief Gets the rated movies
 * 
 * @return vector<pair<int, double>> 
 */
vector<pair<int, double>> User::getRatedMovies() const{
    
    return _ratedMovies;

}

/**
 * @brief Calculates a similarity score between this user and another.
 * 
 * Uses Cosine Similarity: dot(A,B) / (||A|| * ||B||)
 * 
 * @param other The other User object.
 * @return double Similarity score between 0 and 1.
 */
double User::similarityTo(const User& other) const {
    double dotProduct = 0.0;
    double normA = 0.0;
    double normB = 0.0;

    const vector<pair<int, double>>& otherRatings = other.getRatedMovies();

    // Calculate norms and dot product for common movies
    // For a more efficient implementation, we could use a map
    for (size_t i = 0; i < _ratedMovies.size(); i++) {
        normA += _ratedMovies[i].second * _ratedMovies[i].second;
        
        for (size_t j = 0; j < otherRatings.size(); j++) {
            if (_ratedMovies[i].first == otherRatings[j].first) {
                dotProduct += _ratedMovies[i].second * otherRatings[j].second;
            }
        }
    }

    for (size_t j = 0; j < otherRatings.size(); j++) {
        normB += otherRatings[j].second * otherRatings[j].second;
    }

    if (normA == 0 || normB == 0) return 0.0;

    double similarity = dotProduct / (sqrt(normA) * sqrt(normB));
    return similarity;
}

/**
 * @brief prints detailed information about the user, including their name, ID, 
 * and all the movies they have rated.
 * 
 */
void User::displayInfo() const {
    //Displays users name and id
    cout << "User: " << _userName << " ID: " << _userID << endl;
    //Prints the Rated movies
    cout << "Rated Movies: " << endl;
    //If the movie is not rated it will show no rating yet
    if(_ratedMovies.empty()){
        cout << "No ratings yet" << endl;
        return;
    }

    //Loop over the rated movies and displays the move id and the movie rating
    for(size_t i = 0; i < _ratedMovies.size(); i++){ 
        
        cout <<"Movie ID: " << _ratedMovies[i].first << " " << "| Movie rating: " << _ratedMovies[i].second << endl;
    }

}
