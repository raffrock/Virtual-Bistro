/** 
*@file test.cpp 
* Rafael Chetata
* 09/14/24
* This tests the Dish class and files by creating two dish objects, changing variables with setter functions, and prints both dishes with the display function.
*/

#include "Dish.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {

    
    // creating and testing Dish1 object
    Dish Dish1; // note to see: when using default constructor no ()
    Dish1.setPrepTime(30);
    Dish1.setPrice(9.99);
    Dish1.display();

    Dish BaconEggCheese;

    // testing set function that aren't tested above
    BaconEggCheese.setName("BaconEggAndCheese");
    BaconEggCheese.setCuisineType(Dish::CuisineType::AMERICAN);
    BaconEggCheese.setIngredients({"Egg", "Bacon", "Cheese"});

    // testing get functions
    std::cout << BaconEggCheese.getName() << std::endl;
    std::vector<std::string> BaconEggCheeseIng = BaconEggCheese.getIngredients();
    std::cout << BaconEggCheese.getPrepTime() << std::endl;
    std::cout << BaconEggCheese.getPrice() << std::endl;
    std::cout << BaconEggCheese.getCuisineType() << std::endl;
    
    // if i don't do this, i get it an error because name is a const char[] and not a std::string.......
    Dish Dish2("Pasta Carbonara", {"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"}, 20, 12.50, Dish::CuisineType::ITALIAN);
    Dish2.display();

    return 0;
    
}
