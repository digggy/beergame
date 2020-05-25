#include "beergamewindow.h"
#include "ui_beergamewindow.h"

#include  "instructorwindow.h"
#include  "./client/clientinterface.h"
#include "game.h"
#include "player.h"

#include <iostream>

BeerGameWindow::BeerGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BeerGameWindow),
      m_view(new QWebEngineView(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":images/background.jpg"));

    QMovie *gif = new QMovie(":images/beer-game.gif");
    ui->stackedWidget->setCurrentIndex(0);
    // For the demo video
    QGridLayout *gridLayout = new QGridLayout;
    ui->video->setLayout(gridLayout);
    m_view->show();
    ui->video->layout()->addWidget(m_view);

    QPixmap pix(":images/beergame.png");
    QPixmap cover(":images/cover.png");
    QPixmap youtube(":images/youtube.png");
    ui->label_logo->setPixmap(pix.scaled(200,180, Qt::KeepAspectRatio));
    ui->label_cover->setPixmap(cover.scaled(820,820, Qt::KeepAspectRatio));
    ui->youtube_logo->setPixmap(youtube.scaled(36,36, Qt::KeepAspectRatio));
    // The gif cover
    ui->label_cover->setMovie(gif);
    gif->start();
    ui->checkBox_isInstructor->setCheckState(Qt::Checked);
}

BeerGameWindow::~BeerGameWindow()
{
    delete ui;
}

void BeerGameWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_useremail->text();
    QString password = ui->lineEdit_password->text();
    bool isInstructor = ui->checkBox_isInstructor->checkState();
    if(username == "instructor" && password =="123" && isInstructor){
        QMessageBox::information(this,"Instructor Login", "Username and Password is correct");
        hide();
        ui->pushButton_Login->setText("You clicked");
        InstructorWindow* instructorW = new InstructorWindow(this);
        instructorW->show();
        this->hide();
    }else if (username == "player" && password =="123" && !isInstructor){
        QMessageBox::information(this,"Player Login", "Username and Password is correct");
         ClientInterface* client = new ClientInterface;
         client->show();
         this->hide();
    }else
    {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }
}

void BeerGameWindow::on_youtube_btn_clicked()
{
    // For the youtube Video
    m_view->load(QUrl(QStringLiteral("qrc:images/html/index.html")));
    ui->stackedWidget->setCurrentIndex(1);
}

void BeerGameWindow::on_go_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    m_view->reload();
}
