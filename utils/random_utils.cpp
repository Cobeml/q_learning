#include "random_utils.h"
#include <iostream>
#include <algorithm>
#include <cmath>

void TrainingStats::add_episode(double reward, int steps, bool success) {
    episode_rewards.push_back(reward);
    episode_lengths.push_back(steps);
    episode_success.push_back(success);
}

double TrainingStats::get_success_rate(int window) {
    int size = std::min(window, (int)episode_success.size());
    int successes = 0;
    for (int i = episode_success.size() - size; i < episode_success.size(); i++) {
        if (episode_success[i]) successes++;
    }
    return (double)successes / size;
}

double TrainingStats::get_avg_reward(int window) {
    int size = std::min(window, (int)episode_rewards.size());
    double sum = 0;
    for (int i = episode_rewards.size() - size; i < episode_rewards.size(); i++) {
        sum += episode_rewards[i];
    }
    return sum / size;
}

double TrainingStats::get_success_rate_at_episode(int episode, int window) {
    int size = std::min(window, (int)episode_success.size());
    int successes = 0;
    for (int i = episode - size; i < episode; i++) {
        if (episode_success[i]) successes++;
    }
    return (double)successes / size;
}

void TrainingStats::plot_success_rate_ascii(int width, int height) {
    if (episode_success.empty()) return;
    
    std::cout << "\n=== Success Rate Over Time ===\n";
    
    // Calculate rolling average
    std::vector<double> success_rates;
    int window = 100;
    for (int i = window; i <= episode_success.size(); i += 10) {
        int successes = 0;
        for (int j = i - window; j < i; j++) {
            if (episode_success[j]) successes++;
        }
        success_rates.push_back((double)successes / window);
    }
    
    if (success_rates.empty()) return;
    
    // Create ASCII plot
    for (int row = height - 1; row >= 0; row--) {
        double y_value = (double)row / (height - 1);
        
        if (row == height - 1) std::cout << "1.0|";
        else if (row == 0) std::cout << "0.0|";
        else std::cout << "   |";
        
        for (int col = 0; col < width && col < success_rates.size(); col++) {
            double point_value = success_rates[col * success_rates.size() / width];
            if (std::abs(point_value - y_value) < 0.05) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    
    // X-axis
    std::cout << "   +";
    for (int i = 0; i < width; i++) std::cout << "-";
    std::cout << "\n   Episodes: 0 -> " << episode_success.size() << "\n\n";
}

void TrainingStats::plot_avg_reward_ascii(int width, int height) {
    if (episode_rewards.empty()) return;
    
    std::cout << "\n=== Average Reward Over Time ===\n";
    
    // Calculate rolling average
    std::vector<double> avg_rewards;
    int window = 100;
    for (int i = window; i <= episode_rewards.size(); i += 10) {
        double sum = 0;
        for (int j = i - window; j < i; j++) {
            sum += episode_rewards[j];
        }
        avg_rewards.push_back(sum / window);
    }
    
    if (avg_rewards.empty()) return;
    
    // Create ASCII plot
    for (int row = height - 1; row >= 0; row--) {
        double y_value = (double)row / (height - 1);
        
        if (row == height - 1) std::cout << "1.0|";
        else if (row == 0) std::cout << "0.0|";
        else std::cout << "   |";
        
        for (int col = 0; col < width && col < avg_rewards.size(); col++) {
            double point_value = avg_rewards[col * avg_rewards.size() / width];
            if (std::abs(point_value - y_value) < 0.05) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    
    // X-axis
    std::cout << "   +";
    for (int i = 0; i < width; i++) std::cout << "-";
    std::cout << "\n   Episodes: 0 -> " << episode_rewards.size() << "\n\n";
}