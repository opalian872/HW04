#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
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

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop 
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
};

int main() 
{
    AlchemyWorkshop myWorkshop;

    while (true) 
    {
        std::cout << "⚗️ Alchemy Lab Management System" << std::endl;
        std::cout << "1. Add Recipe" << std::endl;
        std::cout << "2. Print All Recipes" << std::endl;
        std::cout << "3. Search Recipes by Name" << std::endl;
        std::cout << "4. Search Recipes by Ingredient" << std::endl;
        std::cout << "5. End" << std::endl;
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
            std::string name;
            std::cout << "Search for potion name: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            PotionRecipe foundPotion = myWorkshop.searchRecipeByName(name);
            if (foundPotion.potionName != "")
            {
                std::cout << "Found the Potion!" << std::endl;
                foundPotion.displayPotionInfo();
            }
            else
            {
                std::cout << "Could not find a potion matching the name." << std::endl;
            }
        }
        else if (choice == 4)
        {
            std::string name;
            std::cout << "Search for ingredient name: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            std::vector <PotionRecipe> foundPotions = myWorkshop.searchRecipeByIngredient(name);
            if (foundPotions.size() != 0)
            {
                for (const PotionRecipe& i : foundPotions)
                {
                    i.displayPotionInfo();
                }
            }
            else
            {
                std::cout << "Could not find a potion with that ingredient." << std::endl;
            }
        }
        else if (choice == 5)
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