#ifndef SHOWCOMM_H
#define SHOWCOMM_H

#include <QDialog>

namespace Ui {
class showcomm;
}

class showcomm : public QDialog
{
    Q_OBJECT

public:
    std::string comboBox;
    std::string comment;
    int showCommentFlag = 0;
    explicit showcomm(QWidget *parent = nullptr);
    ~showcomm();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::showcomm *ui;
};

#endif // SHOWCOMM_H
