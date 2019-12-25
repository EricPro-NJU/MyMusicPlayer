#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    songPath.clear();
    songTitle.clear();
    songSinger.clear();
    ui->title2->hide();
    ui->songInfo1->hide();
    ui->songInfo2->hide();
    ui->songTitle->hide();
    ui->songSinger->hide();
    ui->addConfirm->hide();
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_addButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("选择歌曲"),"C:",tr("音乐文件( *mp3 *wav"));
    if(filename=="\0"){
        return;
    }
    else{
        ui->title2->show();
        ui->songInfo1->show();
        ui->songInfo2->show();
        ui->songTitle->show();
        ui->songSinger->show();
        ui->addConfirm->show();
        songPath = filename;
        ui->filePath->setText(filename);
    }
}

void AddDialog::on_close_clicked()
{
    this->hide();
    emit add_end(this,false,songPath,songTitle,songSinger);
}

void AddDialog::on_addConfirm_clicked()
{
    songPath = ui->filePath->text();
    songTitle = ui->songTitle->text();
    songSinger = ui->songSinger->text();
    if(songPath=="\0"){
        QMessageBox::warning(this,tr("添加歌曲"),tr("添加失败！"));
        return;
    }
    if(songTitle=="\0"||songTitle=="歌曲标题"){
        QMessageBox::warning(this,tr("添加歌曲"),tr("请输入有效歌曲标题"));
        return;
    }
    if(songSinger=="\0"||songSinger=="歌手名称"){
        QMessageBox::warning(this,tr("添加歌曲"),tr("请输入有效歌手名称"));
        return;
    }
    emit add_end(this,true,songPath,songTitle,songSinger);
}
