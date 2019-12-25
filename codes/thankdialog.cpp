#include "thankdialog.h"
#include "ui_thankdialog.h"

ThankDialog::ThankDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThankDialog)
{
    ui->setupUi(this);
}

ThankDialog::~ThankDialog()
{
    delete ui;
}

void ThankDialog::on_close_clicked()
{
    emit end_thank();
}
