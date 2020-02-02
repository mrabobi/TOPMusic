#ifndef SHOWCOMMWINDOW_H
#define SHOWCOMMWINDOW_H

#include <QDialog>

namespace Ui {
class showcommwindow;
}

class showcommwindow : public QDialog
{
    Q_OBJECT

public:
    explicit showcommwindow(QWidget *parent = nullptr);
    explicit showcommwindow(std::string answer, QWidget *parent = nullptr);
    ~showcommwindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::showcommwindow *ui;
};

#endif // SHOWCOMMWINDOW_H
