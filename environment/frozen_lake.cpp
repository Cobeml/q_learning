#include "frozen_lake.h"
#include <iostream>
#include <random>
#include <tuple>
#include <queue>

FrozenLake::FrozenLake(int rows, int cols, double slip_probability, double hole_percentage)
    : rows(rows), cols(cols), slip_probability(slip_probability), hole_percentage(hole_percentage) {
    grid = std::vector<std::vector<char> >(rows, std::vector<char>(cols, 'H'));

    // Set the start and goal states
    grid[0][0] = 'S';
    grid[rows - 1][cols - 1] = 'G';


    // Set the hole states randomly
    std::cout << "Generating grid..." << std::endl;
    std::vector<std::vector<char> > grid_copy = grid;
    int attempts = 0;
    while (!path_exists(&grid_copy, 0, rows * cols - 1)) {
        grid_copy = grid;
        attempts++;
        std::cout << "Attempt " << attempts << "..." << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, rows * cols - 1);
        int num_holes = rows * cols - 2;
        while (num_holes > rows * cols * hole_percentage) {
            int hole_index = dis(gen);
            if (grid_copy[hole_index / cols][hole_index % cols] == 'H') {
                grid_copy[hole_index / cols][hole_index % cols] = 'F';
                num_holes--;
            }
        }
    }
    std::cout << "Grid generated in " << attempts << " attempts" << std::endl;
    grid = grid_copy;

    // Set the current state to the start state
    current_state = 0;
};

bool FrozenLake::path_exists(std::vector<std::vector<char> > *grid, int start, int goal) {
    std::vector<bool> visited(get_state_count(), false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == goal) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int next_state = current + (i == 0 ? -1 : i == 1 ? cols : i == 2 ? 1 : -cols);
            if (next_state >= 0 && next_state < get_state_count() && !visited[next_state] && grid->at(next_state / cols).at(next_state % cols) != 'H') {
                q.push(next_state);
                visited[next_state] = true;
            }
        }
    }

    return false;
};

int FrozenLake::reset() {
    current_state = 0;
    return current_state;
};

std::tuple<int, double, bool> FrozenLake::step(int action) {
    int next_state = current_state;
    double reward = 0.0;
    bool done = false;

    // Check if the action is valid
    if (action < 0 || action >= get_action_count()) {
        std::cerr << "Invalid action: " << action << std::endl;
        return std::make_tuple(next_state, reward, done);
    }

    // Randomly choose a integer between 0 and 3 with slip probability
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> action_dis(0, 3);
    double random_value = dis(gen);
    if (random_value < slip_probability) {
        action = action_dis(gen);
    }

    switch (action) {
        case 0: // LEFT
            if (current_state % cols == 0) {
                next_state = current_state;
            } else {
                next_state = current_state - 1;
            }
            break;
        case 1: // DOWN
            if (current_state / cols == rows - 1) {
                next_state = current_state;
            } else {
                next_state = current_state + cols;
            }
            break;
        case 2: // RIGHT
            if (current_state % cols == cols - 1) {
                next_state = current_state;
            } else {
                next_state = current_state + 1;
            }
            break;
        case 3: // UP
            if (current_state / cols == 0) {
                next_state = current_state;
            } else {
                next_state = current_state - cols;
            }
            break;
        default:
            std::cerr << "Invalid action: " << action << std::endl;
            return std::make_tuple(next_state, reward, done);
    }

    reward = -0.01;

    // Check if the next state is a hole or the goal
    if (grid[next_state / cols][next_state % cols] == 'H') {
        reward = -1.0;
        done = true;
    } else if (grid[next_state / cols][next_state % cols] == 'G') {
        reward = 1.0;
        done = true;
    }

    // Update the current state
    current_state = next_state;

    return std::make_tuple(next_state, reward, done);
};

int FrozenLake::get_state_count() {
    return rows * cols;
};

int FrozenLake::get_action_count() {
    return 4;
};

void FrozenLake::render() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Print the grid
            std::cout << grid[i][j] << " ";

            // Print the agent position
            if (i == current_state / cols && j == current_state % cols) {
                std::cout << "A";
            }
        }
        std::cout << std::endl;
    }
};

bool FrozenLake::is_done() {
    return grid[current_state / cols][current_state % cols] == 'G' || grid[current_state / cols][current_state % cols] == 'H';
};

char FrozenLake::get_grid_char(int state) {
    return grid[state / cols][state % cols];
};