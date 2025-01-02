/**
 * @file Desset.hpp
 * @brief This file is the header of the Dessert class, which represents a dish in a virtual bistro simulation.
 * 
 * The Dessert class includes attributes such as flavor profile, sweetness level, and if it contains nuts.
 * It provides constructors, accessor and mutator functions. 
 * the details of a dish.
 * 
 * @date 9/30/24
 * @author Rafael Chetata
 */

#ifndef DESSERT_HPP
#define DESSERT_HPP
#include "Dish.hpp"
#include<iostream>

class Dessert : public Dish {
public:
    enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI };

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    Dessert();

    /**
     * Parameterized constructor.
     * @param name The name of the dessert.
     * @param ingredients The ingredients used in the dessert.
     * @param prep_time The preparation time in minutes.
     * @param price The price of the dessert.
     * @param cuisine_type The cuisine type of the dessert.
     * @param flavor_profile The flavor profile of the dessert.
     * @param sweetness_level The sweetness level of the dessert.
     * @param contains_nuts Flag indicating if the dessert contains nuts.
     */ 
    Dessert(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, const FlavorProfile& flavor_profile = FlavorProfile::SWEET, const int& sweetness_level = 0, const bool& contains_nuts = false);

    /**
    * Sets the flavor profile of the dessert.
    * @param flavor_profile The new flavor profile.
    * @post Sets the private member `flavor_profile_` to the value of the parameter.
    */
    void setFlavorProfile(const FlavorProfile& new_flavor_profile_);

    /**
    * @return The flavor profile of the dessert (as an enum).
    */
    FlavorProfile getFlavorProfile() const;

    /**
    * Sets the sweetness level of the dessert.
    * @param sweetness_level An integer representing the sweetness level of
    the dessert.
    * @post Sets the private member `sweetness_level_` to the value of the
    parameter.
    */
    void setSweetnessLevel(const int& new_sweetness_level);

    /**
    * @return The sweetness level of the dessert.
    */
    int getSweetnessLevel() const;

    /**
    * Sets the contains_nuts flag of the dessert.
    * @param contains_nuts A boolean indicating if the dessert contains
    nuts.
    * @post Sets the private member `contains_nuts_` to the value of the
    parameter.
    */
    void setContainsNuts(const bool& if_contains_nuts_);

    /**
    * @return True if the dessert contains nuts, false otherwise.
    */
    bool containsNuts() const;

private:
    FlavorProfile flavor_profile_;
    int sweetness_level_;
    bool contains_nuts_;
};

#endif