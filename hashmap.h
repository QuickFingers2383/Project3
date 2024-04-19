#include <vector>

struct House{
    int num_bedroom;
    int num_bathroom;
    int year;
    float area;
    float price;
};

// will use a hash map, with separate chaining to solve collisions
class HouseMap{
    // create 5 maps based on the searching criterion
    std::vector<std::vector<House>> houses_by_bedroom;
    std::vector<std::vector<House>> houses_by_bathroom;
    std::vector<std::vector<House>> houses_by_area;
    std::vector<std::vector<House>> houses_by_year;
    std::vector<std::vector<House>> houses_by_price;

public:
    // hash function for number of bedroom as key
    int HashBedRoom(int num_bedroom){
        // since number of bedroom only ranges from 2 to 6, the hash function can just return that number minus 2
        return num_bedroom-2;
    }

    void InsertBedroom(House house){
        // insert the house into map with hashed index
        houses_by_bedroom[HashBedRoom(house.num_bedroom)].push_back(house);
    }

    std::vector<House> SearchByBedroom(int num_bedroom){
        int code = HashBedRoom(num_bedroom);
        std::vector<House> result;
        for(int i = 0; i < houses_by_bedroom[code].size(); i++){
            if(houses_by_bedroom[code][i].num_bedroom == num_bedroom){
                result.push_back(houses_by_bedroom[code][i]);
            }
        }
        return result;
    }

    int HashBathroom(int num_bathroom){
        return num_bathroom - 2;
    }

    void InsertBathroom(House house){
        houses_by_bathroom[HashBathroom(house.num_bathroom)].push_back(house);
    }

    std::vector<House> SearchByBathroom(int num_bathroom){
        int code = HashBathroom(num_bathroom);
        std::vector<House> result;
        for(int i = 0; i < houses_by_bathroom[code].size(); i++){
            if(houses_by_bathroom[code][i].num_bathroom == num_bathroom){
                result.push_back(houses_by_bathroom[code][i]);
            }
        }
        return result;
    }

    int HashArea(float area){
        // range of area is 1500 to 3500
        int scaledValue = static_cast<int>((area - 1500.0f) * 100.0f);
        return scaledValue % 10000;
    }

    void InsertArea(House house){
        houses_by_area[HashArea(house.area)].push_back(house);
    }

    std::vector<House> SearchByArea(float area){
        int code = HashArea(area);
        std::vector<House> result;
        for(int i = 0; i < houses_by_area[code].size(); i++){
            if(houses_by_area[code][i].area == area){
                result.push_back(houses_by_area[code][i]);
            }
        }
        return result;
    }

    int HashPrice(float price){
        // price ranges from 150k to 739k
        int scaledValue = static_cast<int>(price - 150000);
        return scaledValue % 10000;
    }

    void InsertPrice(House house){
        houses_by_price[HashPrice(house.price)].push_back(house);
    }

    std::vector<House> SearchByPrice(float price){
        int code = HashPrice(price);
        std::vector<House> result;
        for(int i = 0; i < houses_by_price[code].size(); i++){
            if(houses_by_price[code][i].price == price){
                result.push_back(houses_by_price[code][i]);
            }
        }
        return result;
    }

    int HashYear(int year){
        // range of the year built is 1980 to 2022
        return year - 1980;
    }

    void InsertYear(House house){
        houses_by_year[HashYear(house.year)].push_back(house);
    }

    std::vector<House> SearchByYear(int year){
        int code = HashYear(year);
        std::vector<House> result;
        for(int i = 0; i < houses_by_year[code].size(); i++){
            if(houses_by_year[code][i].year == year){
                result.push_back(houses_by_year[code][i]);
            }
        }
        return result;
    }
};
