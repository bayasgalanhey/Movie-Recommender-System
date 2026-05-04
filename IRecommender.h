#ifndef IRECOMMENDER_H
#define IRECOMMENDER_H

#include <vector>
#include "Movie.h"      

class IRecommender {
public:
    /**
     * @brief Generate a list of recommended movies for the given user.
     * 
     * @param userId The unique ID of the user to recommend movies for.
     * @return std::vector<Movie> A list of movies recommended for this user.
     */
    virtual std::vector<Movie> recommendForUser(int userId) const = 0;

    /**
     * @brief Display recommended movies for the given user to the console.
     * 
     * @param userId The unique ID of the user to display recommendations for.
     */
    virtual void displayRecommendations(int userId) const = 0;

    /**
     * @brief Destroy the IRecommender object
     * Virtual destructor for interface cleanup.
     * 
     */
    virtual ~IRecommender() {}
};

#endif
