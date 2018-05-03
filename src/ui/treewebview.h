#ifndef TREEWEBVIEW_H
#define TREEWEBVIEW_H

#include <QDir>
#include <QWebEngineView>

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
};

#endif // TREEWEBVIEW_H
