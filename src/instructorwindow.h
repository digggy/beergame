#ifndef INSTRUCTORWINDOW_H
#define INSTRUCTORWINDOW_H

#include <QDialog>

#include "instructor.h"
#include "./server/beergameserver.h"

class Instructor;
class BeerGameServer;

namespace Ui {
class InstructorWindow;
}

/**
 * @brief This is the class for Instructor Window
*/

class InstructorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InstructorWindow(QWidget *parent = nullptr);
    ~InstructorWindow();
    QWidget *parent;

private slots:
    void on_startBtn_clicked();
    void on_go_online_clicked();
    void on_home_screen_clicked();
    void on_start_server_btn_clicked();
    void on_stop_server_btn_clicked();

private:
    Instructor* instructor;
    Ui::InstructorWindow *ui;
    BeerGameServer* beerGameServer;
};

#endif // INSTRUCTORWINDOW_H
