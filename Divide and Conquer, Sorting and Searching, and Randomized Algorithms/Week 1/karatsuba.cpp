// karatsuba.cpp
// ---------------------------------------------
// Implementation of Karatsuba Multiplication
// ---------------------------------------------
// Karatsuba is a divide-and-conquer algorithm that multiplies two large integers
// faster than the classical O(n²) method. It reduces the number of recursive
// multiplications to three, achieving approximately O(n^1.58) complexity.
//
// The algorithm works by splitting each number into two halves and recursively
// computing three key products: ac, bd, and (a+b)(c+d), then combining the results.

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Recursive function to compute multiplication using Karatsuba algorithm
unsigned long long karatsuba(unsigned long long x, unsigned long long y) {
    // Base case: if either number is single-digit, perform direct multiplication
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Convert to string to determine number of digits
    string a_str = to_string(x);
    string b_str = to_string(y);

    // Take the max number of digits
    size_t n = max(a_str.length(), b_str.length());
    size_t half = n / 2;

    // Split the numbers into halves
    unsigned long long high1 = stoull(a_str.substr(0, a_str.length() - half));
    unsigned long long low1  = stoull(a_str.substr(a_str.length() - half));
    unsigned long long high2 = stoull(b_str.substr(0, b_str.length() - half));
    unsigned long long low2  = stoull(b_str.substr(b_str.length() - half));

    // Three recursive calls
    unsigned long long z0 = karatsuba(low1, low2);
    unsigned long long z1 = karatsuba((low1 + high1), (low2 + high2));
    unsigned long long z2 = karatsuba(high1, high2);

    // Combine the results using Karatsuba formula
    return z2 * pow(10, 2 * half) + (z1 - z2 - z0) * pow(10, half) + z0;
}

int main() {
    unsigned long long num1 = 12345678;
    unsigned long long num2 = 87654321;

    cout << "Karatsuba Multiplication of " << num1 << " and " << num2 << " is:\n";
    cout << karatsuba(num1, num2) << endl;

    return 0;
}
