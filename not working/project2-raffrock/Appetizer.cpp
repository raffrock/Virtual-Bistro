/**
 * @file Appetizer.cpp
 * @brief This file is the implementation of the Appetizer class, which represents a dish in a virtual bistro simulation.
 * 
 * The Appetizer class includes attributes such as serving style, spice level, and if it is vegetarian.
 * It provides constructors, accessor and mutator functions. 
 * the details of a dish.
 * 
 * @date 9/30/24
 * @author Rafael Chetata
 */

#include "Appetizer.hpp"
#include<iostream>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer() : Dish() {
    serving_style_;
    spiciness_level_;
    vegetarian_ = false;
}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int& prep_time, const double& price, const CuisineType& cuisine_type, const ServingStyle& serving_style, const int& spiciness_level, const bool& vegetarian) : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_ (serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {
} 

/**
* Sets the serving style of the appetizer.
* @param serving_style The new serving style.
* @post Sets the private member `serving_style_` to the value of the
parameter.
*/
void Appetizer::setServingStyle(const ServingStyle& new_serving_style) {
    serving_style_ = new_serving_style;
}

/**
* @return The serving style of the appetizer (as an enum).
*/
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
* Sets the spiciness level of the appetizer.
* @param spiciness_level An integer representing the spiciness level of
the appetizer.
* @post Sets the private member `spiciness_level_` to the value of the
parameter.
*/
void Appetizer::setSpicinessLevel(const int& new_spiciness_level_) {
    spiciness_level_ = new_spiciness_level_;
}

/**
* @return The spiciness level of the appetizer.
*/
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
* Sets the vegetarian flag of the appetizer.
* @param vegetarian A boolean indicating if the appetizer is
vegetarian.
* @post Sets the private member `vegetarian_` to the value of the
parameter.
*/
void Appetizer::setVegetarian(const bool& if_vegetarian_) {
    vegetarian_ = if_vegetarian_;
}

/**
* @return True if the appetizer is vegetarian, false otherwise.
*/
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}