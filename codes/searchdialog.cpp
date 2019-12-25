#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent, SongList* songlist, int type) :
    QDialog(parent),
    ui(new Ui::SearchDialog),
    list(songlist),
    type(type)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->searchView->setModel(model);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,tr("序号"));
    model->setHeaderData(1,Qt::Horizontal,tr("歌曲名"));
    model->setHeaderData(2,Qt::Horizontal,tr("歌手"));
    model->setHeaderData(3,Qt::Horizontal,tr("时长"));
    ui->searchView->setColumnWidth(0, 37);
    ui->searchView->setColumnWidth(1, 150);
    ui->searchView->setColumnWidth(2, 150);
    ui->searchView->setColumnWidth(3, 46);
    rows=0;
    if(type==1){//search by title
        ui->findMode->setText("歌名查找");
        ui->findResult->setText("请输入关键词");
        this->show();
    }
    else if(type==2){//search by singer
        ui->findMode->setText("歌手查找");
        ui->findResult->setText("请输入关键词");
        this->show();
    }
    else{
        QMessageBox::warning(this,tr("Error"),tr("查找界面呼出错误"));
        emit search_end(this, -1);
    }
}

SearchDialog::~SearchDialog()
{
    delete ui;
    delete model;
}

void SearchDialog::showTable(vector<SongInfo> songlist){
    qDebug()<<"before: rows = "<<rows;
    if(rows!=0){
        model->removeRows(0,rows);
    }
    rows = songlist.size();
    qDebug()<<"after: rows = "<<rows;
    int i=0;
    for(vector<SongInfo>::iterator it = songlist.begin();it!=songlist.end();it++){
        int id = it->Id();
        QString title = it->Title();
        QString singer = it->Singer();
        qint64 min = it->Minute();
        qint64 sec = it->Second();
        model->setItem(i,0,new QStandardItem(QString::number(id)));
        model->setItem(i,1,new QStandardItem(title));
        model->setItem(i,2,new QStandardItem(singer));
        model->setItem(i,3,new QStandardItem(dur_trans(min,sec)));
        i++;
    }
    ui->searchView->installEventFilter(this);
    ui->searchView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->searchView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->searchView->verticalHeader()->hide();
    ui->searchView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->searchView->setColumnWidth(0, 37);
    ui->searchView->setColumnWidth(1, 150);
    ui->searchView->setColumnWidth(2, 150);
    ui->searchView->setColumnWidth(3, 46);
}

void SearchDialog::on_searchButton_clicked()
{
    if(ui->searchInput->text().isEmpty()){
        QMessageBox::warning(this,tr("查找歌曲"),tr("请输入关键字进行搜索"));
        return;
    }
    vector <SongInfo> res;
    QString input = ui->searchInput->text();
    if(type==1){
        res = list->searchByName(input);
        if(res.empty()){
            QMessageBox::warning(this,tr("查找歌曲"),tr("未找到相应的歌曲，换个关键字试试"));
            return;
        }
        unsigned num = res.size();
        QString remider;
        remider = "找到以下";
        remider += QString::number(num);
        remider += "首关于\"";
        remider += input;
        remider += "\"的歌曲。";
        ui->findResult->setText(remider);
        showTable(res);
    }
    else if(type==2){
        res = list->searchBySinger(input);
        if(res.empty()){
            QMessageBox::warning(this,tr("查找歌曲"),tr("未找到相应的歌曲，换个关键字试试"));
            return;
        }
        unsigned num = res.size();
        QString remider;
        remider = "找到以下";
        remider += QString::number(num);
        remider += "首关于歌手\"";
        remider += input;
        remider += "\"的歌曲。";
        ui->findResult->setText(remider);
        showTable(res);
    }

}

void SearchDialog::on_close_clicked()
{
    this->hide();
    emit search_end(this, -1);
}

void SearchDialog::on_searchView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *modessl = ui->searchView->model();
    QModelIndex indextemp = modessl->index(row,0);
    QVariant datatemp = modessl->data(indextemp);
    qDebug()<<"datatemp is "<<datatemp;
    emit search_end(this,datatemp.toInt());
}
