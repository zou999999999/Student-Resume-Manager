#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 全局默认字体：微软雅黑，兼顾中英文显示
    QFont font(QStringLiteral("微软雅黑"), 10);
    app.setFont(font);

    MainWindow w;
    w.show();

    return app.exec();
}
