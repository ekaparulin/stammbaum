#include "treewebview.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>



TreeWebView::TreeWebView():
    m_appData(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))) {

    if(!m_appData.exists()) {
        m_appData.mkdir(m_appData.absolutePath());
    }

    extractResourceDir("js");
    extractResourceDir(QString("www%1tree").arg(QDir::separator()));

    createCodeJs();
    load(QUrl::fromLocalFile(m_appData.absolutePath() + "/www/tree/index.html"));
    show();
}

void TreeWebView::reload() {
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    createCodeJs();
    QWebEngineView::reload();
}

void TreeWebView::extractResourceDir(const QString& dir) {
    if(!m_appData.exists(dir)) {
        m_appData.mkpath(dir);
    }
    for(QString file: QDir(QString(":/%1").arg(dir)).entryList()) {
        QFile::copy(QString(":/%1/%2").arg(dir).arg(file),
                    QString("%1%2%3%4%5")
                    .arg(m_appData.absolutePath())
                    .arg(QDir::separator())
                    .arg(dir)
                    .arg(QDir::separator())
                    .arg(file)
                   );

    }
}

void TreeWebView::createCodeJs() {
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    // TODO: populate code.js from DB
    QFile::copy(m_appData.absolutePath() + "/www/tree/code.js.tmpl",
                m_appData.absolutePath() + "/www/tree/code.js");
}
