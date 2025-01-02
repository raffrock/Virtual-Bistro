/** 
*@file StationManager.cpp 
* Rafael Chetata
* 12/16/24
* Implementation file for RecipeBook class. This file contains the code for all class functions.
*/

#include "RecipeBook.hpp"

/**
* Default Constructor.
* @post: Initializes an empty RecipeBook.
*/
RecipeBook::RecipeBook() {
}

/**
* Parameterized Constructor.
* @param filename A const reference to a string representing the name of a
CSV file.
* @post: The RecipeBook is populated with Recipes from the CSV file.
* The file format is as follows:
* name,difficulty_level,description,mastered
* Ignore the first line. Each subsequent line represents a Recipe to be
added to the RecipeBook.
*/
RecipeBook::RecipeBook(const std::string& filename) {
    // open file based on name in parameter
    std::ifstream recipe_file(filename);

    // stores string that contains all recipe information
    // ex. name,difficulty_level,description,mastered
    std::string recipe_line;
    // skip first line of information
    std::getline(recipe_file,recipe_line);

    if (recipe_file.is_open()) {
        while (std::getline(recipe_file,recipe_line)) {
            // turns line into stream to get information from
            std::istringstream r_stream(recipe_line);
            // hold individual pieces of information
            std::string r_word;
            // empty Recipe object to assign values from on r_stream
            Recipe placeholder_recipe;

            // asigning values to placeholder_recipe
            std::getline(r_stream, r_word, ',');
            placeholder_recipe.name_ = r_word;
            std::getline(r_stream, r_word, ',');
            placeholder_recipe.difficulty_level_ = std::stoi(r_word);
            std::getline(r_stream, r_word, ',');
            placeholder_recipe.description_ = r_word;
            std::getline(r_stream, r_word, ',');
            placeholder_recipe.mastered_ = std::stoi(r_word); // 0 or 1

            // add recipe to tree
            addRecipe(placeholder_recipe);
        }
    }

    recipe_file.close();
}

/**
* Finds a Recipe in the tree by name.
* @param name A const reference to the name.
* @return A pointer to the node containing the Recipe with the given
difficulty level, or nullptr if not found.
*/
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findRecipe(const std::string& name) {
    // using stack to hold the nodes
    std::stack<std::shared_ptr<BinaryNode<Recipe>>> node_stack; 
    // start with root node
    node_stack.push(getRoot());

    while (!node_stack.empty() && node_stack.top() != nullptr) {
        // get node at top of stack
        std::shared_ptr<BinaryNode<Recipe>> current_node_ptr = node_stack.top();
        node_stack.pop();

        // check if current node is the recipe 
        if (current_node_ptr->getItem().name_ == name) {
            // return if is recipe
            return current_node_ptr;
        }

        // append left and right nodes to stack if they exist
        if (current_node_ptr->getLeftChildPtr() != nullptr) {
            node_stack.push(current_node_ptr->getLeftChildPtr());
        }
        if (current_node_ptr->getRightChildPtr() != nullptr) {
            node_stack.push(current_node_ptr->getRightChildPtr());
        }
    }

    // if recipe not found
    return nullptr;
}

/**
* Adds a Recipe to the tree.
* @param recipe A const reference to a Recipe object.
* @pre: The Recipe does not already exist in the tree (based on name).
* @post: The Recipe is added to the tree in BST order (based on difficult
level).
* @return: True if the Recipe was successfully added; false if a Recipe with
the same name already exists.
*/
bool RecipeBook::addRecipe(const Recipe& recipe) {
    // if name already in tree, cannot add
    if (findRecipe(recipe.name_) != nullptr) {
        return false;
    }
    // the BST add function adds new nodes based on equality 
    // (which is based on the override operaters for Recipe, which revolve around the name)
    add(recipe);
    return true;
}

/**
* Removes a Recipe from the tree by name.
* @param name A const reference to a string representing the name of the
Recipe.
* @post: If found, the Recipe is removed from the tree.
* @return: True if the Recipe was successfully removed {} false otherwise.
*/
bool RecipeBook::removeRecipe(const std::string& name) {
    std::shared_ptr<BinaryNode<Recipe>> recipe_ptr = findRecipe(name);
    if (recipe_ptr == nullptr) {
        // no recipe to remove
        return false;
    } else {
        // return result of remove function
        return remove(recipe_ptr->getItem());
    }
}

/**
* Clears all Recipes from the tree.
* @post: The tree is emptied, and all nodes are deallocated.
*/
void RecipeBook::clear() {
    // remove from left and right subtree until root has no children
    while(!getRoot()->isLeaf()) {
        if (getRoot()->getLeftChildPtr() != nullptr) {
            remove(getRoot()->getLeftChildPtr()->getItem());
        }
        if (getRoot()->getRightChildPtr() != nullptr) {
            remove(getRoot()->getRightChildPtr()->getItem());
        }
    }

    // remove root
    remove(getRoot()->getItem());
}

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
int RecipeBook::calculateMasteryPoints(const std::string& name) {
    int mastery_points = 0;

    // if not found, return -1
    if (findRecipe(name) == nullptr) {
        return -1;
    }

    int difficulty_level = findRecipe(name)->getItem().difficulty_level_;

    // using stack to hold the nodes
    std::stack<std::shared_ptr<BinaryNode<Recipe>>> node_stack; 
    node_stack.push(getRoot());

    while (!node_stack.empty()) {

        // focus on node at top of stack
        std::shared_ptr<BinaryNode<Recipe>> current_node_ptr = node_stack.top();
        Recipe this_recipe = current_node_ptr->getItem();
        node_stack.pop();

        // check if diffculty less than node & not mastered
        if (this_recipe.difficulty_level_ < difficulty_level && !this_recipe.mastered_) {
            mastery_points++;
        } else if (this_recipe.name_ == name) {
            // if choosen recipe not mastered, add one
            if (!this_recipe.mastered_) {
                mastery_points++;
            } else {
                // if recipe already mastered, return 0
                return 0;
            }
        }

        // add left and right nodes to stack
        if (current_node_ptr->getLeftChildPtr() != nullptr) {
            node_stack.push(current_node_ptr->getLeftChildPtr());
        }
        if (current_node_ptr->getRightChildPtr() != nullptr) {
            node_stack.push(current_node_ptr->getRightChildPtr());
        }
    }

    return mastery_points;
}

