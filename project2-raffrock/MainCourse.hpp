/**
 * @file MainCourse.hpp
 * @brief This file is the header of the Main Course class, which represents a dish in a virtual bistro simulation.
 * 
 * The Appetizer class includes attributes such as cooking method, side dish, and category, such as grain, pasta, and etc.
 * It provides constructors, accessor and mutator functions. 
 * the details of a dish.
 * 
 * @date 9/30/24
 * @author Rafael Chetata
 */

#ifndef MAINCOURSE_HPP
#define MAINCOURSE_HPP
#include "Dish.hpp"
#include<iostream>
#include<vector>

class MainCourse : public Dish {
public:
    enum CookingMethod { GRILLED, BAKED, FRIED, STEAMED, RAW };
    enum Category { GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE };
    struct  SideDish {    
        std::string name;
        Category category;
    };

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    MainCourse();

    /**
     * Parameterized constructor.
     * @param name The name of the main course.
     * @param ingredients A vector of the ingredients used in the main
    course.
    * @param prep_time The preparation time in minutes.
    * @param price The price of the main course.
    * @param cuisine_type The cuisine type of the main course.
    * @param cooking_method The cooking method used for the main course.
    * @param protein_type The type of protein used in the main course.
    * @param side_dishes A vector of the side dishes served with the main
    course.
    * @param gluten_free Boolean flag indicating if the main course is
    gluten-free.
    */
    MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int& prep_time, const double& price, const CuisineType& cuisine_type, const CookingMethod& cooking_method = CookingMethod::RAW, const std::string& protein_type = "None", const std::vector<MainCourse::SideDish>& side_dishes = {}, const bool& gluten_free = false);

    /**
    * Sets the cooking method of the main course.
    * @param cooking_method The new cooking method.
    * @post Sets the private member `cooking_method_` to the value of the
    parameter.
    */
    void setCookingMethod(const CookingMethod& new_cooking_method);

    /**
    * @return The cooking method of the main course (as an enum).
    */
    CookingMethod getCookingMethod() const;

    /**
    * Sets the type of protein in the main course.
    * @param protein_type A string representing the type of protein.
    * @post Sets the private member `protein_type_` to the value of the
    parameter.
    */
    void setProteinType(const std::string& new_protein_type_);

    /**
    * @return The type of protein in the main course.
    */
    std::string getProteinType() const;

    /**
    * Adds a side dish to the main course.
    * @param side_dish A SideDish struct containing the name and category
    of the side dish.
    * @post Adds the side dish to the `side_dishes_` vector.
    */
    void addSideDish(const SideDish& side_dish);

    /**
    * @return A vector of SideDish structs representing the side dishes
    served with the main course.
    */
    std::vector<MainCourse::SideDish> getSideDishes() const;

    /**
    * Sets the gluten-free flag of the main course.
    * @param gluten_free A boolean indicating if the main course is glutenfree.
    * @post Sets the private member `gluten_free_` to the value of the
    parameter.
    */
    void setGlutenFree(const bool& if_gluten_free);

    /**
    * @return True if the main course is gluten-free, false otherwise.
    */
    bool isGlutenFree() const;

private:
    CookingMethod cooking_method_;
    std::string protein_type_;
    bool gluten_free_;  
    std::vector<SideDish> side_dishes_;
};

#endif