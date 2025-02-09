#ifndef BASKET_MANAGER_H
#define BASKET_MANAGER_H
#include "helpers.h"
#include "basket.h"
#include <random>

class BasketManager
{
public:
    BasketManager(
          Basket& basket1,
          Basket& basket2
    );

    void extractTwoBalls();
    void moveBallFromFirstToSecond();
    void moveBallFromSecondToFirst();
    Stats getStates();

private:
    Basket& basket1;
    Basket& basket2;

    int weightedRandomChoice(int redCount, int blueCount) const;
    bool removeRandomBall(Basket &basket);
    void moveBall(Basket& from, Basket& to);

    mutable std::mt19937 gen;
    mutable std::random_device rd;
};

#endif // BASKET_MANAGER_H
