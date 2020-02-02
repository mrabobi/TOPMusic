#ifndef SHOWTOPGENERAL_H
#define SHOWTOPGENERAL_H

#include <QDialog>

namespace Ui {
class showTopGeneral;
}

class showTopGeneral : public QDialog
{
    Q_OBJECT

public:
    explicit showTopGeneral(QWidget *parent = nullptr);
    explicit showTopGeneral(std::string songs, QWidget *parent = nullptr);
    ~showTopGeneral();

private slots:
    void on_pushButton_clicked();

private:
    Ui::showTopGeneral *ui;
};

#endif // SHOWTOPGENERAL_H
