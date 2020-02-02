#include "usermenu.h"
#include "ui_usermenu.h"
#include "addsongwindow.h"
#include "usermenu.h"
#include "adminpanel.h"
#include "voteasong.h"
#include "addcomm.h"
#include "showcomm.h"
#include "banwindow.h"
#include "removesong.h"
#include "adminpanel.h"

userMenu::userMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userMenu)
{
    ui->setupUi(this);
}

userMenu::userMenu(std::string username, std::string answerLogIN,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userMenu)
{
    ui->setupUi(this);
    if(answerLogIN == "user"){
        ui->pushButton_setAcces->setHidden(true);
        ui->pushButton_removeSong->setHidden(true);
        ui->pushButton_ban->setHidden(true);
    }
    showFLAG = 0;
    ui->label_2->setText("[" + QString(answerLogIN.data()) + "] Connected as: " + QString(username.data()));

}

userMenu::~userMenu()
{
    delete ui;
}

void userMenu::on_pushButton_addSong_clicked()
{
    addSongWIndow addSongWindow;
    addSongWindow.setModal(true);
    addSongWindow.exec();
    addSong = "addSong#^" + addSongWindow.addSongName + "#^" + addSongWindow.addUrl + "#^" + addSongWindow.addGen + "#^" + addSongWindow.addDesc;
    if(addSong == "addSong#^#^#^#^")
        addSong = "";
    else {
        this->close();
    }
}

void userMenu::on_pushButton_exitMenu_clicked()
{
    menuCloseFlag = 1;
    this->close();
}

void userMenu::on_pushButton_2_clicked()
{
    showFLAG = 1;
    showGeneralTopFlag = 1;
    this->close();
}

void userMenu::on_pushButton_5_clicked()
{
    showFLAG = 1;
    showGeneralTopPop = 1;
    this->close();
}

void userMenu::on_pushButton_6_clicked()
{
    showFLAG = 1;
    showGeneralTopRock = 1;
    this->close();
}

void userMenu::on_pushButton_7_clicked()
{
    showFLAG = 1;
    showGeneralTopChill = 1;
    this->close();
}

void userMenu::on_pushButton_8_clicked()
{
    showFLAG = 1;
    showGeneralTopIndie = 1;
    this->close();
}

void userMenu::on_pushButton_9_clicked()
{
    showFLAG = 1;
    showGeneralTopLatino = 1;
    this->close();
}

void userMenu::on_pushButton_10_clicked()
{
    showFLAG = 1;
    showGeneralTopManele = 1;
    this->close();
}

void userMenu::on_pushButton_11_clicked()
{
    showFLAG = 1;
    showGeneralTopHipHop = 1;
    this->close();
}

void userMenu::on_pushButton_12_clicked()
{
    showFLAG = 1;
    showGeneralTopElectro = 1;
    this->close();
}

void userMenu::on_pushButton_13_clicked()
{
    showFLAG = 1;
    showGeneralTopPopulara = 1;
    this->close();
}

void userMenu::on_pushButton_clicked()
{
    showFLAG = 1;
    showGeneralTopMY = 1;
    this->close();
}

void userMenu::on_pushButton_3_clicked()
{
    voteasong voteasong;
    voteasong.setModal(true);
    voteasong.exec();
    if(voteasong.votesongflag == 1)
        voteSong = "voteSongByLink#^" + voteasong.lineEdit;
    else if(voteasong.votesongflag == 2)
        voteSong = "voteSongByName#^" + voteasong.lineEdit;
    if(voteasong.votesongflag == 3)
        voteSong = "rmVoteSongByLink#^" + voteasong.lineEdit;
    else if(voteasong.votesongflag == 4)
        voteSong = "rmVoteSongByName#^" + voteasong.lineEdit;

    if(voteSong == "voteSongByLink#^" || voteSong == "voteSongByName#^" || voteSong == "rmVoteSongByLink#^" || voteSong == "rmVoteSongByName#^")
        voteSong = "";
    else {
        this->close();
    }

}

void userMenu::on_pushButton_15_clicked()
{
    addComm addComm;
    addComm.setModal(true);
    addComm.exec();
    if(addComm.addCommentFlag == 1)
        addComms = "addCommByLink#^" + addComm.lineEdit + "#^" + addComm.comment;
    else if (addComm.addCommentFlag == 2)
        addComms = "addCommByName#^" + addComm.lineEdit + "#^" + addComm.comment;

    if(addComms == "addCommByName#^" || addComms == "addCommByLink#^")
        addComms = "";
    else {
        this->close();
    }
}

void userMenu::on_pushButton_4_clicked()
{
    showcomm showComm;
    showComm.setModal(true);
    showComm.exec();
    if(showComm.showCommentFlag == 1)
        showComms = "showCommByLink#^" + showComm.comment;
    else if (showComm.showCommentFlag == 2)
        showComms = "showCommByName#^" + showComm.comment;

    if(showComms == "showCommByName#^" || showComms == "showCommByLink#^")
        showComms = "";
    else {
        this->close();
    }
}

void userMenu::on_pushButton_ban_clicked()
{
    banWindow banWindow;
    banWindow.setModal(true);
    banWindow.exec();
    if(banWindow.banFlag == 1)
        banCommand = "ban#^" + banWindow.username;
    else if (banWindow.banFlag == 2)
        banCommand = "unban#^" + banWindow.username;

    if(banCommand == "ban#^" || banCommand == "unban#^")
        banCommand = "";
    else {
        this->close();
    }
}

void userMenu::on_pushButton_removeSong_clicked()
{
    removesong removeSongWindow;
    removeSongWindow.setModal(true);
    removeSongWindow.exec();
    if(removeSongWindow.removeFlag == 1)
    removeaSong = "removeSongByName#^" + removeSongWindow.song ;
    else
        removeaSong = "removeSongByLink#^" + removeSongWindow.song ;

    if(removeaSong == "removeSongByName#^" || removeaSong == "removeSongByLink#^")
        removeaSong = "";
    else {
        this->close();
    }
}

void userMenu::on_pushButton_setAcces_clicked()
{
    adminPanel adminPanel;
    adminPanel.setModal(true);
    adminPanel.exec();
    setAcces = "setAcces#^" + adminPanel.user + "#^" + adminPanel.levelAcces + "#^" + adminPanel.voteAcces;
    if(setAcces == "setAcces#^#^#^")
        setAcces = "";
    else {
        this->close();
    }
}
