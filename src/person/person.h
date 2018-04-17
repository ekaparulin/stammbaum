#ifndef PERSON_PERSON_H
#define PERSON_PERSON_H

#include <QDateTime>


namespace person {

class Person {
public:
    Person();
    ~Person();

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QDateTime birthDate() const;
    void setBirthDate(const QDateTime &birthDate);

    QDateTime deathDate() const;
    void setDeathDate(const QDateTime &deathDate);

    bool alive() const;
    void setAlive(bool alive);

    int fatherId() const;
    void setFatherId(int fatherId);

    int motherId() const;
    void setMotherId(int motherId);

    int id() const;
    void setId(int id);

private:
    int         m_id {0};
    QString     m_firstName;
    QString     m_lastName;
    QDateTime   m_birthDate;
    QDateTime   m_deathDate;
    bool        m_alive;
    int         m_fatherId {0};
    int         m_motherId {0};
};

}
#endif // PERSON_PERSON_H
