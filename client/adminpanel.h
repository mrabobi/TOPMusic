#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>

namespace Ui {
class adminPanel;
}

class adminPanel : public QDialog
{
    Q_OBJECT

public:
    std::string voteAcces,levelAcces,user;
    explicit adminPanel(QWidget *parent = nullptr);
    ~adminPanel();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::adminPanel *ui;
};

#endif // ADMINPANEL_H
