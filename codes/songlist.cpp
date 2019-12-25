#include "songlist.h"
QString dur_trans(qint64 min, qint64 sec){
    QString res;
    if(min<10) res+="0";
    res += QString::number(min);
    res += ":";
    if(sec<10) res+="0";
    res += QString::number(sec);
    return res;
}
/* INVALID CHARACTER:
 * SPACE TAB \ / : * ? " < > |
 * */

QString string_validity(QString& string){
    QString res(string);
    while(res.indexOf(" ")!=-1){
        res.replace(res.indexOf(" "),1,"_");
    }
    while(res.indexOf("\t")!=-1){
        res.replace(res.indexOf("\t"),1,"_");
    }
    while(res.indexOf("\\")!=-1){
        res.replace(res.indexOf("\\"),1,"_");
    }
    while(res.indexOf("/")!=-1){
        res.replace(res.indexOf("/"),1,"_");
    }
    while(res.indexOf(":")!=-1){
        res.replace(res.indexOf(":"),1,"_");
    }
    while(res.indexOf("?")!=-1){
        res.replace(res.indexOf("?"),1,"_");
    }
    while(res.indexOf("\"")!=-1){
        res.replace(res.indexOf("\""),1,"_");
    }
    while(res.indexOf("<")!=-1){
        res.replace(res.indexOf("<"),1,"_");
    }
    while(res.indexOf(">")!=-1){
        res.replace(res.indexOf(">"),1,"_");
    }
    while(res.indexOf("|")!=-1){
        res.replace(res.indexOf("|"),1,"_");
    }
    return res;
}

/* ATTENTION: When user is asked to set title and singer name to the song, chances are they might
 * put spaces (' ') in. So pre-process of replacing space (' ') with underline ('_') is required.
 * Otherwise there might be unexpected errors when running!
 * Also, in windows file, characters like \/:*?"<>| are not allowed,
 * for simplicity, all replaced with '_', and inform the user
 * */
SongInfo::SongInfo(int id, QString path, QString title, QString singer){
    this->id = id;
    this->title = title;
    this->singer = singer;
    this->star = 0.0;
    this->scoreNum=0;
    this->playedNum=0;
    this->songStatus=0;
    QString dest = "music\\";
    dest += singer;
    dest += "-";
    dest += title;
    QFile::copy(path,dest);
    filename = dest;
    minute = second = 0;
    display = singer;
    display += " - ";
    display += title;
}

SongInfo::SongInfo(int id, QString title, QString singer, double star, int scoreNum, int playedNum, qint64 minute, qint64 second){
    this->id = id;
    this->title = title;
    this->singer = singer;
    this->star = star;
    this->scoreNum = scoreNum;
    this->playedNum = playedNum;
    this->minute = minute;
    this->second = second;
    this->songStatus=0;
    filename = "music\\";
    filename += singer;
    filename += "-";
    filename += title;
    display = singer;
    display += " - ";
    display += title;
}

bool SongInfo::play_song(){
    if(songStatus) return false;
    songStatus = 1;
    playedNum++;
    qDebug()<<"now PlayedNum is "<<playedNum;
    return true;
}

bool SongInfo::stop_song(){
    if(!songStatus) return false;
    songStatus = 0;
    return false;
}

void SongInfo::score_song(double val){
    double total = star*scoreNum;
    total += val;
    scoreNum ++;
    star = total/scoreNum;
}

QString SongInfo::displayTitle(){
    QString res = singer;
    res += " - ";
    res += title;
    return res;
}

void SongInfo::setName(QString title, QString singer){
    this->title = title;
    this->singer = singer;
    QString filename = "music\\";
    filename += singer;
    filename += "-";
    filename += title;
    this->filename = filename;
}

SongList::SongList(QString filename){
    num = 0;
    sysfile = filename;
    list.clear();
    current = nullptr;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"fatal error! sysfile open failed!";
        exit(-1);
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString title,singer;
        double star;
        int scoreNum, playedNum;
        qint64 minute, second;
        in>>title>>singer>>star>>scoreNum>>playedNum>>minute>>second;
        if(title=="\0") continue;
        num++;
        SongInfo song(num,title,singer,star,scoreNum,playedNum,minute,second);
        list.push_back(song);
    }
    file.close();
}

bool SongList::add_to_list(QString path, QString title, QString singer){
    QString filename = "music\\";
    filename += singer;
    filename += "-";
    filename += title;
    SongInfo* song = getSong(filename);
    if(song!=nullptr){
        qDebug()<<"Song title crashed, add failed!";
        return false;
    }
    num++;
    SongInfo newSong(num,path,title,singer);
    list.push_back(newSong);
    return true;
}

