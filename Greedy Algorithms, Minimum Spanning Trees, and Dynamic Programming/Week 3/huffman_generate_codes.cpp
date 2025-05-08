// huffman_generate_codes.cpp
// ------------------------------------------------------------------------
// Builds a Huffman tree from character weights and generates binary
// prefix codes for each character.
//
// This example uses a static character set and outputs the Huffman codes.
//
// Example:
//   Input:  {a, b, c, d, e, f}
//   Weights: {5, 9, 12, 13, 16, 45}
//
// Output:
//   f: 0
//   c: 100
//   d: 101
//   a: 1100
//   b: 1101
//   e: 111
// ------------------------------------------------------------------------

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Node structure for Huffman tree
struct MinHeapNode {
    char data;
    unsigned weight;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned weight) {
        this->data = data;
        this->weight = weight;
        left = right = nullptr;
    }
};

// Comparator for min-heap
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return l->weight > r->weight;
    }
};

// Recursively print codes from root of Huffman tree
void printCodes(MinHeapNode* root, string code) {
    if (!root) return;

    // Print the character and its code (exclude internal '$' nodes)
    if (root->data != '$') {
        cout << root->data << ": " << code << "\n";
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Generate Huffman tree and output codes
void HuffmanCodes(char data[], int weight[], int size) {
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new MinHeapNode(data[i], weight[i]));
    }

    while (minHeap.size() > 1) {
        MinHeapNode* left = minHeap.top(); minHeap.pop();
        MinHeapNode* right = minHeap.top(); minHeap.pop();

        MinHeapNode* parent = new MinHeapNode('$', left->weight + right->weight);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    MinHeapNode* root = minHeap.top();
    printCodes(root, "");
}

int main() {
    char symbols[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int weights[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(symbols) / sizeof(symbols[0]);

    cout << "Huffman Codes:\n";
    HuffmanCodes(symbols, weights, size);

    return 0;
}
