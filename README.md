# Q-Learning Implementation in C++

A C++ implementation of the Q-Learning reinforcement learning algorithm applied to the Frozen Lake environment. This project demonstrates tabular Q-learning for solving a grid-world navigation problem with stochastic dynamics.

## Overview

The agent learns to navigate from a start position to a goal position on a frozen lake while avoiding holes. The environment includes slip probability, making movement stochastic and requiring the agent to learn robust policies.

![process](https://github.com/user-attachments/assets/6689ed1d-66f2-4e6b-98ca-4a215ce63fe7)

*Development process of creating this Q-Learning implementation (click to view animated GIF)*

## Project Structure

```
Q-Learning/
├── agent/                    # Q-Learning agent implementation
│   ├── q_learning_agent.h    # Agent interface and class definition
│   └── q_learning_agent.cpp  # Agent implementation
├── environment/              # Environment implementations
│   ├── frozen_lake.h         # Frozen Lake environment interface
│   └── frozen_lake.cpp       # Frozen Lake environment implementation
├── utils/                    # Utility functions and training statistics
│   ├── random_utils.h        # Training statistics and plotting utilities
│   └── random_utils.cpp      # Implementation of utilities
├── main.cpp                  # Main program entry point
└── README.md                 # This file
```

## Features

### Frozen Lake Environment
- **Grid World**: Configurable NxN grid with start (S), frozen (F), hole (H), and goal (G) states
- **Stochastic Movement**: Slip probability causes random movement direction
- **Automatic Grid Generation**: Ensures a valid path exists from start to goal
- **Reward Structure**:
  - Goal reached: +1.0
  - Hole entered: -1.0
  - Regular movement: -0.01 (encourages shorter paths)

### Q-Learning Agent
- **Tabular Q-Learning**: Maintains Q-values for all state-action pairs
- **Epsilon-Greedy Policy**: Balances exploration vs exploitation
- **Configurable Parameters**:
  - Learning rate (α): How much to update Q-values
  - Discount factor (γ): Importance of future rewards
  - Exploration rate (ε): Initial exploration probability with decay

### Training Statistics
- **Success Rate Tracking**: Monitors agent performance over episodes
- **Reward Tracking**: Tracks average rewards per episode
- **ASCII Plotting**: Visual feedback during training
- **Windowed Statistics**: Configurable window size for smoothed metrics

## Building and Running

### Prerequisites
- C++ compiler with C++11 support (g++, clang++, etc.)
- Make (optional, for build automation)

### Compilation
```bash
# Simple compilation
g++ -std=c++11 -o q_learning main.cpp agent/q_learning_agent.cpp environment/frozen_lake.cpp utils/random_utils.cpp

# Or compile with optimization
g++ -std=c++11 -O2 -o q_learning main.cpp agent/q_learning_agent.cpp environment/frozen_lake.cpp utils/random_utils.cpp
```

### Running
```bash
./q_learning
```

## Configuration

The main parameters can be modified in `main.cpp`:

```cpp
int rows = 8;                    // Grid height
int cols = 8;                    // Grid width
double slip_probability = 0.15;  // Chance of random movement
double hole_percentage = 0.25;   // Percentage of grid as holes

// Agent parameters
double learning_rate = 0.1;      // α (alpha)
double discount_factor = 0.9;    // γ (gamma)  
double epsilon = 0.15;           // ε (epsilon)

int episodes = 1000;             // Training episodes
```

## Example Output

The program will display:
1. **Training Progress**: Episode-by-episode success rate and average reward
2. **ASCII Plots**: Success rate and reward progression over training
3. **Grid Visualization**: Final lake layout with S, F, H, G markers
4. **Learned Policy**: Optimal action for each grid position (L/D/R/U for Left/Down/Right/Up)

```
=== Success Rate Over Time ===
1.0|                                                  
   |                               ** *               
   |               *****        ********     ******   
   |              ********    *****  * *** ***********
   |             *       *** **          ***        **
   |             *        ****                        
   |                        *                         
   |            *                                     
   |           **                                     
   |           *                                      
   |                                                  
   |          *                                       
   |          *                                       
   |                                                  
   |         *                                        
   |         *                                        
   |        *                                         
   |***** ***                                         
   |********                                          
0.0|                                                  
   +--------------------------------------------------
   Episodes: 0 -> 1000


=== Average Reward Over Time ===
1.0|                                                  
   |                                                  
   |                                                  
   |                                                  
   |                                                  
   |                                                  
   |                               ** *               
   |                  *          ******         *     
   |                 ***        ***  * **    ******   
   |                ** ***     *       **  ***** **** 
   |               *    **    **         ****       **
   |               *      *   *          **          *
   |                      ** *                        
   |                       ***                        
   |                        *                         
   |                                                  
   |                                                  
   |                                                  
   |                                                  
0.0|                                                  
   +--------------------------------------------------
   Episodes: 0 -> 1000

Lake:
S F F H F F F H 
F F H H H F F F 
F F F F H F H F 
F F F F F H F F 
F F F F F F F F 
F F H H F F F F 
F F H H F F F F 
F F H F H H H G 

Policy:
D L L L L L L L 
D U L L L L L L 
D D D L L L L D 
R R R R D L D U 
L U U R R R D D 
U U L L R R R D 
U U L L U R U D 
U L L L L L L L 
```

## Algorithm Details

The Q-Learning update rule implemented:
```
Q(s,a) ← Q(s,a) + α[r + γ max Q(s',a') - Q(s,a)]
```

Where:
- s: current state
- a: action taken
- r: immediate reward
- s': next state
- α: learning rate
- γ: discount factor

## Contributing

Feel free to extend this implementation by:
- Adding new environments
- Implementing other RL algorithms (SARSA, Expected SARSA, etc.)
- Adding function approximation methods
- Implementing visualization tools

## License

This project is open source and available under the MIT License. 
