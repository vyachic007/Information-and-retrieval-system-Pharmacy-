#ifndef DRUG_H
#define DRUG_H
#include <QString>

// Базовый класс Drug
class Drug
{
private:
    QString m_name;
    int m_price;
    int m_quantity;
     QString info;  ///

public:
    Drug(QString name, int price, int quantity)
        : m_name(name), m_price(price), m_quantity(quantity) {}

    virtual ~Drug() {}  //виртуальный диструктор

    QString getName() const { return m_name; }
    void setName(const QString& name) { m_name = name; }

    int getPrice() const { return m_price; }
    void setPrice(int price) { m_price = price; }

    int getQuantity() const { return m_quantity; }
    void setQuantity(int quantity) { m_quantity = quantity; }


    QString getInfo() const { return info; } // Метод для получения информации
    void setInfo(const QString &newInfo) { info = newInfo; } // Метод для установки информации

    virtual QString getType() const = 0;    //чисто виртуальная функция для получения типа
};




// Класс Antibiotic, наследуемый от Drug
class Antibiotic : public Drug
{
private:
    QString m_sideEffects; //Побочные эффекты

public:
    Antibiotic(QString name, int price, int quantity, QString sideEffects)
        : Drug(name, price, quantity), m_sideEffects(sideEffects) {}

    QString getType() const override { return "Antibiotic"; }

    QString getSideEffects() const { return m_sideEffects; }
    void setSideEffects(QString sideEffects) { m_sideEffects = sideEffects; }
};





// Класс Vitamin, наследуемый от Drug
class Vitamin : public Drug
{
private:
    QString m_vitaminComplex; //Витаминный комплекс

public:
    Vitamin(QString name, int price, int quantity, QString vitaminComplex)
        : Drug(name, price, quantity), m_vitaminComplex(vitaminComplex) {}

    QString getType() const override { return "Vitamin"; }

    QString getVitaminComplex() const { return m_vitaminComplex; }
    void setVitaminComplex(QString vitaminComplex) { m_vitaminComplex = vitaminComplex; }
};




// Класс Antipyretic, наследуемый от Drug
class Antipyretic : public Drug
{
private:
    int m_maxDosage; // Максимальная доза

public:
    Antipyretic(QString name, int price, int quantity, int maxDosage)
        : Drug(name, price, quantity), m_maxDosage(maxDosage) {}

    QString getType() const override { return "Antipyretic"; }

    int getMaxDosage() const { return m_maxDosage; }
    void setMaxDosage(int maxDosage) { m_maxDosage = maxDosage; }
};


#endif
