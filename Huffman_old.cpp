#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "treeWrapper.h"

using namespace std;

unordered_map<char, int> letterCounter(string input);

int main() {

    string input = "aaaabbbcddhhiiiii";

    unordered_map<char, int> letterCounted = letterCounter(input);

    priority_queue<TreeWrapper> q;

    // Create base trees and put them in a queue
    for(const auto & pair: letterCounted) {
        q.push(TreeWrapper(new Tree(pair.second, pair.first)));
    }

    while (q.size() > 1) {
        Tree* t1 = q.top().tree; 
        q.pop();
        Tree* t2 = q.top().tree;
        q.pop();

        //Merge first and second spot in queue
        int weight = t1->getWeight() + t2->getWeight();
        q.push(TreeWrapper(new Tree(weight, t1, t2)));
    }

    vector<char> bitString;
    q.top().tree->printTree(bitString);
    
    return 0;
}

// Function to count the occurrences of each character in the input string
unordered_map<char, int> letterCounter(string input) {

    unordered_map<char, int> letterMap;

    // Traverse each character in the string
    for(int i=0; i< input.length(); i++) {
        
        // If the character is already in the map, increment its count
        if(letterMap.find(input[i]) != letterMap.end()){
            letterMap[input[i]]++;
        }

        // Otherwise, add the character to the map with a count of 1
        else {
            letterMap[input[i]] = 1;
        }
    }

    // Return the map containing character counts
    return letterMap;
}