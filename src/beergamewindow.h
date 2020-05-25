#ifndef BEERGAMEWINDOW_H
#define BEERGAMEWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QMovie>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class BeerGameWindow; }
QT_END_NAMESPACE

/**
 * \brief Game login screen for player and instructor  
 */

class BeerGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    BeerGameWindow(QWidget *parent = nullptr);
    ~BeerGameWindow();

private slots:
    void on_pushButton_Login_clicked();

    void on_youtube_btn_clicked();

    void on_go_back_clicked();

private:
    Ui::BeerGameWindow *ui;
    QWebEngineView *m_view;
};
#endif // BEERGAMEWINDOW_H
