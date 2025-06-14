#include "q_learning_agent.h"
#include <random>

QLearningAgent::QLearningAgent(int state_count, int action_count, double learning_rate, double discount_factor, double epsilon)
    : state_count(state_count), action_count(action_count), learning_rate(learning_rate), discount_factor(discount_factor), epsilon(epsilon) {
    q_table = std::vector<std::vector<double> >(state_count, std::vector<double>(action_count, 0.0));
}

int QLearningAgent::choose_action(int state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> action_dis(0, 3);

    if (dis(gen) < epsilon) {
        return action_dis(gen);
    } else {
        return std::max_element(q_table[state].begin(), q_table[state].end()) - q_table[state].begin();
    }
}

void QLearningAgent::update_q_value(int state, int action, double reward, int next_state) {
    double old_q_value = q_table[state][action];
    double max_future_q = *std::max_element(q_table[next_state].begin(), q_table[next_state].end());
    double new_q_value = old_q_value + learning_rate * (reward + discount_factor * max_future_q - old_q_value);
    q_table[state][action] = new_q_value;
}

void QLearningAgent::decay_epsilon() {
    epsilon = std::max(0.01, epsilon * 0.995);
}

std::vector<int> QLearningAgent::get_policy() {
    std::vector<int> policy(state_count);
    for (int state = 0; state < state_count; state++) {
        policy[state] = std::max_element(q_table[state].begin(), q_table[state].end()) - q_table[state].begin();
    }

    return policy;
}
