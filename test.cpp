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

    // testing set function that aren't tested above
    Dish1.setName("BaconEggAndCheese");
    Dish1.setCuisineType(Dish::CuisineType::AMERICAN);
    Dish1.setIngredients({"Egg", "Bacon", "Cheese"});
    
    // testing get functions
    // dont cout, doesn't match instruction 
    Dish1.getName();
    std::vector<std::string> dish1Ing = Dish1.getIngredients();
    Dish1.getPrepTime();
    Dish1.getPrice();
    Dish1.getCuisineType();
    
    // if i don't do this, i get it an error because name is a const char[] and not a std::string.......
    Dish Dish2("Pasta Carbonara", {"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"}, 20, 12.50, Dish::CuisineType::ITALIAN);
    Dish2.display();

    return 0;
    
}
