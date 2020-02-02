#ifndef REGISTERTIME_H
#define REGISTERTIME_H

#include <QDialog>

namespace Ui {
class registerTime;
}

class registerTime : public QDialog
{
    Q_OBJECT

public:
    std::string regUsername;
    std::string regPassword;
    std::string regConfpass;
    explicit registerTime(QWidget *parent = nullptr);
    ~registerTime();

private slots:
    void on_pushButton_register_clicked();

private:
    Ui::registerTime *ui;
};

#endif // REGISTERTIME_H