bool SongList::remove_from_list(int id){
    if(id>num||id<=0){
        qDebug()<<"No song marked no."<<id<<" exist, remove failed!";
        return false;
    }
    list.erase(list.begin()+id-1);
    vector<SongInfo>::iterator it = list.begin()+id-1;
    int index = id;
    while(it!=list.end()){
        it->setId(index);
        index++;
        it++;
    }
    num--;
    return true;
}

SongInfo* SongList::getSong(int id){
    if(id>num||id<=0) return nullptr;
    vector<SongInfo>::iterator it;
    for(it = list.begin();it != list.end();it++){
        if(it->Id()==id) return &(*it);
    }
    return nullptr;
}


SongInfo* SongList::getSong(QString filename){
    vector<SongInfo>::iterator it;
    for(it = list.begin();it != list.end();it++){
        if(it->Filename()==filename) return &(*it);
        //qDebug()<<"the file name "<<it->Filename()<<", different from the target "<<filename;
    }
    return nullptr;
}

int SongList::getpos(QString display){
    vector<SongInfo>::iterator it;
    for(it = list.begin();it != list.end();it++){
        if(it->displayTitle()==display) return it->Id();
        //qDebug()<<"the file name "<<it->Filename()<<", different from the target "<<filename;
    }
    return 0;
}

void SongList::save_to_file(){
    QFile file(sysfile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"fatal error! Cannot open sysfile "<<sysfile;
        return;
    }
     QTextStream out(&file);
    vector<SongInfo>::iterator it;
    for(it = list.begin();it!=list.end();it++){
        if(it!=list.begin()) out<<"\n";
        out<<it->Title()<<"\t"<<it->Singer()<<"\t"<<it->Star()<<"\t"<<it->ScoreNum()<<"\t"<<it->PlayedNum()<<"\t"
          <<it->Minute()<<"\t"<<it->Second();
    }
    file.close();
}

vector<SongInfo> SongList::searchBySinger(QString singer){
    vector <SongInfo> res;
    res.clear();
    vector <SongInfo>::iterator it;
    for(it=list.begin();it!=list.end();it++){
        int index = it->Singer().indexOf(singer);
        if(index!=-1){
            res.push_back(*it);
        }
    }
    return res;
}

vector<SongInfo> SongList::searchByName(QString name){
    vector <SongInfo> res;
    res.clear();
    vector <SongInfo>::iterator it;
    for(it=list.begin();it!=list.end();it++){
        int index = it->Title().indexOf(name);
        if(index!=-1){
            res.push_back(*it);
        }
    }
    return res;
}

bool SongList::sift_up(int id){
    if(id==1) {
        qDebug()<<"Seriously?? it's already on top!";
        return false;
    }
    if(id>num||id<=0){
        qDebug()<<"Song not found.";
        return false;
    }
    vector<SongInfo>::iterator it1 = list.begin()+id-1;
    vector<SongInfo>::iterator it2 = list.begin()+id-2;
    it1->setId(id-1);
    it2->setId(id);
    swap(list[id-1],list[id-2]);
    return true;
}

bool SongList::sift_down(int id){
    if(id==num){
        qDebug()<<"Seriously?? it's already at the bottom!";
        return false;
    }
    if(id>num||id<=0){
        qDebug()<<"Song not found.";
        return false;
    }
    vector<SongInfo>::iterator it1 = list.begin()+id-1;
    vector<SongInfo>::iterator it2 = list.begin()+id;
    it1->setId(id+1);
    it2->setId(id);
    swap(list[id-1],list[id]);
    return true;
}

bool SongList::rename(int id, QString title, QString singer){
    QString filename = "music\\";
    filename += singer;
    filename += "-";
    filename += title;
    if(getSong(filename)!=nullptr){
        return false;
    }
    SongInfo* song = getSong(id);
    QString original_name = song->Filename();
    QFile::copy(original_name,filename);
    QFile file(original_name);
    if(!file.remove()){
        QFile file2(filename);
        file2.remove();
        return false;
    }
    else{
        song->setName(title,singer);
        return true;
    }
}

/* here "PlaySong" is just a mark of the song being played.
 * The playing effects defined in widget classes.
 * */
bool SongList::playSong(QString filename){
    SongInfo* song = getSong(filename);
    if(song==nullptr){
        qDebug()<<"Failed played the song "<<filename;
        return false;
    }
    if(current==song){
        return true;
    }
    else{
        if(current!=nullptr){
            current->stop_song();
        }
        current = song;
        qDebug()<<"ready to call song->play_song()";
        song->play_song();
        return true;
    }
}

void SongList::stopPlaying(){
    if(current!=nullptr){
        current->stop_song();
        current=nullptr;
    }
}
