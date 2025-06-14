#ifndef FROZEN_LAKE_H
#define FROZEN_LAKE_H

#include <tuple>
#include <vector>

class FrozenLake {
private:
    std::vector<std::vector<char> > grid;  // 2D grid: 'S'=start, 'F'=frozen, 'H'=hole, 'G'=goal
    int rows, cols;                        // Grid dimensions
    int current_state;                     // Current position as 1D index (0 to rows*cols-1)
    double slip_probability;               // Probability of sliding in random direction (0.0-1.0)
    double hole_percentage;               // Percentage of holes in the grid (0.0-1.0)
    bool path_exists(std::vector<std::vector<char> > *grid, int start, int goal);

public:
    FrozenLake(int rows, int cols, double slip_probability, double hole_percentage);
    int reset();                           // Reset to start position, return initial state
    std::tuple<int, double, bool> step(int action);  // Take action, return (next_state, reward, done)
    int get_state_count();                 // Total number of states (rows * cols)
    int get_action_count();                // Number of actions (always 4: LEFT, DOWN, RIGHT, UP)
    void render();                         // Display current grid and agent position
    bool is_done();                        // Check if the game is done
    char get_grid_char(int state);         // Get the character at a given state
};

#endif