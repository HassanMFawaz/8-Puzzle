#include <iostream>
#include "Node.h"
#include <vector>
#include <queue>
#include <cmath>

void waitForSeconds(int seconds)
{
    // Get the current clock time
    clock_t startTime = clock();

    // Loop until the specified time has passed
    while (static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC < seconds)
    {
        // Do nothing, just wait
    }
}

std::vector<std::vector<int>> veryEasy = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 0, 8}
};

std::vector<std::vector<int>> easy = {
    {1, 2, 0},
    {4, 5, 3},
    {7, 8, 6}
};

std::vector<std::vector<int>> doable = {
    {0, 1, 2},
    {4, 5, 3},
    {7, 8, 6}
};

std::vector<std::vector<int>> ohBoy = {
    {8, 7, 1},
    {6, 0, 2},
    {5, 4, 3}
};

std::vector<std::vector<int>> impossible = {
    {1, 2, 3},
    {4, 5, 6},
    {8, 7, 0}
};

// Don't delete, this struct is needed for std::priority queue third argument
struct CompareCost
{
    // operator overload
    bool operator()(const Node *left, const Node *right)
    {
        return left->cost > right->cost;
    }
};

std::vector<std::vector<int>> goalState = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}};

int algorithmChoice = 1;
// vector to store all created nodes, useful for deletion.
std::vector<Node*> allNodes;
bool isMatching(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
void search(Node *curr);
// Hassan, given curr state, calculate cost to goal state using algorithmChoice selected by user
void calculateCost(Node *state);

// Salma, given curr state, generate the legal next states, use calculate cost for them, store in their Nodes
std::vector<int> emptyTile(Node *state);

// Get empty tile position
std::vector<int> emptyTile(Node *state)
{
    std::vector<std::vector<int>> curState = state->getState();
    for (int i = 0; i < curState.size(); i++)
    {
        for (int j = 0; j < curState[i].size(); j++)
        {
            if (curState[i][j] == 0)
            {
                return std::vector<int>{i, j};
            }
        }
    }
    return std::vector<int>();
}
// Get next legal states
std::vector<Node *> getNextState(Node *state)
{
    std::vector<Node *> nextStates;
    std::vector<std::vector<int>> curState = state->getState();
    std::vector<std::vector<int>> newState;
    std::vector<int> position = emptyTile(state);
    int xPos = position[0]; // Vertical position
    int yPos = position[1]; // Horizontal position

    // Down
    if (xPos < curState.size() - 1)
    {
        newState = curState;
        std::swap(newState[xPos][yPos], newState[xPos + 1][yPos]);
        Node *newNode = new Node(state, state->pcost, state->hcost, state->cost, "Down", newState);
        calculateCost(newNode);
        nextStates.push_back(newNode);
    }
    // Up
    if (xPos > 0)
    {
        newState = curState;
        std::swap(newState[xPos][yPos], newState[xPos - 1][yPos]);
         Node *newNode = new Node(state, state->pcost, state->hcost, state->cost, "Down", newState);
        calculateCost(newNode);
        nextStates.push_back(newNode);
    }
    // Right
    if (yPos < curState[xPos].size() - 1)
    {
        newState = curState;
        std::swap(newState[xPos][yPos], newState[xPos][yPos + 1]);
         Node *newNode = new Node(state, state->pcost, state->hcost, state->cost, "Down", newState);
        calculateCost(newNode);
        nextStates.push_back(newNode);
    }
    // Left
    if (yPos > 0)
    {
        newState = curState;
        std::swap(newState[xPos][yPos], newState[xPos][yPos - 1]);
        Node *newNode = new Node(state, state->pcost, state->hcost, state->cost, "Down", newState);
        calculateCost(newNode);
        nextStates.push_back(newNode);
    }
    allNodes.insert(allNodes.end(), nextStates.begin(), nextStates.end());
    return nextStates;
}

int main()
{

    int startLoop = 0;
    int puzzleChoice = 1;
    int userPuzzle = 0;
    std::vector<std::vector<int>> state =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8}
    };

    Node initialState(nullptr, -1,0,0, "", state);
    std::cout << "Welcome to XXX (change this to your student ID) 8 puzzle solver." << std::endl;
    std::cout << "Type \"1\" to use a default puzzle, or “2” to enter your own puzzle." << std::endl;

    if (!(std::cin >> puzzleChoice))
    {
        std::cout << "Invilid input. Bye.";
        return 0;
    }

     if (puzzleChoice == 1)
    {
        int difficulty;
        std::cout << "Select difficulty level:\n"
                  << "1. VeryEasy\n"
                  << "2. Easy\n"
                  << "3. Doable\n"
                  << "4. OhBoy\n"
                  << "5. Impossible\n" ;

        if (!(std::cin >> difficulty))
        {
            std::cout << "Invalid input. Bye.";
            return 0;
        }

        // Set state based on difficulty
        switch (difficulty)
        {
            case 1:
                state = veryEasy;
                break;
            case 2:
                state = easy;
                break;
            case 3:
                state = doable;
                break;
                 case 4:
                state = ohBoy;
                break;
                 case 5:
                state = impossible;
                break;
            default:
                std::cout << "Invalid difficulty level. Using default state." << std::endl;
                state = easy; 
        }
    }

    if (puzzleChoice == 2)
    {
        for (int i = 0; i < state.size(); i++)
        {
            for (int j = 0; j < state[i].size(); j++)
            {
                std::cout << "Please Enter Your Own Puzzle, Integer by Integer: ";
                std::cin >> userPuzzle;
                state[i][j] = userPuzzle;
            }
        }
    }
    std::cout << "Enter your choice of algorithm:\n"
              << "Type \"1\" to use Uniform Cost Search.\n"
              << "Type \"2\" to use A* with the Misplaced Tile Heuristic.\n"
              << "Type \"3\" to use A* with the Euclidean distance Heuristic.\n";
    if (!(std::cin >> algorithmChoice))
    {
        std::cout << "Invilid input. Bye.";
        return 0;
    }
    std::cout << std::endl ;

    /*if(algorithmChoice != 1 && algorithmChoice != 2 && algorithmChoice != 3)
   {
       std::cout << "Invalid input. Bye.";
       return 0;
   }
   */

    initialState.setState(state);
    initialState.printState();
    std::cout << std::endl ;
    search(&initialState);

    // clean up nodes
    for (Node* node: allNodes) {
        delete node;
    }
    
    return 0;
}