/**
* Balances the tree.
* @post: The tree is balanced such that for any node, the heights of its
left and right subtrees differ by no more than 1.
* @note: You may implement this by performing an inorder traversal to get
sorted Recipes and rebuilding the tree.
*/ 
void RecipeBook::balance() {
    std::stack<std::shared_ptr<BinaryNode<Recipe>>> node_stack; 
    std::shared_ptr<BinaryNode<Recipe>> current_node = getRoot();

    std::map<std::string, Recipe> name_and_recipe_vector; // name_, recipe
    std::vector<std::string> name_list = {};

    while (current_node != nullptr || !node_stack.empty()) {
        // search left of subtree
        while (current_node != nullptr) {
            node_stack.push(current_node);
            current_node = current_node->getLeftChildPtr();
        }

        // done travsering left bc found leaf
        // return to root
        current_node = node_stack.top();
        // remove leaf 
        node_stack.pop();

        name_and_recipe_vector.insert({current_node->getItem().name_, current_node->getItem()});
        name_list.push_back(current_node->getItem().name_);

        current_node = current_node->getRightChildPtr();
    }

    // sort diffculty_list
    std::sort(name_list.begin(), name_list.end());

    // console log to check

    // std::cout << "\n\tdiffculty_list:";
    // for (int diff : diffculty_list) {
    //     std::cout << " " << diff;
    // }
    // std::cout << std::endl;

    // std::cout << "\trecipe: by diffculty: ";
    // for (auto& [level, recipe] : name_and_recipe_vector) {
    //     std::cout << recipe.name_ << " ";
    // }
    // std::cout << std::endl;

    clear();
    
    // pair recipe to range
    std::queue<std::pair<Recipe,std::pair<int,int>>> recipe_queue;
    // find middle value, it will be the root 
    int l = 0;
    int r = name_list.size()-1;
    int mid = r / 2;
    std::string name = name_list[mid];
    // add root to queue
    recipe_queue.push({name_and_recipe_vector[name], {0, r}});

    // iterate through queue of recipes
    // take recipe from front and add to tree
    // add left and right children to queue
        // children choose with modified binary search 
    // pair recipe with the range of indices that contain it's possible children 
    // repeat and find their children until no more recipes to add

    while (!recipe_queue.empty()) {

        // add recipe to tree and remove from queue
        std::pair<Recipe,std::pair<int,int>> front = recipe_queue.front();
        Recipe current_recipe = front.first;
        add(current_recipe);
        recipe_queue.pop();

        // store range of the recipe
        l = front.second.first;
        r = front.second.second;
        // finds new middle in the range
        int index = l + (r-l) / 2;

        // check range of recipes 
        // std::cout << "\n\t" << current_recipe.name_ << " l: " << l << " r: " << r << " index: " << index;

        // if there is a recipe to the left of middle in range, attempt to add middle recipe to queue
        if (l < index) {
            // 
            mid = l + (index-1 - l) / 2;
            name = name_list[mid];
            Recipe left = name_and_recipe_vector[name];
            // store with it's own range
            recipe_queue.push({left,{l, index - 1}});
        }
        // if there is a recipe to the right of middle in range, attempt to add middle recipe to queue
        if (r > index) {
            mid = index + 1 + (r - index - 1) / 2;
            name = name_list[mid];
            Recipe right = name_and_recipe_vector[name];
            // store with it's own range
            recipe_queue.push({right,{index + 1, r}});
        }
    }
}

/**
* Displays the tree in preorder traversal.
* @post: Outputs the Recipes in the tree in preorder, formatted as:
* Name: [name_]
* Difficulty Level: [difficulty_level_]
* Description: [description_]
* Mastered: [Yes/No]
* (Add an empty line between Recipes)
*/
void RecipeBook::preorderDisplay() {
    if (getRoot() == nullptr) {
        return;
    }

    // using stack to hold the nodes
    std::stack<std::shared_ptr<BinaryNode<Recipe>>> node_stack; 
    node_stack.push(getRoot());

    while (!node_stack.empty()) {
        std::shared_ptr<BinaryNode<Recipe>> current_node_ptr = node_stack.top();
        Recipe this_recipe = current_node_ptr->getItem();
        node_stack.pop();

        // display recipe
        std::cout << "Name: " << this_recipe.name_ << std::endl;
        std::cout << "Difficulty Level: " << this_recipe.difficulty_level_ << std::endl;
        std::cout << "Description: " << this_recipe.description_ << std::endl;
        std::cout << "Mastered: ";
        if (this_recipe.mastered_) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
        std::cout << std::endl;

        // traverse left and right substrees if avaiblie 
        if (current_node_ptr->getRightChildPtr() != nullptr) {
            node_stack.push(current_node_ptr->getRightChildPtr());
        }
        if (current_node_ptr->getLeftChildPtr() != nullptr) {
            node_stack.push(current_node_ptr->getLeftChildPtr());
        }
    }
}

