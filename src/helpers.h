#ifndef HELPERS_H
#define HELPERS_H

enum ActionEnum {
    NO_ACTION,
    TAKE_RED,
    TAKE_BLUE,
    SET_RED,
    SET_BLUE
};

struct BasketData {
    int totalCount;
    int redBallsCount;
    int blueBallsCount;
    ActionEnum lastAction;
};

struct BasketStats: public BasketData {
    double redBallProbability;
    double blueBallProbability;
};

struct CommonStats {
    double twoRedBallsProbability;
    double twoBlueBallsProbability;
    double twoDifferentBallsProbability;
};

struct Stats {
    BasketStats firstBasket;
    BasketStats secondBasket;
    CommonStats common;
};


#endif // HELPERS_H
