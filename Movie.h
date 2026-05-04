#ifndef MOVIE_H
#define MOVIE_H

#include "IEntity.h"
#include <string>


class Movie : public IEntity {

public:

    /**
     * @brief Default constructor.
     * Initializes an empty movie with default values.
     */
    Movie();

    /**
     * @brief Constructs a Movie with the given parameters.
     * @param id Unique identifier for the movie.
     * @param name Name/title of the movie.
     * @param genre Genre/category of the movie.
     * @param rating Initial rating (default is 0.0).
     */
    Movie(int id, const std::string& name, const std::string& genre, double rating = 0.0);

    /**
     * @brief Gets the movie's name.
     * @return The name of the movie.
     */
    std::string getName() const override;

    /**
     * @brief Gets the movie's current rating.
     * @return The average rating of the movie.
     */
    double getRating() const;

    /**
     * @brief Gets the movie's ID.
     * @return The unique identifier of the movie.
     */
    int getID() const override;

    /**
     * @brief Gets the movie's genre.
     * @return The genre of the movie.
     */
    std::string getGenre() const;

    /**
     * @brief Displays movie information to the console.
     */
    void displayInfo() const override;

    /**
     * @brief Adds a user rating and updates the average rating.
     * @param rating The rating value given by a user.
     */
    void addUserRating(double rating);

    /**
     * @brief Calculates similarity between this movie and another.
     * 
     * The similarity metric is implementation-specific and may consider 
     * attributes such as genre, rating, etc.
     * 
     * @param other The other Movie object to compare against.
     * @return A similarity score.
     */
    double similarityTo(const Movie& other) const;

private:

    /** @brief Title of the movie. */
    std::string _name;

    /** @brief Current average rating of the movie. */
    double _rating;

    /** @brief Unique identifier for the movie. */
    int _id;

    /** @brief Genre or category of the movie. */
    std::string _genre;

    /** @brief Number of user ratings received. */
    int _ratingCount;
};

#endif
