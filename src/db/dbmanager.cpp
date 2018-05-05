#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QStandardPaths>

#include "dbmanager.h"
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
                      ID VARCHAR PRIMARY KEY,
                      FAMILY_NAME TEXT,
                      FIRST_NAME TEXT NOT NULL,
                      SEX INTEGER,
                      BIRTH_DATE DATE,
                      DEATH_DATE DATE,
                      ALIVE BOOLEAN,
                      FATHER_ID VARCHAR,
                      MOTHER_ID VARCHAR
                      );
                  )"
                 );
    if(query.exec()) {
        return;
    }

    qDebug() << query.lastError();

}

Manager::~Manager() {
    qDebug() << __FUNCTION__;
}

bool Manager::addPerson(const people::Person *p) {
    bool success = false;
    QSqlQuery query;
    query.prepare(R"(
                      INSERT INTO people(
                          ID,
                          FAMILY_NAME,
                          FIRST_NAME,
                          SEX,
                          BIRTH_DATE,
                          DEATH_DATE,
                          ALIVE,
                          FATHER_ID,
                          MOTHER_ID
                      ) values (
                          :ID,
                          :FAMILY_NAME,
                          :FIRST_NAME,
                          :SEX,
                          :BIRTH_DATE,
                          :DEATH_DATE,
                          :ALIVE,
                          :FATHER_ID,
                          :MOTHER_ID
                      ))");
    query.bindValue(":ID", p->id().toString());
    query.bindValue(":FAMILY_NAME", p->lastName());
    query.bindValue(":FIRST_NAME",  p->firstName());
    query.bindValue(":SEX",  static_cast<int>(p->gender()));

    if(p->event(people::Event::Type::Birth).use_count()) {
        query.bindValue(":BIRTH_DATE",  p->event(people::Event::Type::Birth)->date().toString(DATE_FORMAT));
    }

    if(p->event(people::Event::Type::Death).use_count()) {
        query.bindValue(":DEATH_DATE",  p->event(people::Event::Type::Death)->date().toString(DATE_FORMAT));
    }

    query.bindValue(":ALIVE",       p->alive());
    if(p->parent(people::Parent::Type::Father) != nullptr)
        query.bindValue(":FATHER_ID",   p->parent(people::Parent::Type::Father)->toString());

    if(p->parent(people::Parent::Type::Mother) != nullptr)
        query.bindValue(":MOTHER_ID",   p->parent(people::Parent::Type::Mother)->toString());

    if(query.exec()) {
        success = true;
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    } else {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__
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
                          SEX = :SEX,
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
    query.bindValue(":SEX", static_cast<int>(p->gender()));

    if(p->event(people::Event::Type::Birth).use_count()) {
        query.bindValue(":BIRTH_DATE",
                        p->event(people::Event::Type::Birth)->date()
                        .toString(DATE_FORMAT));
    }
    if(p->event(people::Event::Type::Death).use_count()) {
        query.bindValue(":DEATH_DATE",
                        p->event(people::Event::Type::Death)->date()
                        .toString(DATE_FORMAT));
    }
    query.bindValue(":ALIVE",       p->alive());
    if(p->parent(people::Parent::Type::Father).use_count()) {
        query.bindValue(":FATHER_ID",
                        p->parent(people::Parent::Type::Father)->toString());
    }
    if(p->parent(people::Parent::Type::Mother).use_count()) {
        query.bindValue(":MOTHER_ID",
                        p->parent(people::Parent::Type::Mother)->toString());
    }

    if(query.exec()) {
        success = true;
    } else {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__
                 << query.lastError();
    }

    return success;
}

bool Manager::deletePerson(const QUuid &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM people WHERE ID = (:id)");
    query.bindValue(":id", id.toString());
    return query.exec();
}

std::shared_ptr<people::Person> Manager::person(const QUuid &id) {
    QSqlQuery query("SELECT * FROM people WHERE ID = \""+ id.toString()+"\"");
    if(!query.exec()) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__
                 << query.lastError();
    }

    auto p = std::make_shared<people::Person>(id);
    auto lastNameIdx = query.record().indexOf("FAMILY_NAME");
    auto firstNameIdx = query.record().indexOf("FIRST_NAME");
    auto sexIdx = query.record().indexOf("SEX");
    auto birthDateIdx = query.record().indexOf("BIRTH_DATE");
    auto deathDateIdx = query.record().indexOf("DEATH_DATE");
    auto aliveIdx = query.record().indexOf("ALIVE");
    auto fatherIdIdx = query.record().indexOf("FATHER_ID");
    auto motherIdIdx = query.record().indexOf("MOTHER_ID");

    while (query.next()) {
        p->setLastName(query.value(lastNameIdx).toString());
        p->setFirstName(query.value(firstNameIdx).toString());
        p->setGender(static_cast<people::Person::Gender>(query.value(sexIdx).toInt()));

        if(!query.value(birthDateIdx).isNull()) {
            p->addEvent(people::Event(people::Event::Type::Birth, QDateTime::fromString(query.value(birthDateIdx).toString(), DATE_FORMAT)));
        }
        if(!query.value(deathDateIdx).isNull()) {
            p->addEvent(people::Event(people::Event::Type::Death, QDateTime::fromString(query.value(deathDateIdx).toString(), DATE_FORMAT)));
        }

        p->setAlive(query.value(aliveIdx).toBool());
        p->addParent(people::Parent::Type::Father, QUuid(query.value(fatherIdIdx).toString()));
        p->addParent(people::Parent::Type::Mother, QUuid(query.value(motherIdIdx).toString()));
    }

    return p;
}

