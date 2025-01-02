// testing kichen

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include "Kitchen.hpp"

#include<iostream>

int main() {
    Kitchen theBear;
    Dish Pasta("Pasta Carbonara", {"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"}, 70, 12.50, Dish::ITALIAN); 
    Dish WorstPasta("Pasta with carbs", {"Pasta", "Pasta", "Pasta"}, 10, 10.50, Dish::AMERICAN); 
    Dish WorstPastaEgg("Pasta with carbs", {"Pasta", "Pasta", "Pasta", "Eggs"}, 10, 11.50, Dish::AMERICAN); 
    std::cout << theBear.newOrder(Pasta);
    std::cout << theBear.newOrder(WorstPasta);
    std::cout << theBear.newOrder(WorstPastaEgg) << std::endl;
    //theBear.releaseDishesBelowPrepTime(12);
    theBear.releaseDishesOfCuisineType();
    std::cout << "Total Prep time: " << theBear.getPrepTimeSum() << std::endl;
    std::cout << "Elab count: " << theBear.elaborateDishCount() << std::endl;
    std::cout << "Tally of Italian: " << theBear.tallyCuisineTypes("ITALIAN") << std::endl;
    theBear.kitchenReport();

    if (Pasta == Pasta) {
        std::cout << "True";
    }
    
}