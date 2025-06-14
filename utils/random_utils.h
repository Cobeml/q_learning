#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <vector>
#include <algorithm>

struct TrainingStats {
    std::vector<double> episode_rewards;
    std::vector<int> episode_lengths;
    std::vector<bool> episode_success;
    
    void add_episode(double reward, int steps, bool success);
    double get_success_rate(int window = 50);
    double get_avg_reward(int window = 50);
    double get_success_rate_at_episode(int episode, int window = 50);

    void plot_success_rate_ascii(int width = 50, int height = 20);
    void plot_avg_reward_ascii(int width = 50, int height = 20);
};

#endif