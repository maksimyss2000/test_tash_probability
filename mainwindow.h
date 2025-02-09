#include <QMainWindow>
#include <QListWidget>
#include "helpers.h"
#include "basket_manager.h" // Include your BasketManager class

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string ActionEnumToString(ActionEnum action);
private:
    Ui::MainWindow *ui;
    BasketManager *basketManager;  // Assuming BasketManager is initialized
    void updateData();

private slots:
    void onClickMoveToSecond();
    void onClickMoveToFirst();
    void onClickTakeTwo();

};
