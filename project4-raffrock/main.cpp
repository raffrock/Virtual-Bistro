#include "ArrayBag.hpp"
#include "Kitchen.hpp"
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <iostream>

int main() 
{
    Kitchen myKitchen("Dishes.csv");
    myKitchen.displayMenu();
    //std::cout << "\nAFTER diet adjustments: " << std::endl;
    Dish::DietaryRequest myAdjustments = {true, true, true, true, true, true};
    myKitchen.dietaryAdjustment(myAdjustments);
    //myKitchen.displayMenu();
    myKitchen.~Kitchen();
   //return 0;
}