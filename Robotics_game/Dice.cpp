#include "Dice.h"

#include <cstdlib>
#include <random>
#include <ctime>

int Dice::ThrowDice() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, DICE_VAL_MAX);
    //dice_value = rand() % DICE_VAL_MAX + 1;
    //dice_value = 1;
    dice_value = dist(rng);
    return dice_value;
}

int Dice::GetLastDiceVal() {
    return dice_value;
}