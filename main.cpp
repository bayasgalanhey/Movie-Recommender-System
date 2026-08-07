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
//
// Returns false if the input stream ended (end-of-file) before a value could be
// read. End-of-file is permanent, so retrying after it would loop forever --
// the caller must stop asking and shut down instead.
bool getInt(const string& prompt, int& value) {
    cout << prompt;

    while (!(cin >> value)) {
        if (cin.eof()) {
            return false; // No more input will ever arrive; give up.
        }
        cin.clear(); // Reset the fail state of cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove invalid input
        cout << "Invalid input. Try again: ";
    }

    return true;
}

// Reads a valid double value. Used specifically for movie rating input.
// Rating values must be numeric, and this function ensures the user enters
// a valid number rather than text or invalid characters.
//
// Returns false on end-of-file, for the same reason as getInt().
bool getDouble(const string& prompt, double& value) {
    cout << prompt;

    while (!(cin >> value)) {
        if (cin.eof()) {
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
    }

    return true;
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
        cout << "\n\033[1;36m=========================================\033[0m\n";
        cout << "\033[1;33m       Movie Recommendation System       \033[0m\n";
        cout << "\033[1;36m=========================================\033[0m\n";
        cout << "  \033[1;32m[1]\033[0m Add New User\n";
        cout << "  \033[1;32m[2]\033[0m Rate a Movie\n";
        cout << "  \033[1;32m[3]\033[0m Show Recommendations\n";
        cout << "  \033[1;32m[4]\033[0m List Movies\n";
        cout << "  \033[1;32m[6]\033[0m Show User Info\n";
        cout << "  \033[1;31m[5]\033[0m Exit\n";
        cout << "\033[1;36m=========================================\033[0m\n";

        // Request user input for the menu choice using safe integer input.
        // A false return means the input stream ended, so there is nothing
        // left to read and the program must stop.
        if (!getInt("\033[1;35mEnter choice:\033[0m ", choice)) {
            cout << "\nInput ended. Goodbye!" << endl;
            break;
        }

        // Option 1: Add a new user to the system
        if (choice == 1) {
            string name;

            // Collect the user's name
            cout << "Enter user name: ";
            if (!(cin >> name)) {  // Assumes names are one word
                cout << "\nInput ended. Goodbye!" << endl;
                break;
            }

            // Collect a numeric ID for the user
            int id;
            if (!getInt("Enter user ID: ", id)) {
                cout << "\nInput ended. Goodbye!" << endl;
                break;
            }

            // Store the user in the recommender system
            rec.addUser(name, id);
        }

        // Option 2: Allow a user to rate a movie
        else if (choice == 2) {
            // Gather necessary information: user id, movie id, and rating
            int userId, movieId;
            double rating;
            if (!getInt("Enter your user ID: ", userId) ||
                !getInt("Enter movie ID to rate: ", movieId) ||
                !getDouble("Enter rating (0–10): ", rating)) {
                cout << "\nInput ended. Goodbye!" << endl;
                break;
            }

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
            int id;
            if (!getInt("Enter user ID: ", id)) {
                cout << "\nInput ended. Goodbye!" << endl;
                break;
            }
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
            // Use the validated helper here too, so a non-numeric entry or a
            // closed input stream is handled the same way as everywhere else.
            int id;
            if (!getInt("Enter user ID: ", id)) {
                cout << "\nInput ended. Goodbye!" << endl;
                break;
            }

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

        // Discard anything left over on the current input line (such as the
        // newline that >> leaves behind). Deliberately no cin.clear() here:
        // clearing would also erase the end-of-file flag, and that flag is
        // what tells the next read to stop instead of spinning forever.
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}