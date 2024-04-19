#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "b+tree.h"

// CSV parsing function
vector<House> parseCSV(const string& filename) {
    // initialize struct
    vector<House> houses;
    ifstream file(filename);
    // checks if file exists
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return houses;
    }
    // skips first line, which are column titles
    string line;
    getline(file, line);
    // Transfers CSV data into a vector of houses
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        House house{};
        // Read each cell of the line
        getline(ss, cell, ','); // square_feet
        house.square_feet = stoi(cell);
        getline(ss, cell, ','); // bedrooms
        house.bedrooms = stoi(cell);
        getline(ss, cell, ','); // bathrooms
        house.bathrooms = stof(cell);
        getline(ss, cell, ','); // year_built
        house.year_built = stoi(cell);
        getline(ss, cell, ','); // house_price
        house.house_price = stod(cell);
        // Add the house to the vector
        houses.push_back(house);
    }
    file.close();
    return houses;
}

int main() {
    // Create a B+ tree
    BPlusTree bptree(3);

    // Only the absolute path works, not sure why. Change this path in your computer!
    string filename = R"(C:\Users\yjwan\CLionProjects\Project3\data\house_data1.csv)";
    vector<House> houses = parseCSV(filename);
    if (houses.empty()) {
        cout << "No housing data found in file: " << filename << endl;
        return 1;
    }

    // Insert housing data into the B+ tree
    for (const auto& house : houses) {
        bptree.insert(house);
    }

    return 0;
}
