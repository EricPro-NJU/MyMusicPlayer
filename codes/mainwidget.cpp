#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    songlist("sysfile\\music_table.txt"),
    current_playing(),
    status(LIST_CIR),
    modified(false),
    deleted_num(0)
{
    ui->setupUi(this);
    miniwidget = new MinimizeWidget;
    miniwidget->setWindowTitle("小蓝鲸音乐");
    miniwidget->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::WindowMinimizeButtonHint);
    thanks = new ThankDialog;
    thanks->setWindowTitle("关于我们");
    thanks->hide();
    connect(thanks,SIGNAL(end_thank()),this,SLOT(end_thank()));
    connect(this,SIGNAL(volumnChanged(int)),miniwidget,SLOT(changeVolumn(int)));
    connect(this,SIGNAL(changeLab(QString)),miniwidget,SLOT(changeLab(QString)));
    connect(this,SIGNAL(playBtn_clicked()),miniwidget,SLOT(playBtn()));
    connect(this,SIGNAL(playBtn_pause()),miniwidget,SLOT(playBtn_pause()));
    connect(this,SIGNAL(cirType_clicked()),miniwidget,SLOT(cirType()));
    connect(this,SIGNAL(setTitle(QString)),miniwidget,SLOT(changeTitle(QString)));
    connect(miniwidget,SIGNAL(playBtn_clicked()),this,SLOT(on_playBtn_clicked()));
    connect(miniwidget,SIGNAL(LastBtn_clicked()),this,SLOT(on_lastBtn_clicked()));
    connect(miniwidget,SIGNAL(NextBtn_clicked()),this,SLOT(on_nextBtn_clicked()));
    connect(miniwidget,SIGNAL(volumnMoved(int)),this,SLOT(on_volumnSlider_sliderMoved(int)));
    connect(miniwidget,SIGNAL(cirType_clicked()),this,SLOT(on_cirType_clicked()));
    connect(miniwidget,SIGNAL(back()),this,SLOT(back()));
    tableMenu.addAction("修改信息",this,SLOT(onModify()));
    tableMenu.addAction("删除歌曲",this,SLOT(onRemove()));
    tableMenu.addAction("上移",this,SLOT(siftUp()));
    tableMenu.addAction("下移",this,SLOT(siftDown()));
    player = nullptr;
    model = new QStandardItemModel(this);
    ui->songList->setModel(model);
    ui->songList->setSortingEnabled(1);
    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal,tr("序号"));
    model->setHeaderData(1,Qt::Horizontal,tr("歌曲名"));
    model->setHeaderData(2,Qt::Horizontal,tr("歌手"));
    model->setHeaderData(3,Qt::Horizontal,tr("播放量"));
    model->setHeaderData(4,Qt::Horizontal,tr("评分"));
    model->setHeaderData(5,Qt::Horizontal,tr("时长"));
    model->setHeaderData(6,Qt::Horizontal,tr(""));

    showTable();
    ui->playBtn->setProperty("id","play");
    ui->cirType->setProperty("id","list_cir");
    player = new QMediaPlayer;
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(ChangeSlider(qint64)));
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(state_changed(qint64)));
    playlist = new QMediaPlaylist;
    loadPlaylist();
    playlist->setCurrentIndex(0);
    //qDebug()<<"now current index is "<<playlist->currentIndex();
    ui->playingSong->setText(songlist.getSong(1)->displayTitle());
    emit setTitle(songlist.getSong(1)->displayTitle());
    //qDebug()<<"now current index is "<<playlist->currentIndex();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    //qDebug()<<"now current index is "<<playlist->currentIndex();
    connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSong(int)));
    //qDebug()<<"now current index is "<<playlist->currentIndex();
    player->setPlaylist(playlist);
    //qDebug()<<"now current index is "<<playlist->currentIndex();
    player->stop();
    songlist.playSong(songlist.getSong(1)->Filename());
    current_playing = songlist.getSong(1)->displayTitle();
    //qDebug()<<"now current index is "<<playlist->currentIndex();
}

