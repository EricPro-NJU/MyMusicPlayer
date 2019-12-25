#include "minimizewidget.h"
#include "ui_minimizewidget.h"

MinimizeWidget::MinimizeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinimizeWidget)
{
    ui->setupUi(this);
    ui->playBtn->setProperty("id","play");
    ui->cirType->setProperty("id","list_cir");
}

void MinimizeWidget::changeVolumn(int position){
    ui->volumnSlider->setValue(position);
}

void MinimizeWidget::changeLab(QString label){
    ui->label_2->setText(label);
}

void MinimizeWidget::changeTitle(QString title){
    ui->playingSong->setText(title);
}

void MinimizeWidget::playBtn(){
    if(ui->playBtn->property("id")=="pause"){
        ui->playBtn->setProperty("id","play");
        ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/play.jpg);");
    }
    else if(ui->playBtn->property("id")=="play"){
        qDebug()<<"ready to change to pause!!!";
        ui->playBtn->setProperty("id","pause");
        ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/pause.jpg);");
    }
    else{
        qDebug()<<"Error. property type: "<<ui->playBtn->property("id");
    }
}

void MinimizeWidget::playBtn_pause(){
    qDebug()<<"ready to change to pause!!!";
    ui->playBtn->setProperty("id","pause");
    ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/pause.jpg);");
}

void MinimizeWidget::cirType(){
    if(ui->cirType->property("id")=="list_cir"){
        ui->cirType->setProperty("id","single_cir");
        ui->cirType->setStyleSheet("border-image: url(:/new/prefix1/single_cir.jpg);");
    }
    else if(ui->cirType->property("id")=="single_cir"){
        ui->cirType->setProperty("id","random_cir");
        ui->cirType->setStyleSheet("border-image: url(:/new/prefix1/random_cir.jpg);");
    }
    else if(ui->cirType->property("id")=="random_cir"){
        ui->cirType->setProperty("id","list_cir");
        ui->cirType->setStyleSheet("border-image: url(:/new/prefix1/list_cir.jpg);");
    }
    else{
        qDebug()<<"Error. property type: "<<ui->cirType->property("id");
    }
}

MinimizeWidget::~MinimizeWidget()
{
    delete ui;
}

void MinimizeWidget::on_playBtn_clicked()
{

    emit playBtn_clicked();
}

void MinimizeWidget::on_lastBtn_clicked()
{
    emit LastBtn_clicked();
}

void MinimizeWidget::on_nextBtn_clicked()
{
    emit NextBtn_clicked();
}

void MinimizeWidget::on_volumnSlider_sliderMoved(int position)
{
    emit volumnMoved(position);
}

void MinimizeWidget::on_cirType_clicked()
{
    emit cirType_clicked();
}

void MinimizeWidget::on_back_clicked()
{
    this->hide();
    emit back();
}
