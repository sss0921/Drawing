/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include <QMenu>
#include <memory>

class RecentFilesMenuPrivate;
class RecentFilesMenu : public QMenu
{
    Q_OBJECT
public:
    RecentFilesMenu(QWidget *parent = nullptr);
    RecentFilesMenu(const QString &title, QWidget *parent = nullptr);
    ~RecentFilesMenu();

    int maxCount() const;
    int count() const;
    QString recentFile(int index = 0) const;

    QByteArray saveRecentFiles() const;
    bool restoreRecentFiles(const QByteArray &data);

public slots:
    void addRecentFile(const QString &filePath);
    void clearRecentFiles();
    void setMaxCount(int count);

signals:
    void recentFileTriggered(const QString &filePath);

protected:
    void showEvent(QShowEvent *event);

private:
    std::unique_ptr<RecentFilesMenuPrivate> d;
};
