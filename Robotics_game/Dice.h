#pragma once

enum {DICE_VAL_MAX = 9};

class Dice {
public:
    int ThrowDice();
    int GetLastDiceVal();

protected:
    int dice_value;
};

