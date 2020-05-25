#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <string>
#include <vector>

#include "game.h"
#include "instructorwindow.h"
#include "ui_instructorwindow.h"

/**
 * @brief This is the class for Instructor
*/

class Instructor
{
private:
    int instrId;
    std::string instrEmail;
    std::string instrPassword;

    std::vector<Game> games;
    Ui::InstructorWindow *ui;
    QWidget* uiParent;

public: // every function here has been made void just for making template, change it accordingly

    /// @brief show game status
    void showGameStatus();

    /// @brief create game and apply all the game setting that were given in the instructor dialog
    int createGame();
    
    /// @brief create a certain amount of games
    /// @param numberOfGames number of games
    /// @returns vector of games
    std::vector<Game> createGames(int numberOfGames);

    void setUi(Ui::InstructorWindow* ui);

    void setWindowParent(QWidget* parent);

    //// 
    // TEST
    ////

    /// @brief Setter Method for Instructor's Email
    /// @param instrEmail Instructor Email
    void setInstrEmail(std::string instrEmail);

    /// @brief Setter Method for Instructor's Email
    /// @param instrPassword Instructor's Password
    void setInstrPassword(std::string instrPassword);

    /// @brief Setter Method for Instructor's Email
    /// @param instrID Instructor's Id
    void setInstrId(int instrID);

    /// @brief Getter Method for Instructor's Email
    /// @return string Instructor Email
    std::string getInstrEmail();

    /// @brief Getter Method for Instructor's Password
    /// @return string Instructor Password
    std::string getInstrPassword();

    /// @brief Getter Method for Instructor's Id
    /// @return int Instructor's Id
    int getInstrId();
};

#endif //INSTRUCTOR_H
