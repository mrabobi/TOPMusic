#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    std::string username;
    std::string password;
    std::string regAnswer = "";
    std::string closeValue = "true";
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_loginButton_clicked();

    void on_pushButton_clear_clicked();

    void on_registerButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
