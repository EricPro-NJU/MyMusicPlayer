#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(0);
    QApplication a(argc, argv);
    MainWidget w;
    w.setWindowTitle(QObject::tr("小蓝鲸音乐"));
    w.setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    w.show();

    return a.exec();
}
