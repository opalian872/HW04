#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경

class StockManager;
class RecipeManager;

class PotionRecipe
{
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    bool operator==(const std::string& otherName) const
    {
        return potionName == otherName;
    }
    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients)
    {

    }

    //Potion 정보 보여주는 메서드
    void displayPotionInfo() const
    {
        std::cout << "This potion's name is: " << potionName << " and it's ingredients are: ";
        for (size_t i = 0; i < ingredients.size(); ++i)
        {
            std::cout << ingredients[i];
            // 마지막 재료가 아니면 쉼표로 구분
            if (i < ingredients.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        return;
    }
};

// AlchemyWorkshop 클래스 RecipeManager로 변경
class RecipeManager
{
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> New Recipe '" << name << "'has been added." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const
    {
        if (recipes.empty())
        {
            std::cout << "No recipes existing." << std::endl;
            return;
        }

        std::cout << "\n---[Recipes List]---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i)
        {
            std::cout << "- Potion Name: " << recipes[i].potionName << std::endl;
            std::cout << "  > Ingredients needed: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j)
            {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }
    std::vector<PotionRecipe> getAllRecipes() const
    {
        return recipes;
    }
    PotionRecipe searchRecipeByName(const std::string& name) const
    {
        auto it = std::find(recipes.begin(), recipes.end(), name);
        if (it != recipes.end())
        {
            PotionRecipe foundPotion = *it;
            return foundPotion;
        }
        else
        {
            return PotionRecipe("", {});
        }
    }
    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient) const
    {
        std::vector<PotionRecipe> foundRecipes;
        for (const PotionRecipe& recipe : recipes)
        {
            for (const std::string& searchIngredient : recipe.ingredients)
            {
                if (searchIngredient == ingredient)
                {
                    foundRecipes.push_back(recipe);
                    break;
                }
            }
        }
        return foundRecipes;
    }
    std::vector <PotionRecipe> searchRecipeUniversal(const std::string& keyword) const
    {
        std::vector<PotionRecipe> foundRecipes;
        PotionRecipe nameResult = searchRecipeByName(keyword);
        if (nameResult.potionName != "")
        {
            foundRecipes.push_back(nameResult);
        }
        std::vector<PotionRecipe> ingredientSearchRecipes = searchRecipeByIngredient(keyword);
        for (const PotionRecipe& recipe : ingredientSearchRecipes)
        {
            if (recipe.potionName != nameResult.potionName)
            {
                foundRecipes.push_back(recipe);
            }
        }
        return foundRecipes;
    }
};

class StockManager
{
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;
public:
    void initializeStock(std::string potionName)
    {
        {
            potionStock.insert({potionName, 3});
        }
    }
    bool dispensePotion(std::string potionName)
    {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end())
        {
            if (it->second > 0)
            {
                it->second--;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    bool retrievePotion(std::string potionName)
    {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end())
        {
            if (it->second < MAX_STOCK)
            {
                it->second++;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    int getStock(std::string potionName) const
    {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end()) 
        {
            return it->second;
        }
        else
        {
            std::cout << "Potion cannot be found. getStock Failed" << std::endl;
            return -1;
        }
    }

};

class AlchemyWorkshop
{
private:
    RecipeManager recipeManager;
    StockManager stockManager;
public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    {
        recipeManager.addRecipe(name, ingredients);
        stockManager.initializeStock(name);
    }
    void displayAllRecipes() const
    {
        recipeManager.displayAllRecipes();
    }
    PotionRecipe searchRecipeByName(const std::string& name) const
    {
        return recipeManager.searchRecipeByName(name);
    }
    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient) const
    {
        return recipeManager.searchRecipeByIngredient(ingredient);
    }
    std::vector <PotionRecipe> searchRecipeUniversal(const std::string& keyword) const
    {
        return recipeManager.searchRecipeUniversal(keyword);
    }
    bool dispensePotion(const std::string& name)
    {
        return stockManager.dispensePotion(name);
    }
    bool retrievePotion(const std::string& name)
    {
        return stockManager.retrievePotion(name);
    }
    int getStock(const std::string& potionName) const
    {
        return stockManager.getStock(potionName);
    }
    void displayAllStocks() const
    {
        std::vector<PotionRecipe> recipes = recipeManager.getAllRecipes();
        for (const PotionRecipe& recipe : recipes)
        {
            std::cout << "Potion name: " << recipe.potionName << " Current stock: " << stockManager.getStock(recipe.potionName) << std::endl;
        }
    }
};
int main()
{
    AlchemyWorkshop myWorkshop;

    while (true)
    {
        std::cout << "⚗️ Alchemy Lab Management System" << std::endl;
        std::cout << "1. Add Recipe" << std::endl;
        std::cout << "2. Print All Recipes" << std::endl;
        std::cout << "3. Print Potion Stocks" << std::endl;
        std::cout << "4. Search Recipes by Name" << std::endl;
        std::cout << "5. Search Recipes by Ingredient" << std::endl;
        std::cout << "6. Search Recipes by Both" << std::endl; // 이름, 재료 둘 다로 검색 가능하게
        std::cout << "7. Dispense Potion" << std::endl; //포션 건네주기
        std::cout << "8. Retrieve Potion Bottle from Adventurer" << std::endl; //물약 돌려받기
        std::cout << "9. End" << std::endl;
        std::cout << "Choose: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "Invalid input. Put in a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::string name;
            std::cout << "Potion Name: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "Enter all necessary ingredients. Enter 'End' when you are finished." << std::endl;

            while (true)
            {
                std::cout << "Enter ingredient - one at a time: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "End")
                {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty())
            {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else
            {
                std::cout << ">> No ingredients added. Canceling Recipe creation." << std::endl;
            }

        }
        else if (choice == 2)
        {
            myWorkshop.displayAllRecipes();
        }
        else if (choice == 3)
        {
            myWorkshop.displayAllStocks();
        }
        else if (choice == 4)
        {
            std::string name;
            std::cout << "Search for potion name: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            PotionRecipe foundPotion = myWorkshop.searchRecipeByName(name);
            if (foundPotion.potionName != "")
            {
                std::cout << "Found the Potion!" << std::endl;
                foundPotion.displayPotionInfo();
                while (true)
                {
                    std::cout << "Choose What you wish to do with the Potion: " << std::endl;
                    std::cout << "1. Dispense Potion" << std::endl;
                    std::cout << "2. Retrieve Bottle" << std::endl;
                    std::cout << "3. Return to Main Menu" << std::endl;
                    int choiceSearch;
                    std::cin >>choiceSearch;
                    if (std::cin.fail())
                    {
                        std::cout << "Invalid input. Put in a number." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    if (choiceSearch == 1)
                    {
                        bool success = myWorkshop.dispensePotion(foundPotion.potionName);
                        if (success)
                        {
                            std::cout << "Potion " << foundPotion.potionName << " dispensed! Stock: " << myWorkshop.getStock(foundPotion.potionName) << std::endl;
                        }
                        else
                        {
                            std::cout << "Dispense failed. No stock left." << std::endl;
                        }
                        break;
                    }
                    if (choiceSearch == 2)
                    {
                        bool success = myWorkshop.retrievePotion(foundPotion.potionName);
                        if (success)
                        {
                            std::cout << "Potion " << foundPotion.potionName << " Retrieved! Stock: " << myWorkshop.getStock(foundPotion.potionName) << std::endl;
                        }
                        else
                        {
                            std::cout << "Retrieval failed. Full Stock." << std::endl;
                        }
                        break;
                    }
                    if (choiceSearch == 3)
                    {
                        break;
                    }
                }
            }
            else
            {
                std::cout << "Could not find a potion matching the name." << std::endl;
            }
            std::cout << "---------------------------\n";
        }
        else if (choice == 5)
        {
            std::string name;
            std::cout << "Search for ingredient name: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            std::vector <PotionRecipe> foundPotions = myWorkshop.searchRecipeByIngredient(name);
            if (foundPotions.size() != 0)
            {
                std::cout << "Found the Potion!" << std::endl;
                for (const PotionRecipe& i : foundPotions)
                {
                    i.displayPotionInfo();
                }
                while (true)
                {
                    std::cout << "Choose What you wish to do with the Potions: " << std::endl;
                    std::cout << "1. Dispense All Potions" << std::endl;
                    std::cout << "2. Retrieve All Bottles" << std::endl;
                    std::cout << "3. Return to Main Menu" << std::endl;
                    int choiceSearch;
                    std::cin >> choiceSearch;
                    if (std::cin.fail())
                    {
                        std::cout << "Invalid input. Put in a number." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    if (choiceSearch == 1)
                    {
                        for (const PotionRecipe& recipe : foundPotions)
                        {
                            bool success = myWorkshop.dispensePotion(recipe.potionName);
                            if (success)
                            {
                                std::cout << "Potion " << recipe.potionName << " dispensed! Stock: " << myWorkshop.getStock(recipe.potionName) << std::endl;
                            }
                            else
                            {
                                std::cout << "Dispense failed for " << recipe.potionName << " .No stock left." << std::endl;
                            }
                        }
                        break;
                    }
                    if (choiceSearch == 2)
                    {
                        for (const PotionRecipe& recipe : foundPotions)
                        {
                            bool success = myWorkshop.retrievePotion(recipe.potionName);
                            if (success)
                            {
                                std::cout << "Potion " << recipe.potionName << " retrieved! Stock: " << myWorkshop.getStock(recipe.potionName) << std::endl;
                            }
                            else
                            {
                                std::cout << "Retrieval failed for " << recipe.potionName << " . Full Stock." << std::endl;
                            }
                        }
                        break;
                    }
                    if (choiceSearch == 3)
                    {
                        break;
                    }
                }
            }
            else
            {
                std::cout << "Could not find a potion with that ingredient." << std::endl;
            }
            std::cout << "---------------------------\n";
        }
        else if (choice == 6)
        {
            std::string name;
            std::cout << "Search for either name or ingredient: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            std::vector <PotionRecipe> foundPotions = myWorkshop.searchRecipeUniversal(name);
            if (foundPotions.size() != 0)
            {
                for (const PotionRecipe& i : foundPotions)
                {
                    i.displayPotionInfo();
                }
                while (true)
                {
                    std::cout << "Choose What you wish to do with the Potions: " << std::endl;
                    std::cout << "1. Dispense All Potions" << std::endl;
                    std::cout << "2. Retrieve All Bottles" << std::endl;
                    std::cout << "3. Return to Main Menu" << std::endl;
                    int choiceSearch;
                    //std::cin.ignore(10000, '\n');
                    std::cin >> choiceSearch;
                    if (std::cin.fail())
                    {
                        std::cout << "Invalid input. Put in a number." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    if (choiceSearch == 1)
                    {
                        for (const PotionRecipe& recipe : foundPotions)
                        {
                            bool success = myWorkshop.dispensePotion(recipe.potionName);
                            if (success)
                            {
                                std::cout << "Potion " << recipe.potionName << " dispensed! Stock: " << myWorkshop.getStock(recipe.potionName) << std::endl;
                            }
                            else
                            {
                                std::cout << "Dispense failed for " << recipe.potionName << " .No stock left." << std::endl;
                            }
                        }
                        break;
                    }
                    if (choiceSearch == 2)
                    {
                        for (const PotionRecipe& recipe : foundPotions)
                        {
                            bool success = myWorkshop.retrievePotion(recipe.potionName);
                            if (success)
                            {
                                std::cout << "Potion " << recipe.potionName << " retrieved! Stock: " << myWorkshop.getStock(recipe.potionName) << std::endl;
                            }
                            else
                            {
                                std::cout << "Retrieval failed for " << recipe.potionName << " . Full Stock." << std::endl;
                            }
                        }
                        break;
                    }
                    if (choiceSearch == 3)
                    {
                        break;
                    }
                }
            }
            else
            {
                std::cout << "Could not find a potion with that keyword." << std::endl;
            }
            std::cout << "---------------------------\n";
        }
        else if (choice == 7)
        {
            std::string name;
            std::cout << "Name the potion you wish to dispense." << std::endl;
            std::cout << "Potion Name: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            if (myWorkshop.dispensePotion(name))
            {
                std::cout << "Potion " << name << " dispensed! Remaining Stock: " << myWorkshop.getStock(name) << std::endl;
            }
            else
            {
                std::cout << "Dispensing Failed. " << std::endl;
            }
        }
        else if (choice == 8)
        {
            std::string name;
            std::cout << "Name the potion you wish to retrieve." << std::endl;
            std::cout << "Potion Name: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            if (myWorkshop.retrievePotion(name))
            {
                std::cout << "Potion " << name << " retrieved! Remaining Stock: " << myWorkshop.getStock(name) << std::endl;
            }
            else
            {
                std::cout << "Retrieval Failed. " << std::endl;
            }
        }
        else if (choice == 9)
        {
            std::cout << "Closing the lab door..." << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}