QString Manager::treeNodes() const {
    QStringList ret;

    QSqlQuery query("SELECT * FROM people ORDER BY BIRTH_DATE");
    if(!query.exec()) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__
                 << query.lastError();
    }

    auto idIdx = query.record().indexOf("ID");
    auto lastNameIdx = query.record().indexOf("FAMILY_NAME");
    auto firstNameIdx = query.record().indexOf("FIRST_NAME");
    auto sexIdx = query.record().indexOf("SEX");
    /*auto birthDateIdx = query.record().indexOf("BIRTH_DATE");
    auto deathDateIdx = query.record().indexOf("DEATH_DATE");
    auto aliveIdx = query.record().indexOf("ALIVE");
    auto fatherIdIdx = query.record().indexOf("FATHER_ID");
    auto motherIdIdx = query.record().indexOf("MOTHER_ID");
    */
    while (query.next()) {
        // TODO: Replace with real images, once they will be stored in DB

        QString image;
        switch (static_cast<people::Person::Gender>(query.value(sexIdx).toInt())) {
        case people::Person::Gender::Female:
            image = "./female.png";
        case people::Person::Gender::Male:
            image = "./male.png";
        case people::Person::Gender::Unknown:
            image = "./unknown.png";
        }
        ret << QString("{ data: { id: '%1', content: '%2', background_image: '%3' }}")
            .arg(query.value(idIdx).toString())
            .arg(query.value(firstNameIdx).toString() + " " + query.value(lastNameIdx).toString())
            .arg(image);

    }
    return ret.join(",");
}

QString Manager::treeEdges() const {
    QStringList ret;

    QSqlQuery query("SELECT ID, FATHER_ID, MOTHER_ID  FROM people");
    if(!query.exec()) {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__
                 << query.lastError();
    }

    auto idIdx = query.record().indexOf("ID");
    auto fatherIdIdx = query.record().indexOf("FATHER_ID");
    auto motherIdIdx = query.record().indexOf("MOTHER_ID");

    while (query.next()) {

        if(!QUuid(query.value(fatherIdIdx).toString()).isNull()) {
            ret << QString("{ data: { source: '%1', target: '%2' }}")
                .arg(query.value(fatherIdIdx).toString())
                .arg(query.value(idIdx).toString());
        }
        if(!QUuid(query.value(motherIdIdx).toString()).isNull()) {
            ret << QString("{ data: { source: '%1', target: '%2' }}")
                .arg(query.value(motherIdIdx).toString())
                .arg(query.value(idIdx).toString());
        }
    }

    return ret.join(",");
}

Manager::ManagerPtr Manager::instance() {

    QDir appData = QDir(
                       QStandardPaths::writableLocation(
                           QStandardPaths::AppDataLocation));

    if(!appData.exists()) {
        appData.mkdir(appData.absolutePath());
    }

    static ManagerPtr  s = std::shared_ptr<Manager>(new Manager(appData.filePath("persons.db")));
    return s;

}

} /* namespace db */
