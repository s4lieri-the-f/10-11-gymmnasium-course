#include <iostream>
#include "matrix.hpp"
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> vec{{1}, {2}};
    vector<vector<int>> vec2{{1, 2, 3}};
    Matrix A(vec);
    Matrix B(vec2);
    cout << A * B;
    return 0;
}
