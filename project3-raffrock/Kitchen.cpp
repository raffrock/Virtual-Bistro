/**
* @file Kitchen.cpp
* @brief This file is the implementation of the Kitchen class, which can manages the Dish objects in a virtual bistro simulation.
*
* The Kitchen class manages Dish objects.
* It provides constructors, accessor and mutator functions.
* It has functions that add and remove Dish objects from the Kitchen, query the
* Kitchen for information about the Dish objects it contains, and releases
* dishes from the kitchen based on their preparation time and cuisine type.
*
* @date 10/15/24
* @author Rafael Chetata
*/


// NOTE TO SELF: Need to use pointer to allDishes. and maybe switch name to all_dishes
    // helpful link : https://stackoverflow.com/questions/26331628/reference-to-non-static-member-function-must-be-called

#include "Kitchen.hpp"
#include<iostream>

/**
 * Default constructor.
 * Default-initializes all private members.
 */

Kitchen::Kitchen() : ArrayBag<Dish>(),  totalprep_time(0),  countelaborate(0) {
}

/**
 * @param : A reference to a `Dish` being added to the kitchen.
 * @post : If the given `Dish` is not already in the kitchen, adds the
`Dish` to the kitchen and updates the preparation time sum and elaborate
dish count if the dish is elaborate.
* @return : Returns true if a `Dish` was successfully added to the
kitchen, false otherwise.
Hint: Use the above definition of equality to help determine if a
`Dish` is already in the kitchen.
*/

bool Kitchen::newOrder(const Dish& dish) {
    if ((dish.getIngredients().size() >= 5) && (dish.getPrepTime() >= 60)) {
        countelaborate++;
    }
    totalprep_time += dish.getPrepTime();
    return add(dish);
}

/**
 * @param : A reference to a `Dish` leaving the kitchen.
 * @return : Returns true if a dish was successfully removed from the
kitchen (i.e.,
items_), false otherwise.
* @post : Removes the dish from the kitchen and updates the preparation
time sum.
If the `Dish` is elaborate, it also updates the elaborate
count.
*/

bool Kitchen::serveDish(const Dish& dish) {
    if ((dish.getIngredients().size() >= 5) && (dish.getPrepTime() >= 60)) {
        countelaborate--;
    }
     totalprep_time -= dish.getPrepTime();
    return remove(dish);
}

/**
 * @return : The integer sum of preparation times for all the dishes
currently in the kitchen.
*/

int Kitchen::getPrepTimeSum() const {
    return  totalprep_time;
}

/**
 * @return : The average preparation time (int) of all the dishes in the
kitchen. The lowest possible average prep time should be 0.
* @post : Computes the average preparation time (double) of the kitchen
rounded to the NEAREST integer.
*/

int Kitchen::calculateAvgPrepTime() const {
    double avg_time = (double) totalprep_time / (double)item_count_;
    return std::round(avg_time);
}

/**
* @return : The integer count of the elaborate dishes in the kitchen.
*/
int Kitchen::elaborateDishCount() const {
    return countelaborate;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the
kitchen. The lowest possible percentage should be 0%.
* @post : Computes the percentage of elaborate dishes in the kitchen
rounded up to 2 decimal places.
*/

double Kitchen::calculateElaboratePercentage() const {
    int returnInt = 0;
    double percentage_elaborate = (double)countelaborate / (double)item_count_;
    returnInt += percentage_elaborate;
    return returnInt;
}

/**
 * @param : A reference to a string representing a cuisine type with a
value in
["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
"FRENCH", "OTHER"].
* @return : An integer tally of the number of dishes in the kitchen of the
given cuisine type.
If the argument string does not match one of the expected
cuisine types, the tally is zero.
NOTE: No pre-processing of the input string necessary, only
uppercase input will match.
*/

int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) {
    int tally = 0;
    for (int i = 0; i < item_count_; i++) {
        if (items_[i].getCuisineType() == cuisine_type) {
            tally++;
        }
    }
    return tally;

}

/**
 * @param : A reference to an integer representing the preparation time
threshold of the dishes to be removed from the kitchen, with a default value of 0.
* @post : Removes all dishes from the kitchen whose preparation time is
less than the given time.
If no time is given, removes all dishes from the kitchen. Ignore
negative input.
* @return : The number of dishes removed from the kitchen.
*/

int Kitchen::releaseDishesBelowPrepTime(int prep_time_limit) {
    int num_removed = 0;
    for (Dish dish : items_) {
        if (dish.getPrepTime() < prep_time_limit) {
            //std::cout << "Removed " << items_[i].getName() << std::endl;
            serveDish(dish); // use this so prep_time and elab updated
            num_removed++;
        }
    }
    return num_removed;
}

/**
 * @param : A reference to a string representing a cuisine type with a
value in
["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
"FRENCH", "OTHER"],
or a default value of "ALL" if no cuisine type is given.
* @post : Removes all dishes from the kitchen whose cuisine type matches
the given type.
If no cuisine type is given, removes all dishes from the kitchen.
* @return : The number of dishes removed from the kitchen.
NOTE: No pre-processing of the input string necessary, only
uppercase input will match.
If the input string does not match one of the expected cuisine
types, do not remove any dishes.
*/

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type) {
    int num_removed = 0;
    for (Dish dish : items_) {
        if ((dish.getCuisineType() == cuisine_type) || (cuisine_type == "ALL")) {
            serveDish(dish);
            num_removed++;
        }
    }
    return num_removed;
}

/**
 * @post : Outputs a report of the dishes currently in the kitchen in the
form:
* "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:
*  {x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
*  AVERAGE PREP TIME: {x}\nelaborate: {x}%\n"
*  Note that the average preparation time should be rounded to the
* NEAREST integer, and the
* percentage of elaborate dishes in the kitchen should be
*  rounded to 2 decimal places.
* Example output:
* ITALIAN: 2
* MEXICAN: 3
* CHINESE: 2
* INDIAN: 1
* AMERICAN: 1
* FRENCH: 2
* OTHER: 2
* AVERAGE PREP TIME: 62
* elaborate: 53.85%
*/

void Kitchen::kitchenReport() {
    std::cout << "ITALIAN: {"<< tallyCuisineTypes("ITALIAN") <<"}\nMEXICAN: {"<< tallyCuisineTypes("MEXICAN") <<"}\nCHINESE: {"<< tallyCuisineTypes("CHINESE") <<"}\nINDIAN: {"<< tallyCuisineTypes("INDIAN") <<"}\nAMERICAN: {"<< tallyCuisineTypes("AMERICAN") <<"}\nFRENCH: {"<< tallyCuisineTypes("FRENCH") <<"}\nOTHER: {"<< tallyCuisineTypes("OTHER") <<"}\n";
    std::cout << "AVERAGE PREP TIME: "<< calculateAvgPrepTime() <<"\n";
    std::cout << "ELABORATE: " << calculateElaboratePercentage() << "%\n";
}