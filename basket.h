#ifndef BASKET_H
#define BASKET_H
#include "helpers.h"

class Basket
{
public:
    Basket(int red = 0, int blue = 0);

    int getRedBallsCount() const;
    int getBlueBallsCount() const;
    int getTotalBallsCount() const;

    void addRed();
    void addBlue();
    bool removeRed();
    bool removeBlue();
    void setAction(ActionEnum action);

    BasketData getData();

private:
    int redBalls;
    int blueBalls;
    ActionEnum lastAction;
};

#endif // BASKET_H
