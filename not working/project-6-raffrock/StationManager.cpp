/** 
*@file StationManager.cpp 
* Rafael Chetata
* 12/02/24
* Implementation for the dish queue and backup ingredients vector management functions added to the header file. 
*/

#include "StationManager.hpp"
#include <iostream>

// Default Constructor
StationManager::StationManager() {
    // Initializes an empty station manager
}


// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < item_count_; ++i) {
        if (getEntry(i)->getName() == station_name) {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}


int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

/**
* Retrieves the current dish preparation queue.
* @return A copy of the queue containing pointers to Dish objects.
* @post: The dish preparation queue is returned unchanged.
*/
std::queue<Dish*> StationManager::getDishQueue() {
    return dish_queue_;
}

/**
* Retrieves the list of backup ingredients.
* @return A vector containing Ingredient objects representing backup
supplies.
* @post: The list of backup ingredients is returned unchanged.
*/
std::vector<Ingredient> StationManager::getBackupIngredients() {
    return backup_ingredients_;
}

/**
* Sets the current dish preparation queue.
* @param dish_queue A queue containing pointers to Dish objects.
* @pre: The dish_queue contains valid pointers to dynamically allocated
Dish objects.
* @post: The dish preparation queue is replaced with the provided
queue.
*/
void StationManager::setDishQueue(std::queue<Dish*> dish_queue) {
    dish_queue_.swap(dish_queue);
}

/**
* Sets the backup ingredients list.
* @param backup_ingredients A vector of Ingredient objects representing
backup supplies.
* @pre: The backup_ingredients vector contains valid Ingredient
objects.
* @post: The list of backup ingredients is replaced with the provided vector.
*/
void StationManager::setBackupIngredients(std::vector<Ingredient> backup_ingredients) {
    backup_ingredients_ = backup_ingredients;
}

/**
* Adds a dish to the preparation queue without dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @pre: The dish pointer is not null.
* @post: The dish is added to the end of the queue.
*/ 
void StationManager::addDishToQueue(Dish* dish) {
    dish_queue_.push(dish);
}

/**
* Adds a dish to the preparation queue with dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @param request A DietaryRequest object specifying dietary
accommodations.
* @pre: The dish pointer is not null.
* @post: The dish is adjusted for dietary accommodations and added to
the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish, Dish::DietaryRequest request) {
    // modify dish to accommodation request, then add to queue
    dish->dietaryAccommodations(request);
    dish_queue_.push(dish);
}

/**
* Prepares the next dish in the queue if possible.
* @pre: The dish queue is not empty.
* @post: The dish is processed and removed from the queue.
* @return: True if the dish was prepared successfully; false otherwise.
*/
bool StationManager::prepareNextDish() {
    // store pointer and name of current dish
    Dish* next_dish = dish_queue_.front();
    std::string next_dish_name = next_dish->getName();

    if (!canCompleteOrder(next_dish_name)) {
        return false; // dish cannot be completed at any station
    }

    std::string station_name; // holds name for prepareDishAtStation

    // find station that can prepare dish
    for (size_t i = 0; i < getLength(); i++) {
        station_name = getEntry(i)->getName();
        if (findStation(station_name)->canCompleteOrder(next_dish_name)) {
            findStation(station_name)->prepareDish(next_dish_name);
            dish_queue_.pop();
            return true;
        }
    }

    return false; // dish not found in station, or not enough ingredients

}

/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/
void StationManager::displayDishQueue() {
    // create list copy to display front then pop in loop
    std::queue<Dish*> display_queue = dish_queue_;
    while (!display_queue.empty()) {
        std::cout << display_queue.front()->getName() << std::endl;
        display_queue.pop();
    }
}

/**
* Clears all dishes from the preparation queue.
* @pre: None.
* @post: The dish queue is emptied and all allocated memory is freed.
*/
void StationManager::clearDishQueue() {
    // pop every Dish in queue
    while (!dish_queue_.empty()) {
        // Dish* dish = dish_queue_.front();
        dish_queue_.pop();
        // delete dish; // deleted to deallocate memory
    }
}

/**
* Replenishes a specific ingredient at a given station from the backup
ingredients stock by a specified quantity.
* @param station_name A string representing the name of the station.
* @param ingredient_name A string representing the name of the ingredient
to replenish.
* @param quantity An integer representing the amount to replenish.
* @pre None.
* @post If the ingredient is found in the backup ingredients stock and has
sufficient quantity, it is added to the station's ingredient stock by the
specified amount, and the function returns true.
* The quantity of the ingredient in the backup stock is decreased by
the specified amount.
* If the ingredient in backup stock is depleted (quantity becomes
zero), it is removed from the backup stock.
* If the ingredient does not have sufficient quantity in backup
stock, or the ingredient or station is not found, returns false.
* @return True if the ingredient was replenished from backup; false
otherwise.
*/
bool StationManager::replenishStationIngredientFromBackup(std::string station_name, std::string ingredient_name, int quantity) {
    // if station not present
    if (findStation(station_name) == nullptr) {
        return false;
    }

    for (size_t i = 0; i < backup_ingredients_.size(); i++) {
        if (backup_ingredients_[i].name == ingredient_name) { 

            // create backup ingredient with correct quantity
            Ingredient ingredient_at_quantity = backup_ingredients_[i];
            ingredient_at_quantity.quantity = quantity;
            
            if (backup_ingredients_[i].quantity > quantity) { // there is enough
                backup_ingredients_[i].quantity -= quantity;
            } else if (backup_ingredients_[i].quantity == quantity) {
                // remove because it is depleted
                backup_ingredients_.erase(backup_ingredients_.begin() + i);
            } else {
                return false; // not enough to replenish
            }

            // attempt to add to station
            return replenishIngredientAtStation(station_name, ingredient_at_quantity);
        }
    }
    return false; // ing not found
}