MainWidget::~MainWidget()
{
    delete ui;
    delete model;
    delete player;
    delete playlist;
    delete miniwidget;
}

void MainWidget::loadPlaylist(){
    for(int i=1;i<=songlist.Size();i++){
        SongInfo* song = songlist.getSong(i);
        QString file;
        file = song->Filename();
        playlist->addMedia(QUrl::fromLocalFile(file));
    }
}

bool MainWidget::eventFilter(QObject* obj, QEvent *evt){
    if(obj == ui->songList  &&  evt->type() == QEvent::ContextMenu)    {
        if(ui->songList->currentIndex().isValid()==true)        {
            tableMenu.exec(cursor().pos());           //在当前鼠标位置上运行菜单menu对象
        }
    }
    return QWidget::eventFilter(obj,evt);
}

void MainWidget::showTable(){
    songlist.save_to_file();

    /*model->setItem(0, 0, new QStandardItem(tr("1")));
    model->setItem(0, 1, new QStandardItem(tr("Hop")));
    model->setItem(0, 2, new QStandardItem(tr("Azis")));
    model->setItem(0, 3, new QStandardItem(tr("66666")));
    model->setItem(0, 4, new QStandardItem(tr("5.0")));
    model->setItem(0, 5, new QStandardItem(tr("100:00")));*/
    vector<SongInfo> song = songlist.List();
    int i = 0;
    for(vector<SongInfo>::iterator it = song.begin();it!=song.end();it++){
        int id = it->Id();
        QString title = it->Title();
        QString singer = it->Singer();
        int played = it->PlayedNum();
        double star = it->Star();
        qint64 min = it->Minute();
        qint64 sec = it->Second();
        QString name = singer;
        name += " - ";
        name += title;
        //qDebug()<<"name = "<<name<<" current_playing = "<<current_playing;
        if(name==current_playing){
            title+="【正在播放】";
        }
        QStandardItem* item1 = new QStandardItem;
        item1->setData(QVariant(id),Qt::EditRole);
        model->setItem(i,0,item1);
        model->setItem(i,1,new QStandardItem(title));
        model->setItem(i,2,new QStandardItem(singer));
        QStandardItem* item2 = new QStandardItem;
        item2->setData(QVariant(played),Qt::EditRole);
        model->setItem(i,3,item2);
        model->setItem(i,4,new QStandardItem(QString::number(star,10,1)));
        model->setItem(i,5,new QStandardItem(dur_trans(min,sec)));
        model->setItem(i,6,new QStandardItem("normal"));
        QPushButton* button = new QPushButton(tr("评分"));
        button->setProperty("id",id);
        connect(button, SIGNAL(clicked()), this, SLOT(onScoreBtnClicked()));
        ui->songList->setIndexWidget(model->index(i, 6), button);

        i++;
    }
    while(deleted_num>0){
        model->removeRow(i);
        deleted_num--;
    }
    ui->songList->installEventFilter(this);
    ui->songList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->songList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->songList->verticalHeader()->hide();
    ui->songList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->songList->setColumnWidth(0, 37);
    ui->songList->setColumnWidth(1, 150);
    ui->songList->setColumnWidth(2, 150);
    ui->songList->setColumnWidth(3, 50);
    ui->songList->setColumnWidth(4, 46);
    ui->songList->setColumnWidth(5, 46);
    ui->songList->setColumnWidth(6, 42);
}

bool MainWidget::playSong(int id){ //id is index of song (from 1 to Size();)
    id--;
    qDebug()<<"now index is "<<id<<" currentindex is "<<playlist->currentIndex();
    if(id==playlist->currentIndex()){
        player->play();
        ui->playBtn->setProperty("id","pause");
        ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/pause.jpg);");
        emit playBtn_pause();
        songlist.playSong(songlist.getSong(id+1)->Filename());
        return true;
    }
    if(id>=songlist.Size()||id<0){
        QMessageBox::warning(this,tr("播放错误"),tr("歌曲定位错误"));
        return false;
    }
    player->stop();
    playlist->setCurrentIndex(id);
    player->play();
    ui->playBtn->setProperty("id","pause");
    ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/pause.jpg);");
    emit playBtn_pause();
    songlist.playSong(songlist.getSong(id+1)->Filename());
    current_playing = songlist.getSong(id+1)->displayTitle();
    return true;

}

