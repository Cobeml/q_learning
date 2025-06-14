#ifndef Q_LEARNING_AGENT_H
#define Q_LEARNING_AGENT_H

#include <vector>

// Q-Learning Reinforcement Learning Agent
// Implements tabular Q-learning algorithm for discrete state/action spaces
class QLearningAgent {
private:
    std::vector<std::vector<double> > q_table;  // Q-values: q_table[state][action]
    double learning_rate;                       // Alpha: how much to update Q-values (0.0-1.0)
    double discount_factor;                     // Gamma: importance of future rewards (0.0-1.0)
    double epsilon;                             // Exploration rate for epsilon-greedy policy (0.0-1.0)
    int state_count;
    int action_count;

public:
    QLearningAgent(int state_count, int action_count, double learning_rate, double discount_factor, double epsilon);
    int choose_action(int state);               // Select action using epsilon-greedy policy
    void update_q_value(int state, int action, double reward, int next_state);  // Q-value update method
    void decay_epsilon();                       // Reduce epsilon over time (decrease exploration)
    std::vector<int> get_policy();             // Extract greedy policy (best action for each state)
};

#endif