#include "Recommender.h"
#include "Movie.h"
#include "User.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * @brief Returns a reference to the internal map of users.
 * @return Map of User objects stored in the recommender.
 */
unordered_map<int, User>& Recommender::getUsers() {
    return _users;
}

/**
 * @brief Returns a reference to the internal map of movies.
 * @return Map of Movie objects stored in the recommender.
 */
unordered_map<int, Movie>& Recommender::getMovies()  {
    return _movies;
}

/**
 * @brief Loads movies from a CSV file and stores them in the recommender.
 * 
 * The CSV must contain: id, name, genre, rating.
 * Handles movie titles that contain commas inside quotes.
 * 
 * @param filename The path to the CSV file.
 */
void Recommender::loadMovies(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open movie file: " << filename << endl;
        return;
    }

    string line;
    string header;

    // Skip header line
    getline(file, header);

    while (getline(file, line)) {

        // Extract columns with proper handling of quoted titles
        vector<string> cols;
        string temp = "";
        bool insideQuotes = false;

        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];

            if (c == '"') {
                insideQuotes = !insideQuotes;
            }
            else if (c == ',' && !insideQuotes) {
                cols.push_back(temp);
                temp = "";
            }
            else {
                temp += c;
            }
        }

        cols.push_back(temp);

        // Expecting exactly 4 columns: id, name, genre, rating
        if (cols.size() != 4) {
            continue;
        }

        int id = stoi(cols[0]);
        string name = cols[1];
        string genre = cols[2];
        double rating = stod(cols[3]);

        _movies[id] = Movie(id, name, genre, rating);
    }

    file.close();
    cout << "Loaded " << _movies.size() << " movies." << endl;
}

/**
 * @brief Loads a small set of default users for testing.
 * 
 * Creates two test users and assigns them a few movie ratings.
 */
void Recommender::loadUsers() {

    User u1("Alice", 99);
    User u2("Bob", 98);

    u1.rateMovie(1, 9.2);
    u1.rateMovie(5, 8.4);

    u2.rateMovie(2, 7.5);
    u2.rateMovie(5, 9.1);

    _users[u1.getID()] = u1;
    _users[u2.getID()] = u2;

    cout << "Users loaded: " << _users.size() << endl;
}

/**
 * @brief Adds a new user to the recommender.
 * 
 * Checks if the user ID already exists before inserting.
 * 
 * @param name The name of the new user.
 * @param id Unique identifier for the user.
 */
void Recommender::addUser(const string& name, int id) {

    if (_users.find(id) != _users.end()) {
        cout << "Error: User ID already exists." << endl;
        return;
    }

    _users[id] = User(name, id);

    cout << "User " << name << " added successfully!" << endl;
}

/**
 * @brief Generates movie recommendations for a user.
 * 
 * Uses Collaborative Filtering (User-Based) with weighted averages.
 * 
 * @param userId The ID of the user for whom to generate recommendations.
 * @return A vector of Movie objects recommended for the user.
 */
vector<Movie> Recommender::recommendForUser(int userId) const {

    vector<Movie> recommendations;

    // 1. Locate target user (O(1) lookup)
    auto itUser = _users.find(userId);
    if (itUser == _users.end()) {
        cout << "User not found!" << endl;
        return recommendations;
    }
    const User& targetUser = itUser->second;

    // 2. Identify movies the target user has already rated
    vector<pair<int, double>> targetRatings = targetUser.getRatedMovies();
    
    // 3. For each movie the user HAS NOT rated, predict a rating
    vector<pair<double, Movie>> scoredMovies;

    for (auto const& [movieId, movie] : _movies) {

        // Skip if already rated
        bool alreadyRated = false;
        for (size_t j = 0; j < targetRatings.size(); j++) {
            if (targetRatings[j].first == movieId) {
                alreadyRated = true;
                break;
            }
        }
        if (alreadyRated) continue;

        // Predict rating using Collaborative Filtering
        double weightedSum = 0.0;
        double similaritySum = 0.0;

        for (auto const& [otherId, otherUser] : _users) {
            if (otherId == userId) continue;

            double sim = targetUser.similarityTo(otherUser);
            if (sim <= 0) continue;

            // Check if this other user rated the movie
            vector<pair<int, double>> otherRatings = otherUser.getRatedMovies();
            for (size_t k = 0; k < otherRatings.size(); k++) {
                if (otherRatings[k].first == movieId) {
                    weightedSum += otherRatings[k].second * sim;
                    similaritySum += sim;
                    break;
                }
            }
        }

        // Final score for the movie (predicted rating)
        double predictedRating = 0.0;
        if (similaritySum > 0) {
            predictedRating = weightedSum / similaritySum;
        } else {
            // Fallback: use movie's average rating but with low weight
            predictedRating = movie.getRating() * 0.1; 
        }

        scoredMovies.push_back({predictedRating, movie});
    }

    // 4. Sort by predicted rating (descending)
    sort(scoredMovies.begin(), scoredMovies.end(), [](const pair<double, Movie>& a, const pair<double, Movie>& b) {
        return a.first > b.first;
    });

    // 5. Limit to top 5 recommendations
    size_t limit = min((size_t)5, scoredMovies.size());
    for (size_t i = 0; i < limit; i++) {
        recommendations.push_back(scoredMovies[i].second);
    }

    return recommendations;
}

/**
 * @brief Prints movie recommendations for the given user.
 * 
 * Displays up to 5 recommended movies using Movie::displayInfo().
 * 
 * @param userId The ID of the user whose recommendations to display.
 */
void Recommender::displayRecommendations(int userId) const {

    vector<Movie> recs = recommendForUser(userId);

    cout << "Recommended movies for user " << userId << ":" << endl;

    if (recs.size() == 0) {
        cout << "No recommendations available." << endl;
        return;
    }

    for (size_t i = 0; i < recs.size(); i++) {
        recs[i].displayInfo();
    }
}
