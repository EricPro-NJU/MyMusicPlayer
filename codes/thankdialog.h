#ifndef THANKDIALOG_H
#define THANKDIALOG_H

#include <QDialog>

namespace Ui {
class ThankDialog;
}

class ThankDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThankDialog(QWidget *parent = nullptr);
    ~ThankDialog();

private slots:
    void on_close_clicked();

signals:
    void end_thank();

private:
    Ui::ThankDialog *ui;
};

#endif // THANKDIALOG_H
