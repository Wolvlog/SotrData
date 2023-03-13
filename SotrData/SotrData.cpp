#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<int> parseLine(string line) {
    vector<int> res;
    stringstream ss(line);
    int x;
    while (ss >> x) {
        res.push_back(x);
    }
    return res;
}

bool is_keyword(vector<int> line, vector<int> keywords) {
    for (int keyword : keywords) {
        if (find(line.begin(), line.end(), keyword) != line.end()) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> data;
    vector<int> filter;
    ifstream input("input.txt");
    ifstream filterFile("filter.txt");
    string line;
    while (getline(input, line)) {
        data.push_back(parseLine(line));
    }
    input.close();
    int x;
    while (filterFile >> x) {
        filter.push_back(x);
    }
    filterFile.close();

    // Keep only the lines that contain one of the keywords
    data.erase(remove_if(data.begin(), data.end(), [&filter](vector<int> line) { return !is_keyword(line, filter); }), data.end());

    // Sort the filtered lines of integers
    sort(data.begin(), data.end(), [](vector<int> a, vector<int> b) { return a[0] < b[0]; });

    // Create the output file stream object
    ofstream output("output.txt");

    // Output the sorted lines of integers to the output file
    for (auto line : data) {
        for (auto x : line)
            output << x << " ";
        output << endl;
    }

    // Close the output file stream object
    output.close();
    return 0;
}
