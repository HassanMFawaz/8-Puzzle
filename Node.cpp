#include "Node.h"

//Constructor
Node::Node(Node* parent, int pcost, int hcost, int cost, std::string action, std::vector<std::vector<int>>& state)
: parent(parent), pcost(pcost), hcost(hcost), cost(cost), action(action), state(state){}

void Node::setState(std::vector<std::vector<int>>& newState){
    state = newState;
}

void Node::printState() 
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            std::cout << state[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



bool Node::checkDone() {
    std::vector<std::vector<int>> completeState = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    if (completeState == state) {
        std::cout << "The Goal State Was Achieved:" << std::endl;
        return true;
    }
    return false;
}


std::vector<std::vector<int>> Node::getState() const {
    return state;
}


void Node::printTree() {
    if (parent) {
        parent->printTree();
        std::cout << std::endl ; 
    }
    printState();
}