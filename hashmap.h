#include <vector>

struct House{
    int bedrooms;
    int bathrooms;
    int year_built;
    float square_feet;
    float house_price;
};

// will use a hash map, with separate chaining to solve collisions
class HouseMap{
    // create 5 maps based on the searching criterion
    std::vector<std::vector<House>> houses_by_bedroom;
    std::vector<std::vector<House>> houses_by_bathroom;
    std::vector<std::vector<House>> houses_by_square_feet;
    std::vector<std::vector<House>> houses_by_year_built;
    std::vector<std::vector<House>> houses_by_house_price;

public:
    // hash function for number of bedroom as key
    int HashBedRoom(int bedrooms){
        // since number of bedroom only ranges from 2 to 6, the hash function can just return that number minus 2
        return bedrooms-2;
    }

    void InsertBedroom(House house){
        // insert the house into map with hashed index
        houses_by_bedroom[HashBedRoom(house.bedrooms)].push_back(house);
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

    int HashBathroom(int bathrooms){
        return bathrooms - 2;
    }

    void InsertBathroom(House house){
        houses_by_bathroom[HashBathroom(house.bathrooms)].push_back(house);
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

    int HashArea(float square_feet){
        // range of square_feet is 1500 to 3500
        int scaledValue = static_cast<int>((square_feet - 1500.0f) * 100.0f);
        return scaledValue % 10000;
    }

    void Insertsquare_feet(House house){
        houses_by_square_feet[HashArea(house.square_feet)].push_back(house);
    }

    std::vector<House> SearchBysquare_feet(float square_feet){
        int code = HashArea(square_feet);
        std::vector<House> result;
        for(int i = 0; i < houses_by_square_feet[code].size(); i++){
            if(houses_by_square_feet[code][i].square_feet == square_feet){
                result.push_back(houses_by_square_feet[code][i]);
            }
        }
        return result;
    }

    int HashPrice(float house_price){
        // house_price ranges from 150k to 739k
        int scaledValue = static_cast<int>(house_price - 150000);
        return scaledValue % 10000;
    }

    void Inserthouse_price(House house){
        houses_by_house_price[HashPrice(house.house_price)].push_back(house);
    }

    std::vector<House> SearchByhouse_price(float house_price){
        int code = HashPrice(house_price);
        std::vector<House> result;
        for(int i = 0; i < houses_by_house_price[code].size(); i++){
            if(houses_by_house_price[code][i].house_price == house_price){
                result.push_back(houses_by_house_price[code][i]);
            }
        }
        return result;
    }

    int HashYear(int year_built){
        // range of the year_built built is 1980 to 2022
        return year_built - 1980;
    }

    void Insertyear_built(House house){
        houses_by_year_built[HashYear(house.year_built)].push_back(house);
    }

    std::vector<House> SearchByyear_built(int year_built){
        int code = HashYear(year_built);
        std::vector<House> result;
        for(int i = 0; i < houses_by_year_built[code].size(); i++){
            if(houses_by_year_built[code][i].year_built == year_built){
                result.push_back(houses_by_year_built[code][i]);
            }
        }
        return result;
    }
};
