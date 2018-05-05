#ifndef TREEWEBVIEW_H
#define TREEWEBVIEW_H

#include <QDir>
#include <QWebEngineView>

#include "db/dbmanager.h"

class TreeWebView : public QWebEngineView {
public:
    TreeWebView();

public slots:
    void reload();

private:
    void extractResourceDir(const QString& );
    void createCodeJs();
private:
    QDir m_appData;
    db::Manager::ManagerPtr m_dbmPtr;
};

#endif // TREEWEBVIEW_H
