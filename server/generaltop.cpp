#include "generaltop.h"
#include "ui_generaltop.h"

generalTop::generalTop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generalTop)
{
    ui->setupUi(this);
}

generalTop::~generalTop()
{
    delete ui;
}

void generalTop::on_pushButton_clicked()
{
    this->close();
}