void MainWidget::onRemove(){
    int row = ui->songList->currentIndex().row();
    QAbstractItemModel *modessl = ui->songList->model();
    QModelIndex indextemp = modessl->index(row,0);
    QVariant datatemp = modessl->data(indextemp);
    if(songlist.getSong(datatemp.toInt())->displayTitle()==current_playing){
        QMessageBox::warning(this,tr("删除失败"),tr("歌曲正在播放，无法删除。"));
        return;
    }
    else{
        backup = current_playing;
        modified = true;
        QString filename = songlist.getSong(datatemp.toInt())->Filename();
        QFile file(filename);

        if(!songlist.remove_from_list(datatemp.toInt())){
            QMessageBox::warning(this,tr("删除失败"),tr("由于系统底层实现错误，无法删除歌曲"));
            return;
        }
        if(!file.remove()){
            QMessageBox::warning(this,tr("删除失败"),tr("由于系统文件操作错误，无法删除歌曲"));
            return;
        }
        deleted_num++;
        showTable();

    }
}

void MainWidget::onModify(){
    int row = ui->songList->currentIndex().row();
    QAbstractItemModel *modessl = ui->songList->model();
    QModelIndex indextemp = modessl->index(row,0);
    QVariant datatemp = modessl->data(indextemp);
    if(songlist.getSong(datatemp.toInt())->displayTitle()==current_playing){
        QMessageBox::warning(this,tr("修改失败"),tr("歌曲正在播放，无法修改信息。"));
        return;
    }
    backup = current_playing;
    modified = true;
    ModifyDialog* modifydia = new ModifyDialog(this,songlist.getSong(datatemp.toInt()));
    modifydia->setWindowTitle("修改歌曲信息");
    connect(modifydia,SIGNAL(modify_end(int, QString, QString)),this,SLOT(modify_end(int,QString,QString)));
    modifydia->show();
}

void MainWidget::modify_end(int id ,QString title ,QString singer){
    if(songlist.rename(id,title,singer)){
        QMessageBox::warning(this,tr("修改信息"),tr("修改成功！"));
        showTable();
        return;
    }
    else{
        QMessageBox::warning(this,tr("修改信息"),tr("修改失败，请检查关键字是否冲突。"));
        return;
    }


}

void MainWidget::siftUp(){
    backup = current_playing;
    modified = true;
    int row = ui->songList->currentIndex().row();
    QAbstractItemModel *modessl = ui->songList->model();
    QModelIndex indextemp = modessl->index(row,0);
    QVariant datatemp = modessl->data(indextemp);
    if(songlist.sift_up(datatemp.toInt())){
        qDebug()<<"song no."<<datatemp<<" being sifted up.";
        showTable();
    }
}

void MainWidget::siftDown(){
    backup = current_playing;
    modified =true;
    int row = ui->songList->currentIndex().row();
    QAbstractItemModel *modessl = ui->songList->model();
    QModelIndex indextemp = modessl->index(row,0);
    QVariant datatemp = modessl->data(indextemp);
    if(songlist.sift_down(datatemp.toInt())){
        qDebug()<<"song no."<<datatemp<<" being sifted down.";
        showTable();
    }
}

void MainWidget::score_end(ScoreDialog* sd){
    sd->hide();
    showTable();
}

void MainWidget::search_end(SearchDialog* sd, int id){
    qDebug()<<"called search_end";
    if(id == -1) return;
    else{
        playSong(id);
    }
    sd->hide();
    return;
}

