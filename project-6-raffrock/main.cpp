#include "Dish.hpp"
#include "MainCourse.hpp"
#include "Appetizer.hpp"
#include "Dessert.hpp"
// #include "KitchenStation.hpp"
#include "StationManager.hpp"

#include <iostream>

/** 
*@file main.cpp 
* Rafael Chetata
* 12/02/24
* The testing file for the new function and queue in the StationManager class. 
*/

int main() {
    // creating ingredient and dish objects
    // Ingredient() : name("UNKNOWN"), quantity(0), required_quantity(0), price(0.0)
    Ingredient Tomato("Tomato", 4, 2, 2.00);
    Ingredient Onion("Onion", 3, 1, 1.50);
    Ingredient BellPepper("Bell Pepper", 10, 1, 3.50);
    Ingredient Beef("Beef Strips", 5, 1, 10.50);
    Ingredient Chicken("Chicken breast", 3, 1, 10.50);
    Ingredient Oil("Olive oil", 40, 2, 20.0);
    Ingredient Chips("Tortilla Chips", 50, 10, 6.50);
    Ingredient Cheese("Shredded Chedder", 30, 5, 10.25);
    Ingredient Milk("Whole Milk", 10, 1, 4.00);
    Ingredient Sugar("Processed Sugar", 20, 1, 5.00);
    Ingredient Flour("All-Purpose Flour", 20, 3, 10.0);
    Ingredient Egg("Brown Eggs", 12, 2, 4.0);
    Ingredient Tofu("Pressed Tofu", 3, 1, 20.0);

    // app
    Dish* chickenNachos = new Appetizer("Chicken Nachos", {Tomato, Onion, Chicken, Chips, Cheese}, 10, 15.0, Dish::MEXICAN, Appetizer::ServingStyle::FAMILY_STYLE, 0, false);
    Dish* beefNachos = new Appetizer("Beef Nachos", {Tomato, Onion, Beef, Chips, Cheese}, 10, 15.0, Dish::MEXICAN, Appetizer::ServingStyle::FAMILY_STYLE, 0, false);
    // side dishes
    MainCourse::SideDish stickyRice;
    stickyRice.name = "Sticky Rice";
    stickyRice.category = MainCourse::STARCHES;
    MainCourse::SideDish jasmineRice;
    jasmineRice.name = "Jasmine Rice";
    jasmineRice.category = MainCourse::STARCHES;
    MainCourse::SideDish noodle;
    noodle.name = "Rice Noodle";
    noodle.category = MainCourse::STARCHES;
    // main course dishes
    Dish* beefStirFry = new MainCourse("Beef Stir Fry", {Onion, BellPepper, Beef}, 20, 30.00, Dish::OTHER, MainCourse::CookingMethod::FRIED, "Beef", {stickyRice}, true);
    Dish* chickenStirFry = new MainCourse("Chicken Stir Fry", {Onion, BellPepper, Chicken}, 15, 20.00, Dish::OTHER, MainCourse::CookingMethod::FRIED, "Chicken", {jasmineRice}, true);
    Dish* tofuStirFry = new MainCourse("Tofu Stir Fry", {Onion, BellPepper, Tomato, Tofu}, 20, 25.00, Dish::OTHER, MainCourse::CookingMethod::FRIED, "Tofu", {noodle}, true);
    // dessert
    Dish* smallCake = new Dessert("Small Cake", {Milk, Flour, Sugar}, 30, 15.0, Dish::AMERICAN, Dessert::FlavorProfile::SWEET, 6, false);

    // request (six bool)
    Dish::DietaryRequest nuts_sodium;
    nuts_sodium.nut_free = true;
    nuts_sodium.low_sodium = true;

    Dish::DietaryRequest sugar;
    sugar.low_sugar = true;

    // create KitchenStation and assign dishes and ingredients
    KitchenStation* Nachos = new KitchenStation("Nachos");
    KitchenStation* StirFry = new KitchenStation("Stir Fry");
    KitchenStation* Cake = new KitchenStation("Cake");
    Nachos->assignDishToStation(chickenNachos);
    Nachos->assignDishToStation(beefNachos);
    Nachos->assignDishToStation(tofuStirFry);
    StirFry->assignDishToStation(beefStirFry);
    StirFry->assignDishToStation(chickenStirFry);
    StirFry->assignDishToStation(tofuStirFry);
    // Cake->assignDishToStation(smallCake);

    for (Ingredient ing : {Tomato, Onion, Chicken, Chips, Cheese, Beef}) {
        Nachos->replenishStationIngredients(ing);
    }
    for (Ingredient ing : {Onion, BellPepper, Chicken, Beef, Tofu}) {
        StirFry->replenishStationIngredients(ing);
    }
    for (Ingredient ing : {Milk, Flour, Sugar}) {
        Cake->replenishStationIngredients(ing);
    }

    // create KitchenManager and assign stations
    StationManager FridayMenu;
    FridayMenu.addStation(Nachos);
    FridayMenu.addStation(StirFry);
    // FridayMenu.addStation(Cake);

//        TESTING STARTS HERE

// Testing addDish, displayDishqueue, clearDishQueue (0/15)
    // FridayMenu.addDish();
    // where is this?
    std::cout << "displayDishQueue" << std::endl;

    FridayMenu.addDishToQueue(beefNachos);
    FridayMenu.clearDishQueue();

    FridayMenu.displayDishQueue(); // return nothing

    FridayMenu.addDishToQueue(beefNachos);
    // FridayMenu.addDishToQueue(chickenNachos, nuts_sodium);
    FridayMenu.addDishToQueue(beefStirFry);
    FridayMenu.addDishToQueue(tofuStirFry);
    // FridayMenu.addDishToQueue(smallCake, sugar);
    FridayMenu.addDishToQueue(smallCake);
    FridayMenu.addDishToQueue(tofuStirFry);
    FridayMenu.addDishToQueue(tofuStirFry);
    FridayMenu.addDishToQueue(tofuStirFry);
    FridayMenu.addDishToQueue(tofuStirFry);
    FridayMenu.addDishToQueue(chickenStirFry);
    // FridayMenu.addDishToQueue(chickenStirFry);

    FridayMenu.displayDishQueue(); // return all above

    std::cout << std::endl;

// Testing prepareNextDish (0/10)
    std::cout << "prepareNextDish ";
    std::cout << FridayMenu.prepareNextDish() << " ";
    std::cout << FridayMenu.prepareNextDish() << std::endl; // check if correct

// Tests addBackupIngredients, clearBackupIngredients (0/10)
    std::cout << "addBackupIngredients ";
    std::cout << FridayMenu.addBackupIngredients({Tomato, Onion, Beef, Chicken}) << " ";
    FridayMenu.clearBackupIngredients();
    // // test clear then add again
    std::cout << FridayMenu.addBackupIngredients({Tomato, Onion, Beef, Chicken, BellPepper, Tofu, Milk, Flour, Sugar}) << std::endl;

// Tests replenishStationIngredientFromBackup (0/15)
    std::cout << "replenishStationIngredientFromBackup ";
    std::cout << FridayMenu.replenishStationIngredientFromBackup("Stir Fry", "Beef Strips", 2) << " ";
    std::cout << FridayMenu.replenishStationIngredientFromBackup("Stir Fry", "Chicken breast", 1) << " ";
    std::cout << FridayMenu.replenishStationIngredientFromBackup("Stir Fry", "Tomato", 1) << std::endl;
    
    // std::cout << std::endl;
    // for (Ingredient ing : FridayMenu.findStation("Stir Fry")->getIngredientsStock()) {
    //     std::cout << "\t" << ing.name << " " << ing.quantity << std::endl;
    // }

    // std::cout << std::endl;
    // for (Ingredient ing : FridayMenu.getBackupIngredients()) {
    //     std::cout << "\t" << ing.name << " " << ing.quantity << std::endl;
    // }

    std::cout << std::endl;

// Tests processAllDishes (0/25)
    FridayMenu.processAllDishes();

    std::cout << std::endl;

    FridayMenu.displayDishQueue(); // return unmade dishes

//     std::cout << std::endl;

    // for (Ingredient ing : FridayMenu.findStation("Stir Fry")->getIngredientsStock()) {
    //     std::cout << "\t" << ing.name << " " << ing.quantity << " " << ing.required_quantity << std::endl;
    // }

    // std::cout << std::endl;
    // for (Ingredient ing : FridayMenu.getBackupIngredients()) {
    //     std::cout << "\t" << ing.name << " " << ing.quantity << " " << ing.required_quantity << std::endl;
    // }
}