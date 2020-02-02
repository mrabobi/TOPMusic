#ifndef REMOVESONG_H
#define REMOVESONG_H

#include <QDialog>

namespace Ui {
class removesong;
}

class removesong : public QDialog
{
    Q_OBJECT

public:
    std::string song;
    int removeFlag;
    explicit removesong(QWidget *parent = nullptr);
    ~removesong();

private slots:
    void on_pushButton_clicked();

private:
    Ui::removesong *ui;
};

#endif // REMOVESONG_H
