#ifndef ADDCOMM_H
#define ADDCOMM_H

#include <QDialog>

namespace Ui {
class addComm;
}

class addComm : public QDialog
{
    Q_OBJECT

public:
    std::string comboBox;
    std::string lineEdit;
    std::string comment;
    int addCommentFlag = 0;
    explicit addComm(QWidget *parent = nullptr);
    ~addComm();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::addComm *ui;
};

#endif // ADDCOMM_H
