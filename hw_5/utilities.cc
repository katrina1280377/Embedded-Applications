#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <regex>
#include "utilities.h"

using namespace std;

void sort_by_magnitude(vector<double>& vec) {
    sort(vec.begin(), vec.end(), [](double a, double b) {
        return abs(a) < abs(b);
    });
}

TypedArray<TypedArray<double>> read_matrix_csv(const string& path) {
    ifstream file(path);

    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    TypedArray<TypedArray<double>> matrix;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        TypedArray<double> row;
        string value;

        while (getline(ss, value, ',')) {
            try {
                row.set(row.size(), stod(value));
            } catch (const invalid_argument& e) {
                throw runtime_error("Invalid data in CSV file");
            }
        }

        matrix.set(matrix.size(), row);
    }

    file.close();
    return matrix;
}

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const string& path) {
    ofstream file(path);

    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.safe_get(i).size(); ++j) {
            file << matrix.safe_get(i).get(j);
            if (j != matrix.safe_get(i).size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

     file.close();
}

map<string, int> occurrence_map(const string& path) {
    ifstream file(path);

    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    map<string, int> occurrences;
    string line;

    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        stringstream ss(line);
        string word;
        while (ss >> word) {
            // Remove punctuation at the end of the word
            while (!word.empty() && ispunct(word.back()) && word.back() != '\'') {
                word.pop_back();
            }

            // Remove punctuation at the beginning of the word
            while (!word.empty() && ispunct(word.front()) && word.front() != '\'') {
                word.erase(word.begin());
            }

            // Check if the word contains any invalid characters
            if (regex_search(word, regex("[^a-z0-9']"))) {
                continue; // Skip if it contains invalid characters
            }

            if (occurrences.find(word) == occurrences.end()) {
                occurrences[word] = 1;
            } else {
                occurrences[word]++;
            }
        }
    }

    for (const auto& pair : occurrences) {
        cout << pair.first << ": " << pair.second << endl;
    }
    file.close();
    return occurrences;
}