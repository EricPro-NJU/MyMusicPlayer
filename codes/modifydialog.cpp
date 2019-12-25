#include "modifydialog.h"
#include "ui_modifydialog.h"

ModifyDialog::ModifyDialog(QWidget *parent, SongInfo* song) :
    QDialog(parent),
    ui(new Ui::ModifyDialog),
    song(song)
{
    ui->setupUi(this);
    ui->number->setText(QString::number(song->Id()));
    ui->title->setText(song->Title());
    ui->singer->setText(song->Singer());
    ui->duration->setText(dur_trans(song->Minute(),song->Second()));

}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked()
{
    if(ui->title->text()=="\0"||ui->singer->text()=="\0"){
        QMessageBox::warning(this,tr("修改信息"),tr("输入信息不能为空！"));
        return;
    }
    QString title = ui->title->text();
    QString singer = ui->singer->text();
    emit modify_end(song->Id(),string_validity(title),string_validity(singer));
    this->hide();

    return;
}

void ModifyDialog::on_pushButton_2_clicked()
{
    this->hide();
    return;
}
