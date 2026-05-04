#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "IRecommender.h"
#include "User.h"
#include "Movie.h"

#include <vector>
#include <unordered_map>

 
class Recommender : public IRecommender {

private:

    /** @brief Map of all movies available in the system (ID -> Movie). */
    std::unordered_map<int, Movie> _movies;

    /** @brief Map of registered users in the system (ID -> User). */
    std::unordered_map<int, User> _users;

public:

    /**
     * @brief Retrieves the map of users.
     * @return Reference to internal map of User objects.
     */
    std::unordered_map<int, User>& getUsers();

    /**
     * @brief Retrieves the map of movies.
     * @return Reference to internal map of Movie objects.
     */
    std::unordered_map<int, Movie>& getMovies();

    /**
     * @brief Loads movies from a CSV file.
     * 
     * Expected format: id, name, genre, rating  
     * Handles quoted movie titles containing commas.
     * 
     * @param filename Path to the CSV file.
     */
    void loadMovies(const std::string& filename);

    /**
     * @brief Loads users into the system.
     * 
     * Default implementation loads no users.
     * Intended for later extension (e.g., loading from file).
     */
    void loadUsers();

    /**
     * @brief Adds a new user to the recommender system.
     * 
     * Ensures the user ID is unique before inserting.
     * 
     * @param name Name of the user.
     * @param id Unique identifier for the user.
     */
    void addUser(const std::string& name, int id);

    /**
     * @brief Generates movie recommendations for a user.
     * 
     * Uses similarity scoring on movies the user has rated.
     * Returns up to the top 5 recommended movies.
     *
     * @param userId ID of the target user.
     * @return Vector of recommended Movie objects.
     */
    std::vector<Movie> recommendForUser(int userId) const override;

    /**
     * @brief Displays recommendations for the given user.
     * 
     * Calls recommendForUser() and prints movie info
     * using Movie::displayInfo().
     * 
     * @param userId ID of the user.
     */
    void displayRecommendations(int userId) const override;
};

#endif // RECOMMENDER_H
