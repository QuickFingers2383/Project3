#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "b+tree.h"
#include "hashmap.h"
#include "House.h"
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
        House house;
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

void timer(int search_type, float parameter, BPlusTree bptree, HouseMap housemap) {
    auto h_start = chrono::high_resolution_clock::now();
    // run hash map search function
    cout << "Displaying One Result: " << endl;
    if(search_type == 1) {
        housemap.Display(housemap.SearchByArea(parameter));
    } else if(search_type == 2) {
        housemap.Display(housemap.SearchByBedroom(parameter));
    } else if(search_type == 3) {
        housemap.Display(housemap.SearchByBathroom(parameter));
    } else if(search_type == 4) {
        housemap.Display(housemap.SearchByYearBuilt(parameter));
    } else if(search_type == 5) {
        housemap.Display(housemap.SearchByHousePrice(parameter));
    }

    auto h_stop = chrono::high_resolution_clock::now();
    
    auto bp_duration = chrono::duration_cast<chrono::microseconds>(h_stop-h_start);
    cout << "Duration of Hash map: " << bp_duration.count() << endl;
    cout << "-------------------------------" << endl;  // separate two methods

    auto bp_start = chrono::high_resolution_clock::now();
    // run b+ tree search function
    cout << "Displaying One Result: " << endl;
    // TODO: Display search results
    if(search_type == 1) {
        bptree.Search(parameter, "square_feet");
    } else if(search_type == 2) {
        bptree.Search(parameter, "bedrooms");
    } else if(search_type == 3) {
        bptree.Search(parameter, "bathrooms");
    } else if(search_type == 4) {
        bptree.Search(parameter, "year");
    } else if(search_type == 5) {
        bptree.Search(parameter, "price");
    }

    auto bp_stop = chrono::high_resolution_clock::now();
    
    auto h_duration = chrono::duration_cast<chrono::microseconds>(bp_stop-bp_start);
    cout << "Duration of B+ Tree: " << h_duration.count() << endl;
}
int main() {
    // Create a B+ tree
    BPlusTree bptree(3);

    // Only the absolute path works, not sure why. Change this path in your computer!
    string filename = "C:\\Users\\yjwan\\CLionProjects\\Project3\\data\\house_data1.csv";
    vector<House> houses = parseCSV(filename);
    if (houses.empty()) {
        cout << "No housing data found in file: " << filename << endl;
        return 1;
    }

    HouseMap housemap;
    for(int i = 0; i < houses.size(); i++){
        housemap.InsertBathroom(houses[i]);
        housemap.InsertBedroom(houses[i]);
        housemap.InsertSquareFeet(houses[i]);
        housemap.InsertHousePrice(houses[i]);
        housemap.InsertYearBuilt(houses[i]);
    }

    cout << "-----------------------------------------------" << endl;
    cout << "Welcome to Cillow! The search engine for homes!" << endl;
    cout << "-----------------------------------------------" << endl;

    int option;
    float num_sqft, num_bedrooms, num_bathrooms, year, price;

    // run search functions then display results of search function and time it took
    while(true) {
        cout << "Choose what option you want: \n" << endl;
        cout << "Search by Square Feet (1)\n"
                "Search by bedrooms (2)\n"
                "Search by bathrooms (3)\n"
                "Search by year built (4)\n"
                "Search by price (5)\n"
                "Quit (6)" << endl;
        cin >> option;
        if(option == 1) {
            // Insert housing data into the B+ tree
            for (const auto& house : houses) {
                bptree.Insert(house, "square_feet");
            }
            cout << "Square feet (between 1.5k-3.5k)" << endl;
            cin >> num_sqft;
            timer(1, num_sqft, bptree, housemap);
        }
        if(option == 2) {
            // Insert housing data into the B+ tree
            for (const auto& house : houses) {
                bptree.Insert(house, "bedrooms");
            }
            cout << "Number of bedrooms: 2, 3, 4, 5, 6" << endl;
            cin >> num_bedrooms;
            timer(2, num_bedrooms, bptree, housemap);
        }
        if(option == 3) {
            // Insert housing data into the B+ tree
            for (const auto& house : houses) {
                bptree.Insert(house, "bathrooms");
            }
            cout << "Number of bathrooms: 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8" << endl;
            cin >> num_bathrooms;
            timer(3, num_bathrooms, bptree, housemap);
        }
        if(option == 4) {
            // Insert housing data into the B+ tree
            for (const auto& house : houses) {
                bptree.Insert(house, "year");
            }
            cout << "Year built: 1980-2022" << endl;
            cin >> year;
            timer(4, year, bptree, housemap);
        }
        if(option == 5) {
            // Insert housing data into the B+ tree
            for (const auto& house : houses) {
                bptree.Insert(house, "price");
            }
            cout << "Price: 150k-739k" << endl;
            cin >> price;
            timer(5, price, bptree, housemap);
        }
        if(option == 6) {
            break;
        }
    }

    return 0;
}
