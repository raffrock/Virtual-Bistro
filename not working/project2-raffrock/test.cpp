/**
 * @file test.cpp
 * @brief This file tests the Dish subclasses in the virtual bistro simulation.
 * 
 * @date 9/30/24
 * @author Rafael Chetata
 */

#include<iostream>
#include<vector>
#include<string>
#include <iomanip>

#include "Dish.hpp"
#include "MainCourse.hpp"
#include "Appetizer.hpp"
#include "Dessert.hpp"

int main() {
    // Instantiate an appetizer with the default constructor and change with setter functions. 
    Appetizer appOne;
    appOne.setSpicinessLevel(7);
    appOne.setServingStyle(Appetizer::ServingStyle::FAMILY_STYLE);
    appOne.setVegetarian(true);
    // printing out using accessor functions 
    std::cout << "Dish Name: " << appOne.getName() << std::endl;
    std::cout << "Ingredients: ";
    for (size_t i = 0; i < appOne.getIngredients().size(); ++i) {
        std::cout << appOne.getIngredients()[i];
        if (i != appOne.getIngredients().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << appOne.getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << appOne.getPrice() << std::endl;
    std::cout << "Cuisine Type: " << appOne.getCuisineType() << std::endl;
    std::cout << "Spiciness Level: " << appOne.getSpicinessLevel() << std::endl;
    std::cout << "Serving Style: ";
    switch (appOne.getServingStyle()) {
        case Appetizer::ServingStyle::PLATED: std::cout << "PLATED" << std::endl; break;
        case Appetizer::ServingStyle::FAMILY_STYLE: std::cout << "FAMILY STYLE" << std::endl; break;
        case Appetizer::ServingStyle::BUFFET: std::cout << "BUFFET" << std::endl; break;
    }
    std::cout << "Vegetarian: ";
    if (appOne.isVegetarian() == true) {
        std::cout << "True" << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }

    //testing not tested functions
    appOne.setName("Name");
    appOne.setIngredients({"This","That"});
    appOne.setPrepTime(10);
    appOne.setPrice(30.0);
    appOne.setCuisineType(Dish::CuisineType::AMERICAN);

    // name, intg, prep, price, cuisne, cooking, protien, gulten 
    MainCourse mainOne("Grilled Chicken", {"Chicken", "Olive Oil", "Garlic", "Rosemary"}, 30, 18.99, Dish::CuisineType::AMERICAN, MainCourse::CookingMethod::GRILLED, "Chicken", {{"Mashed Potatoes",MainCourse::Category::STARCHES},{"Green Beans",MainCourse::Category::VEGETABLE}}, false);
    mainOne.setGlutenFree(false);
    // printing out using accessor functions 
    std::cout << "Dish Name: " << mainOne.getName() << std::endl;
    std::cout << "Ingredients: ";
    for (size_t i = 0; i < mainOne.getIngredients().size(); ++i) {
        std::cout << mainOne.getIngredients()[i];
        if (i != mainOne.getIngredients().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << mainOne.getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << mainOne.getPrice() << std::endl;
    std::cout << "Cuisine Type: " << mainOne.getCuisineType() << std::endl;
    std::cout << "Cooking Method: ";
    switch (mainOne.getCookingMethod()) {
        case MainCourse::CookingMethod::GRILLED: std::cout << "GRILLED" << std::endl; break;
        case MainCourse::CookingMethod::BAKED: std::cout << "BAKED" << std::endl; break;
        case MainCourse::CookingMethod::FRIED: std::cout << "FRIEND" << std::endl; break;
        case MainCourse::CookingMethod::STEAMED: std::cout << "STEAMED" << std::endl; break;
        case MainCourse::CookingMethod::RAW: std::cout << "RAW" << std::endl; break;
    }
    std::cout << "Protein Type: " << mainOne.getProteinType() << std::endl;
    std::cout << "Side Dishes: ";
    
    for (int i = 0; i < mainOne.getSideDishes().size(); i++) {
        std::cout <<  mainOne.getSideDishes()[i].name << " (";
        switch (mainOne.getSideDishes()[i].category) {
            case MainCourse::Category::GRAIN:
                std::cout << "Grain)";
                break;
            case MainCourse::Category::PASTA:
                std::cout << "Pasta)";
                break;
            case MainCourse::Category::LEGUME:
                std::cout << "Legume)";
                break;
            case MainCourse::Category::BREAD:
                std::cout << "Bread)";
                break;
            case MainCourse::Category::SALAD:
                std::cout << "Salad)";
                break;
            case MainCourse::Category::SOUP:
                std::cout << "Soup)";
                break;
            case MainCourse::Category::STARCHES:
                std::cout << "Starches)";
                break;
            case MainCourse::Category::VEGETABLE:
                std::cout << "Vegetable)";
                break;
            default: 
                std::cout << "ERROR!";
        }
        if ( i < mainOne.getSideDishes().size()-1 ) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Gluten-Free: " << mainOne.isGlutenFree() << std::endl;

    //testing not tested functions
    mainOne.setName("Name");
    mainOne.setIngredients({"This","That"});
    mainOne.setPrepTime(10);
    mainOne.setPrice(30.0);
    mainOne.setCuisineType(Dish::CuisineType::AMERICAN);
    mainOne.setCookingMethod(MainCourse::CookingMethod::FRIED);
    mainOne.setProteinType("Beef");
    mainOne.addSideDish({"Bread Rolls",MainCourse::Category::STARCHES});
    mainOne.setGlutenFree(false);

    Dessert desOne("Chocolate Cake", {"Flour", "Sugar", "Cocoa Powder", "Eggs"}, 45, 7.99, Dish::CuisineType::FRENCH, Dessert::FlavorProfile::SWEET, 9, false);
    desOne.setContainsNuts(false);
    // printing out using accessor functions 
    std::cout << "Dish Name: " << desOne.getName() << std::endl;
    std::cout << "Ingredients: ";
    for (size_t i = 0; i < desOne.getIngredients().size(); ++i) {
        std::cout << desOne.getIngredients()[i];
        if (i != desOne.getIngredients().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << desOne.getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << desOne.getPrice() << std::endl;
    std::cout << "Cuisine Type: " << desOne.getCuisineType() << std::endl;
    std::cout << "Flavor Profile: ";
    switch (desOne.getFlavorProfile()) {
        case Dessert::SWEET: std::cout << "SWEET" << std::endl; break;
        case Dessert::BITTER: std::cout << "BITTER" << std::endl; break;
        case Dessert::SOUR: std::cout << "SOUR" << std::endl; break;
        case Dessert::SALTY: std::cout << "SALTY" << std::endl; break;
        case Dessert::UMAMI: std::cout << "UMAMI" << std::endl; break;
    }
    std::cout << "Sweetness Level: " << desOne.getSweetnessLevel() << std::endl;
    std::cout << "Contains Nuts: ";
    if (desOne.containsNuts() == true) {
        std::cout << "True" << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }

    //testing not tested functions
    desOne.setName("Name");
    desOne.setIngredients({"This","That"});
    desOne.setPrepTime(10);
    desOne.setPrice(30.0);
    desOne.setCuisineType(Dish::CuisineType::AMERICAN);
    desOne.setFlavorProfile(Dessert::SOUR);
    desOne.setSweetnessLevel(9);
    desOne.setContainsNuts(true);

    return 0;
}