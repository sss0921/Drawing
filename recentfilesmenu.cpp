/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include "recentfilesmenu.h"

#include <QAction>
#include <QDataStream>

class RecentFilesMenuPrivate
{
public:
    RecentFilesMenuPrivate(RecentFilesMenu *q);

    void updateActions();
    void onActionTriggered(const QString &filePath);

    int maxCount;
    QStringList filePaths;
    bool dirty;
    RecentFilesMenu *q;

    static quint32 magic;
};

quint32 RecentFilesMenuPrivate::magic = 0x99887766;

RecentFilesMenuPrivate::RecentFilesMenuPrivate(RecentFilesMenu *q)
    : maxCount(10)
    , dirty(true)
    , q(q)
{
    q->setDisabled(true);
}

void RecentFilesMenuPrivate::updateActions()
{
    if (!dirty)
        return;
    dirty = false;

    q->clear();
    foreach (QString filePath, filePaths) {
        QAction *act = new QAction(filePath, q);
        q->connect(act, &QAction::triggered, q,
                   [this, filePath]() { this->onActionTriggered(filePath); });
        q->addAction(act);
    }
    q->addSeparator();
    QAction *act = new QAction(q->tr("Clear Menu"), q);
    q->connect(act, &QAction::triggered, q, &RecentFilesMenu::clearRecentFiles);
    q->addAction(act);
}

void RecentFilesMenuPrivate::onActionTriggered(const QString &filePath)
{
    emit q->recentFileTriggered(filePath);
}

RecentFilesMenu::RecentFilesMenu(QWidget *parent)
    : QMenu(parent)
    , d(new RecentFilesMenuPrivate(this))
{
}

RecentFilesMenu::RecentFilesMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
    , d(new RecentFilesMenuPrivate(this))
{
}

RecentFilesMenu::~RecentFilesMenu()
{
}

int RecentFilesMenu::maxCount() const
{
    return d->maxCount;
}

int RecentFilesMenu::count() const
{
    return d->filePaths.count();
}

QString RecentFilesMenu::recentFile(int index) const
{
    if (index >= 0 && index < d->filePaths.size())
        return d->filePaths.at(index);
    return QString();
}

QByteArray RecentFilesMenu::saveRecentFiles() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << d->magic;
    stream << d->filePaths;
    return data;
}

bool RecentFilesMenu::restoreRecentFiles(const QByteArray &data)
{
    QDataStream stream(data);
    quint32 magic;
    stream >> magic;
    if (magic != d->magic)
        return false;
    stream >> d->filePaths;
    d->dirty = true;
    setDisabled(d->filePaths.isEmpty());
    return true;
}

void RecentFilesMenu::addRecentFile(const QString &filePath)
{
    if (recentFile(0) == filePath)
        return;

    d->filePaths.removeOne(filePath);
    d->filePaths.prepend(filePath);

    while (d->filePaths.count() > d->maxCount)
        d->filePaths.removeLast();

    d->dirty = true;
    setEnabled(true);
}

void RecentFilesMenu::clearRecentFiles()
{
    d->filePaths.clear();
    d->dirty = true;
    setEnabled(false);
}

void RecentFilesMenu::setMaxCount(int count)
{
    if (d->maxCount == count)
        return;

    d->maxCount = count;

    while (d->filePaths.count() > d->maxCount)
        d->filePaths.removeLast();
    d->dirty = true;
}

void RecentFilesMenu::showEvent(QShowEvent *event)
{
    d->updateActions();
    QMenu::showEvent(event);
}
