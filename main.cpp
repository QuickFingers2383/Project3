#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "b+tree.h"
#include "hashmap.h"
#include <chrono>

using namespace std;

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

void timer(int search_type, string parameter) {
    auto bp_start = chrono::high_resolution_clock::now();
    // run b+ tree search function
    // TODO: Add search functions for each type
    if(search_type == 1) {

    } else if(search_type == 2) {

    } else if(search_type == 3) {

    } else if(search_type == 4) {

    } else if(search_type == 5) {

    }

    auto bp_stop = chrono::high_resolution_clock::now();

    // display stuff
    auto bp_duration = chrono::duration_cast<chrono::microseconds>(bp_stop-bp_start);
    cout << "Duration: " << bp_duration.count() << endl;

    auto h_start = chrono::high_resolution_clock::now();
    // run b+ tree search function
    // TODO: Add search functions for each type
    if(search_type == 1) {

    } else if(search_type == 2) {

    } else if(search_type == 3) {

    } else if(search_type == 4) {

    } else if(search_type == 5) {

    }

    auto h_stop = chrono::high_resolution_clock::now();

    // TODO: Display search results
    auto h_duration = chrono::duration_cast<chrono::microseconds>(h_stop-h_start);
    cout << "Duration: " << h_duration.count() << endl;

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

    HouseMap housemap;
    for(int i = 0; i < houses.size(); i++){
        housemap.InsertBathroom(houses[i]);
        housemap.InsertBedroom(houses[i]);
        housemap.InsertArea(houses[i]);
        housemap.InsertPrice(houses[i]);
        housemap.InsertYear(houses[i]);
    }

    cout << "-----------------------------------------------" << endl;
    cout << "Welcome to Cillow! The search engine for homes!" << endl;
    cout << "-----------------------------------------------" << endl;

    int option;
    string num_bedrooms, num_bathrooms, num_sqft, year, price;

    // run search functions then display results of search function and time it took
    while(true) {
        cout << "Choose what option you want: " << endl;
        cout << "Search by Square Feet (1)\n"
                "Search by bedrooms (2)\n"
                "Search by bathrooms (3)\n"
                "Search by year built (4)\n"
                "Search by price (5)\n"
                "Quit (6) \n" << endl;
        cin >> option;
        if(option == 1) {
            cout << "Square feet: 1.5k-2k, 2k-2.5k, 2.5k-3k, 3k-3.5k" << endl;
            cin >> num_sqft;
            timer(1, num_sqft);
        }
        if(option == 2) {
            cout << "Number of bedrooms: 2, 3, 4, 5, 6" << endl;
            cin >> num_bedrooms;
            timer(2, num_bedrooms);
        }
        if(option == 3) {
            cout << "Number of bathrooms: 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8" << endl;
            cin >> num_bathrooms;
            timer(3, num_bathrooms);
        }
        if(option == 4) {
            cout << "Year built: 1980-1985, 1985-1990, 1990-1995, 1995-2000, 200-2005, 2005-2010, 2010-2015, 2015+" << endl;
            cin >> year;
            timer(4, year);
        }
        if(option == 5) {
            cout << "Price: 150k-200k, 200k-250k, 250k-300k, 300k-350k. 350k-400k, 400k-450k, 450k-500k, 500k-550k, 550k-600k, 600k+" << endl;
            cin >> price;
            timer(5, price);
        }
        if(option == 6) {
            break;
        }
    }

    return 0;
}
