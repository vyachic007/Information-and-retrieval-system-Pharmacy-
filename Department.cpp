#include "Department.h"

//Конструктор класса Department, который инициализирует все поля класса
Department::Department(QString name, QString pharmacist, QString phoneNumber)
    : m_name(name), m_pharmacist(pharmacist), m_phoneNumber(phoneNumber),
    m_drugsHead(nullptr), m_drugsTail(nullptr), m_next(nullptr) {}

/* создается новый узел списка лекарств с помощью оператора new,
который выделяет память для нового объекта DrugNode. Затем этот новый узел добавляется в конец списка лекарств отдела */

void Department::addDrug(Drug* drug)
{
    //Проверка, что лекарство не является nullptr
    if (drug) {
        //Если это первое лекарство в отделе, устанавливает его как голову и хвост списка лекарств
        if (!m_drugsHead)
        {
            m_drugsHead = new DrugNode(drug, 0);
            m_drugsTail = m_drugsHead;
        } else {
            //Если это не первое лекарство, добавляет его в конец списка и обновляет хвост списка
            DrugNode* newNode = new DrugNode(drug, 0);
            m_drugsTail->setNext(newNode);
            m_drugsTail = newNode;
        }
    }
}

//Геттеры и сеттеры для полей класса
DrugNode* Department::getDrugsHead() const {
    return m_drugsHead;
}

Department* Department::getNext() const {
    return m_next;
}

void Department::setDrugsHead(DrugNode* head) {
    m_drugsHead = head;
}

DrugNode* Department::getDrugsTail() const {
    return m_drugsTail;
}

void Department::setDrugsTail(DrugNode* tail) {
    m_drugsTail = tail;
}

QString Department::getName() const {
    return m_name;
}

void Department::setNext(Department* next) {
    m_next = next;
}

QString Department::getPharmacist() const {
    return m_pharmacist;
}

QString Department::getPhoneNumber() const {
    return m_phoneNumber;
}

void Department::setName(const QString& name) {
    m_name = name;
}

void Department::setPharmacist(const QString& pharmacist) {
    m_pharmacist = pharmacist;
}

void Department::setPhoneNumber(const QString& phoneNumber) {
    m_phoneNumber = phoneNumber;
}