void MainWidget::onScoreBtnClicked(){
    QPushButton *button = (QPushButton *)sender();
    int id = button->property("id").toInt();
    ScoreDialog* scoredia = new ScoreDialog(this,songlist.getSong(id));
    connect(scoredia,SIGNAL(score_end(ScoreDialog* )),this,SLOT(score_end(ScoreDialog* )));
    scoredia->setWindowTitle("评分系统");
    scoredia->show();
}

void MainWidget::on_pushButton_clicked()
{
    AddDialog* adddia = new AddDialog(this);
    connect(adddia,SIGNAL(add_end(AddDialog*,bool,QString,QString,QString)),this,SLOT(add_end(AddDialog*,bool,QString,QString,QString)));
    adddia->setWindowTitle("添加歌曲");
    adddia->show();
}

void MainWidget::add_end(AddDialog* adddia, bool valid, QString path, QString title, QString singer){
    if(!valid){
        adddia->hide();
        return;
    }
    title = string_validity(title);
    singer = string_validity(singer);
    if(!songlist.add_to_list(path,title,singer)){
        QMessageBox::warning(this,tr("添加失败"),tr("添加失败，歌单内已经有相应的歌曲了，尝试换个标题吧。"),QMessageBox::Abort);
        return;
    }
    songlist.save_to_file();
    QString file = "music\\";
    file += singer;
    file += "-";
    file += title;
    playlist->addMedia(QUrl::fromLocalFile(file));
    qDebug()<<"successfully add song "<<singer<<"-"<<title<<" to the songlist";
    playSong(songlist.Size());
    adddia->hide();
    return;
}


void MainWidget::on_songList_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *modessl = ui->songList->model();
    QModelIndex indextemp = modessl->index(row,0);
    QVariant datatemp = modessl->data(indextemp);
    if(modified){
        modified = false;
        player->stop();
        playlist->clear();
        loadPlaylist();
    }
    qDebug()<<"datatemp is "<<datatemp;
    playSong(datatemp.toInt());
}

void MainWidget::on_volumnSlider_sliderMoved(int position)
{

    if(player!=nullptr)
        player->setVolume(position);
}

void MainWidget::updateDuration(qint64 duration){
    ui->SongSlider->setRange(0,duration);//根据播放时长来设置滑块的范围
    ui->SongSlider->setEnabled(duration>0);
    ui->SongSlider->setPageStep(duration/10);//以及每一步的步数
    qint64 time = duration/1000;
    qint64 min = time/60;
    qint64 sec = time%60;

    songlist.Current()->modify_dur(min,sec);
    showTable();
}

void MainWidget::ChangeSlider(qint64 val){
    if(val==0) return ;
    //qDebug()<<"val is "<<val;
    //qDebug()<<"duration: "<<player->duration();
    ui->SongSlider->setValue(val);

}

void MainWidget::on_SongSlider_valueChanged(int position)
{
    int max = ui->SongSlider->maximum();
    int val_m = position/60000;
    int val_s = (position%60000)/1000;
    int max_m = max/60000;
    int max_s = (max%60000)/1000;
    QString str;
    if(val_m<10){
        str += "0";
    }
    str += QString::number(val_m);
    str += ":";
    if(val_s<10){
        str += "0";
    }
    str += QString::number(val_s);
    str += " / ";
    if(max_m<10){
        str += "0";
    }
    str += QString::number(max_m);
    str += ":";
    if(max_s<10){
        str += "0";
    }
    str += QString::number(max_s);
    //qDebug()<<"label: "<<str;
    ui->songLabel->setText(str);
    emit changeLab(str);
}

void MainWidget::on_SongSlider_sliderReleased()
{
    int position = ui->SongSlider->value();
    player->setPosition(position);
}

