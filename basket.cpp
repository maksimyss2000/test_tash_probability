#include "basket.h"

Basket::Basket(int red, int blue)
    : redBalls(red), blueBalls(blue), lastAction(ActionEnum::NO_ACTION)
{
}

BasketData Basket::getData() {
    return BasketData{redBalls + blueBalls, redBalls, blueBalls, lastAction};
}

int Basket::getRedBallsCount() const {
    return redBalls;
}

int Basket::getBlueBallsCount() const {
    return blueBalls;
}

int Basket::getTotalBallsCount() const {
    return blueBalls + redBalls;
}

bool Basket::removeRed()  {
    if(redBalls > 0) {
        redBalls = redBalls - 1;

        setAction(ActionEnum::TAKE_RED);
        return true;
    }

    redBalls = 0;
    return false;
}

bool Basket::removeBlue() {
    if(blueBalls > 0) {
        blueBalls = blueBalls - 1;
        setAction(ActionEnum::TAKE_BLUE);
        return true;
    }

    blueBalls = 0;
    return false;
}

void Basket::setAction(ActionEnum action) {
    lastAction = action;
}

void Basket::addRed() {
    redBalls += 1;
    setAction(ActionEnum::SET_RED);
}

void Basket::addBlue() {
    blueBalls += 1;
    setAction(ActionEnum::SET_BLUE);
}

