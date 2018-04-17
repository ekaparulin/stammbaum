#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>

namespace person {
class Person;
}

namespace db {

class Manager {
public:
    using ManagerPtr = std::shared_ptr<Manager>;

    Manager(const QString&);

    bool addPerson(const person::Person&);
    bool updatePerson(const person::Person&);
    bool deletePerson(const int&);
    person::Person person(const int&);
    bool personExists(const QString&);
    bool deleteAll();
    void getAllPersons();

    static ManagerPtr defaultManager();

private:
    static const QString DATE_FORMAT;
    QSqlDatabase m_db;
};

} /* namespace db */

#endif // DB_MANAGER_H


//CREATE TABLE people(ids integer primary key, name text);
