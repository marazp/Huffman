#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "treeWrapper.h"

using namespace std;

// Function declaration
unordered_map<char, int> letterCounter(string input);
TreeWrapper createTrees(const unordered_map<char, int>& letterCounted);

int main() {

    string input = "aaaabbbcddhhiiiii";

    // Count the frequency of each character in the input
    unordered_map<char, int> letterCounted = letterCounter(input);

    // Create and merge trees using the character frequency map
    TreeWrapper queue = createTrees(letterCounted);

    // Print the resulting Huffman tree
    vector<char> bitString;
    queue.tree->printTree(bitString);
    
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

    // Return the map containing character frequencies
    return letterMap;
}

// Function to create and merge trees
TreeWrapper createTrees(const unordered_map<char, int>& letterCounted){

    priority_queue<TreeWrapper> q;

    // Create base trees for each character-frequency pair
    for(const auto & pair: letterCounted) {
        // Create a TreeWrapper object for each character and push it into the priority queue
        q.push(TreeWrapper(new Tree(pair.second, pair.first)));
    }

    // Merge trees in the priority queue until a single tree remains
    while (q.size() > 1) {

        // Extract the two trees with the smallest weights
        Tree* t1 = q.top().tree; 
        q.pop();
        Tree* t2 = q.top().tree;
        q.pop();

        //Create a new merges tree with the combined weight
        int weight = t1->getWeight() + t2->getWeight();
        q.push(TreeWrapper(new Tree(weight, t1, t2)));
    }

    // Return the root of the final merged tree
    return q.top();
}