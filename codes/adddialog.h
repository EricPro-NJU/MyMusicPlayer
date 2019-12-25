#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "songlist.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_addButton_clicked();

    void on_close_clicked();

    void on_addConfirm_clicked();

signals:
    void add_end(AddDialog* adddia,bool valid, QString songPath, QString songTitle, QString songSinger);

private:
    Ui::AddDialog *ui;
    QString songPath;
    QString songTitle;
    QString songSinger;
};

#endif // ADDDIALOG_H
