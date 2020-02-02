#ifndef USERMENU_H
#define USERMENU_H

#include <QDialog>

namespace Ui {
class userMenu;
}

class userMenu : public QDialog
{
    Q_OBJECT

public:

    int showFLAG = 0;
    int menuCloseFlag = 0;
    int showGeneralTopFlag = 0,showGeneralTopPop = 0,showGeneralTopRock = 0,
            showGeneralTopChill = 0,showGeneralTopIndie = 0,showGeneralTopLatino = 0,
            showGeneralTopManele = 0,showGeneralTopHipHop = 0,showGeneralTopElectro = 0,
               showGeneralTopPopulara = 0, showGeneralTopMY = 0;

    std::string addSong;
    std::string voteSong;
    std::string addComms;
    std::string showComms;
    std::string banCommand;
    std::string removeaSong;
    std::string setAcces;
    explicit userMenu(QWidget *parent = nullptr);
    explicit userMenu(std::string username, std::string answerLogIN, QWidget *parent = nullptr );
    ~userMenu();

private slots:
    void on_pushButton_addSong_clicked();

    void on_pushButton_exitMenu_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_ban_clicked();

    void on_pushButton_removeSong_clicked();

    void on_pushButton_setAcces_clicked();

private:
    Ui::userMenu *ui;
};

#endif // USERMENU_H
