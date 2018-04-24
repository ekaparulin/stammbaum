#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>

namespace people {
class Person;
}

namespace db {

class Manager {
public:
    using ManagerPtr = std::shared_ptr<Manager>;

    Manager(const QString&);

    bool addPerson(const people::Person*);
    bool updatePerson(const people::Person*);
    bool deletePerson(const QUuid&);
    std::shared_ptr<people::Person> person(const QUuid&);

    static ManagerPtr defaultManager();

private:
    static const QString DATE_FORMAT;
    QSqlDatabase m_db;
};

} /* namespace db */

#endif // DB_MANAGER_H


//CREATE TABLE people(ids integer primary key, name text);
