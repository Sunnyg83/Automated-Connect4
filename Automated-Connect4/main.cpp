#include "provided.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void testSmartMove(int cols, int levels, int N) {
    Scaffold s(cols, levels);
    SmartPlayer sp("AI");

    cout << "Testing SmartPlayer on " << cols << "x" << levels << " board with N = " << N << "...\n";

    auto start = high_resolution_clock::now();
    int move = sp.chooseMove(s, N, RED); // Or BLACK
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(end - start).count();

    cout << "Chosen move: " << move << " | Time: " << duration << " seconds\n";

    if (duration > 10)
        cout << "❌ FAILED: Took too long.\n";
    else
        cout << "✅ PASSED: Within time limit.\n";

    cout << "---------------------------\n";
}

int main() {
    testSmartMove(3, 5, 5);
    testSmartMove(4, 4, 3);
    testSmartMove(5, 3, 2);
    testSmartMove(5, 2, 5);
    testSmartMove(6, 2, 3);
    testSmartMove(10, 2, 2);
    testSmartMove(10, 1, 4);

    return 0;
}

