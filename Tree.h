#include <vector>
using namespace std;

class Tree {
    public:
        Tree(int w, char c) {
            weight = w;
            this->c = c;
        };
        Tree(int w, Tree* t1, Tree* t2) {
            weight = w;
            left = t1;
            right = t2;
        };
        ~Tree() {
            delete left;
            delete right;
        };
        int getWeight() const{
            return weight;
        };
        void printTree(vector<char>& bitString, size_t index=0) const {
            
            if (!left && !right) { // Leaf node
                cout << string(bitString.begin(), bitString.end()) << " : " << c << endl;
                return;
            }
            if (left) {
                bitString.push_back('0');
                left->printTree(bitString);
                bitString.pop_back();
            }
            if (right) {
                bitString.push_back('1');
                right->printTree(bitString);
                bitString.pop_back();
            }

        };
        
    private:
        Tree* left;
        Tree* right;
        int weight;
        char c;
};