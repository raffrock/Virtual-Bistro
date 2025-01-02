#include "MainCourse.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
* Displays the main course's details.
* @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
* Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
* Side Dishes: [Side dish name] (Category: [Category: e.g., Starches, Vegetables])
* Gluten-Free: [Yes/No]
*/
void MainCourse::display() const {
    std::cout << "Dish Name: " << getName() << std::endl;
    std::cout << "Ingredients: ";
    std::vector<std::string> ingredients_ = getIngredients();
    for (size_t i = 0; i < ingredients_.size(); ++i) {
        std::cout << ingredients_[i];
        if (i != ingredients_.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;
    std::cout << "Cooking Method: ";
    switch (getCookingMethod()) {
        case MainCourse::CookingMethod::GRILLED: std::cout << "Grilled" << std::endl; break;
        case MainCourse::CookingMethod::BAKED: std::cout << "Baked" << std::endl; break;
        case MainCourse::CookingMethod::BOILED: std::cout << "Boiled" << std::endl; break;
        case MainCourse::CookingMethod::FRIED: std::cout << "Fried" << std::endl; break;
        case MainCourse::CookingMethod::STEAMED: std::cout << "Steamed" << std::endl; break;
        case MainCourse::CookingMethod::RAW: std::cout << "Raw" << std::endl; break;
    }
    std::cout << "Protein Type: " << getProteinType() << std::endl;
    std::cout << "Side Dishes: ";
    for (int i = 0; i < getSideDishes().size(); i++) {
        std::cout <<  getSideDishes()[i].name << " (Category: ";
        switch (getSideDishes()[i].category) {
            case MainCourse::Category::GRAIN:
                std::cout << "GRAIN)";
                break;
            case MainCourse::Category::PASTA:
                std::cout << "PASTA)";
                break;
            case MainCourse::Category::LEGUME:
                std::cout << "LEGUME)";
                break;
            case MainCourse::Category::BREAD:
                std::cout << "BREAD)";
                break;
            case MainCourse::Category::SALAD:
                std::cout << "SALAD)";
                break;
            case MainCourse::Category::SOUP:
                std::cout << "SOUP)";
                break;
            case MainCourse::Category::STARCHES:
                std::cout << "STARCHES)";
                break;
            case MainCourse::Category::VEGETABLE:
                std::cout << "VEGETABLE)";
                break;
            default: 
                std::cout << "ERROR!";
        }
        if (i < getSideDishes().size()-1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "Gluten-Free: ";
    if (isGlutenFree() == true) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
}

/**
* Modifies the main course based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the main course's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Changes `protein_type_` to "Tofu".
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
*
* - If `request.vegan` is true:
* - Changes `protein_type_` to "Tofu".
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
*
* - If `request.gluten_free` is true:
* - Sets `gluten_free_` to true.
* - Removes side dishes from `side_dishes_` whose category
involves gluten.
* Gluten-containing side dish categories are: `GRAIN`,
`PASTA`, `BREAD`, `STARCHES`.
*/
void MainCourse::dietaryAccommodations(const DietaryRequest& request) {
    std::vector<std::string> ingredients_to_change = getIngredients();
    if (request.vegetarian == true) {
        int replaceCount = 0;
        std::vector<std::string> meat = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        std::vector<int> remove_index = {};
        for (int i = 0; i < ingredients_to_change.size(); ++i) {
            if (std::find(meat.begin(), meat.end(), ingredients_to_change[i]) != meat.end()) {
                replaceCount++;
                if (replaceCount == 1) {
                    ingredients_to_change[i] = "Beans";
                } else if (replaceCount == 2) {
                    ingredients_to_change[i] = "Mushrooms";
                } else {
                    remove_index.push_back(i);
                }
            }
        }
        // iterate through the vector of index of elements to remove backward to avoid issues with indices
        for (int i = remove_index.size()-1; i >= 0; i--) {
            ingredients_to_change.erase(ingredients_to_change.begin()+remove_index[i]);
        }
    } 
    if (request.vegan == true) {
        setProteinType("Tofu");
        std::vector<std::string> egg_and_dairy = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
        // iterate through the vector of ingredients to remove backward to avoid issues with indices
        for (int i = ingredients_to_change.size()-1; i >= 0; i--) {
            if (std::find(egg_and_dairy.begin(), egg_and_dairy.end(), ingredients_to_change[i]) != egg_and_dairy.end()) {
                ingredients_to_change.erase(ingredients_to_change.begin()+i);
            }
        }
    }
    if (request.gluten_free == true) {
        setGlutenFree(true);
        std::vector<Category> gluten = {GRAIN, PASTA, BREAD, STARCHES};
        for (int i = side_dishes_.size()-1; i >= 0; i--) {
            if (std::find(gluten.begin(), gluten.end(), side_dishes_[i].category) != gluten.end()) {
                side_dishes_.erase(side_dishes_.begin()+i);
            }
        }
    }
    setIngredients(ingredients_to_change);
}


/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}