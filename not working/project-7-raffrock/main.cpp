/** 
*@file StationManager.cpp 
* Rafael Chetata
* 12/16/24
* Testing file for RecipeBook class.
*/

#include <iostream>
#include "RecipeBook.hpp"
// #include "BinaryNode.hpp"

/*
        ISSUES:
    None for now. But gradescope is 0...
    We can use helper functions!!
*/

// code to check if the final tree is balanced
    // counts the height of a tree recursively 
// int height(std::shared_ptr<BinaryNode<Recipe>> root) {
//     if (root == nullptr) {
//         return 0;
//     }
//     return 1 + std::max(height(root->getLeftChildPtr()), height(root->getRightChildPtr()));
// }
//     // uses height function to check if there is less than 1 unit of difference between heights of subtrees
// bool isBalanced(std::shared_ptr<BinaryNode<Recipe>> root) {
//     if (root == nullptr) {
//         return true;
//     }
//     int leftHeight = height(root->getLeftChildPtr());
//     int rightHeight = height(root->getRightChildPtr());
//     if (std::abs(leftHeight - rightHeight) <= 1 && isBalanced(root->getLeftChildPtr()) && isBalanced(root->getRightChildPtr())) {
//         return true;
//     }
//     return false;
// }

int main() {
    
    Recipe name5 = Recipe("name5", 5, "description5");
    std::cout << "test default ctor for recipe: " << name5.mastered_ << std::endl;

    RecipeBook myRecipeBook = RecipeBook("debug.csv");
    RecipeBook onlyName5;
    onlyName5.addRecipe(name5);

    std::cout << "root: " << onlyName5.getRoot()->getItem().name_ << std::endl;

    std::cout << "findRecipe: name2 -> " << myRecipeBook.findRecipe("name2")->getItem().name_ << std::endl;
    std::cout << "addRecipe: " << myRecipeBook.addRecipe(name5) << std::endl;  // 0
    std::cout << "removeRecipe: " << myRecipeBook.removeRecipe("name6") << std::endl; // 1
    onlyName5.clear(); //works
    std::cout << "calculateMasteryPoints: " << myRecipeBook.calculateMasteryPoints("name2") << std::endl; // 1+2+3+4 = 10
    // std::cout << "before height: " << myRecipeBook.getHeight();
    myRecipeBook.balance();
    // std::cout << "  after heigh
    t: " << myRecipeBook.getHeight() << std::endl;
    //  std::cout << "  left height: " << myRecipeBook.get() << "  right height: " << myRecipeBook.getHeight() << std::endl;
    std::cout << "\nonlyName5 display\n\n";
    onlyName5.preorderDisplay();
    std::cout << "\nmyRecipeBook display\n\n";
    myRecipeBook.preorderDisplay();

    // std::cout << "is balanced? " << isBalanced(myRecipeBook.getRoot());

}
