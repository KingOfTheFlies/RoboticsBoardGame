#include "Dice.h"

#include <cstdlib>
#include <ctime>

int Dice::ThrowDice() {
    std::srand(std::time(nullptr)); 
    int random_variable = std::rand();
    int temp = 7;
    while (temp > 6) {
        temp = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
    }
    dice_value = temp;
    return dice_value;
}

int Dice::GetLastDiceVal() {
    return dice_value;
}