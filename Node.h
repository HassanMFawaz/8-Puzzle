// Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>

class Node {
private:
public:

//Constructor
Node(Node* parent, int pcost, int hcost, int cost, std::string action, std::vector<std::vector<int>>& state);


Node* parent ;
int pcost ;
int hcost ;
int cost ;
std::string action ;
std::vector<std::vector<int>> state ;
std::vector<std::vector<int>> getState() const;

//Function
bool checkDone();
void printState();
void printTree();
void setState(std::vector<std::vector<int>>& state);


};

#endif