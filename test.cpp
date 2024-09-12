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
    
    // if i don't do this, i get it an error because name is a const char[] and not a std::string.......
    std::string dish_name = "Pasta Carbonara";
    std::vector<std::string> dish_ing = {"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"};
    Dish Dish2(dish_name, dish_ing, 20, 12.50, Dish::CuisineType::ITALIAN);
    Dish2.display();

    return 0;
    
}
