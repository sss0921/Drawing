/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenActionTriggered);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAboutActionTriggered);
}

void MainWindow::onOpenActionTriggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open Image File"), "", "Tif(*.tif *.tiff);;Bmp(*.bmp);;Png(*.png);;Jpg(*.jpg)");

    if (!filePath.isEmpty())
        doOpenFile(filePath);
}

void MainWindow::onAboutActionTriggered()
{
    QString data = QString("%1 version: %2").arg(qApp->applicationName()).arg("1.0.0.0");
    QMessageBox::about(this, QString("About %1").arg(qApp->applicationName()), data);
}

void MainWindow::doOpenFile(const QString &filePath)
{
    QFileInfo info(filePath);
    if (info.suffix() == "tif" || info.suffix() == "tiff") {
        // reader tif file
    } else {
        m_image = QImage(filePath);
    }
}
