/* Project Title: Movie recommendation system
 *
 * Author: bayasgalan_zorigt
 * 
 * 
 * 
 * This program loads movie data and user data, allows users to create accounts,
 * rate movies, view recommended movies, and browse a list of all movies.
 * All user interaction happens through a text-based menu system.
 * This file contains the main driver of the program, along with helper input
 *validation functions to ensure safe and predictable user input.
 *
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Recommender.h"

using namespace std;

// Reads a valid integer from the user. If the user enters an invalid value
// (such as letters or symbols), the function keeps asking until a valid
// integer is received. This prevents the program from crashing or skipping input.
int getInt(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;

    while (cin.fail()) {
        cin.clear(); // Reset the fail state of cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove invalid input
        cout << "Invalid input. Try again: ";
        cin >> value;
    }

    return value;
}

// Reads a valid double value. Used specifically for movie rating input.
// Rating values must be numeric, and this function ensures the user enters
// a valid number rather than text or invalid characters.
double getDouble(const string& prompt) {
    double value;
    cout << prompt;
    cin >> value;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
        cin >> value;
    }

    return value;
}

int main() {

    Recommender rec;  // Main recommendation engine

    // Load initial data required by the system.
    // Movie data is loaded from movies.csv
    // User data is loaded from stored files or initialized if none exist.
    rec.loadMovies("movies.csv");
    rec.loadUsers();

    int choice = 0;   // Tracks the user's menu selection

    // Main menu loop. The program continues until the user selects Exit
    while (choice != 5) {

        // Menu displayed to the user
        cout << endl;
        cout << "===== Movie Recommendation System =====" << endl;
        cout << "1. Add New User" << endl;
        cout << "2. Rate a Movie" << endl;
        cout << "3. Show Recommendations" << endl;
        cout << "4. List Movies" << endl;
        cout << "5. Exit" << endl;
        cout << "6. Show User Info" << endl;

        // Request user input for the menu choice using safe integer input
        choice = getInt("Enter choice: ");

        // Option 1: Add a new user to the system
        if (choice == 1) {
            string name;

            // Collect the user's name
            cout << "Enter user name: ";
            cin >> name;  // Assumes names are one word

            // Collect a numeric ID for the user
            int id = getInt("Enter user ID: ");

            // Store the user in the recommender system
            rec.addUser(name, id);
        }

        // Option 2: Allow a user to rate a movie
        else if (choice == 2) {
            // Gather necessary information: user id, movie id, and rating
            int userId = getInt("Enter your user ID: ");
            int movieId = getInt("Enter movie ID to rate: ");
            double rating = getDouble("Enter rating (0–10): ");

            // Check that the rating falls within the accepted range
            if (rating < 0.0 || rating > 10.0) {
                cout << "Rating must be between 0.0 and 10.0." << endl;
            } else {
                // Access the map of users for O(1) lookup
                unordered_map<int, User>& users = rec.getUsers();
                auto it = users.find(userId);

                if (it != users.end()) {
                    // If found, apply the rating to the specified movie
                    it->second.rateMovie(movieId, rating);
                    cout << "Rating saved." << endl;
                } else {
                    // If no matching user ID exists, inform the user
                    cout << "User not found." << endl;
                }
            }
        }

        // Option 3: Display personalized recommendations for a given user
        else if (choice == 3) {
            int id = getInt("Enter user ID: ");
            rec.displayRecommendations(id);
        }

        // Option 4: Print the entire movie list to the screen
        else if (choice == 4) {
            cout << endl << "=== Movie List ===" << endl;

            // Retrieve the movie map from the recommender system
            unordered_map<int, Movie>& movies = rec.getMovies();

            // Display information for each movie using range-based loop
            for (auto const& [id, movie] : movies) {
                movie.displayInfo();
            }
        }

        // Option 5: Exit the program
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }//Option 6: Show user info
        else if (choice == 6) {
            int id;
            cout << "Enter user ID: ";
            cin >> id;

            unordered_map<int, User>& users = rec.getUsers();
            auto it = users.find(id);

            if (it != users.end()) {
                it->second.displayInfo();
            } else {
                cout << "User not found." << endl;
            }
        // If the user entered an invalid menu choice
        }else {
            cout << "Invalid choice. Try again." << endl;
        }

        // Clear any leftover characters in the input buffer to prevent issues
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}