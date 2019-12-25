#ifndef MINIMIZEWIDGET_H
#define MINIMIZEWIDGET_H

#include <QWidget>
#include "songlist.h"

namespace Ui {
class MinimizeWidget;
}

class MinimizeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MinimizeWidget(QWidget *parent = nullptr);
    ~MinimizeWidget();

signals:
    void playBtn_clicked();
    void LastBtn_clicked();
    void NextBtn_clicked();
    void volumnMoved(int);
    void cirType_clicked();
    void back();

public slots:
    void changeVolumn(int);
    void changeLab(QString);
    void playBtn();
    void playBtn_pause();
    void cirType();
    void changeTitle(QString);

private slots:
    void on_playBtn_clicked();

    void on_lastBtn_clicked();

    void on_nextBtn_clicked();

    void on_volumnSlider_sliderMoved(int position);

    void on_cirType_clicked();

    void on_back_clicked();

private:
    Ui::MinimizeWidget *ui;
};

#endif // MINIMIZEWIDGET_H
