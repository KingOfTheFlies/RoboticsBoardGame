#pragma once


class Dice {
public:
    int ThrowDice();
    int GetLastDiceVal();

protected:
    int dice_value;
};