void search(Node *curr)
{

    std::priority_queue<Node *, std::vector<Node *>, CompareCost> pq;
    calculateCost(curr);
    pq.push(curr);

    int nodeExpanded = 0;
    int queueCounter = 0;
    int currCounter ;

    /// visitedNodes.push_back(nextState);
    std::vector<Node *> visitedNodes;

    while (!pq.empty())
    {
        currCounter = pq.size();
        
        if (currCounter > queueCounter)
        {
            queueCounter = currCounter ;
        }

        Node *best = pq.top();
        pq.pop();

        std::cout << "The Heuristic Cost Is: " << best->hcost << std::endl;
        std::cout << "The Path Cost Is: " << best->pcost << std::endl;
        std::cout << "The Total Cost Is: " << best->cost << std::endl;
        std::cout << std::endl; 
        best->printState();
        waitForSeconds(0);
        std::cout << std::endl;

        bool isVisited = false;
        for (int i = 0; i < visitedNodes.size(); i++)
        {
            if (isMatching(visitedNodes[i]->state, best->state))
            {
                isVisited = true;
                break;
            }
        }

        if (isVisited)
        {
            std::cout << "This node has been visited. Skipping." << std::endl;
            continue;
        }

        if (best->checkDone())
        {
            std::cout << "This Is The Amount Of Node Expanded " << nodeExpanded << std::endl;
            std::cout << "This Is The Largest Queue Counter " << queueCounter << std::endl;
            std::cout << "This Is The Solution Path Printed Below " << std::endl;
            std::cout << std::endl;

            best->printTree();
            return;
        }

        std::vector<Node *> nextStates = getNextState(best);
        for (Node *nextState : nextStates)
        {
            pq.push(nextState);
        }
        visitedNodes.push_back(best);

        nodeExpanded++;
    }
}

