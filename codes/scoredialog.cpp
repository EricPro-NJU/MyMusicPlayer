#include "scoredialog.h"
#include "ui_scoredialog.h"

ScoreDialog::ScoreDialog(QWidget *parent ,SongInfo* song) :
    QDialog(parent),
    ui(new Ui::ScoreDialog)
{
    ui->setupUi(this);
    this->song = song;
    score = 5;
    QString songname = song->Singer();
    songname += " - ";
    songname += song->Title();
    ui->title->setText(songname);
    ui->prescore->setText(QString::number(song->Star(),10,1));
}

ScoreDialog::~ScoreDialog()
{
    delete ui;
}

void ScoreDialog::on_star1_L_clicked()
{
    score = 1;
    ui->star1_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star2_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->star3_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->star4_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->star5_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->curscore->setText("1");
}

void ScoreDialog::on_star2_L_clicked()
{
    score = 2;
    ui->star1_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star2_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star3_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->star4_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->star5_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->curscore->setText("2");
}

void ScoreDialog::on_star3_L_clicked()
{
    score = 3;
    ui->star1_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star2_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star3_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star4_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->star5_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->curscore->setText("3");
}

void ScoreDialog::on_star4_L_clicked()
{
    score = 4;
    ui->star1_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star2_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star3_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star4_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star5_L->setStyleSheet("border-image: url(:/new/prefix1/star2.jpg);");
    ui->curscore->setText("4");
}

void ScoreDialog::on_star5_L_clicked()
{
    score = 5;
    ui->star1_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star2_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star3_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star4_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->star5_L->setStyleSheet("border-image: url(:/new/prefix1/star1.jpg);");
    ui->curscore->setText("5");
}

void ScoreDialog::on_okbtn_clicked()
{
    song->score_song(score);
    this->hide();
    QMessageBox::warning(this,tr("歌曲评分"),tr("成功提交！"));
    emit score_end(this);
}

void ScoreDialog::on_dltbtn_clicked()
{
    this->hide();
    emit score_end(this);
}
