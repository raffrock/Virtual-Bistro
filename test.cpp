/** 
*@file test.cpp 
* Rafael Chetata
* 09/14/24
* This tests the Dish class and files by creating two dish objects, changing variables with setter functions, and prints both dishes with the display function.
*/

#include <iostream>
#include<string>
#include<vector>

#include "Dish.cpp"

int main() {
    // adding enum to file to allow to be in the para of the para'ized constructor
    enum CuisineType { ITALIAN, MEXICAN, CHINESE, INDIAN,
AMERICAN, FRENCH, OTHER };
    
    // creating and testing Dish1 object
    Dish Dish1; // note to see: when using default constructor no ()
    Dish1.setPrepTime(30);
    Dish1.setPrice(9.99);
    Dish1.display();
    
    // creating and testing Dish2 object
    Dish Dish2("Pasta Carbonara",  {"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"}, 20, 12.50, Dish::ITALIAN);
    Dish2.display();

    return 0;
    
}
