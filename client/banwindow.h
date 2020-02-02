#ifndef BANWINDOW_H
#define BANWINDOW_H

#include <QDialog>

namespace Ui {
class banWindow;
}

class banWindow : public QDialog
{
    Q_OBJECT

public:
    std::string username,command;
    int banFlag;
    explicit banWindow(QWidget *parent = nullptr);
    ~banWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::banWindow *ui;
};

#endif // BANWINDOW_H
