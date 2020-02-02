#ifndef ADDSONGWINDOW_H
#define ADDSONGWINDOW_H

#include <QDialog>

namespace Ui {
class addSongWIndow;
}

class addSongWIndow : public QDialog
{
    Q_OBJECT

public:
    std::string addSongName;
    std::string addUrl;
    std::string addGen;
    std::string addDesc;
    explicit addSongWIndow(QWidget *parent = nullptr);
    ~addSongWIndow();

private slots:
    void on_pushButton_addSong_clicked();

private:
    Ui::addSongWIndow *ui;
};

#endif // ADDSONGWINDOW_H
