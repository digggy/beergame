#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QTcpSocket>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

#include "game.h"
#include "player.h"

class Game;
class Player;

namespace Ui {
class PlayerInterface;
}

/**
 * @brief This is the class for PlayerInterface
*/

class PlayerInterface : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerInterface(QWidget *parent = nullptr);

    /// @brief Construct a player dialog
    /// @param parent  The parent ui for the class
    /// @param game  The game pointer of the player's game
    /// @param allPlayers  The vector of pointers of the players linked with the player dialog
    explicit PlayerInterface(QWidget *parent, Game *game, std::vector<Player *> allPlayers);

    ~PlayerInterface();

    virtual void receiveOrder(int);
    virtual void receiveShipment(int);
    virtual void placeOrder(int);
    virtual void placeShipment(int);
    virtual void updateUi();

    void sendOrderToPlayer(int);

    virtual void setPlayer(Player* player);
    virtual void setGame(Game* game);
    virtual int getRole();
    Game* getGame() {return game;};

    // Helper functions
    void setStackWidgetUI();
    void startGame();
    void linkInterfaceAndGame(int player_number);


protected:
    Ui::PlayerInterface *ui;
    Game* game = nullptr;
    Player* player = nullptr;
    std::vector<Player *> allPlayers;

    QtCharts::QLineSeries *series;
    QtCharts::QStackedBarSeries *bseries;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;

private slots:
    void on_orderBtn_clicked();
    void on_retailer_btn_clicked();
    void on_wholesaler_btn_clicked();
    void on_distributor_btn_clicked();
    void on_factory_btn_clicked();
    void on_stat_btn_clicked();
    void on_current_game_clicked();
    void on_linegraph_check_stateChanged(int arg1);
    /// @brief Method for player to exit the game
    void on_exit_game_clicked();

    void on_show_incoming_stateChanged(int arg1);
    void on_show_outgoing_stateChanged(int arg1);
};


#endif // PLAYERINTERFACE_
