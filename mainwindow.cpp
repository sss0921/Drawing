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
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_color(QColor(Qt::red))
    , m_image(QImage())
    , m_recentFilesMenu(new RecentFilesMenu(this))
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveSettings()
{
}

void MainWindow::loadSettings()
{
}

void MainWindow::init()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenActionTriggered);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAboutActionTriggered);

    m_penAction = new QAction(this);
    m_penAction->setCheckable(true);
    m_penAction->setIcon(QIcon(":/image/pen.png"));
    ui->toolBar->addAction(m_penAction);

    QPixmap pixmap = QPixmap(200, 200);
    pixmap.fill(m_color);
    m_colorAction = new QAction(this);
    m_colorAction->setIcon(QIcon(pixmap));
    ui->toolBar->addAction(m_colorAction);

    connect(m_penAction, &QAction::triggered, this, &MainWindow::onPenActionTriggered);
    connect(m_colorAction, &QAction::triggered, this, &MainWindow::onColorActionTriggered);

    ui->actionRecentFiles->setMenu(m_recentFilesMenu);
    connect(m_recentFilesMenu, &RecentFilesMenu::recentFileTriggered, this,
            &MainWindow::doOpenFile);
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

void MainWindow::onPenActionTriggered(bool checked)
{
    if (checked)
        ui->graphicsView->setMode(GraphicsImageScene::DrawShapePathMode);
    else
        ui->graphicsView->setMode(GraphicsImageScene::NormalMode);
}

void MainWindow::onColorActionTriggered()
{
    QColor color = QColorDialog::getColor(m_color, this, tr("Get Pen Color"));

    if (!color.isValid())
        return;

    m_color = color;
    QPixmap pixmap = QPixmap(200, 200);
    pixmap.fill(m_color);
    m_colorAction->setIcon(QIcon(pixmap));
}

void MainWindow::doOpenFile(const QString &filePath)
{
    QFileInfo info(filePath);
    if (info.suffix() == "tif" || info.suffix() == "tiff") {
        // reader tif file
    } else {
        m_image = QImage(filePath);
    }

    ui->graphicsView->setImage(m_image);
    m_recentFilesMenu->addRecentFile(filePath);
}
