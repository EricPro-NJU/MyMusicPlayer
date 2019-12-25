#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "songlist.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr, SongList* songlist = nullptr, int type = 0);
    void showTable(vector <SongInfo>);
    ~SearchDialog();

signals:
    void search_end(SearchDialog*, int);

private slots:
    void on_searchButton_clicked();

    void on_close_clicked();

    void on_searchView_doubleClicked(const QModelIndex &index);

private:
    Ui::SearchDialog *ui;
    SongList* list;
    QStandardItemModel* model;
    int type;
    int rows;
};

#endif // SEARCHDIALOG_H
