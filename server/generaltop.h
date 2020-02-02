#ifndef GENERALTOP_H
#define GENERALTOP_H

#include <QDialog>

namespace Ui {
class generalTop;
}

class generalTop : public QDialog
{
    Q_OBJECT

public:
    explicit generalTop(QWidget *parent = nullptr);
    ~generalTop();

private slots:
    void on_pushButton_clicked();

private:
    Ui::generalTop *ui;
};

#endif // GENERALTOP_H
