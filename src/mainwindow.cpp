#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Basket *basket1 = new Basket(10, 20);
    Basket *basket2 = new Basket(5, 15);
    basketManager = new BasketManager(*basket1, *basket2);

    updateData();

    ui->moveToFirstBtn->setCursor(Qt::PointingHandCursor);
    ui->moveToSecondBtn->setCursor(Qt::PointingHandCursor);
    ui->takeTwoBtn->setCursor(Qt::PointingHandCursor);

    connect(ui->moveToFirstBtn, &QPushButton::clicked, this, &MainWindow::onClickMoveToFirst);
    connect(ui->moveToSecondBtn, &QPushButton::clicked, this, &MainWindow::onClickMoveToSecond);
    connect(ui->takeTwoBtn, &QPushButton::clicked, this, &MainWindow::onClickTakeTwo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickMoveToSecond() {
    basketManager->moveBallFromFirstToSecond();
    updateData();
}

void MainWindow::onClickMoveToFirst() {
    basketManager->moveBallFromSecondToFirst();
    updateData();
}

void MainWindow::onClickTakeTwo() {
    basketManager->extractTwoBalls();
    updateData();
}

void MainWindow::updateData()
{
    auto data = basketManager->getStates();
    ui->Basket1->clear();
    ui->Basket1->addItem(QString("Шаров в корзине: %1").arg(data.firstBasket.totalCount));
    ui->Basket1->addItem(QString("Синих шаров в корзине: %1").arg(data.firstBasket.blueBallsCount));
    ui->Basket1->addItem(QString("Красных шаров в корзине: %1").arg(data.firstBasket.redBallsCount));
    ui->Basket1->addItem(QString("Вероятность достать синий шар: %1%").arg(QString::number(data.firstBasket.blueBallProbability, 'f', 2)));
    ui->Basket1->addItem(QString("Вероятность достать красный шар: %1%").arg(QString::number(data.firstBasket.redBallProbability, 'f', 2)));
    ui->Basket1->addItem(QString("Последнее действие: %1").arg(QString::fromStdString(ActionEnumToString(data.firstBasket.lastAction))));

    ui->Basket2->clear();
    ui->Basket2->addItem(QString("Шаров в корзине: %1").arg(data.secondBasket.totalCount));
    ui->Basket2->addItem(QString("Синих шаров в корзине: %1").arg(data.secondBasket.blueBallsCount));
    ui->Basket2->addItem(QString("Красных шаров в корзине: %1").arg(data.secondBasket.redBallsCount));
    ui->Basket2->addItem(QString("Вероятность достать синий шар: %1%").arg(QString::number(data.secondBasket.blueBallProbability, 'f', 2)));
    ui->Basket2->addItem(QString("Вероятность достать красный шар: %1%").arg(QString::number(data.secondBasket.redBallProbability, 'f', 2)));
    ui->Basket2->addItem(QString("Последнее действие: %1").arg(QString::fromStdString(ActionEnumToString(data.secondBasket.lastAction))));

    ui->Common->clear();
    ui->Common->addItem(QString("Вероятность достать 2 синих шара: %1%").arg(QString::number(data.common.twoBlueBallsProbability, 'f', 2)));
    ui->Common->addItem(QString("Вероятность достать 2 красных шара: %1%").arg(QString::number(data.common.twoRedBallsProbability, 'f', 2)));
    ui->Common->addItem(QString("Вероятность достать 1 красный и 1 синий шары: %1%").arg(QString::number(data.common.twoDifferentBallsProbability, 'f', 2)));
}

std::string MainWindow::ActionEnumToString(ActionEnum action) {
    switch(action) {
        case ActionEnum::TAKE_RED: return "извлекли красный шар";
        case ActionEnum::TAKE_BLUE: return "извлекли синий шар";
        case ActionEnum::SET_RED: return "добавили красный шар";
        case ActionEnum::SET_BLUE: return "добавили синий шар";
        default: return "бездействие";
    }
}