/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.
*/
bool StationManager::addBackupIngredient(Ingredient ingredient) {
    if (ingredient.quantity == 0) {
        return false; // nothing to add
    }

    bool found = false;
   for (size_t i = 0; i < backup_ingredients_.size(); i++) {
        if (backup_ingredients_[i].name == ingredient.name) {
            backup_ingredients_[i].quantity += ingredient.quantity;
            found = true;
        }
    }
    if (!found) {
        backup_ingredients_.push_back(ingredient);
    }
    return true;
}
/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.
*/
bool StationManager::addBackupIngredients(std::vector<Ingredient> ingredients) {
    // if empty, return false
    if (ingredients.size() == 0) {
        return false; // nothing to add?
    }
    // method where stock is update
    for (Ingredient ing : ingredients) {
        bool found = false;
        for (size_t i = 0; i < backup_ingredients_.size(); i++) {
            if (backup_ingredients_[i].name == ing.name) {
                backup_ingredients_[i].quantity += ing.quantity;
                found = true;
            }
        }
        if (!found) {
            backup_ingredients_.push_back(ing);
        }
    }
    return true;
}


/**
* Empties the backup ingredients vector
* @post The backup_ingredients_ private member variable is empty.
*/
void StationManager::clearBackupIngredients() {
    backup_ingredients_.clear(); 
}

void StationManager::processAllDishes() {
    /**
     * while dish_queue isn't empty
     * iterate through all stations (move to next if dish not found or prepared)
     * find dish at station
     * attempt prepareDishAtStation
     * check if ingredients are avialable (cross-reference dish_ing and station_ing)
     *     if not, attempt to replenish missing ingredients from backup
     *     return false if fails
     * attempt prepareDishAtStation again, print two expected reponse if passed or failed
     * if dish not made at any station, pop then push to new queue
     * swap queue with new queue to store unprepared dishes
     */
    
    std::queue<Dish*> new_queue; 

    while (!dish_queue_.empty()) 
    {
        Dish* dish = dish_queue_.front();
        std::string dish_name = dish->getName();

        std::string station_name;

        bool prepared = false;
        std::cout << "PREPARING DISH: " << dish_name << std::endl;

        // going through stations to find one that can prepare dish
        for (size_t i = 0; i < getLength(); i++) {

            station_name = getEntry(i)->getName();
            std::cout << station_name << " attempting to prepare " << dish_name << "..." << std::endl;
            bool dish_found = false;
            
            for (Dish* d : getEntry(i)->getDishes()) {
                // station has dish
                if (d->getName() == dish_name) {
                    dish_found = true;
                    // dish prepared
                    if (prepareDishAtStation(station_name,dish_name)) {
                        std::cout << station_name << ": Successfully prepared " << dish_name << "." << std::endl;
                        prepared = true;
                        break;

                    } else {
                        // needs more ingredients 
                        std::cout << station_name << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;
                        bool replenished = false; 
                        for (Ingredient d_ing : dish->getIngredients()) {
                            bool found = false;
                            for (Ingredient s_ing : findStation(station_name)->getIngredientsStock()) 
                            {
                                if (d_ing.name == s_ing.name) 
                                {
                                    found = true;
                                    int difference = d_ing.required_quantity - s_ing.quantity;
                                    // if ing found in low qautity, attempt to add needed quantity
                                    if (difference > 0 && replenishStationIngredientFromBackup(station_name, d_ing.name, difference)) 
                                    {
                                        replenished = true;
                                    }
                                }
                            }
                            // if ing not found, attemot to add correct amount
                            if (!found && replenishStationIngredientFromBackup(station_name, d_ing.name, d_ing.required_quantity)) {
                                replenished = true;
                            } 
                        }
                        // if any ing is replenished
                        if (replenished) {
                                std::cout << station_name << ": Ingredients replenished." << std::endl;
                            if (prepareDishAtStation(station_name,dish_name)) {
                                // if dish can now be prepared
                                std::cout << station_name << ": Successfully prepared " << dish_name << "." << std::endl;
                                prepared = true;
                                break;
                            } else {
                                // replenished but not enough 
                                std::cout << station_name << ": Unable to prepare " << dish_name << "." << std::endl;
                            }
                        } else {
                            // not replenished
                            std::cout << station_name << ": Unable to replenish ingredients. Failed to prepare " << dish_name << "." << std::endl;
                        }
                    }
                }
            }

            // if dish not found in station
            if (!dish_found) {
                std::cout << station_name << ": Dish not available. Moving to next station..." << std::endl;
            }

            if (prepared) {
                break;
            }
        }

        // dish not prepared, add to new queue (of unprepared dishes)
        if (!prepared) {
            std::cout << dish_name << " was not prepared.\n" << std::endl;
            new_queue.push(dish);
            dish_queue_.pop();
            continue;
        }

        // move to next
        dish_queue_.pop();

        // add space
        std::cout << std::endl;
    }

    // add unmade dishes to current queue
    if (!new_queue.empty()) { 
        setDishQueue(new_queue);
    }

    std::cout << "\nAll dishes have been processed." << std::endl;

}

