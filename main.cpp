#include "environment/frozen_lake.h"
#include "agent/q_learning_agent.h"
#include "utils/random_utils.h"

#include <iostream>

int main() {
    int rows = 8;
    int cols = 8;
    FrozenLake lake(rows, cols, 0.15, 0.25);
    QLearningAgent agent(lake.get_state_count(), lake.get_action_count(), 0.1, 0.9, 0.15);

    TrainingStats stats;

    for (int i = 0; i < 1000; i++) {
        int state = lake.reset();
        int steps = 0;
        bool success = false;
        double total_reward = 0;
        while (!lake.is_done()) {
            int action = agent.choose_action(state);
            std::tuple<int, double, bool> result = lake.step(action);
            int next_state = std::get<0>(result);
            double step_reward = std::get<1>(result);
            total_reward += step_reward;
            bool done = std::get<2>(result);
            agent.update_q_value(state, action, step_reward, next_state);
            state = next_state;
            steps++;
            if (done) {
                success = (lake.get_grid_char(state) == 'G');
            }
        }
        agent.decay_epsilon();
        stats.add_episode(total_reward, steps, success);
        std::cout << "Episode " << i << " - Success Rate: " << stats.get_success_rate() << " - Avg Reward: " << stats.get_avg_reward() << std::endl;
    }

    stats.plot_success_rate_ascii();
    stats.plot_avg_reward_ascii();

    std::cout << "Lake:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << lake.get_grid_char(i * cols + j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Policy:" << std::endl;

    std::vector<int> policy = agent.get_policy();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int state = i * cols + j;
            char policy_letter = 'L';
            switch (policy[state]) {
                case 0:
                    policy_letter = 'L';
                    break;
                case 1:
                    policy_letter = 'D';
                    break;
                case 2:
                    policy_letter = 'R';
                    break;
                case 3:
                    policy_letter = 'U';
                    break;
            }
            std::cout << policy_letter << " ";
        }
        std::cout << std::endl;
    }
    return 0;
};