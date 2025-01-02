/** 
*@file StationManager.cpp 
* Rafael Chetata
* 12/16/24
* Header file for RecipeBook class. It contained the recipe struct, and is a subclass of BinarySearchTree.
*/

#ifndef RECIPEBOOK_HPP
#define RECIPEBOOK_HPP

#include "BinarySearchTree.hpp"

#include <iostream>
// to read in file
#include <fstream>
// to use stringstream class for string manipulation 
#include <sstream>
// for string functions 
#include <vector>
    // multiple use
#include <map>
    // map Recipe to index pairs
#include <queue>
    // for balance
#include <stack>
    // for stacking notes
#include <algorithm>
    // std::sort
#include <utility>
    // std::pair

struct Recipe
{
    std::string name_;
    int difficulty_level_;
    std::string description_;
    bool mastered_;

    /**
    * Default constructor.
    * @post: Initializes name_ and description_ to empty strings,
    difficulty_level_ to 0, and mastered_ to false.
    */
    Recipe() : name_(""), difficulty_level_(0), description_(""), mastered_(false) {
    }

    /**
    * Parameterized Constructor.
    * @param name The name of the recipe.
    * @param difficulty_level The difficulty level of the recipe.
    * @param description A brief description of the recipe.
    * @param mastered Indicates whether the recipe has been mastered (default is
    false).
    * @post: Initializes the Recipe with the provided values.
    */
    Recipe(std::string name, int difficulty_level, std::string description, bool mastered = false) : name_(name), difficulty_level_(difficulty_level), description_(description), mastered_(mastered) {
    }

    /**
    * Equality operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is equal to other’s name_; false otherwise.
    */
    bool operator== (const Recipe& other) {
        return name_ == other.name_;
    }
   /**
    * Less-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically less than other's name_; false
    otherwise
    */
    bool operator< (const Recipe& other) {
        return name_ < other.name_;
    }
   /**
    * Greater-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically greater than other's name_;
    false otherwise.
    */
    bool operator> (const Recipe& other) {
        return name_ > other.name_;
    }

};

class RecipeBook : public BinarySearchTree<Recipe> {

public:
    /**
    * Default Constructor.
    * @post: Initializes an empty RecipeBook.
    */
    RecipeBook();

    /**
    * Parameterized Constructor.
    * @param filename A const reference to a string representing the name of a
    CSV file.
    * @post: The RecipeBook is populated with Recipes from the CSV file.
    * The file format is as follows:
    *   name,difficulty_level,description,mastered
    * Ignore the first line. Each subsequent line represents a Recipe to be
    added to the RecipeBook.
    */
    RecipeBook(const std::string& filename);

    /**
    * Finds a Recipe in the tree by name.
    * @param name A const reference to the name.
    * @return A pointer to the node containing the Recipe with the given
    difficulty level, or nullptr if not found.
    */
    std::shared_ptr<BinaryNode<Recipe>> findRecipe(const std::string& name);

   /**
    * Adds a Recipe to the tree.
    * @param recipe A const reference to a Recipe object.
    * @pre: The Recipe does not already exist in the tree (based on name).
    * @post: The Recipe is added to the tree in BST order (based on difficult
    level).
    * @return: True if the Recipe was successfully added; false if a Recipe with
    the same name already exists.
    */
    bool addRecipe(const Recipe& recipe);

    /**
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.
    */
    bool removeRecipe(const std::string& name);

    /**
    * Clears all Recipes from the tree.
    * @post: The tree is emptied, and all nodes are deallocated.
    */
    void clear();

    /**
    * Calculates the number of mastery points needed to master a Recipe.
    * @param name A const reference to a string representing the name of the
Recipe.
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty
    levels must also be mastered.
    * @return: An integer representing the number of mastery points needed, or
    -1 if the Recipe is not found. If the recipe is already mastered, return 0.
    * Note: Mastery points are calculated as the number of unmastered Recipes in
    the tree with a lower difficulty level than the given Recipe. Add one if the
    Recipe is not mastered.
    */
    int calculateMasteryPoints(const std::string& name);

    /**
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
    left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get
    sorted Recipes and rebuilding the tree.
    */
    void balance();

    /**
    * Displays the tree in preorder traversal.
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    * Name: [name_]
    * Difficulty Level: [difficulty_level_]
    * Description: [description_]
    * Mastered: [Yes/No]
    * (Add an empty line between Recipes)
    */
    void preorderDisplay();

};

# endif