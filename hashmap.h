#include <vector>
#include "House.h"

// will use a hash map, with separate chaining to solve collisions
class HouseMap{
private:
    // create 5 maps based on the searching criterion
    std::vector<std::vector<House> > houses_by_bedroom;
    std::vector<std::vector<House> > houses_by_bathroom;
    std::vector<std::vector<House> > houses_by_square_feet;
    std::vector<std::vector<House> > houses_by_year_built;
    std::vector<std::vector<House> > houses_by_house_price;
    int num_buckets;
    float load_factor;
    int size;

    int HashBedRoom(int bedrooms) {
        return bedrooms % num_buckets;
    }

    int HashBathroom(float bathrooms) {
        return static_cast<int>(bathrooms) % num_buckets;
    }

    int HashArea(int square_feet) {
        return square_feet % num_buckets;
    }

    int HashPrice(float house_price) {
        return static_cast<int>(house_price) % num_buckets;
    }

    int HashYear(int year_built) {
        return year_built % num_buckets;
    }

    void checkAndRehash() {
        if ((float)size / num_buckets > load_factor)
            rehash();
    }

    void rehash() {
        num_buckets *= 2;
        std::vector<std::vector<House>> new_houses_by_bedroom(num_buckets);
        std::vector<std::vector<House>> new_houses_by_bathroom(num_buckets);
        std::vector<std::vector<House>> new_houses_by_square_feet(num_buckets);
        std::vector<std::vector<House>> new_houses_by_house_price(num_buckets);
        std::vector<std::vector<House>> new_houses_by_year_built(num_buckets);
        for (auto& bucket : houses_by_bedroom) {
            for (auto& house : bucket) {
                int index = HashBedRoom(house.bedrooms);
                new_houses_by_bedroom[index].push_back(house);
            }
        }
        for (auto& bucket : houses_by_bathroom) {
            for (auto& house : bucket) {
                int index = HashBathroom(house.bathrooms);
                new_houses_by_bathroom[index].push_back(house);
            }
        }
        for (auto& bucket : houses_by_square_feet) {
            for (auto& house : bucket) {
                int index = HashArea(house.square_feet);
                new_houses_by_square_feet[index].push_back(house);
            }
        }
        for (auto& bucket : houses_by_house_price) {
            for (auto& house : bucket) {
                int index = HashPrice(house.house_price);
                new_houses_by_house_price[index].push_back(house);
            }
        }
        for (auto& bucket : houses_by_year_built) {
            for (auto& house : bucket) {
                int index = HashYear(house.year_built);
                new_houses_by_year_built[index].push_back(house);
            }
        }
        houses_by_bedroom = std::move(new_houses_by_bedroom);
        houses_by_bathroom = std::move(new_houses_by_bathroom);
        houses_by_square_feet = std::move(new_houses_by_square_feet);
        houses_by_house_price = std::move(new_houses_by_house_price);
        houses_by_year_built = std::move(new_houses_by_year_built);
    }

public:
    HouseMap() {
        num_buckets = 10;
        load_factor = 0.75;
        size = 0;
        houses_by_bedroom.resize(num_buckets);
        houses_by_bathroom.resize(num_buckets);
        houses_by_square_feet.resize(num_buckets);
        houses_by_house_price.resize(num_buckets);
        houses_by_year_built.resize(num_buckets);
    }

    void InsertBedroom(House house) {
        int index = HashBedRoom(house.bedrooms);
        if (houses_by_bedroom[index].empty())
            size++;
        houses_by_bedroom[index].push_back(house);
        checkAndRehash();
    }

    void InsertBathroom(House house) {
        int index = HashBathroom(house.bathrooms);
        if (houses_by_bathroom[index].empty())
            size++;
        houses_by_bathroom[index].push_back(house);
        checkAndRehash();
    }

    void InsertSquareFeet(House house) {
        int index = HashArea(house.square_feet);
        if (houses_by_square_feet[index].empty())
            size++;
        houses_by_square_feet[index].push_back(house);
        checkAndRehash();
    }

    void InsertHousePrice(House house) {
        int index = HashPrice(house.house_price);
        if (houses_by_house_price[index].empty())
            size++;
        houses_by_house_price[index].push_back(house);
        checkAndRehash();
    }

    void InsertYearBuilt(House house) {
        int index = HashYear(house.year_built);
        if (houses_by_year_built[index].empty())
            size++;
        houses_by_year_built[index].push_back(house);
        checkAndRehash();
    }

    std::vector<House> SearchByBedroom(int bedrooms){
        int code = HashBedRoom(bedrooms);
        std::vector<House> result;
        for(int i = 0; i < houses_by_bedroom[code].size(); i++){
            if(houses_by_bedroom[code][i].bedrooms == bedrooms){
                result.push_back(houses_by_bedroom[code][i]);
            }
        }
        return result;
    }

    std::vector<House> SearchByBathroom(int bathrooms){
        int code = HashBathroom(bathrooms);
        std::vector<House> result;
        for(int i = 0; i < houses_by_bathroom[code].size(); i++){
            if(houses_by_bathroom[code][i].bathrooms == bathrooms){
                result.push_back(houses_by_bathroom[code][i]);
            }
        }
        return result;
    }

    std::vector<House> SearchByArea(float square_feet){
        int code = HashArea(square_feet);
        std::vector<House> result;
        for(int i = 0; i < houses_by_square_feet[code].size(); i++){
            if(houses_by_square_feet[code][i].square_feet == square_feet){
                result.push_back(houses_by_square_feet[code][i]);
            }
        }
        return result;
    }

    std::vector<House> SearchByHousePrice(float house_price){
        int code = HashPrice(house_price);
        std::vector<House> result;
        for(int i = 0; i < houses_by_house_price[code].size(); i++){
            if(houses_by_house_price[code][i].house_price == house_price){
                result.push_back(houses_by_house_price[code][i]);
            }
        }
        return result;
    }

    std::vector<House> SearchByYearBuilt(int year_built){
        int code = HashYear(year_built);
        std::vector<House> result;
        for(int i = 0; i < houses_by_year_built[code].size(); i++){
            if(houses_by_year_built[code][i].year_built == year_built){
                result.push_back(houses_by_year_built[code][i]);
            }
        }
        return result;
    }

    void Display(vector<House> houses){
        for(int i = 0; i < 5; i++){
            cout << "Number of bedrooms: " << houses[i].bedrooms << endl;
            cout << "Number of bathrooms: " << houses[i].bathrooms << endl;
            cout << "Area: " << houses[i].square_feet << endl;
            cout << "Year built: " << houses[i].year_built << endl;
            cout << "Price: " << houses[i].house_price << endl;
            cout << endl;
        }
    }
};

