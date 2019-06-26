/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include <QImage>
#include <QPixmap>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void onOpenActionTriggered();
    void onAboutActionTriggered();
    void onPenActionTriggered(bool checked);
    void onColorActionTriggered();
    void doOpenFile(const QString &filePath);

    Ui::MainWindow *ui;
    QAction *m_penAction;
    QAction *m_colorAction;
    QColor m_color;
    QImage m_image;
};