void calculateCost(Node *state)
{   

    // Uniform Cost Search
    if (algorithmChoice == 1)
    {
        state->pcost = state->pcost + 1 ;
        state->cost = state->pcost ;
    }

    // A* with the Misplaced Tile Heuristic
    if (algorithmChoice == 2)
    {

        state->hcost = 0 ;

        int oneElementGoal = goalState[0][0];
        int twoElementGoal = goalState[0][1];
        int threeElementGoal = goalState[0][2];
        int fourElementGoal = goalState[1][0];
        int fiveElementGoal = goalState[1][1];
        int sixElementGoal = goalState[1][2];
        int sevenElementGoal = goalState[2][0];
        int eightElementGoal = goalState[2][1];
        int nineElementGoal = goalState[2][2];

        int oneElementState = state->state[0][0];
        int twoElementState = state->state[0][1];
        int threeElementState = state->state[0][2];
        int fourElementState = state->state[1][0];
        int fiveElementState = state->state[1][1];
        int sixElementState = state->state[1][2];
        int sevenElementState = state->state[2][0];
        int eightElementState = state->state[2][1];
        int nineElementState = state->state[2][2];

        if (oneElementGoal != oneElementState)
        {
             state->hcost++;
        }
        if (twoElementGoal != twoElementState)
        {
             state->hcost++;
        }
        if (threeElementGoal != threeElementState)
        {
             state->hcost++;
        }
        if (fourElementGoal != fourElementState)
        {
             state->hcost++;
        }
        if (fiveElementGoal != fiveElementState)
        {
             state->hcost++;
        }
        if (sixElementGoal != sixElementState)
        {
             state->hcost++;
        }
        if (sevenElementGoal != sevenElementState)
        {
             state->hcost++;
        }
        if (eightElementGoal != eightElementState)
        {
             state->hcost++;
        }
        if (nineElementGoal != nineElementState)
        {
             state->hcost++;
        }

        
        state->pcost = state->pcost + 1 ;
        state->cost = state->pcost + state->hcost ;

    }
    // A* with the Euclidean distance Heuristic
    if (algorithmChoice == 3)
    {
        state->hcost = 0 ;

        int oneElementGoal = goalState[0][0];
        int twoElementGoal = goalState[0][1];
        int threeElementGoal = goalState[0][2];
        int fourElementGoal = goalState[1][0];
        int fiveElementGoal = goalState[1][1];
        int sixElementGoal = goalState[1][2];
        int sevenElementGoal = goalState[2][0];
        int eightElementGoal = goalState[2][1];
        int nineElementGoal = goalState[2][2];

        int oneElementState = state->state[0][0];
        int twoElementState = state->state[0][1];
        int threeElementState = state->state[0][2];
        int fourElementState = state->state[1][0];
        int fiveElementState = state->state[1][1];
        int sixElementState = state->state[1][2];
        int sevenElementState = state->state[2][0];
        int eightElementState = state->state[2][1];
        int nineElementState = state->state[2][2];


        if (state->state[0][0] != goalState[0][0])
        {
            int tile = state->state[0][0];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(0 - goalX, 2) + std::pow(0 - goalY, 2));
        }

        if (state->state[0][1] != goalState[0][1])
        {
            int tile = state->state[0][1];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(0 - goalX, 2) + std::pow(1 - goalY, 2));
        }

        if (state->state[0][2] != goalState[0][2])
        {
            int tile = state->state[0][2];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(0 - goalX, 2) + std::pow(2 - goalY, 2));
        }

        if (state->state[1][0] != goalState[1][0])
        {
            int tile = state->state[1][0];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(1 - goalX, 2) + std::pow(0 - goalY, 2));
        }

        if (state->state[1][1] != goalState[1][1])
        {
            int tile = state->state[1][1];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(1 - goalX, 2) + std::pow(1 - goalY, 2));
        }

        if (state->state[1][2] != goalState[1][2])
        {
            int tile = state->state[1][2];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(1 - goalX, 2) + std::pow(2 - goalY, 2));
        }

        if (state->state[2][0] != goalState[2][0])
        {
            int tile = state->state[2][0];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(2 - goalX, 2) + std::pow(0 - goalY, 2));
        }

        if (state->state[2][1] != goalState[2][1])
        {
            int tile = state->state[2][1];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(2 - goalX, 2) + std::pow(1 - goalY, 2));
        }

        if (state->state[2][2] != goalState[2][2])
        {
            int tile = state->state[2][2];
            int goalX = (tile - 1) / 3;
            int goalY = (tile - 1) % 3;
             state->hcost += std::sqrt(std::pow(2 - goalX, 2) + std::pow(2 - goalY, 2));
        }

        state->pcost = state->pcost + 1 ;
        state->cost = state->pcost + state->hcost ;

        //state->cost = state->cost + euclideanDistance + 1;
    }
}

bool isMatching(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2)
{

    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (v1[j][k] != v2[j][k])
            {
                return false;
            }
        }
    }
    return true;
}