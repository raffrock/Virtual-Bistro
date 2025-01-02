/** 
*@file main.cpp 
* Rafael Chetata
* 11/14/24
* Tests all classes and their functions. 
*/

#include "LinkedList.hpp"
#include "Node.hpp"
#include "Dish.hpp"
#include "StationManager.hpp"
#include "KitchenStation.hpp"
#include <iostream>

int main () {
// Testing Ingredient struct 
    Ingredient Tomato("Tomato", 4, 2, 2.00);
    Ingredient Onion("Onion", 5, 1, 1.50);
    Ingredient BellPepper("Bell Pepper", 10, 1, 3.50);
    Ingredient Beef("Beef Strips", 15, 1, 10.50);
    Ingredient Chicken("Chicken breast", 15, 1, 10.50);
// Testing Kitchen Station and Assign Dish 
    // Dish( std::string& name, std::vector<Ingredient>& ingredients, int prep_time, double price, CuisineType cuisine_type)
    KitchenStation* StirFry = new KitchenStation("StirFry");
    KitchenStation* VeganStirFry = new KitchenStation("VeganStirFry");
    Dish* BeefStirFry = new Dish("Beef Stir Fry", {Onion, BellPepper, Beef}, 20, 30.00, Dish::OTHER);
    Dish* TomatoStirFry = new Dish("Tomato Stir Fry", {Onion, BellPepper, Tomato}, 15, 20.00, Dish::OTHER);
    Dish* ChickenStirFry = new Dish("Chicken Stir Fry", {Onion, BellPepper, Chicken}, 20, 25.00, Dish::OTHER);
// Tests assignDishToStation() 
    std::cout << "assignDishToStation ";
    std::cout << StirFry->assignDishToStation(BeefStirFry) << " ";
    std::cout << StirFry->assignDishToStation(ChickenStirFry) << " ";
    std::cout << VeganStirFry->assignDishToStation(TomatoStirFry) << std::endl;
// Tests canCompleteOrder and replenishStationIngredients 
    for (auto ing : {Onion, BellPepper, Beef, Chicken}) {
        StirFry->replenishStationIngredients(ing);
    }
    for (auto ing : {Onion, BellPepper, Tomato}) {
        VeganStirFry->replenishStationIngredients(ing);
    }
    // check ing at station StirFry
        // std::cout << "  Ings for" << VeganStirFry->getName() << ":" << std::endl;
        // for (auto ing : VeganStirFry->getIngredientsStock()) {
        //     std::cout << "   " << ing.name << " " << ing.quantity << std::endl;
        // }
    std::cout << "canCompleteOrder ";
    std::cout << StirFry->canCompleteOrder("Tomato Stir Fry")  << " "; // 0
    std::cout << VeganStirFry->canCompleteOrder("Tomato Stir Fry")  << std::endl; // 1
// Tests prepareDish() 
    std::cout << "prepareDish ";
    std::cout << StirFry->prepareDish("Beef Stir Fry") << " ";
    std::cout << VeganStirFry->prepareDish("Tomato Stir Fry") << std::endl;
// Tests addStation, removeStation 
    StationManager HotFood;
    std::cout << "addStation/removeStation ";
    std::cout << HotFood.addStation(StirFry) <<  " ";
    std::cout << HotFood.removeStation("StirFry") <<  " ";
    std::cout << HotFood.addStation(StirFry) <<  " ";
    std::cout << HotFood.addStation(VeganStirFry) << std::endl;
// Tests moveStationToFront() 
    std::cout << "moveStationToFront " << HotFood.moveStationToFront("VeganStirFry") << std::endl;
// Tests MergeStations() 
    std::cout << "mergeStations " << HotFood.mergeStations("StirFry", "VeganStirFry")  << std::endl;
// Tests replenishIngredientAtStation() 
    std::cout << "replenishIngredientAtStation " << HotFood.replenishIngredientAtStation("StirFry", Tomato) << std::endl;
// Tests canCompleteOrder() 
    std::cout << "canCompleteOrder " << HotFood.canCompleteOrder("Tomato Stir Fry") << std::endl;
// Tests PrepareDishAtStation() 
    std::cout << "prepareDishAtStation " << HotFood.prepareDishAtStation("StirFry","Tomato Stir Fry") << " ";
    std::cout << HotFood.prepareDishAtStation("StirFry","Tomato Stir Fry") << " ";
    std::cout << HotFood.prepareDishAtStation("StirFry","Tomato Stir Fry") << " ";
    std::cout << HotFood.prepareDishAtStation("StirFry","Tomato Stir Fry") << std::endl;
    // check to see if stock updates
        // for (auto ing : HotFood.findStation("StirFry")->getIngredientsStock()) {
        //     std::cout << "   " << ing.name << " " << ing.quantity << std::endl;
        // }
}