void MainWidget::on_playBtn_clicked()
{

    if(player==nullptr) return;
    emit playBtn_clicked();
    if(ui->playBtn->property("id")=="pause"){
        ui->playBtn->setProperty("id","play");
        ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/play.jpg);");
        player->pause();
    }
    else if(ui->playBtn->property("id")=="play"){
        ui->playBtn->setProperty("id","pause");
        ui->playBtn->setStyleSheet("border-image: url(:/new/prefix1/pause.jpg);");
        player->play();
    }
    else{
        qDebug()<<"Error. property type: "<<ui->playBtn->property("id");
    }
}

void MainWidget::on_cirType_clicked()
{
    emit cirType_clicked();
    if(ui->cirType->property("id")=="list_cir"){
        ui->cirType->setProperty("id","single_cir");
        ui->cirType->setStyleSheet("border-image: url(:/new/prefix1/single_cir.jpg);");
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        status = SINGLE_CIR;
    }
    else if(ui->cirType->property("id")=="single_cir"){
        ui->cirType->setProperty("id","random_cir");
        ui->cirType->setStyleSheet("border-image: url(:/new/prefix1/random_cir.jpg);");
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        status = RANDOM_CIR;
    }
    else if(ui->cirType->property("id")=="random_cir"){
        ui->cirType->setProperty("id","list_cir");
        ui->cirType->setStyleSheet("border-image: url(:/new/prefix1/list_cir.jpg);");
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        status = LIST_CIR;
    }
    else{
        qDebug()<<"Error. property type: "<<ui->cirType->property("id");
    }
}


void MainWidget::changeSong(int position){
    if(!modified){
        position = position % songlist.Size();
        QString label = songlist.getSong(position+1)->displayTitle();
        ui->playingSong->setText(label);
        emit setTitle(label);
        songlist.playSong(songlist.getSong(position+1)->Filename());
        current_playing = songlist.getSong(position+1)->displayTitle();
    }
    else{
        modified = false;
        player->stop();
        playlist->clear();
        loadPlaylist();
        int lastpos = songlist.getpos(backup);
        qDebug()<<"last pos is "<<lastpos;
        if(status==SINGLE_CIR){
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            playSong(lastpos);
        }
        else if(status==LIST_CIR){
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
            lastpos++;
            if(lastpos>songlist.Size()) lastpos=1;
            playSong(lastpos);
        }
        else if(status==RANDOM_CIR){
            playlist->setPlaybackMode(QMediaPlaylist::Random);
            lastpos+=rand()%songlist.Size();
            if(lastpos>songlist.Size()) lastpos=1;
            playSong(lastpos);
        }
    }
}

void MainWidget::on_nextBtn_clicked()
{
    if(playlist->currentIndex()>=songlist.Size()-1){
        playlist->setCurrentIndex(0);
        player->play();
        return;
    }
    playlist->setCurrentIndex((playlist->currentIndex()+1)%songlist.Size());
    player->play();
}

void MainWidget::on_lastBtn_clicked()
{
    if(playlist->currentIndex()==0){
        playlist->setCurrentIndex(songlist.Size()-1);
        player->play();
        return;
    }
    playlist->setCurrentIndex((playlist->currentIndex()-1)%songlist.Size());
    player->play();
}

void MainWidget::on_titleSearchButton_clicked()
{
    SearchDialog* searchdia = new SearchDialog(this,&songlist,1);
    connect(searchdia,SIGNAL(search_end(SearchDialog*,int)),this,SLOT(search_end(SearchDialog*,int)));
    searchdia->setWindowTitle("查找歌曲");
    searchdia->show();
}

void MainWidget::on_singerSearchButton_clicked()
{
    SearchDialog* searchdia = new SearchDialog(this,&songlist,2);
    connect(searchdia,SIGNAL(search_end(SearchDialog*,int)),this,SLOT(search_end(SearchDialog*,int)));
    searchdia->setWindowTitle("查找歌手");
    searchdia->show();
}

void MainWidget::on_pushButton_2_clicked()
{
    this->hide();
    miniwidget->show();
}

void MainWidget::on_pushButton_3_clicked()
{
    thanks->show();
}

void MainWidget::end_thank(){
    thanks->hide();
}
