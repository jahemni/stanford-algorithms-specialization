// huffman_tree_depth.cpp
// --------------------------------------------------------------------
// Builds a full Huffman tree and computes the maximum and minimum
// codeword lengths (i.e., the depth of leaf nodes).
//
// Input: "huffman.txt"
// Format:
//   Line 1: number of symbols
//   Next N lines: symbol weights
//
// Output:
//   Maximum and minimum codeword lengths from the tree
// --------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

// Node structure for Huffman tree
struct MinHeapNode {
    int data;
    unsigned weight;
    MinHeapNode *left, *right;

    MinHeapNode(int data, unsigned weight) {
        this->data = data;
        this->weight = weight;
        left = right = nullptr;
    }
};

// Custom comparator for priority queue (min-heap by weight)
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return l->weight > r->weight;
    }
};

// Compute maximum depth (longest codeword)
int maxDepth(MinHeapNode* root) {
    if (!root) return -1;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

// Compute minimum depth (shortest codeword)
int minDepth(MinHeapNode* root) {
    if (!root) return -1;
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}

int main() {
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    int n;
    ifstream file("huffman.txt");
    file >> n;

    int w;
    while (file >> w) {
        minHeap.push(new MinHeapNode(w, w));
    }

    // Build Huffman Tree
    while (minHeap.size() > 1) {
        MinHeapNode* left = minHeap.top(); minHeap.pop();
        MinHeapNode* right = minHeap.top(); minHeap.pop();

        MinHeapNode* parent = new MinHeapNode(-1, left->weight + right->weight);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    MinHeapNode* root = minHeap.top();

    cout << "Maximum codeword length: " << maxDepth(root) << endl; // Expected: 19
    cout << "Minimum codeword length: " << minDepth(root) << endl; // Expected: 9

    return 0;
}
