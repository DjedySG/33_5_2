#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <exception>

extern std::vector <std::string> pole = { "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" };

class CatchBootException : public std::exception
{
    const char* what() const noexcept override
    {
        return "You catch a boot";
    }
};

class CatchFishException : public std::exception
{
    const char* what() const noexcept override
    {
        return "You catch a fish";
    }
};

void placeFish(std::vector <std::string>& pole)
{
    pole[std::rand() % 9] = "fish";
}

void placeBoot(std::vector <std::string>& pole)
{
    int count = 0;
    int place = 0;
    while (count < 3)
    {
        place = std::rand() % 9;
        if (pole[place] == "empty")
        {
            count++;
            pole[place] = "Boot";
        }
    }
}

void game(const std::vector <std::string>& pole, int& count, bool& check)
{
    std::cout << "Where will we fish? " << std::endl;
    int place = -1;
    while (place < 0 || place > 8)
    {
        std::cin >> place;
        if (place < 0 || place > 8)
            throw std::invalid_argument("incorrect place for fishing");
    }
    if (pole[place] == "fish")
    {
        ++count;
        throw CatchFishException();
    }
    if (pole[place] == "Boot")
    {
        ++count;
        throw CatchBootException();
    }
    count++;
}

int main()
{
    std::srand(std::time(nullptr));
    placeFish(pole);
    placeBoot(pole);
    for (int i = 0; i < pole.size(); i++)
    {
        std::cout << pole[i] << std::endl;
    }
    int count = 0;
    std::cout << "Welcome to the Fish game!" << std::endl;
    bool check = true;
    while (check)
    {
        try
        {
            game(pole, count, check);
        }
        catch (std::exception& y)
        {
            std::cerr << y.what() << std::endl;
            check = false;
            std::cout << "Game end" << std::endl;
            std::cout << "There were " << count << " steps" << std::endl;
        }
    }


}
