#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QString>
#include "Drug.h"




class DrugNode {
private:
    Drug* drug; //указатель н объект
    DrugNode* next;
    int index; // Новое поле для хранения индекса лекарства
public:
    // Конструктор и методы доступа
    DrugNode(Drug* d, int i) : drug(d), next(nullptr), index(i) {} // Инициализация индекса в конструкторе
    Drug* getDrug() { return drug; }
    DrugNode* getNext() { return next; }
    void setNext(DrugNode* n) { next = n; }
    int getIndex() { return index; }
};



class Department     // Определение класса ОТДЕЛОВ
{
private:
    QString m_name;
    QString m_pharmacist;
    QString m_phoneNumber;
    DrugNode* m_drugsHead;     // Указатель на начало списка лекарств
    DrugNode* m_drugsTail;    // Указатель на конец списка лекарств
    Department* m_next;     // Указатель на следующий отдел в списке


public:
    Department(QString name, QString pharmacist, QString phoneNumber);  // Конструктор класса

    QString getName() const;  //Геттер для имени отдела
    void setName(const QString& name);  //Сеттер для имени отдела

    QString getPharmacist() const;  //Геттер для имени фармацевта
    void setPharmacist(const QString& pharmacist);  //Сеттер для имени фармацевта

    QString getPhoneNumber() const;  //Геттер для номера телефона
    void setPhoneNumber(const QString& phoneNumber);  //Сеттер для номера телефона

    void addDrug(Drug* drug);  //Метод для добавления лекарства в список


    DrugNode* getDrugsHead() const;    //Геттер для головы списка лекарств
    DrugNode* getDrugsTail() const;    //Геттер для хвоста списка лекарств
    void setDrugsHead(DrugNode* head);  //Сеттер для головы списка лекарств
    void setDrugsTail(DrugNode* tail);  //Сеттер для хвоста списка лекарств

    Department* getNext() const;  //Геттер для следующего отдела в списке
    void setNext(Department* next);  //Сеттер для следующего отдела в списке
};


#endif

/*при добавлении нового лекарства в отдел, создается  новый объект DrugNode,
в котором указатель drug указывает на новый объект Vitamin, Antibiotic
 или Antipyretic. Затем добавляется этот DrugNode в двусвязный список лекарств для соответствующего отдела*/
