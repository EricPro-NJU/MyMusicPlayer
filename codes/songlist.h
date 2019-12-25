#ifndef SONGLIST_H
#define SONGLIST_H
#include <bits/stdc++.h>
#include <windows.h>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QMenu>
#include <QStandardItem>
using namespace std;
/*
 * this file defines songlist and its operations, regardless of the appearance to the users.
 * those functions will be called in mainwidget slots
 * */
//this class defines a single song.
class SongInfo{
    int id;
    QString title;
    QString singer;
    QString filename;
    double star;
    int scoreNum;
    int playedNum;
    bool songStatus; //(0: not playing; 1: playing)
    qint64 minute;
    qint64 second;
    QString display;
public:
    SongInfo(int id, QString path, QString title, QString singer);//create new
    SongInfo(int id, QString title, QString singer, double star, int scoreNum, int playedNum, qint64 minute, qint64 second);//load existing
    bool play_song();
    bool stop_song();
    void score_song(double val);
    int Id(){return id;}
    QString Title(){return title;}
    QString Singer(){return singer;}
    QString Filename(){return filename;}
    int ScoreNum(){return scoreNum;}
    int PlayedNum(){return playedNum;}
    double Star(){return star;}
    bool is_playing(){return songStatus;}
    qint64 Minute(){return minute;}
    qint64 Second(){return second;}
    void modify_dur(qint64 min, qint64 sec){if(min==0&&sec==0) return; minute = min; second = sec;}
    void setId(int id){this->id = id;}
    void setName(QString title, QString singer);
    QString displayTitle();
};
//this class defines a song list containing multiple songs.
//ATTENTION: NO \n or \r put at the last of music_table.txt
class SongList{
    int num;
    QString sysfile;
    vector <SongInfo> list;
    SongInfo* current;
public:
    SongList():num(0),sysfile("\0"),current(nullptr){list.clear();}
    SongList(QString sysfile);
    int Size(){return num;}
    bool add_to_list(QString path, QString title, QString singer);
    bool remove_from_list(int id);
    SongInfo* getSong(int id);
    SongInfo* getSong(QString filename);
    int getpos(QString display);
    void save_to_file();
    vector<SongInfo> List(){return list;}
    vector<SongInfo> searchBySinger(QString singer);	//search by singer name
    vector<SongInfo> searchByName(QString name);		//seach by song name
    bool sift_up(int id); //adjust position of the song in the songlist
    bool sift_down(int id);
    bool rename(int id, QString title, QString singer);
    bool playSong(QString filename);
    void stopPlaying();
    SongInfo* Current(){return current;}
    ~SongList(){list.clear();}
};
QString dur_trans(qint64 min, qint64 sec);
QString string_validity(QString& string);
#endif // SONGLIST_H
