#include "Appetizer.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

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
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}

/**
* Displays the appetizer's details.
* @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level, and
vegetarian status, to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Serving Style: [Serving style: Plated, Family Style, or Buffet]
* Spiciness Level: [Spiciness level]
* Vegetarian: [Yes/No]
*/
void Appetizer::display() const {
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
    std::cout << "Serving Style: ";
    if (getServingStyle() == PLATED) {
        std::cout << "Plated";
    } else if (getServingStyle() == FAMILY_STYLE) {
        std::cout << "Family Style";
    } else {
        std::cout << "Buffet";
    }
    std::cout << std::endl;
    std::cout << "Spiciness Level: " << getSpicinessLevel() << std::endl;
    std::cout << "Vegetarian: ";
    if (isVegetarian() == true) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
}

/**
* Modifies the appetizer based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the appetizer's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Sets `vegetarian_` to true.
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
*
* - If `request.low_sodium` is true:
* - Reduces `spiciness_level_` by 2 (minimum of 0).
*
* - If `request.gluten_free` is true:
* - Removes gluten-containing ingredients from
`ingredients_`.
* Gluten-containing ingredients are: "Wheat", "Flour",
"Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/
void Appetizer::dietaryAccommodations(const Dish::DietaryRequest& request) {
    std::vector<std::string> ingredients_to_change = Dish::getIngredients();
    if (request.vegetarian == true) {
        setVegetarian(true);
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
    if (request.low_sodium == true) {
        if (getSpicinessLevel() >= 2) {
            int newSpiceLevel = getSpicinessLevel()-2;
            setSpicinessLevel(newSpiceLevel);
        } else if (getSpicinessLevel() < 2 && getSpicinessLevel() > 0) {
            setSpicinessLevel(0);
        }
    }
    if (request.gluten_free == true) {
        std::vector<std::string> gluten = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"};
        // iterate through the vector of ingredients to remove backward to avoid issues with indices
        for (int i = ingredients_to_change.size()-1; i >= 0; i--) {
            if (std::find(gluten.begin(), gluten.end(), ingredients_to_change[i]) != gluten.end()) {
                ingredients_to_change.erase(ingredients_to_change.begin()+i);
            }
        }
    }
    setIngredients(ingredients_to_change);
}