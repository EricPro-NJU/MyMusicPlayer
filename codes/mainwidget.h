#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "songlist.h"
#include "scoredialog.h"
#include "searchdialog.h"
#include "adddialog.h"
#include "minimizewidget.h"
#include "modifydialog.h"
#include "thankdialog.h"
enum PlayStatus{
    NONE,
    LIST_CIR,
    SINGLE_CIR,
    RANDOM_CIR,
};


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    bool eventFilter(QObject* obj, QEvent *evt);
    void showTable();
    bool playSong(int);
    void loadPlaylist();
    ~MainWidget();

private slots:
    void on_pushButton_clicked();

    void siftUp();

    void onRemove();

    void onModify();

    void siftDown();

    void onScoreBtnClicked();

    void score_end(ScoreDialog* );

    void search_end(SearchDialog*, int);

    void add_end(AddDialog*,bool,QString,QString,QString);

    void modify_end(int,QString,QString);

    void on_songList_doubleClicked(const QModelIndex &index);

    void ChangeSlider(qint64 val);

    void updateDuration(qint64 duration);

    void on_volumnSlider_sliderMoved(int value);

    void on_SongSlider_valueChanged(int position);

    void on_SongSlider_sliderReleased();

    void on_playBtn_clicked();

    void on_cirType_clicked();

    void changeSong(int position);

    //void state_changed(qint64 position);

    void on_nextBtn_clicked();

    void on_lastBtn_clicked();

    void on_titleSearchButton_clicked();

    void on_singerSearchButton_clicked();

    void back(){this->show();}

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void end_thank();

signals:
    void volumnChanged(int);
    void changeLab(QString);
    void playBtn_clicked();
    void cirType_clicked();
    void playBtn_pause();
    void setTitle(QString);

private:
    Ui::MainWidget* ui;
    MinimizeWidget* miniwidget;
    ThankDialog* thanks;
    QStandardItemModel* model;
    SongList songlist;
    QMenu tableMenu;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    QString current_playing;
    PlayStatus status;
    bool modified;
    int deleted_num;
    QString backup;
};

#endif // MAINWIDGET_H
