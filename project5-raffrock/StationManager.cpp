/** 
*@file StationManager.cpp 
* Rafael Chetata
* 11/14/24
* Implementation file for Station Manager.
*/

#include "StationManager.hpp"

/**
* Default Constructor
* @post: Initializes an empty station manager.
*/
StationManager::StationManager() { }

/**
* Destructor
* @post: Deallocates all kitchen stations and clears the list.
*/
StationManager::~StationManager() {
    for (int i = 0; i < item_count_; i++) {
        delete getEntry(i);
    }
    clear(); 
}

/**
* Adds a new station to the station manager.
* @param station A pointer to a KitchenStation object.
* @post: Inserts the station into the linked list.
* @return: True if the station was successfully added false
otherwise.
*/
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station); // bool function
}

/**
* Removes a station from the station manager by name.
* @param station_name A string representing the station's name.
* @post: Removes the station from the list and deallocates it.
* @return: True if the station was found and removed {} false
otherwise.
*/
bool StationManager::removeStation(std::string station_name) {
    // searches for station name
    for (int i = 0; i < item_count_; i++) {
        if (getPointerTo(i)->getItem()->getName() == station_name) { // compares name
            return remove(i); // uses LinkedList remove function
        }
    }
    return false; // not found
}

/**
* Finds a station in the station manager by name.
* @param station_name A string representing the station's name.
* @return: A pointer to the KitchenStation if found, nullptr otherwise.
*/
KitchenStation* StationManager::findStation(std::string station_name) { 
    for (int i = 0; i < item_count_; i++) {
        if (getPointerTo(i)->getItem()->getName() == station_name) { // compares name
            return getPointerTo(i)->getItem(); // returns KS pointer
        }
    }
    return nullptr; 
}

/**
* Moves a specified station to the front of the station manager
list.
* @param station_name A string representing the station's name.
* @post: The station is moved to the front of the list if it
exists.
* @return: True if the station was found and moved, false otherwise.
*/
bool StationManager::moveStationToFront(std::string station_name) {
    for (int i = 0; i < item_count_; i++) {
        if (getEntry(i)->getName() == station_name) { // compares name
            KitchenStation* to_insert = getEntry(i);
            remove(i);
            insert(0, to_insert); // insert at beginning
            return true;
        }
    }
    // check 
        // std::cout << "\tcheck\n";
        // for (int i = 0; i < item_count_; i++) {
        //     std::cout << getEntry(i)->getName() << " ";
        // }
    return false;
}

/**
* Merges the dishes and ingredients of two specified stations.
* @param station_name1 The name of the first station.
* @param station_name2 The name of the second station.
* @post: The second station is removed from the list, and its
contents are added to the first station.
* @return: True if both stations were found and merged {} false
otherwise.
*/
bool StationManager::mergeStations(std::string station_name1, std::string station_name2) {
    KitchenStation* station_ptr1 = findStation(station_name1);
    KitchenStation* station_ptr2 = findStation(station_name2);

    if (station_ptr1 == nullptr || station_ptr2 == nullptr) {
        return false; // if a station isn't found, it can not be merged
    }
    // add ingredient from s2 to s1
    for (Ingredient ing : station_ptr2->getIngredientsStock()) {
        station_ptr1->replenishStationIngredients(ing);
    }
    // add dishes
    for (Dish* dish : station_ptr2->getDishes()) {
        station_ptr1->assignDishToStation(dish);
    }
    removeStation(station_name2); 
    return true;
}

/**
* Assigns a dish to a specific station.
* @param station_name A string representing the station's name.
* @param dish A pointer to a Dish object.
* @post: Assigns the dish to the specified station.
* @return: True if the station was found and the dish was assigned
false otherwise.
*/
bool StationManager::assignDishToStation(std::string station_name, Dish* dish) {
    if (findStation(station_name) != nullptr) {
        //KitchenStation* station = findStation(station_name);
        return findStation(station_name)->assignDishToStation(dish); 
    }
    return false; // not found
}

/**
* Replenishes an ingredient at a specific station.
* @param station_name A string representing the station's name.
* @param ingredient An Ingredient object.
* @post: Replenishes the ingredient stock at the specified station.
* @return: True if the station was found and the ingredient was
replenished, false otherwise.
*/
bool StationManager::replenishIngredientAtStation(std::string station_name, Ingredient ingredient) {
    if (findStation(station_name) != nullptr) {
        //KitchenStation* station = findStation(station_name);
            // std::cout << "BEFORE" << std::endl;
            // for (Ingredient ing : findStation(station_name)->getIngredientsStock()) {
            //     std::cout << ing.name << " " << ing.quantity << std::endl;
            // }
        findStation(station_name)->replenishStationIngredients(ingredient); 
        //station->replenishStationIngredients(ingredient); 
            // std::cout << "AFTER" << std::endl;
            // for (Ingredient ing : findStation(station_name)->getIngredientsStock()) {
            //     std::cout << ing.name << " " << ing.quantity << std::endl;
            // }
        return true;
    }
    return false; // not found
}

/**
* Checks if any station in the station manager can complete an
order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if any station can complete the order, false otherwise.
*/
bool StationManager::canCompleteOrder(std::string dish_name) {
    for (int i = 0; i < item_count_; i++) {
        if (getPointerTo(i)->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
    }
    return false; // no station can complete order
}

/**
* Prepares a dish at a specific station if possible.
* @param station_name A string representing the station's name.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduces the quantities of the
used ingredients at the station.
* @return: True if the dish was prepared successfully, false
otherwise.
*/
bool StationManager::prepareDishAtStation(std::string station_name, std::string dish_name) {
    if (findStation(station_name) != nullptr) {
        return findStation(station_name)->prepareDish(dish_name);
    }
    return false; // not found
}