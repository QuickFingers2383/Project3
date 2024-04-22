#include <vector>
#include "House.h"

// will use a hash map, with separate chaining to solve collisions
class HouseMap{
private:
    // create 5 maps based on the searching criterion
    std::vector<std::vector<House> > houses_by_bedroom;
    int num_buckets_bedroom;
    float load_factor_bedroom;
    int size_bedroom;
    std::vector<std::vector<House> > houses_by_bathroom;
    int num_buckets_bathroom;
    float load_factor_bathroom;
    int size_bathroom;
    std::vector<std::vector<House> > houses_by_square_feet;
    int num_buckets_sf;
    float load_factor_sf;
    int size_sf;
    std::vector<std::vector<House> > houses_by_year_built;
    int num_buckets_yb;
    float load_factor_yb;
    int size_yb;
    std::vector<std::vector<House> > houses_by_house_price;
    int num_buckets_p;
    float load_factor_p;
    int size_p;

    int HashBedRoom(int bedrooms) {
        return bedrooms % num_buckets_bedroom;
    }

    int HashBathroom(float bathrooms) {
        return static_cast<int>(bathrooms) % num_buckets_bathroom;
    }

    int HashArea(int square_feet) {
        return square_feet % num_buckets_sf;
    }

    int HashPrice(float house_price) {
        return static_cast<int>(house_price) % num_buckets_p;
    }

    int HashYear(int year_built) {
        return year_built % num_buckets_yb;
    }

    void checkBedroom() {
        if ((float)size_bedroom / num_buckets_bedroom > load_factor_bedroom)
            rehashBedroom();
    }

    void rehashBedroom() {
        num_buckets_bedroom *= 2;
        std::vector<std::vector<House>> new_houses_by_bedroom(num_buckets_bedroom);
        for (auto& bucket : houses_by_bedroom) {
            for (auto& house : bucket) {
                int index = HashBedRoom(house.bedrooms);
                new_houses_by_bedroom[index].push_back(house);
            }
        }
        houses_by_bedroom = std::move(new_houses_by_bedroom);
    }

    void checkBathroom() {
        if ((float)size_bathroom / num_buckets_bathroom > load_factor_bathroom)
            rehashBathroom();
    }

    void rehashBathroom() {
        num_buckets_bathroom *= 2;
        std::vector<std::vector<House>> new_houses_by_bathroom(num_buckets_bathroom);
        for (auto& bucket : houses_by_bathroom) {
            for (auto& house : bucket) {
                int index = HashBathroom(house.bathrooms);
                new_houses_by_bathroom[index].push_back(house);
            }
        }
        houses_by_bathroom = std::move(new_houses_by_bathroom);
    }

    void checkPrice() {
        if ((float)size_p / num_buckets_p > load_factor_p)
            rehashPrice();
    }

    void rehashPrice() {
        num_buckets_p *= 2;
        std::vector<std::vector<House>> new_houses_by_p(num_buckets_p);
        for (auto& bucket : houses_by_house_price) {
            for (auto& house : bucket) {
                int index = HashPrice(house.house_price);
                new_houses_by_p[index].push_back(house);
            }
        }
        houses_by_house_price = std::move(new_houses_by_p);
    }

    void checkArea() {
        if ((float)size_sf / num_buckets_sf > load_factor_sf)
            rehashArea();
    }

    void rehashArea() {
        num_buckets_sf *= 2;
        std::vector<std::vector<House>> new_houses_by_sf(num_buckets_sf);
        for (auto& bucket : houses_by_square_feet) {
            for (auto& house : bucket) {
                int index = HashArea(house.square_feet);
                new_houses_by_sf[index].push_back(house);
            }
        }
        houses_by_square_feet = std::move(new_houses_by_sf);
    }

    void checkYear() {
        if ((float)size_yb / num_buckets_yb > load_factor_yb)
            rehashYear();
    }

    void rehashYear() {
        num_buckets_yb *= 2;
        std::vector<std::vector<House>> new_houses_by_yb(num_buckets_yb);
        for (auto& bucket : houses_by_year_built) {
            for (auto& house : bucket) {
                int index = HashYear(house.year_built);
                new_houses_by_yb[index].push_back(house);
            }
        }
        houses_by_year_built = std::move(new_houses_by_yb);
    }

public:
    HouseMap() {
        num_buckets_bedroom = 10;
        num_buckets_bathroom = 10;
        num_buckets_yb = 10;
        num_buckets_sf = 10;
        num_buckets_p = 10;
        load_factor_bedroom = 0.75;
        load_factor_bathroom = 0.75;
        load_factor_sf = 0.75;
        load_factor_yb = 0.75;
        load_factor_p = 0.75;
        size_bedroom = 0;
        size_bathroom = 0;
        size_sf = 0;
        size_yb = 0;
        size_p = 0;
        houses_by_bedroom.resize(num_buckets_bedroom);
        houses_by_bathroom.resize(num_buckets_bathroom);
        houses_by_square_feet.resize(num_buckets_sf);
        houses_by_house_price.resize(num_buckets_p);
        houses_by_year_built.resize(num_buckets_yb);
    }

    void InsertBedroom(House house) {
        int index = HashBedRoom(house.bedrooms);
        if (houses_by_bedroom[index].empty())
            size_bedroom++;
        houses_by_bedroom[index].push_back(house);
        checkBedroom();
    }

    void InsertBathroom(House house) {
        int index = HashBathroom(house.bathrooms);
        if (houses_by_bathroom[index].empty())
            size_bathroom++;
        houses_by_bathroom[index].push_back(house);
        checkBathroom();
    }

    void InsertSquareFeet(House house) {
        int index = HashArea(house.square_feet);
        if (houses_by_square_feet[index].empty())
            size_sf++;
        houses_by_square_feet[index].push_back(house);
        checkArea();
    }

    void InsertHousePrice(House house) {
        int index = HashPrice(house.house_price);
        if (houses_by_house_price[index].empty())
            size_p++;
        houses_by_house_price[index].push_back(house);
        checkPrice();
    }

    void InsertYearBuilt(House house) {
        int index = HashYear(house.year_built);
        if (houses_by_year_built[index].empty())
            size_yb++;
        houses_by_year_built[index].push_back(house);
        checkYear();
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

    std::vector<House> SearchByBathroom(float bathrooms){
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
        if (houses.empty()){
            cout << "No such house!" << endl;
            cout << endl;
        }
        else{
            cout << "Number of bedrooms: " << houses[0].bedrooms << endl;
            cout << "Number of bathrooms: " << houses[0].bathrooms << endl;
            cout << "Area: " << houses[0].square_feet << endl;
            cout << "Year built: " << houses[0].year_built << endl;
            cout << "Price: " << houses[0].house_price << endl;
            cout << endl;
        }
    }
};
