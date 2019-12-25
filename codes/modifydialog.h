#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QDialog>
#include "songlist.h"

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = nullptr, SongInfo* song = nullptr);
    ~ModifyDialog();

signals:
    void modify_end(int, QString, QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ModifyDialog *ui;
    SongInfo* song;
};

#endif // MODIFYDIALOG_H
