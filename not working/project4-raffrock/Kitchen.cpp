#include "Kitchen.hpp"

// changed to hold Dish pointers 
Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {
}

/**
* Parameterized constructor.
* @param filename The name of the input CSV file containing dish
information.
* @pre The CSV file must be properly formatted.
* @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
*/
Kitchen::Kitchen(const std::string& file_name) : ArrayBag<Dish*>() {
    // open file based on name in parameter
    std::ifstream kitchen_file(file_name);

    // stores variables to be used in Dish object creations
    std::string dish_line; 
    std::string dish_word;
    std::vector<std::string> dish_vector = {};
    std::string dish_type, name, ingredient_string;
    int prep_time;
    double price;
    Dish::CuisineType cuisine_type;
    std::vector<std::string> ingredient_vector = {};

    if (kitchen_file.is_open()) {
        // ignore first line
        std::getline(kitchen_file,dish_line);

        // read line by line until end of file
        // information order: 
        // DishType,Name,Ingredients,PreparationTime,Price,CuisineType,AdditionalAttributes
        while ( std::getline(kitchen_file,dish_line) ) {
            // convert string to stringstream to extract info
            std::istringstream dish_stream(dish_line);

            std::getline(dish_stream, dish_word, ',');
            dish_type = dish_word;
            //dish_type >> dish_word;

            std::getline(dish_stream, dish_word, ',');
            name = dish_word;

            std::getline(dish_stream, dish_word, ',');
            ingredient_string = dish_word;
            std::istringstream ingredient_stream(ingredient_string);
            std::string ingredient; 
            while ( std::getline(ingredient_stream, ingredient, ';') ) {
                ingredient_vector.push_back(ingredient);
            } // turn string into vector of ingredients

            std::getline(dish_stream, dish_word, ',');
            try {
                prep_time = std::stoi(dish_word, nullptr, 10); // string to int
            } catch (const std::invalid_argument& e) {
                std::cout << dish_word;
                std::cerr << " Invalid argument: " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << std::endl;
            }

            std::getline(dish_stream, dish_word, ',');
            price = std::stod(dish_word); // string to double

            std::getline(dish_stream, dish_word, ',');
            // using case to store cuisine_type
            // options: ITALIAN, MEXICAN, CHINESE, INDIAN, AMERICAN, FRENCH, OTHER
            if (dish_word == "ITALIAN") {
                cuisine_type = Dish::ITALIAN;
            } else if (dish_word == "MEXICAN") {
                cuisine_type = Dish::MEXICAN;
            } else if (dish_word == "CHINESE") {
                cuisine_type = Dish::CHINESE;
            } else if (dish_word == "INDIAN") {
                cuisine_type = Dish::INDIAN;
            } else if (dish_word == "AMERICAN") {
                cuisine_type = Dish::AMERICAN;
            } else if (dish_word == "FRENCH") {
                cuisine_type = Dish::FRENCH;
            } else {
                cuisine_type = Dish::OTHER;
            }

            std::getline(dish_stream, dish_word, ',');
            std::istringstream attributes_stream(dish_word);
            std::string att_str;

            // type decides processing of attributes_stream
            // and which constructor is called
            if (dish_type == "APPETIZER") {
                // needed vars
                Appetizer::ServingStyle serving_style;
                int spiciness_level;
                bool vegetarian; 

                std::getline(attributes_stream, att_str, ';');
                // serving_style: PLATED, FAMILY_STYLE, BUFFET
                if (att_str == "PLATED") {
                    serving_style = Appetizer::PLATED;
                } else if (att_str == "FAMILY_STYLE") {
                    serving_style = Appetizer::FAMILY_STYLE;
                } else if (att_str == "BUFFET") {
                    serving_style = Appetizer::BUFFET;
                }

                std::getline(attributes_stream, att_str, ';');
                spiciness_level = std::stoi(att_str, nullptr, 10);

                std::getline(attributes_stream, att_str);
                if (att_str == "true") {
                    vegetarian = true;
                } else {
                    vegetarian = false;
                }

                // constructor Dish object pointer and add to Kitchen
                Dish* appetizer = new Appetizer(name, ingredient_vector, prep_time, price, cuisine_type, serving_style, spiciness_level, vegetarian);
                // Dish* appetizer = new Appetizer;
                // Appetizer app = Appetizer(name, ingredient_vector, prep_time, price, cuisine_type, serving_style, spiciness_level, vegetarian);
                // appetizer = &app;
                //unique_ptr<Dish> appetizer(new Appetizer(name, ingredient_vector, prep_time, price, cuisine_type, serving_style, spiciness_level, vegetarian));
                if (appetizer == nullptr) {
                    std::cerr << "App issue";
                }
                newOrder(appetizer);
                //delete appetizer;
            } else if (dish_type == "MAINCOURSE") {
                // vars needed
                MainCourse::CookingMethod cooking_method;
                std::string protein_type;
                std::vector<MainCourse::SideDish> side_dishes = {};
                bool gluten_free;

                std::getline(attributes_stream, att_str, ';');
                // cooking_method: GRILLED, BAKED, BOILED, FRIED, STEAMED, RAW
                if (att_str == "GRILLED") {
                    cooking_method = MainCourse::GRILLED;
                } else if (att_str == "BAKED") {
                    cooking_method = MainCourse::BAKED;
                } else if (att_str == "BOILED") {
                    cooking_method = MainCourse::BOILED;
                } else if (att_str == "FRIED") {
                    cooking_method = MainCourse::FRIED;
                } else if (att_str == "STEAMED") {
                    cooking_method = MainCourse::STEAMED;
                } else if (att_str == "RAW") {
                    cooking_method = MainCourse::RAW;
                }

                std::getline(attributes_stream, att_str, ';');
                protein_type = att_str;

                std::getline(attributes_stream, att_str, ';');
                //att_str += "|"; // adding | to help split the side dishes
                std::istringstream side_dish_stream(att_str);
                std::string side_string;
                //std::vector<std::string> side_vector;
                MainCourse::Category category; // for side dish
                bool last_side_dish = false;
                // Category = {GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE}
                while(std::getline(side_dish_stream, side_string, '|') || (last_side_dish == true)) 
                {
                    std::istringstream name_and_type(side_string);
                    std::string name_or_type;
                    std::string name;

                    std::getline(name_and_type, name_or_type, ':');
                    name = name_or_type;

                    std::getline(name_and_type, name_or_type, ':');
                    if (name_or_type == "GRAIN") { // convert category to be correct data type for struct instance
                        category =  MainCourse::GRAIN;
                    } else if (name_or_type == "PASTA") {
                        category =  MainCourse::PASTA;
                    } else if (name_or_type == "LEGUME") {
                        category =  MainCourse::LEGUME;
                    } else if (name_or_type == "BREAD") {
                        category =  MainCourse::BREAD;
                    } else if (name_or_type == "SALAD") {
                        category =  MainCourse::SALAD;
                    } else if (name_or_type == "SOUP") {
                        category =  MainCourse::SOUP;
                    } else if (name_or_type == "STARCHES") {
                        category =  MainCourse::STARCHES;
                    } else if (name_or_type == "VEGETABLE") {
                        category =  MainCourse::VEGETABLE;
                    }

                        side_dishes.push_back({name, category});

                    if (std::getline(side_dish_stream, side_string, ';') && (last_side_dish == false)) {
                        last_side_dish = true; // to collect the last
                    } else if (last_side_dish == true) {
                        last_side_dish = false;
                    }
                }

                std::getline(attributes_stream, att_str);
                if (att_str == "true") {
                    gluten_free = true;
                } else {
                    gluten_free = false;
                }
                Dish* maincourse = new (std::nothrow) MainCourse(name, ingredient_vector, prep_time, price, cuisine_type, cooking_method, protein_type, side_dishes, gluten_free);
                // Dish* maincourse = new MainCourse;
                // MainCourse mainC = MainCourse(name, ingredient_vector, prep_time, price, cuisine_type, cooking_method, protein_type, side_dishes, gluten_free);
                // maincourse = &mainC;
                // if (maincourse == nullptr) {
                //     std::cerr << "Main issue";
                // }
                newOrder(maincourse);
                //delete maincourse;
            } else if (dish_type == "DESSERT") {
                // vars needed
                Dessert::FlavorProfile flavor_profile;
                int sweetness_level;
                bool contains_nuts;

                std::getline(attributes_stream, att_str, ';');
                //std::cout << att_str << std::endl;
                // convert to enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI }
                if (att_str == "SWEET") {
                    flavor_profile = Dessert::SWEET;
                } else if (att_str == "BITTER") {
                    flavor_profile = Dessert::BITTER;
                } else if (att_str == "SOUR") {
                    flavor_profile = Dessert::SOUR;
                } else if (att_str == "SALTY") {
                    flavor_profile = Dessert::SALTY;
                } else if (att_str == "UMAMI") {
                    flavor_profile = Dessert::UMAMI;
                }

                std::getline(attributes_stream, att_str, ';');
                sweetness_level = std::stoi(att_str, nullptr, 10);

                std::getline(attributes_stream, att_str);
                //std::cout << att_str << std::endl;
                if (att_str == "true") {
                    contains_nuts = true;
                } else {
                    contains_nuts = false;
                }

                Dish*  dessert = new (std::nothrow) Dessert(name, ingredient_vector, prep_time, price, cuisine_type, flavor_profile, sweetness_level, contains_nuts);
                // Dish* dessert = new Dessert;
                // Dessert des = Dessert(name, ingredient_vector, prep_time, price, cuisine_type, flavor_profile, sweetness_level, contains_nuts);
                // dessert = &des;
                if (dessert == nullptr) {
                    std::cerr << "Des issue";
                }
                newOrder(dessert);
                //delete dessert;
            }
            // to check?
            ingredient_vector.clear(); // empty for the next dish object
        }
        kitchen_file.close();
    }
}

