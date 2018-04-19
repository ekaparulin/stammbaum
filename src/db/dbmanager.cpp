#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QStandardPaths>

#include "people/person.h"

namespace db {

const QString Manager::DATE_FORMAT = "yyyy-MM-dd hh:mm:ss.000";

Manager::Manager(const QString& path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail";
        return;
    }

    qDebug() << "Database: connection ok";

    QSqlQuery query;
    query.prepare(R"(
                  CREATE TABLE IF NOT EXISTS people(
                      ID INTEGER PRIMARY KEY AUTOINCREMENT,
                      FAMILY_NAME TEXT,
                      FIRST_NAME TEXT NOT NULL,
                      BIRTH_DATE DATE,
                      DEATH_DATE DATE,
                      ALIVE BOOLEAN,
                      FATHER_ID INTEGER,
                      MOTHER_ID INTEGER
                      );
                  )"
                 );
    if(query.exec()) {
        return;
    }

    qDebug() << query.lastError();

}

bool Manager::addPerson(const people::Person *p) {
    bool success = false;
    QSqlQuery query;
    query.prepare(R"(
                      INSERT INTO people(
                          FAMILY_NAME,
                          FIRST_NAME,
                          BIRTH_DATE,
                          DEATH_DATE,
                          ALIVE,
                          FATHER_ID,
                          MOTHER_ID
                      ) values (
                          :FAMILY_NAME,
                          :FIRST_NAME,
                          :BIRTH_DATE,
                          :DEATH_DATE,
                          :ALIVE,
                          :FATHER_ID,
                          :MOTHER_ID
                      ))");
    query.bindValue(":FAMILY_NAME", p->lastName());
    query.bindValue(":FIRST_NAME",  p->firstName());

    try {
        query.bindValue(":BIRTH_DATE",  p->event(people::Event::Type::Birth).date().toString(DATE_FORMAT));
    } catch(std::exception e) {

    }
    try {
        query.bindValue(":DEATH_DATE",  p->event(people::Event::Type::Death).date().toString(DATE_FORMAT));
    } catch(std::exception e) {

    }

    query.bindValue(":ALIVE",       p->alive());
    query.bindValue(":FATHER_ID",   p->fatherId());
    query.bindValue(":MOTHER_ID",   p->motherId());

    if(query.exec()) {
        success = true;
    } else {
        qDebug() << __FUNCTION__ << " error:  "
                 << query.lastError();
    }

    return success;
}

bool Manager::updatePerson(const people::Person *p) {
    bool success = false;
    QSqlQuery query;

    QString dates;

    query.prepare(R"(
                      UPDATE people SET
                          FAMILY_NAME = :FAMILY_NAME,
                          FIRST_NAME = :FIRST_NAME,
                          BIRTH_DATE = :BIRTH_DATE,
                          DEATH_DATE = :DEATH_DATE,
                          ALIVE = :ALIVE,
                          FATHER_ID = :FATHER_ID,
                          MOTHER_ID = :MOTHER_ID
                      WHERE ID = :ID
                      )");
    query.bindValue(":ID", p->id());
    query.bindValue(":FAMILY_NAME", p->lastName());
    query.bindValue(":FIRST_NAME",  p->firstName());
    try {
        query.bindValue(":BIRTH_DATE",  p->event(people::Event::Type::Birth).date().toString(DATE_FORMAT));
    } catch(std::exception e) {

    }
    try {
        query.bindValue(":DEATH_DATE",  p->event(people::Event::Type::Death).date().toString(DATE_FORMAT));
    } catch(std::exception e) {

    }
    query.bindValue(":ALIVE",       p->alive());
    query.bindValue(":FATHER_ID",   p->fatherId());
    query.bindValue(":MOTHER_ID",   p->motherId());

    if(query.exec()) {
        success = true;
    } else {
        qDebug() << __FUNCTION__ << " error:  "
                 << query.lastError();
    }

    return success;
}

bool Manager::deletePerson(const int &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM people WHERE ID = (:id)");
    query.bindValue(":id", id);
    return query.exec();
}

std::shared_ptr<people::Person> Manager::person(const int &id) {
    QSqlQuery query("SELECT * FROM people WHERE ID = " + QString::number(id));
    if(!query.exec()) {
        qDebug() << __FUNCTION__ << " error:  " << query.lastError();
    }

    auto p = std::make_shared<people::Person>();
    p->setId(id);
    auto lastNameIdx = query.record().indexOf("FAMILY_NAME");
    auto firstNameIdx = query.record().indexOf("FIRST_NAME");
    auto birthNameIdx = query.record().indexOf("BIRTH_DATE");
    auto deathDateIdx = query.record().indexOf("DEATH_DATE");
    auto aliveIdx = query.record().indexOf("ALIVE");
    auto fatherIdIdx = query.record().indexOf("FATHER_ID");
    auto motherIdIdx = query.record().indexOf("MOTHER_ID");

    while (query.next()) {
        p->setLastName(query.value(lastNameIdx).toString());
        p->setFirstName(query.value(firstNameIdx).toString());


        if(!query.value(birthNameIdx).isNull()) {
            p->addEvent(people::Event(people::Event::Type::Birth, QDateTime::fromString(query.value(birthNameIdx).toString(), DATE_FORMAT)));
        }
        if(!query.value(deathDateIdx).isNull()) {
            p->addEvent(people::Event(people::Event::Type::Death, QDateTime::fromString(query.value(deathDateIdx).toString(), DATE_FORMAT)));
        }
        qDebug() << __FUNCTION__ << " " << query.value(birthNameIdx).toString() << " " << query.value(birthNameIdx).isNull() ;
        qDebug() << __FUNCTION__ << " " << query.value(deathDateIdx).toString();


        p->setAlive(query.value(aliveIdx).toBool());
        p->setFatherId(query.value(fatherIdIdx).toInt());
        p->setMotherId(query.value(motherIdIdx).toInt());
    }

    return p;
}

bool Manager::personExists(const QString &name) {
    QSqlQuery query;
    query.prepare("SELECT name FROM people WHERE name = (:name)");
    query.bindValue(":name", name);

    if (query.exec()) {
        return query.next();
    }
    return false;
}

bool Manager::deleteAll() {
    QSqlQuery query;
    query.prepare("DELETE FROM people");
    query.exec();
    return true;
}

void Manager::getAllPersons() {
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next()) {
        QString name = query.value(idName).toString();
        qDebug() << name;
    }
}

Manager::ManagerPtr Manager::defaultManager() {
    QDir appData = QDir(
                       QStandardPaths::writableLocation(
                           QStandardPaths::AppDataLocation));

    if(!appData.exists()) {
        appData.mkdir(appData.absolutePath());
    }

    return std::make_shared<Manager>(appData.filePath("persons.db"));
}

} /* namespace db */
