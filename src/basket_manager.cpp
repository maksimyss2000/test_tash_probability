#include "basket_manager.h"

BasketManager::BasketManager(Basket &b1, Basket &b2)
    : basket1(b1), basket2(b2) {}

void BasketManager::moveBall(Basket &from, Basket &to)
{
    int blueCount = from.getBlueBallsCount();
    int redCount = from.getRedBallsCount();
    int flag = weightedRandomChoice(blueCount, redCount);

    if(flag == 0) {
        if (from.removeRed()) {
            to.addRed();
        }
        else if(from.removeBlue()){
            to.addBlue();
        }
    } else {
        if (from.removeBlue()) {
            to.addBlue();
        }
        else if(from.removeRed()){
            to.addRed();
        }

    }
}

void BasketManager::moveBallFromFirstToSecond() {
    moveBall(basket1, basket2);
}
void BasketManager::moveBallFromSecondToFirst() {
    moveBall(basket2, basket1);
}

void BasketManager::extractTwoBalls()
{
    if (weightedRandomChoice(0, 1) == 0) {
        Basket *selectedBasket = weightedRandomChoice(0, 1) == 0 ? &basket1 : &basket2;
        removeRandomBall(*selectedBasket);
        removeRandomBall(*selectedBasket);
    } else {
        removeRandomBall(basket1);
        removeRandomBall(basket2);
    }
}

bool BasketManager::removeRandomBall(Basket &basket)
{
    int total = basket.getTotalBallsCount();
    if (total == 0)
        return false;

    int redBallsCount = basket.getRedBallsCount();
    int blueBallsCount = basket.getBlueBallsCount();

    int flag = weightedRandomChoice(redBallsCount, blueBallsCount);

    if (flag == 0) {
        return basket.removeRed();
    } else {
        return basket.removeBlue();
    }
}


int BasketManager::weightedRandomChoice(int a_count, int b_count) const {
    std::vector<int> weights = {a_count, b_count};
    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    return dist(gen);
}

Stats BasketManager::getStates() {
    auto firstBasketData = basket1.getData();
    auto secondBasketData = basket2.getData();

    double firstBasketRedBallProbability  = firstBasketData.redBallsCount / static_cast<double>(firstBasketData.totalCount) * 100;
    double firstBasketBlueBallProbability = firstBasketData.blueBallsCount / static_cast<double>(firstBasketData.totalCount) * 100;
    double secondBasketRedBallProbability  = secondBasketData.redBallsCount / static_cast<double>(secondBasketData.totalCount) * 100;
    double secondBasketBlueBallProbability = secondBasketData.blueBallsCount / static_cast<double>(secondBasketData.totalCount) * 100;

    Stats stats = Stats{
        .firstBasket = BasketStats{
            firstBasketData,
            firstBasketRedBallProbability,
            firstBasketBlueBallProbability
        },
        .secondBasket = BasketStats{
            secondBasketData,
            secondBasketRedBallProbability,
            secondBasketBlueBallProbability
        },
        .common = CommonStats{
            .twoRedBallsProbability = firstBasketRedBallProbability * secondBasketRedBallProbability / 100.0,
            .twoBlueBallsProbability = firstBasketBlueBallProbability * secondBasketBlueBallProbability / 100.0,
            .twoDifferentBallsProbability = (firstBasketRedBallProbability * secondBasketBlueBallProbability + firstBasketBlueBallProbability * secondBasketRedBallProbability) / 100.0
        }
    };

    return stats;
}
