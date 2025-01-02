#include "Dessert.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

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
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const {
    return contains_nuts_;
}

/**
* Displays the dessert's details.
* @post Outputs the dessert's details, including name, ingredients,
preparation time, price, cuisine type, flavor profile, sweetness level, and
whether it contains nuts.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
* Sweetness Level: [Sweetness level]
* Contains Nuts: [Yes/No]
*/
void Dessert::display() const {
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
    std::cout << "Flavor Profile: ";
    switch (getFlavorProfile()) {
        case Dessert::SWEET: std::cout << "Sweet" << std::endl; break;
        case Dessert::BITTER: std::cout << "Bitter" << std::endl; break;
        case Dessert::SOUR: std::cout << "Sour" << std::endl; break;
        case Dessert::SALTY: std::cout << "Salty" << std::endl; break;
        case Dessert::UMAMI: std::cout << "Umani" << std::endl; break;
    }
    std::cout << "Sweetness Level: " << getSweetnessLevel() << std::endl;
    std::cout << "Contains Nuts: ";
    if (containsNuts() == true) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
}

/**
* Modifies the dessert based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the dessert's attributes to meet the specified dietary
needs.
* - If `request.nut_free` is true:
* - Sets `contains_nuts_` to false.
* - Removes nuts from `ingredients_`.
* Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
*
* - If `request.low_sugar` is true:
* - Reduces `sweetness_level_` by 3 (minimum of 0).
*
* - If `request.vegan` is true:
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
*/
void Dessert::dietaryAccommodations(const DietaryRequest& request) {
    std::vector<std::string> ingredients_to_change = getIngredients();
    if (request.nut_free == true) {
        setContainsNuts(false);
        std::vector<std::string> nut_types = {"Almonds", "Walnuts", "Pecans", "Hazelnuts", "Peanuts", "Cashews", "Pistachios"};
        // iterate through the vector of ingredients to remove backward to avoid issues with indices
        for (int i = ingredients_to_change.size()-1; i >= 0; i--) {
            if (std::find(nut_types.begin(), nut_types.end(), ingredients_to_change[i]) != nut_types.end()) {
                ingredients_to_change.erase(ingredients_to_change.begin()+i);
            }
        }
    }
    if (request.low_sugar == true) {
        if (getSweetnessLevel() >= 3) {
            int newSweetnessLevel = getSweetnessLevel()-3;
            setSweetnessLevel(newSweetnessLevel);
        } else if (getSweetnessLevel() < 3 && getSweetnessLevel() > 0) {
            setSweetnessLevel(0);
        }
    }
    if (request.vegan == true) {
        std::vector<std::string> egg_and_dairy = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
        // iterate through the vector of ingredients to remove backward to avoid issues with indices
        for (int i = ingredients_to_change.size()-1; i >= 0; i--) {
            if (std::find(egg_and_dairy.begin(), egg_and_dairy.end(), ingredients_to_change[i]) != egg_and_dairy.end()) {
                ingredients_to_change.erase(ingredients_to_change.begin()+i);
            }
        }
    }
    setIngredients(ingredients_to_change);
}