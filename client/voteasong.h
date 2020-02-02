#ifndef VOTEASONG_H
#define VOTEASONG_H

#include <QDialog>

namespace Ui {
class voteasong;
}

class voteasong : public QDialog
{
    Q_OBJECT

public:
    std::string comboBox;
    std::string lineEdit;
    int votesongflag = 0;
    explicit voteasong(QWidget *parent = nullptr);
    ~voteasong();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::voteasong *ui;
};

#endif // VOTEASONG_H
