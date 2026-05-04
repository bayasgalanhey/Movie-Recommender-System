#ifndef USER_H
#define USER_H

#include "IEntity.h"
#include <vector>
#include <string>
#include <utility>


class User : public IEntity {
public:

    /**
     * @brief Default constructor.
     * Creates a user with empty name and ID = 0.
     */
    User();

    /**
     * @brief Constructs a User with a name and ID.
     * @param userName Name of the user.
     * @param userID Unique identifier for the user.
     */
    User(const std::string& userName, int userID);

    /**
     * @brief Retrieves the user's name.
     * @return The user's name as a string.
     */
    std::string getName() const override;

    /**
     * @brief Retrieves the user's ID.
     * @return The user's unique ID number.
     */
    int getID() const override;

    /**
     * @brief Records a rating for a movie.
     * 
     * If the movie was previously rated by the user, the rating is updated.
     * Otherwise, the movie and its rating are added to the user's list.
     * 
     * @param movieId ID of the movie being rated.
     * @param rating Rating value given by the user (0–10).
     */
    void rateMovie(int movieId, double rating);

    /**
     * @brief Gets all movies rated by the user.
     * 
     * Each entry in the vector contains:
     * - movie ID
     * - rating the user assigned
     * 
     * @return A vector of (movieId, rating) pairs.
     */
    std::vector<std::pair<int, double>> getRatedMovies() const;

    /**
     * @brief Calculates a similarity score between this user and another.
     * 
     * Uses Cosine Similarity based on the ratings of movies both users have seen.
     * 
     * @param other The other User object to compare against.
     * @return A similarity score between 0.0 and 1.0.
     */
    double similarityTo(const User& other) const;

    /**
     * @brief Displays user information.
     * 
     * Shows user name, ID, and all rated movies.
     */
    void displayInfo() const override;

private:

    /** @brief The user's name. */
    std::string _userName;

    /** @brief The user's unique identifier. */
    int _userID;

    /**
     * @brief List of movies rated by the user.
     * 
     * Each pair stores:
     * - movie ID  
     * - rating value  
     */
    std::vector<std::pair<int, double>> _ratedMovies;
};

#endif // USER_H
