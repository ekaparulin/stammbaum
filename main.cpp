#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include "genealogy/person.h"
#include "genealogy/familyname.h"
#include "genealogy/family.h"

int main(int argc, char *argv[])
{

    genealogy::Person p;
    p.addName("Константин");
    p.addFamilyName(genealogy::FamilyName("Капарулин"));
    qDebug() << p.toString();

    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");





    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/pages/main.qml")));

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("myModel", QVariant::fromValue(dataList));

    return app.exec();
}
