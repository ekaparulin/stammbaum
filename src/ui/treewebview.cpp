#include "treewebview.h"
#include "db/dbmanager.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>

TreeWebView::TreeWebView():
    m_appData(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))),
    m_dbmPtr(db::Manager::instance()) {

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
    createCodeJs();
    QWebEngineView::reload();
}

void TreeWebView::extractResourceDir(const QString& dir) {
    if(!m_appData.exists(dir)) {
        m_appData.mkpath(dir);
    }
    for(QString file: QDir(QString(":/%1").arg(dir)).entryList()) {
        QString dest(QString("%1%2%3%4%5")
                     .arg(m_appData.absolutePath())
                     .arg(QDir::separator())
                     .arg(dir)
                     .arg(QDir::separator())
                     .arg(file));

        QFile destFile(dest);
        if(destFile.exists()) {
            destFile.remove();
        }
        QFile::copy(QString(":/%1/%2").arg(dir).arg(file), dest);

    }
}

void TreeWebView::createCodeJs() {

    QFile codeJsTmplFile(m_appData.absolutePath() + "/www/tree/code.js.tmpl");

    if (!codeJsTmplFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << __FILE__ << __LINE__ << "Can't read " <<  codeJsTmplFile.fileName();
        return;
    }

    QTextStream in(&codeJsTmplFile);
    QString codeJsTmpl(codeJsTmplFile.readAll());
    codeJsTmplFile.close();

    QFile codeJsFile(m_appData.absolutePath() + "/www/tree/code.js");
    if(!codeJsFile.open(QFile::Truncate | QFile::WriteOnly | QFile::Text)) {
        qDebug() << __FILE__ << __LINE__ << "Can't write to " <<  codeJsFile.fileName();
        return;
    }

    QTextStream stream(&codeJsFile);
    stream << codeJsTmpl.arg(m_dbmPtr->treeNodes()).arg(m_dbmPtr->treeEdges()) << endl;
    codeJsFile.close();
}
