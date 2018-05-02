#include "editparent.h"
#include "ui_editparent.h"
#include "people/person.h"

#include <QDebug>

#include <people/person.h>

EditParent::EditParent(QWidget *parent, people::Parent::Type t) :
    QDialog(parent),
    ui(new Ui::EditParent),
    m_type(t) {

    ui->setupUi(this);

    this->setWindowTitle(t == people::Parent::Type::Mother ? tr("Mother") : tr("Father"));

    m_model.setQuery("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people");
    ui->tableView->setModel(&m_model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addPerson()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveParent()));


}

EditParent::~EditParent() {
    delete ui;
}

people::Person::Gender EditParent::parentsGender() {
    switch(m_type) {
    case people::Parent::Type::Father:
        return people::Person::Gender::Male;
    case people::Parent::Type::Mother:
        return people::Person::Gender::Female;
    default:
        return people::Person::Gender::Unknown;
    }
}

void EditParent::selectParent(const QUuid& uuid) {
    qDebug() << uuid;
    for(int i = 0; i < m_model.rowCount(); ++i) {
        if(m_model.data(m_model.index(i, 0)).toString()
                .compare(uuid.toString()) != 0) {
            continue;
        }
        ui->tableView->setCurrentIndex(m_model.index(i, 0));
        break;
    }
}

void EditParent::edit(const std::shared_ptr<const people::Person>&p) {

    // Populate table filtered by parent gender
    m_query = QString("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people where SEX = %1")
              .arg(QString::number(static_cast<int>(parentsGender())));
    m_model.setQuery(m_query);
    show();

    if(p == nullptr) {
        return;
    }

    // Filter out yourself from parent list
    m_query += QString(" AND ID != \"%1\"").arg(p->id().toString());
    m_model.setQuery(m_query);

    // Filter out persons younger than people::Parent::MIN_AGE or
    // older than people::Parent::MAX_AGE but inlude ones w/o birth date
    people::Person::EventPtr dob = p->event(people::Event::Type::Birth);
    if(dob.use_count()) {
        m_query += QString(" AND (BIRTH_DATE IS NULL OR BIRTH_DATE BETWEEN \"%1\" AND \"%2\")")
                   .arg(dob->date().addYears(-1 * people::Parent::MAX_AGE).toString(db::Manager::DATE_FORMAT))
                   .arg(dob->date().addYears(-1 * people::Parent::MIN_AGE).toString(db::Manager::DATE_FORMAT));
        m_model.setQuery(m_query);
    }

    // Highlight parent if set
    if(p->parent(m_type).use_count()) {
        selectParent(*(p->parent(m_type).get()));
    }
}

void EditParent::addPerson() {
    // TODO: static_cast
    // TODO: preset gender with m_type
    m_ep = std::make_shared<EditPerson>((QWidget *) QDialog::parent());
    m_ep->add(true);
    m_ep->setGender(parentsGender());
    connect(m_ep.get(), SIGNAL(save(const people::Base*)), this, SLOT(savePerson(const people::Base*)));

}

void EditParent::saveParent() {
    emit save(QUuid::fromString(m_model.data(m_model.index(ui->tableView->currentIndex().row(), 0)).toString()));
}

void EditParent::savePerson(const people::Base *b) {

    const people::Person *p = static_cast<const people::Person*>(b);
    db::Manager::ManagerPtr dbm = db::Manager::instance();
    dbm->addPerson(p);

    qDebug() << static_cast<const people::Person*>(b)->id();
    m_model.setQuery(m_query);
    selectParent(p->id());

    // TODO: select newly added person
}
