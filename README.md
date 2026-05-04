# Movie-Recommender-Project

A high-performance C++ CLI Movie Recommender that suggests films using **User-Based Collaborative Filtering**. The system predicts user preferences by analyzing rating patterns across the user base using vector-space similarity.

## Problem Description
This project implements a movie recommendation system that helps users decide what to watch by analyzing their movie ratings and identifying users with similar tastes. The program aims to reduce the “what to watch” dilemma by providing automated, personalized suggestions grounded in mathematical similarity models and stored movie data.

## Key Features & Enhancements
- **Collaborative Filtering Engine:** Uses **Cosine Similarity** to compare users in a vector space based on their shared rating history.
- **Predictive Modeling:** Generates recommendations by calculating weighted average predicted ratings for unvisited movies.
- **High-Performance Architecture:** Utilizes **Hash Maps (`std::unordered_map`)** for $O(1)$ constant-time lookups of users and movies, ensuring scalability for large datasets.
- **Modern C++17:** Leverages structured bindings, lambda expressions, and advanced STL algorithms for clean, efficient code.
- **Robust CSV Parsing:** Custom logic to handle complex CSV data, including quoted movie titles containing commas.

## Program Documentation

### How to Run the Program:
1. **Compile:** Use the provided Makefile (requires a C++17 compatible compiler):
   ```bash
   make
   ```
2. **Data:** Ensure `movies.csv` is in the same directory as the executable.
3. **Run:**
   ```bash
   ./MovieRecommender
   ```
   *Note: The user interacts entirely through a text-based menu.*

### Technical Architecture:
- **Movie:** Encapsulates movie metadata, IDs, and average community ratings.
- **User:** Manages user profiles and rating history. Includes vector-space similarity logic.
- **Recommender:** The central engine that coordinates O(1) data access and executes the recommendation algorithms.

## Data Structures
- **`std::unordered_map`:** Used for primary storage of Users and Movies to provide $O(1)$ lookup performance.
- **`std::vector`:** Used for sequential data processing and storing rating pairs.
- **`std::pair`:** Used to link movie IDs with specific user ratings.

## Possible Future Extensions
- **Data Persistence:** Saving user profiles and ratings to a permanent file.
- **Hybrid Engine:** Combining Collaborative Filtering with Content-Based (genre) weighting.
- **GUI Transition:** Implementing a graphical interface using Qt or a Web API.