/**
* Destructor.
* @post Deallocates all dynamically allocated dishes to prevent memory
leaks.
*/
Kitchen::~Kitchen() {
    for (Dish* item : items_) {
        if (item != nullptr) {
            delete item;
            item = nullptr;
        }
    }
    //items_.clear();
}

bool Kitchen::newOrder(Dish* new_dish)
{
    // if (add(new_dish))
    // {
    //     total_prep_time_ += new_dish.getPrepTime();
    //     //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
    //     //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
    //     if (new_dish.getIngredients().size() >= 5 && new_dish.getPrepTime() >= 60)
    //     {
    //         //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
    //         count_elaborate_++;
    //     }
    //     return true;
    // }
    // return false;

   // rewriting newOrder() rather than using add()
    if (item_count_ < DEFAULT_CAPACITY) {
        total_prep_time_ += new_dish->getPrepTime();
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60)
        {
            count_elaborate_++;
        }
        items_[item_count_] = new_dish;
        item_count_++;
        return true;
    } else {
        return false;
    }
}

bool Kitchen::serveDish(Dish* dish_to_remove)
{   
    auto found = std::find(std::begin(items_), std::end(items_), dish_to_remove);
    if (found != std::end(items_)) {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        items_[(found - std::begin(items_))] = items_[item_count_];
        item_count_--;
        return true;
    }
    return false;
//     if (getCurrentSize() == 0)
//     {
//         return false;
//     }
//     if (remove(dish_to_remove))
//     {
//         total_prep_time_ -= dish_to_remove.getPrepTime();
//         if (dish_to_remove.getIngredients().size() >= 5 && dish_to_remove.getPrepTime() >= 60)
//         {
//             count_elaborate_--;
//         }
//         return true;
//     }
//     return false;
}

int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}

int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

/**
* Adjusts all dishes in the kitchen based on the specified dietary
accommodation.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Calls the `dietaryAccommodations()` method on each dish in the
kitchen to adjust them accordingly.
*/
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest& request) {
    for (Dish* item : this->items_) {
        if (item != nullptr) {
            item->dietaryAccommodations(request);
        }
    }
}

/**
* Displays all dishes currently in the kitchen.
* @post Calls the `display()` method of each dish.
*/
void Kitchen::displayMenu() {
    for (Dish* item : this->items_) {
        if (item != nullptr) {
            item->display();
        }
    }
}