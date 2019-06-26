/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include "mainwindow.h"

#include <QApplication>

int main(int agrc, char *agrv[])
{
    QApplication app(agrc, agrv);

    MainWindow w;
    w.show();

    return app.exec();
}
