/** 
*@file KitchenStation.cpp 
* Rafael Chetata
* 11/14/24
* Implementation file for Kitchen Station class. 
*/

#include "KitchenStation.hpp"

/**
* Default Constructor
* @post: Initializes an empty kitchen station with default values.
*/
KitchenStation::KitchenStation() :  station_name_(""), dishes_({}), ingredients_stock_({}) { }

/**
* Parameterized Constructor
* @param station_name A string representing the station's name.
* @post: Initializes a kitchen station with the given name.
*/
KitchenStation::KitchenStation(const std::string& station_name) : station_name_(station_name), dishes_({}), ingredients_stock_({}) { }

/**
* Destructor
* @post: Deallocates all dynamically allocated dishes in the
station.
*/
KitchenStation::~KitchenStation() {
    for (Dish* dish : dishes_) {
        delete dish;
        // dish = nullptr;
    }
    dishes_.clear();
}

/**
* Retrieves the name of the kitchen station.
* @return: The name of the station.
*/
const std::string& KitchenStation::getName() {
    return station_name_;
}

/**
* Sets the name of the kitchen station.
* @param name A string representing the new station name.
* @post: Updates the station's name.
*/
void KitchenStation::setName(const std::string& name) {
    station_name_ = name;
}

/**
* Retrieves the list of dishes assigned to the kitchen station.
* @return A vector of pointers to Dish objects assigned to the station.
*/
std::vector<Dish*> KitchenStation::getDishes() {
    return dishes_;
}

/**
* Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
*/
std::vector<Ingredient> KitchenStation::getIngredientsStock() {
    return ingredients_stock_;
}

/**
* Assigns a dish to the station.
* @param dish A pointer to a Dish object.
* @post: Adds the dish to the station's list of dishes if not
already present.
* @return: True if the dish was added successfully and false
otherwise.
*/
bool KitchenStation::assignDishToStation(Dish* dish) {
    for (Dish* other_dish : dishes_) {
        if (dish->getName() == other_dish->getName()) {
            return false;
        }
    }
    dishes_.push_back(dish);
    return true;
}

/**
* Replenishes the station's ingredient stock.
* @param ingredient An Ingredient object.
* @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
*/
void KitchenStation::replenishStationIngredients(Ingredient ingredient) {
    bool found = false;
    for (int i = 0; i < ingredients_stock_.size(); i++) {
        if (ingredients_stock_[i].name == ingredient.name) {
            ingredients_stock_[i].quantity += ingredient.quantity;
            found = true;
        }
    }
    if (found == false) {
        ingredients_stock_.push_back(ingredient); // if not found, add to stock
    }
}

/**
* Checks if the station can complete an order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if the station has the dish assigned and all
required ingredients are in stock {} false otherwise.
*/
bool KitchenStation::canCompleteOrder(const std::string& dish_name) {
    /**
     * iterate through dishes_ vector
     * find dish
     * iterate through ing needed for dish
     * find in ing vector use std::find
     * check if required_quantity > quantity
     * if yes, return false
     * if iterated and no false, return true
     */
    int ingredients_found = 0;
    for (int i = 0; i < dishes_.size(); i++) {
        // std::cout << " dish name " << dishes_[i]->getName() << " ";
        // all dishes found
        if (dishes_[i]->getName() == dish_name) {
            for (Ingredient ingredient : dishes_[i]->getIngredients()) {
                for (Ingredient ingredient_in_stock : ingredients_stock_) {
                    if (ingredient.name == ingredient_in_stock.name && ingredient.required_quantity > ingredient_in_stock.quantity) {
                        return false; // required_quantity not met
                    } else if (ingredient.name == ingredient_in_stock.name && ingredient.required_quantity <= ingredient_in_stock.quantity) {
                        ingredients_found++; // one of the ingredients needed for the dishes was found and correct quantity
                    }
                }
            }
            // if ingredient missing
            if (ingredients_found < dishes_[i]->getIngredients().size()) {
                return false; // not enough ingredients found
            } else {
                return true; // dish found and ingredients are present and in correct quantity
            } 
        }
        
    }
    return false; // dish not found
}

/**
* Prepares a dish if possible.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully and false
otherwise.
*/
bool KitchenStation::prepareDish(const std::string& dish_name) {
    /**
     * if can complete order
     * iterate through dish ingredients
     * subtract amount from amount in kitchen station
     */
    if (canCompleteOrder(dish_name)) {
        for (int i = 0; i < dishes_.size(); i++) {
            if (dishes_[i]->getName() == dish_name) {
                // if dish found, remove ingredients
                std::vector<Ingredient> dish_ing = dishes_[i]->getIngredients();
                for (int i = 0; i < dish_ing.size(); i++) {
                    // for (int j = 0; j < ingredients_stock_.size(); j++) {
                    for (int j = ingredients_stock_.size(); j >= 0; j--) {
                        if (dish_ing[i].name == ingredients_stock_[j].name) {
                            ingredients_stock_[j].quantity -= dish_ing[i].required_quantity;
                            if (ingredients_stock_[j].quantity == 0) {
                                //std::cout << "\t" << ingredients_stock_[j].name  << " " << j << std::endl;
                                ingredients_stock_.erase(ingredients_stock_.begin() + j);
                            }
                        }
                    }
                }

                // check ing stock
                // for (Ingredient ing : ingredients_stock_) {
                //     std::cout << "\n\t" << ing.name << " " << ing.quantity;
                // }

                return true; // sucessfully made dish
            }
        }
    } 
    return false; // dish not found
}