#include "dijkstras.h"

void run_test_on_file(const string& filename) {
    cout << "==============================\n";
    cout << "Running test on: " << filename << endl;
    cout << "==============================\n";

    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous); // Start from vertex 0

    for (int v = 0; v < G.numVertices; ++v) {
        vector<int> path = extract_shortest_path(distances, previous, v);
        print_path(path, distances[v]);
    }

    cout << endl;
}

int main() {
    // List of all test files to run
    vector<string> test_files = {"src/small.txt", "src/medium.txt", "src/large.txt", "src/largest.txt"};

    for (const string& file : test_files) {
        run_test_on_file(file);
    }

    return 0;
}
