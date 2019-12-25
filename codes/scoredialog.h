#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include <QDialog>
#include "songlist.h"
namespace Ui {
class ScoreDialog;
}

class ScoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreDialog(QWidget *parent = nullptr, SongInfo* song = nullptr);
    ~ScoreDialog();

private slots:
    void on_star1_L_clicked();

    void on_star2_L_clicked();

    void on_star3_L_clicked();

    void on_star4_L_clicked();

    void on_star5_L_clicked();

    void on_okbtn_clicked();

    void on_dltbtn_clicked();

signals:
    void score_end(ScoreDialog* );

private:
    Ui::ScoreDialog *ui;
    SongInfo* song;
    int score;
};

#endif // SCOREDIALOG_H
