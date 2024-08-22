#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QToolBar>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QScrollArea>
#include <QDialog>
#include <QVBoxLayout>
#include "Department.h"
#include <QFormLayout>
#include <QSpinBox>
#include "Department.h"
#include <QCloseEvent>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpression>
#include <QRegularExpression>




//ГЛАВНОЕ ОКНО

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , firstDepartment(nullptr)
{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: #F0FFFF; }");

    // Создание таблицы
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Антибиотик" << "Витамины" << "Жаропонижающее");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Соединение кнопок с соответствующими слотами
    connect(ui->addDrugButton, &QPushButton::clicked, this, &MainWindow::onAddDrugButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditButtonClicked);
    connect(ui->createDepartmentButton, &QPushButton::clicked, this, &MainWindow::onCreateDepartmentClicked);
    connect(ui->departmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onDepartmentChanged(int)));
    connect(ui->deleteDepartmentButton, &QPushButton::clicked, this, &MainWindow::onDeleteDepartmentClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::openSearchWindow);
    connect(ui->editDepartmentButton, &QPushButton::clicked, this, &MainWindow::onEditDepartmentButtonClicked);
    connect(ui->departmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onDepartmentComboBoxIndexChanged(int)));








    // Создание и применение тени для кнопок
    QGraphicsDropShadowEffect* createDepartmentShadow = new QGraphicsDropShadowEffect();
    createDepartmentShadow->setBlurRadius(7);
    createDepartmentShadow->setXOffset(4);
    createDepartmentShadow->setYOffset(4);
    createDepartmentShadow->setColor(QColor(0, 128, 128, 80));
    ui->createDepartmentButton->setGraphicsEffect(createDepartmentShadow);

    QGraphicsDropShadowEffect* addDrugShadow = new QGraphicsDropShadowEffect();
    addDrugShadow->setBlurRadius(7);
    addDrugShadow->setXOffset(4);
    addDrugShadow->setYOffset(4);
    addDrugShadow->setColor(QColor(0, 0, 0, 80));
    ui->addDrugButton->setGraphicsEffect(addDrugShadow);

    QGraphicsDropShadowEffect* deleteButtonShadow = new QGraphicsDropShadowEffect();
    deleteButtonShadow->setBlurRadius(7);
    deleteButtonShadow->setXOffset(4);
    deleteButtonShadow->setYOffset(4);
    deleteButtonShadow->setColor(QColor(0, 0, 0, 80));
    ui->deleteButton->setGraphicsEffect(deleteButtonShadow);

    QGraphicsDropShadowEffect* deleteDepartmentShadow = new QGraphicsDropShadowEffect();
    deleteDepartmentShadow->setBlurRadius(7);
    deleteDepartmentShadow->setXOffset(4);
    deleteDepartmentShadow->setYOffset(4);
    deleteDepartmentShadow->setColor(QColor(0, 0, 0, 80));
    ui->deleteDepartmentButton->setGraphicsEffect(deleteDepartmentShadow);

    QGraphicsDropShadowEffect* editButtonShadow = new QGraphicsDropShadowEffect();
    editButtonShadow->setBlurRadius(7);
    editButtonShadow->setXOffset(4);
    editButtonShadow->setYOffset(4);
    editButtonShadow->setColor(QColor(0, 0, 0, 80));
    ui->editButton->setGraphicsEffect(editButtonShadow);

    QGraphicsDropShadowEffect* editDepartmentShadow = new QGraphicsDropShadowEffect();
    editDepartmentShadow->setBlurRadius(7);
    editDepartmentShadow->setXOffset(4);
    editDepartmentShadow->setYOffset(4);
    editDepartmentShadow->setColor(QColor(0, 0, 0, 80));
    ui->editDepartmentButton->setGraphicsEffect(editDepartmentShadow);

    QGraphicsDropShadowEffect* searchButtonShadow = new QGraphicsDropShadowEffect();
    searchButtonShadow->setBlurRadius(7);
    searchButtonShadow->setXOffset(4);
    searchButtonShadow->setYOffset(4);
    searchButtonShadow->setColor(QColor(0, 0, 0, 80));
    ui->searchButton->setGraphicsEffect(searchButtonShadow);

    QGraphicsDropShadowEffect* departmentComboBoxShadow = new QGraphicsDropShadowEffect();
    departmentComboBoxShadow->setBlurRadius(6);
    departmentComboBoxShadow->setXOffset(3);
    departmentComboBoxShadow->setYOffset(3);
    departmentComboBoxShadow->setColor(QColor(0, 0, 0, 40));
    ui->departmentComboBox->setGraphicsEffect(departmentComboBoxShadow);

    // Установка прозрачности для кнопок
    ui->createDepartmentButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(127, 255, 212, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(64, 224, 208, 0.58);"
        "    color: #ffffff;"
        "}"
        );

    ui->addDrugButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(127, 255, 212, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(64, 224, 208, 0.58);"
        "    color: #ffffff;"
        "}"
        );
    ui->deleteButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(239, 154, 154, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(229, 57, 53, 0.58);"
        "    color: #ffffff;"
        "}"
        );

    ui->deleteDepartmentButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(239, 154, 154, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(229, 57, 53, 0.58);"
        "    color: #ffffff;"
        "}"
        );

    ui->editButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(255, 183, 77, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(245, 124, 0, 0.58);"
        "    color: #ffffff;"
        "}"
        );


    ui->editDepartmentButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(255, 183, 77, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(245, 124, 0, 0.58);"
        "    color: #ffffff;"
        "}"
        );

    ui->searchButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(129, 212, 250, 0.58);"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(3, 169, 244, 0.58);"
        "    color: #ffffff;"
        "}"
        );




    ui->departmentComboBox->setStyleSheet(
        "QComboBox {"
        "    background-color: rgba(175, 238, 238, 0.58);"
        "    color: #000000;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "}"

        );



    //Создание главного меню
    QMenuBar* menuBar = new QMenuBar;      // Создание новой панели меню
    QMenu* fileMenu = new QMenu(tr("Файл"), this);  // Создание нового меню "Файл"
    QMenu* helpMenu = new QMenu(tr("Справка"), this);   // Создание нового меню "Справка"

    //Добавление подпунктов в меню "Файл"
    fileMenu->addAction(tr("Создать"), this, SLOT(createFile()));
    fileMenu->addAction(tr("Открыть…"), this, SLOT(openFile()));
    fileMenu->addAction(tr("Сохранить"), this, SLOT(saveFile()));
    fileMenu->addAction(tr("Сохранить как…"), this, SLOT(saveFileAs()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Выход"), this, SLOT(close()));



    //Добавление подпунктов в меню "Справка"
    helpMenu->addAction(tr("Руководство"), this, SLOT(showGuide()));
    helpMenu->addAction(tr("О программе"), this, SLOT(showAbout()));

    menuBar->addMenu(fileMenu);  // Добавление меню "Файл" на панель меню
    menuBar->addMenu(helpMenu);  // Добавление меню "Справка" на панель меню

    //Установка меню
    this->setMenuBar(menuBar);
}



MainWindow::~MainWindow()  // Деструктор класса MainWindow
{
    delete ui;  //Удаление объекта интерфейса пользователя

    //Удаление списка отделов
    while (firstDepartment)  //Пока есть отделы в списке…
    {
        Department* nextDepartment = firstDepartment->getNext();  //Получение следующего отдела
        delete firstDepartment;  //Удаление текущего отдела
        firstDepartment = nextDepartment;  //Переход к следующему отделу
    }
}


//ВЫХОД
void MainWindow::closeEvent(QCloseEvent *event)
{
    static bool shown = false;
    if (!shown)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение", "Вы уверены, что хотите выйти?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)  // Если пользователь подтвердил выход...
        {
            shown = true;
            event->accept();  // ...принять событие закрытия, и приложение закроется
        } else {
            event->ignore();  // ...игнорировать событие закрытия, и приложение продолжит работать
        }
    } else {
        event->accept();
    }
}









//ДОБАВЛЕНИЯ ЛЕКАРСТВА
void MainWindow::onAddDrugButtonClicked()
{
    // Получаю текущий выбранный отдел
    Department* currentDepartment = firstDepartment;  // Начало с первого отдела
    for (int i = 0; i < ui->departmentComboBox->currentIndex() && currentDepartment; ++i)  // Прохожу по списку отделов до выбранного
        currentDepartment = currentDepartment->getNext();     // Переход к следующему отделу

    if (!currentDepartment)  // и если отдел не выбран…
    {
        QMessageBox::information(this, "Ошибка", "Сначала выберите отдел.");
        return;
    }

    bool ok;  // Флаг для проверки успешности ввода
    QStringList items = {"Антибиотик", "Жаропонижающее", "Витамины"};  //Список типов лекарств
    QString type = QInputDialog::getItem(this, "Добавить лекарство", "Тип:", items, 0, false, &ok);  //Запрос типа лекарства у пользователя
    if (!ok || type.isEmpty()) // Если ввод неуспешен или пуст…
    {
        return;
    }

    QString name;  // Имя лекарства
    static QRegularExpression re("\\d"); // Создание статического объекта QRegularExpression
    while (true)  // Цикл для запроса имени лекарства у пользователя
    {
        name = QInputDialog::getText(this, "Добавить лекарство", "Название:", QLineEdit::Normal, "", &ok);  // Запрос имени лекарства у пользователя
        if (!ok)   // Если ввод неуспешен…
        {
            return;
        }
        if (name.isEmpty())   // Если имя пустое…
        {
            QMessageBox::information(this, "Ошибка", "Поле названия не может быть пустым.");
        } else if (name.contains(re)) // Если имя содержит цифры...
        {
            QMessageBox::information(this, "Ошибка", "В названии не должно быть цифр.");
        } else {
            // Проверка на уникальность имени
            bool isUnique = true;
            DrugNode* currentNode = currentDepartment->getDrugsHead();
            while (currentNode) {
                if (currentNode->getDrug()->getName() == name)
                {
                    isUnique = false;
                    break;
                }
                currentNode = currentNode->getNext();
            }
            if (!isUnique)
            {
                QMessageBox::information(this, "Ошибка", "Название должно быть уникальным.");
            } else {
                break;  // …иначе выйти из цикла
            }
        }
    }
    int price = QInputDialog::getInt(this, "Добавить лекарство", "Цена:", 1, 1, 1000000, 1, &ok);  // Запрос цены лекарства у пользователя
    if (!ok)  //Если ввод неуспешен…
    {
        return;
    }

    int quantity = QInputDialog::getInt(this, "Добавить лекарство", "Количество:", 1, 1, 1000000, 1, &ok);  // Запрос количества лекарства у пользователя
    if (!ok)
    {  //Если ввод неуспешен…
        return;
    }

    // Создаю новое лекарство на основе введенной информации
    Drug* newDrug;  // Указатель на новое лекарство
    if (type == "Антибиотик")  //если выбран тип "Антибиотик"
    {
        QString sideEffects = QInputDialog::getText(this, "Добавить лекарство", "Побочные эффекты:", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        newDrug = new Antibiotic(name, price, quantity, sideEffects);   // …создать новый объект Antibiotic
    } else if (type == "Жаропонижающее")    // Если тип — "Жаропонижающее"…
    {
        int maxDosage = QInputDialog::getInt(this, "Добавить лекарство", "Максимальная доза:", 1, 1, 100, 1, &ok);
        if (!ok) return;
        newDrug = new Antipyretic(name, price, quantity, maxDosage);  // …создать новый объект Antipyretic
    } else {  // Иначе…
        QString vitaminComplex = QInputDialog::getText(this, "Добавить лекарство", "Витаминный комплекс:", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        newDrug = new Vitamin(name, price, quantity, vitaminComplex);  // …создать новый объект Vitamin
    }

    // Добавление новое лекарство в выбранный отдел
    currentDepartment->addDrug(newDrug);

    // Обновление таблицы
    onDepartmentChanged(ui->departmentComboBox->currentIndex());
}









//УДАЛЯЮ ЛЕКАРСТВО
void MainWindow::onDeleteButtonClicked()
{
    // Получение текущего выбранного отдела
    Department* currentDepartment = firstDepartment; // Начинаем с первого отдела в списке
    for (int i = 0; i < ui->departmentComboBox->currentIndex() && currentDepartment; ++i)
        currentDepartment = currentDepartment->getNext();

    if (!currentDepartment) // Если отдел не выбран…
    {
        QMessageBox::information(this, "Ошибка", "Сначала выберите отдел.");
        return;
    }

    QStringList drugs;
    QString type;
    bool ok;

    do {
        // Запрос типа лекарства у пользователя
        QStringList items = {"Антибиотик", "Жаропонижающее", "Витамины"};
        type = QInputDialog::getItem(this, "Удалить лекарство", "Тип:", items, 0, false, &ok);
        if (!ok || type.isEmpty()) return;

        // Перевод типа лекарства на английский
        if (type == "Антибиотик") type = "Antibiotic";
        else if (type == "Жаропонижающее") type = "Antipyretic";
        else if (type == "Витамины") type = "Vitamin";

        // Создание списка лекарств выбранного типа
        drugs.clear(); // Очищаем список лекарств
        DrugNode* currentNode = currentDepartment->getDrugsHead(); // Начинаем с головы списка лекарств
        while (currentNode)
        {
            Drug* drug = currentNode->getDrug(); // Получаем текущее лекарство
            if (drug->getType() == type) // Если тип текущего лекарства совпадает с выбранным типом…
                drugs << drug->getName(); // …добавляем его в список
            currentNode = currentNode->getNext(); // Переходим к следующему лекарству в списке
        }

        // Проверка на пустоту списка
        if (drugs.isEmpty())
        {
            QMessageBox::information(this, "Удаление", "В этом отделе нет лекарств выбранного типа.");
        }
    } while (drugs.isEmpty());

    // Запрос лекарства для удаления у пользователя
    QString drugName = QInputDialog::getItem(this, "Удалить лекарство", "Название:", drugs, 0, false, &ok);
    if (!ok || drugName.isEmpty()) return;

    // Подтверждение удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение", "Вы уверены, что хотите удалить это лекарство?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) // Если пользователь подтвердил удаление...
    {
        // Нахожу и удаляю выбранное лекарство
        DrugNode* prevNode = nullptr; //Указатель на предыдущий узел в списке
        DrugNode* currentNode = currentDepartment->getDrugsHead(); // Начинаем с головы списка лекарств
        while (currentNode) // Пока есть лекарства в списке…
        {
            if (currentNode->getDrug()->getName() == drugName) // Если имя текущего лекарства совпадает с выбранным именем…
            {
                if (prevNode) // Если есть предыдущий узел…
                    prevNode->setNext(currentNode->getNext()); // …устанавливаем его следующим узлом как следующий узел текущего узла
                else
                    currentDepartment->setDrugsHead(currentNode->getNext()); // …устанавливаем голову списка лекарств как следующий узел текущего узла

                if (currentNode == currentDepartment->getDrugsTail())   // Если текущий узел является хвостом списка…
                    currentDepartment->setDrugsTail(prevNode);        // …устанавливаем хвост списка как предыдущий узел

                delete currentNode->getDrug(); //Удаляем текущее лекарство
                delete currentNode; // Удаляем текущий узел
                break;
            }
            prevNode = currentNode; //Устанавливаем предыдущий узел как текущий
            currentNode = currentNode->getNext(); // Переходим к следующему узлу в списке
        }

        // Обновление таблицы
        onDepartmentChanged(ui->departmentComboBox->currentIndex());
    }
}







//РЕДАКТИРУЮ ЛЕКАРСТВА
void MainWindow::onEditButtonClicked()
{
    // Получение текущего выбранного отдела
    Department* currentDepartment = firstDepartment;
    for (int i = 0; i < ui->departmentComboBox->currentIndex() && currentDepartment; ++i)
        currentDepartment = currentDepartment->getNext();

    if (!currentDepartment) // Если отдел не выбран…
    {
        QMessageBox::information(this, "Ошибка", "Сначала выберите отдел.");
        return;
    }

    QStringList drugs;
    QString selectedDrugType;
    bool ok;
    DrugNode* currentNode; // Объявление переменной перед циклом

    static QRegularExpression re("\\d"); // Создание статического объекта QRegularExpression

    // Создание и заполнение выпадающего списка типов лекарств
    QStringList drugTypes = {"Антибиотики", "Жаропонижающие", "Витамины"};
    selectedDrugType = QInputDialog::getItem(this, "Редактировать лекарство", "Тип:", drugTypes, 0, false, &ok);
    if (!ok || selectedDrugType.isEmpty()) return;

    // Перевод типа лекарства на английский
    if (selectedDrugType == "Антибиотики") selectedDrugType = "Antibiotic";
    else if (selectedDrugType == "Жаропонижающие") selectedDrugType = "Antipyretic";
    else if (selectedDrugType == "Витамины") selectedDrugType = "Vitamin";

    // Создание списка лекарств выбранного типа
    drugs.clear();
    currentNode = currentDepartment->getDrugsHead();
    while (currentNode)
    {
        Drug* drug = currentNode->getDrug();
        if (drug->getType() == selectedDrugType)
            drugs << drug->getName();
        currentNode = currentNode->getNext();
    }

    // Проверка на пустоту списка
    if (drugs.isEmpty())
    {
        QMessageBox::information(this, "Редактирование", "В этом отделе нет лекарств выбранного типа.");
        return;
    }

    // Запрос лекарства для редактирования у пользователя
    QString drugName = QInputDialog::getItem(this, "Редактировать лекарство", "Название:", drugs, 0, false, &ok);
    if (!ok || drugName.isEmpty()) return;

    // Нахожу выбранное лекарство
    currentNode = currentDepartment->getDrugsHead();
    while (currentNode)
    {
        if (currentNode->getDrug()->getName() == drugName)
        {
            // Запрос нового имени лекарства у пользователя
            QString newName;
            do {
                newName = QInputDialog::getText(this, "Редактировать лекарство", "Новое название:", QLineEdit::Normal, drugName, &ok);
                if (!ok) return;
                if (newName.isEmpty()) {
                    QMessageBox::information(this, "Ошибка", "Поле не может быть пустым.");
                } else if (newName.contains(re)) { // Если в названии есть цифры
                    QMessageBox::information(this, "Ошибка", "В названии не могут быть цифры.");
                    newName = ""; // Сброс значения newName, чтобы продолжить цикл
                }
            } while (newName.isEmpty());

            //Запрос новой цены лекарства у пользователя
            double newPrice = QInputDialog::getDouble(this, "Редактировать лекарство", "Новая цена:", currentNode->getDrug()->getPrice(), 0, 1000000, 2, &ok);
            if (!ok) return;

            //Запрос нового количества лекарства у пользователя
            int newQuantity = QInputDialog::getInt(this, "Редактировать лекарство", "Новое количество:", currentNode->getDrug()->getQuantity(), 0, 1000000, 1, &ok);
            if (!ok) return;

            //Запрос новой дополнительной информации о лекарстве у пользователя
            QString newSideEffects;
            int newMaxDosage;
            QString newVitaminComplex;
            if (selectedDrugType == "Antibiotic")
            {
                Antibiotic* antibiotic = dynamic_cast<Antibiotic*>(currentNode->getDrug());
                if (antibiotic)
                {
                    newSideEffects = QInputDialog::getText(this, "Редактировать лекарство", "Побочные эффекты:", QLineEdit::Normal, antibiotic->getSideEffects(), &ok);
                    if (!ok) newSideEffects = antibiotic->getSideEffects(); // Если пользователь нажал "Отмена" или оставил поле пустым, сохраняем текущую информацию
                    antibiotic->setSideEffects(newSideEffects);
                }
            } else if (selectedDrugType == "Antipyretic")
            {
                Antipyretic* antipyretic = dynamic_cast<Antipyretic*>(currentNode->getDrug());
                if (antipyretic)
                {
                    newMaxDosage = QInputDialog::getInt(this, "Редактировать лекарство", "Максимальная доза:", antipyretic->getMaxDosage(), 0, 1000000, 1, &ok);
                    if (!ok) newMaxDosage = antipyretic->getMaxDosage(); // Если пользователь нажал "Отмена" или оставил поле пустым, сохраняем текущую информацию
                    antipyretic->setMaxDosage(newMaxDosage);
                }
            } else if (selectedDrugType == "Vitamin")
            {
                Vitamin* vitamin = dynamic_cast<Vitamin*>(currentNode->getDrug());
                if (vitamin)
                {
                    newVitaminComplex = QInputDialog::getText(this, "Редактировать лекарство", "Витаминный комплекс:", QLineEdit::Normal, vitamin->getVitaminComplex(), &ok);
                    if (!ok) newVitaminComplex = vitamin->getVitaminComplex(); // Если пользователь нажал "Отмена" или оставил поле пустым, сохраняем текущую информацию
                    vitamin->setVitaminComplex(newVitaminComplex);
                }
            }

            // Обновление информации о лекарстве
            currentNode->getDrug()->setName(newName);
            currentNode->getDrug()->setPrice(newPrice);
            currentNode->getDrug()->setQuantity(newQuantity);
        }
        currentNode = currentNode->getNext();
    }

    // Обновление таблицы
    onDepartmentChanged(ui->departmentComboBox->currentIndex());
}












//СОЗДАЮ ОТДЕЛ
void MainWindow::onCreateDepartmentClicked()
{
    bool ok;        //Флаг для проверки успешности ввода
    QString name;   //Имя нового отдела
    while (true)   //Цикл для запроса имени отдела у пользователя
    {
        // запрашиваю у пользователя название отдела
        name = QInputDialog::getText(this, tr("Введите название отдела"), tr("Название:"), QLineEdit::Normal, "", &ok);
        if (!ok) return;  // Если ввод неуспешен, выйти из слота
        //проверяю, не пустое ли название
        if (name.isEmpty())  // Если имя пустое…
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Поле названия не может быть пустым!"));
            continue;  // …и продолжить цикл
        }
        //проверяю, не существует ли уже отдел с таким именем
        Department* currentDepartment = firstDepartment;    // Начало с первого отдела
        while (currentDepartment)   // Пока есть отделы в списке…
        {
            if (currentDepartment->getName() == name)  // Если имя текущего отдела совпадает с введенным именем…
            {
                QMessageBox::warning(this, tr("Ошибка"), tr("Отдел с таким именем уже существует! Пожалуйста, выберите другое имя."));  // …показать сообщение об ошибке
                break;  // …и выйти из цикла
            }
            currentDepartment = currentDepartment->getNext();  // Переход к следующему отделу
        }
        if (currentDepartment == nullptr)  // Если отдел с таким именем не найден…
        {
            // Если отдел с таким именем не найден, выходим из цикла
            break;  // …выйти из цикла
        }
    }

    static QRegularExpression re("\\d"); //создаю статический объект QRegularExpression

    QString pharmacist;  //ФИО фармацевта
    do {
        //запрашиваю у пользователя ФИО фармацевта
        pharmacist = QInputDialog::getText(this, tr("Введите ФИО фармацевта"), tr("ФИО:"), QLineEdit::Normal, "", &ok);  // Запрос ФИО фармацевта у пользователя
        if (!ok) return;     // Если ввод неуспешен, выйти из слота
        //проверяю, не пустое ли ФИО и не содержит ли оно цифры
        if (pharmacist.isEmpty() || pharmacist.contains(re))  // Если ФИО пустое или содержит цифры…
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Поле ФИО не может быть пустым или содержать цифры!"));  // …показать сообщение об ошибке
        }
    } while (pharmacist.isEmpty() || pharmacist.contains(re));  // …и продолжить цикл, пока ФИО не будет введено корректно

    QString phoneNumber;  // Номер телефона
    static QRegularExpression phoneRe("^[0-9]+$"); //создаю статический объект QRegularExpression для проверки номера телефона
    do {
        //запрашиваю у пользователя номер телефона
        phoneNumber = QInputDialog::getText(this, tr("Введите номер телефона"), tr("Номер:"), QLineEdit::Normal, "", &ok);  // Запрос номера телефона у пользователя
        if (!ok) return;  // Если ввод неуспешен, выйти из слота
        //проверяю, не пустой ли номер телефона и содержит ли он только цифры
        if (phoneNumber.isEmpty() || !phoneNumber.contains(phoneRe)) {  // Если номер телефона пустой или содержит не только цифры…
            QMessageBox::warning(this, tr("Ошибка"), tr("Номер телефона должен содержать только цифры!"));  // …показать сообщение об ошибке
        }
    } while (phoneNumber.isEmpty() || !phoneNumber.contains(phoneRe));  // …и продолжить цикл, пока номер телефона не будет введен корректно
    Department* newDepartment = new Department(name, pharmacist, phoneNumber);  // Создание нового отдела с введенными данными
    newDepartment->setDrugsHead(nullptr);   // Инициализируем указатель на начало списка лекарств как nullptr
    newDepartment->setDrugsTail(nullptr);     // Инициализируем указатель на конец списка лекарств как nullptr
    newDepartment->setNext(firstDepartment); //добавляю в начало новый отдел
    firstDepartment = newDepartment;     //обновляю выпадающий список отделов
    updateDepartmentList();
}






//СОЗДАНИЕ ИНФОРМАЦИИ ОБ ОТДЕЛЕ(обновление)
void MainWindow::onDepartmentChanged(int index)
{
    // Очистка таблицы
    ui->tableWidget->setRowCount(0);  // Установка количества строк в таблице на 0, что приводит к ее очистке

    // Нахожу выбранный отдел
    Department* currentDepartment = firstDepartment;      // Начало с первого отдела
    for (int i = 0; i < index && currentDepartment; ++i)  // Проход по списку отделов до выбранного
        currentDepartment = currentDepartment->getNext();  // Переход к следующему отделу

    // Заполняю таблицу данными из выбранного отдела
    if (currentDepartment)  // Если отдел выбран…
    {
        // Определяем максимальное количество строк, которое нам понадобится
        int maxRows = 0;   // Количество строк, необходимых для отображения всех лекарств в выбранном отделе
        DrugNode* currentNode = currentDepartment->getDrugsHead();  // Начало с головы списка лекарств
        while (currentNode)  // Пока есть лекарства в списке…
        {
            ++maxRows;   // …увеличиваем количество строк
            currentNode = currentNode->getNext();  // Переход к следующему лекарству
        }
        ui->tableWidget->setRowCount(maxRows);  // Установка количества строк в таблице равным количеству лекарств в выбранном отделе

        // Заполняем таблицу лекарствами
        currentNode = currentDepartment->getDrugsHead();  // Начало с головы списка лекарств
        int antibioticRow = 0, vitaminRow = 0, antipyreticRow = 0;  // Индексы строк для разных типов лекарств
        while (currentNode)  // Пока есть лекарства в списке…
        {
            Drug* drug = currentNode->getDrug();  // Текущее лекарство
            int column = (drug->getType() == "Antibiotic") ? 0 : (drug->getType() == "Vitamin") ? 1 : 2;  // Определение столбца текущего лекарства в таблице
            int& row = (column == 0) ? antibioticRow : (column == 1) ? vitaminRow : antipyreticRow;  // Выбор соответствующего индекса строки
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(drug->getName() + "\n" + QString::number(drug->getPrice()) + "\n" + QString::number(drug->getQuantity())));  // Добавление ячейки с информацией о лекарстве в таблицу
            ++row;  // Увеличение соответствующего индекса строки
            currentNode = currentNode->getNext();  // Переход к следующему лекарству
        }
    }
}



//ДОБАВЛЕНИЕ ЛЕКАРСТВ В ТАБЛИЦУ
void MainWindow::addDrugsToTable(DrugNode* drugNode, int column)
{
    while (drugNode)  // Пока есть лекарства в списке…
    {
        Drug* drug = drugNode->getDrug();  // Текущее лекарство
        int row = ui->tableWidget->rowCount();  // Количество строк в таблице
        ui->tableWidget->insertRow(row); // Добавление новой строки в таблицу
        ui->tableWidget->setItem(row, column, new QTableWidgetItem(drug->getName() + "\n" + QString::number(drug->getPrice())));  // Добавление ячейки с информацией о лекарстве в таблицу
        drugNode = drugNode->getNext();  // Переход к следующему лекарству
    }
}







//ОБНОВЛЕНИЕ СТРАНИЦЫ
void MainWindow::updateDepartmentList()
{
    // Очистка текущего списка
    ui->departmentComboBox->clear(); // Очищаю выпадающий список отделов.

    // Прохожу по списку отделов и добавление каждого отдела в выпадающий список
    Department* currentDepartment = firstDepartment;    // Устанавливаю текущий отдел как первый отдел.
    while (currentDepartment)     // Пока есть отделы...
    {
        ui->departmentComboBox->addItem(currentDepartment->getName()); // Добавляю имя текущего отдела в выпадающий список.
        currentDepartment = currentDepartment->getNext();                // Перехожу к следующему отделу.
    }
}







//УДАЛЕНИЕ ОТДЕЛА
void MainWindow::onDeleteDepartmentClicked()
{
    // Проверяю, есть ли отделы для удаления
    if (!firstDepartment) // Если нет отделов...
    {
        QMessageBox::information(this, "Удаление", "Нет отделов для удаления.");
        return;
    }

    // Запрашиваю подтверждение от пользователя
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удаление", "Вы уверены, что хотите удалить этот отдел?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) // Если пользователь подтвердил удаление...
    {
        // Нахожу и удаляю выбранный отдел
        int index = ui->departmentComboBox->currentIndex();    // Получает индекс выбранного отдела.
        Department* prevDepartment = nullptr;             // Устанавливает предыдущий отдел как nullptr
        Department* currentDepartment = firstDepartment;  // Устанавливает текущий отдел как первый отдел
        for (int i = 0; i < index && currentDepartment; ++i) // Проходит по списку отделов до выбранного
        {
            prevDepartment = currentDepartment;     // Устанавливаю предыдущий отдел как текущий
            if(currentDepartment) currentDepartment = currentDepartment->getNext(); // Перехожу к следующему отделу
        }


        if (currentDepartment)    //Если отдел выбран...
        {
            //Удаление все лекарства в отделе
            DrugNode* currentNode = currentDepartment->getDrugsHead();   //Устанавливает текущий узел как голову списка лекарств
            while (currentNode)    //Пока есть лекарства...
            {
                DrugNode* nextNode = currentNode->getNext(); // Устанавливаю следующий узел как текущий
                delete currentNode->getDrug(); //Удаляет текущее лекарство
                delete currentNode; //Удаляет текущий узел
                currentNode = nextNode; //Переходит к следующему узлу
            }
            currentDepartment->setDrugsHead(nullptr); //Устанавливает голову списка лекарств как nullptr
            currentDepartment->setDrugsTail(nullptr); //Устанавливает хвост списка лекарств как nullptr

            // Теперь можно безопасно удалить отдел
            if (prevDepartment) // Если есть предыдущий отдел...
            {
                prevDepartment->setNext(currentDepartment->getNext()); //Устанавливает следующий отдел после предыдущего как следующий отдел после текущего
            } else {
                firstDepartment = currentDepartment->getNext(); // Устанавливает первый отдел как следующий отдел после текущего
            }
            delete currentDepartment; //Удаляет текущий отдел
        }

        // Обновление список отделов
        updateDepartmentList();
    }
}





//РЕДАКТИРОВАТЬ ИНФОРМАЦИЮ ОБ ОТДЕЛЕ
void MainWindow::onEditDepartmentButtonClicked()
{
    // Получение текущий выбранный отдел
    Department* currentDepartment = firstDepartment;
    for (int i = 0; i < ui->departmentComboBox->currentIndex() && currentDepartment; ++i)
        currentDepartment = currentDepartment->getNext();

    if (!currentDepartment) // Если отдел не выбран…
    {
        QMessageBox::information(this, "Ошибка", "Сначала выберите отдел.");
        return;
    }

    bool ok;
    QString name;
    while (true)
    {
        name = QInputDialog::getText(this, tr("Редактировать название отдела"), tr("Название:"), QLineEdit::Normal, currentDepartment->getName(), &ok);
        if (!ok) return;
        if (name.isEmpty())
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Поле названия не может быть пустым!"));
        } else {
            break;
        }
    }

    static QRegularExpression digitCheck("\\d");
    QString pharmacist;
    while (true)
    {
        pharmacist = QInputDialog::getText(this, tr("Редактировать имя фармацевта"), tr("Имя:"), QLineEdit::Normal, currentDepartment->getPharmacist(), &ok);
        if (!ok) return;
        if (pharmacist.isEmpty() || pharmacist.contains(digitCheck))
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Имя не должно быть пустым или содержать цифры!"));
        } else {
            break;
        }
    }

    static QRegularExpression phoneCheck("^[0-9]+$");
    QString phoneNumber;
    while (true)
    {
        phoneNumber = QInputDialog::getText(this, tr("Редактировать номер телефона"), tr("Номер:"), QLineEdit::Normal, currentDepartment->getPhoneNumber(), &ok);
        if (!ok) return;
        if (phoneNumber.isEmpty() || !phoneNumber.contains(phoneCheck))
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Номер телефона должен содержать только цифры!"));
        } else {
            break;
        }
    }

    // Обновление информации об отделе
    currentDepartment->setName(name);
    currentDepartment->setPharmacist(pharmacist);
    currentDepartment->setPhoneNumber(phoneNumber);

    // Обновлене списка отделов
    updateDepartmentList();
}









//СОЗДАТЬ (В МЕНЮ "ФАЙЛ")
void MainWindow::createFile()
{
    //Сохранение файла
    saveFile();
    //Очистка данных
    clearData();
    //Очистка имени текущего файла
    currentFileName.clear();
    //Обновление списка отделов
    updateDepartmentList();

}



//ОТКРЫТИЕ ФАЙЛА
void MainWindow::openFile()
{
    // Открывает диалоговое окно для выбора файла, который нужно открыть
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Text Files (*.txt)"));

    // Проверяю, был ли выбран файл
    if (!fileName.isEmpty())
    {
        // Создаею объект QFile для работы с выбранным файлом
        QFile file(fileName);

        //Открываю файл для чтения. Если файл не может быть открыт, функция возвращает управление
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }

        // Очищает текущие данные перед загрузкой новых данных из файла
        clearData();

        // Считывает все данные из файла и создает из них QJsonDocument
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));

        // Преобразует документ в QJsonArray
        QJsonArray departmentsArray = doc.array();
        Department* lastDepartment = nullptr;

        //Проходит по всем элементам массива.
        for (int i = 0; i < departmentsArray.size(); ++i)
        {
            // Преобразует каждый элемент массива в QJsonObject
            QJsonObject departmentObject = departmentsArray[i].toObject();

            // Извлекает данные отдела из объекта и создает новый объект Department
            Department* department = new Department(
                departmentObject["name"].toString(),
                departmentObject["pharmacist"].toString(),
                departmentObject["phoneNumber"].toString()
                );

            // Преобразует поле "drugs" объекта отдела в QJsonArray
            QJsonArray drugsArray = departmentObject["drugs"].toArray();

            // Проходит по всем элементам массива лекарств
            for (int j = 0; j < drugsArray.size(); ++j)
            {
                // Преобразует каждый элемент массива лекарств в QJsonObject
                QJsonObject drugObject = drugsArray[j].toObject();

                // Извлекает тип лекарства из объекта лекарства
                QString type = drugObject["type"].toString();

                // В зависимости от типа лекарства создает новый объект Drug
                Drug* drug = nullptr;
                if (type == "Vitamin")
                {
                    QString vitaminComplex = drugObject["vitaminComplex"].toString();
                    drug = new Vitamin(drugObject["name"].toString(), drugObject["price"].toInt(), drugObject["quantity"].toInt(), vitaminComplex);
                } else if (type == "Antibiotic")
                {
                    QString sideEffects = drugObject["sideEffects"].toString();
                    drug = new Antibiotic(drugObject["name"].toString(), drugObject["price"].toInt(), drugObject["quantity"].toInt(), sideEffects);
                } else if (type == "Antipyretic")
                {
                    int maxDosage = drugObject["maxDosage"].toInt();
                    drug = new Antipyretic(drugObject["name"].toString(), drugObject["price"].toInt(), drugObject["quantity"].toInt(), maxDosage);
                }

                // Если объект Drug был успешно создан, добавляет его в отдел
                if (drug)
                {
                    department->addDrug(drug);
                }
            }

            // Добавляет отдел в список отделов
            if (lastDepartment)
            {
                lastDepartment->setNext(department);
            } else {
                firstDepartment = department;
            }
            lastDepartment = department;
        }

        // Запоминает имя файла, из которого были загружены данные
        currentFileName = fileName;

        // Обновляет интерфейс пользователя
        updateDepartmentList();
        onDepartmentChanged(ui->departmentComboBox->currentIndex());
    }
}










//СОХРАНЯЮ ФАЙЛ
void MainWindow::saveFile()
{
    QString fileName;

    //Проверяет, был ли уже сохранен файл
    if (currentFileName.isEmpty())
    {
        //Если файл еще не был сохранен, открывает диалоговое окно для выбора имени файла
        fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text Files (*.txt)");

        //Если пользователь отменил операцию, функция возвращает управление
        if (fileName.isEmpty())
            return;

        //Обновляет имя текущего файла
        currentFileName = fileName;
    }
    else
    {
        //Использует имя текущего файла
        fileName = currentFileName;
    }

    //Создает объект QFile для работы с текущим файлом
    QFile file(fileName);

    //Пытается открыть файл для записи. Если файл не может быть открыт, функция возвращает управление
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    //Инициализирует массив JSON для хранения данных об отделах
    QJsonArray departmentsArray;

    //Устанавливает текущий отдел как первый отдел
    Department* currentDepartment = firstDepartment;

    //Проходит по всем отделам
    while (currentDepartment)
    {
        //Создает объект JSON для хранения данных об отделе
        QJsonObject departmentObject;

        //Добавляет данные отдела в объект JSON
        departmentObject["name"] = currentDepartment->getName();
        departmentObject["pharmacist"] = currentDepartment->getPharmacist();
        departmentObject["phoneNumber"] = currentDepartment->getPhoneNumber();

        //Инициализирует массив JSON для хранения данных о лекарствах
        QJsonArray drugsArray;

        //Устанавливает текущий узел как голову списка лекарств
        DrugNode* currentNode = currentDepartment->getDrugsHead();

        //Проходит по всем лекарствам в отделе
        while (currentNode)
        {
            //Создает объект JSON для хранения данных о лекарстве
            QJsonObject drugObject;

            //Добавляет общие данные лекарства в объект JSON
            Drug* drug = currentNode->getDrug();
            drugObject["name"] = drug->getName();
            drugObject["price"] = drug->getPrice();
            drugObject["type"] = drug->getType();
            drugObject["quantity"] = drug->getQuantity();

            //Использует динамическое приведение типов для определения типа лекарства и сохранения соответствующих свойств
            if (Antibiotic* antibiotic = dynamic_cast<Antibiotic*>(drug))
            {
                drugObject["sideEffects"] = antibiotic->getSideEffects();
            }
            else if (Vitamin* vitamin = dynamic_cast<Vitamin*>(drug))
            {
                drugObject["vitaminComplex"] = vitamin->getVitaminComplex();
            }
            else if (Antipyretic* antipyretic = dynamic_cast<Antipyretic*>(drug))
            {
                drugObject["maxDosage"] = antipyretic->getMaxDosage();
            }

            //добавляю объект лекарства в массив лекарств
            drugsArray.append(drugObject);

            //перехожу к следующему лекарству
            currentNode = currentNode->getNext();
        }

        //добавляю массив лекарств в объект отдела
        departmentObject["drugs"] = drugsArray;

        //добавляю объект отдела в массив отделов
        departmentsArray.append(departmentObject);

        //перехожу к следующему отделу
        currentDepartment = currentDepartment->getNext();
    }

    //создаю документ JSON из массива отделов
    QJsonDocument doc(departmentsArray);

    //записываю документ JSON в файл
    file.write(doc.toJson());

    file.close();
}






//СОХРАНИТЬ КАК...
void MainWindow::saveFileAs()
{
    //Открывает диалоговое окно для выбора имени файла, в который нужно сохранить данные
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл как..."), "", tr("Text Files (*.txt)"));

    //Проверяет, было ли выбрано имя файла
    if (!fileName.isEmpty())
    {
        //Создает объект QFile для работы с выбранным файлом
        QFile file(fileName);

        //Пытаемся открыть файл для записи. Если файл не может быть открыт, функция возвращает управление
        if (!file.open(QIODevice::WriteOnly))
        {
            return;
        }

        //Инициализирует массив JSON для хранения данных об отделах
        QJsonArray departmentsArray;

        //Устанавливает текущий отдел как первый отдел
        Department* currentDepartment = firstDepartment;

        //Проходит по всем отделам
        while (currentDepartment)
        {
            //Создает объект JSON для хранения данных об отделе
            QJsonObject departmentObject;

            //Добавляет данные отдела в объект JSON
            departmentObject["name"] = currentDepartment->getName();
            departmentObject["pharmacist"] = currentDepartment->getPharmacist();
            departmentObject["phoneNumber"] = currentDepartment->getPhoneNumber();

            //Инициализирует массив JSON для хранения данных о лекарствах
            QJsonArray drugsArray;

            //Устанавливает текущий узел как голову списка лекарств
            DrugNode* currentNode = currentDepartment->getDrugsHead();

            //Инициализирует счетчик для отслеживания номера строки
            int i = 0;

            //Проходит по всем лекарствам в отделе
            while (currentNode)
            {
                //Создает объект JSON для хранения данных о лекарстве
                QJsonObject drugObject;

                //Добавляет общие данные лекарства в объект JSON.
                Drug* drug = currentNode->getDrug();
                drugObject["name"] = drug->getName();
                drugObject["price"] = drug->getPrice();
                drugObject["type"] = drug->getType();
                drugObject["quantity"] = drug->getQuantity();
                drugObject["row"] = i;
                drugObject["column"] = 0;

                //Используем динамическое приведение типов для определения типа лекарства и сохранения их свойств
                if (Antibiotic* antibiotic = dynamic_cast<Antibiotic*>(drug))
                {
                    drugObject["sideEffects"] = antibiotic->getSideEffects();
                }
                else if (Vitamin* vitamin = dynamic_cast<Vitamin*>(drug))
                {
                    drugObject["vitaminComplex"] = vitamin->getVitaminComplex();
                }
                else if (Antipyretic* antipyretic = dynamic_cast<Antipyretic*>(drug))
                {
                    drugObject["maxDosage"] = antipyretic->getMaxDosage();
                }

                //Добавляем объект лекарства в массив лекарств
                drugsArray.append(drugObject);

                //Переходим к следующему лекарству
                currentNode = currentNode->getNext();
                ++i;
            }

            //Добавляет массив лекарств в объект отдела
            departmentObject["drugs"] = drugsArray;

            //Добавляет объект отдела в массив отделов
            departmentsArray.append(departmentObject);

            //Переходит к следующему отделу
            currentDepartment = currentDepartment->getNext();
        }

        //Создает документ JSON из массива отделов
        QJsonDocument doc(departmentsArray);

        //Записывает документ JSON в файл
        file.write(doc.toJson());

        //Запоминает имя файла, в который были сохранены данные
        currentFileName = fileName;
    }
}







//РУКОВОДСТВО ПОЛЬЗОВАТЕЛЯ
void MainWindow::showGuide()
{
    QDialog *dialog = new QDialog(this); //создание нового диалогового окна
    dialog->setWindowTitle(tr("Руководство")); //установка заголовка диалогового окна
    dialog->setMinimumSize(800, 600);   //установка минимального размера диалогового окна

    QVBoxLayout *layout = new QVBoxLayout(dialog);  //создание нового вертикального макета для диалогового окна

    QScrollArea *scroll = new QScrollArea(dialog);  //создание новой области прокрутки
    scroll->setWidgetResizable(true); //установка свойства, позволяющего виджету изменять размер вместе с областью прокрутки

    QWidget *content = new QWidget(scroll); //создание нового виджета, который будет содержать текст руководства
    scroll->setWidget(content); //сстановка виджета в качестве центрального виджета области прокрутки

    QVBoxLayout *vLayout = new QVBoxLayout(content); //создание нового вертикального макета для виджета содержимого

    QLabel *label = new QLabel(content); //создание новой метки, которая будет содержать текст руководства
    label->setTextFormat(Qt::RichText); //установка формата текста метки на RichText, что позволяет использовать HTML-форматирование
    label->setText(
        tr("<b>РУКОВОДСТВО ПОЛЗОВАТЕЛЯ ДЛЯ ПРОГРАММЫ \"АПТЕКА\"</b><br><br>"
           "<b>Общее описание</b><br><br>"
           "Программа \"Аптека\" предназначена для управления информацией об отделах аптеки и лекарствах, которые в них продаются. "
           "Программа позволяет добавлять, удалять и редактировать отделы и лекарства, а также осуществлять поиск лекарств по различным критериям.<br><br>"
           "<b>Интерфейс программы</b><br><br>"
           "Интерфейс программы состоит из таблицы, которая отображает информацию о лекарствах, и ряда кнопок для управления отделами и лекарствами.<br><br>"
           "<b>Таблица лекарств</b><br><br>"
           "Таблица лекарств состоит из трех столбцов: \"Антибиотики\", \"Витамины\" и \"Жаропонижающее\". "
           "В каждом столбце отображаются лекарства соответствующего типа. Каждая ячейка таблицы содержит название лекарства и его цену.<br><br>"
           "<b>Кнопки управления</b><br><br>"
           "Программа предоставляет следующие кнопки управления:<br><br>"
           "Добавить лекарство: Позволяет добавить новое лекарство в выбранный отдел. "
           "При нажатии на эту кнопку открывается диалоговое окно, в котором можно ввести название и цену лекарства, а также выбрать его тип.<br><br>"
           "Удалить лекарство: Удаляет выбранное в таблице лекарство.<br><br>"
           "Редактировать лекарство: Позволяет изменить название и цену выбранного в таблице лекарства.<br><br>"
           "Создать отдел: Создает новый отдел. При нажатии на эту кнопку открывается диалоговое окно, в котором можно ввести название отдела, ФИО фармацевта и номер телефона.<br><br>"
           "Удалить отдел: Удаляет выбранный отдел и все лекарства в нем.<br><br>"
           "<b>Работа с файлами</b><br><br>"
           "Программа позволяет сохранять информацию об отделах и лекарствах в файл и загружать ее из файла. "
           "Для работы с файлами предусмотрены следующие функции:<br><br>"
           "Открыть файл: Загружает информацию об отделах и лекарствах из файла.<br><br>"
           "Сохранить файл: Сохраняет текущую информацию об отделах и лекарствах в файл.<br><br>"
           "Сохранить файл как...: Сохраняет текущую информацию об отделах и лекарствах в новый файл.<br><br>"
           "<b>Поиск лекарств</b><br><br>"
           "Программа предоставляет возможность поиска лекарств по названию, типу и цене. Для этого предусмотрена кнопка \"Поиск\", при нажатии на которую открывается окно поиска."
           )
        );
    vLayout->addWidget(label); //добавление метки в макет виджета содержимого. Метка содержит текст руководства.

    layout->addWidget(scroll); //добавление области прокрутки в макет диалогового окна. Область прокрутки содержит виджет содержимого, который в свою очередь содержит метку с текстом руководства.

    dialog->exec(); //отображение диалогового окна и вход в цикл обработки событий. Это означает, что диалоговое окно будет видимым на экране, и пользователь сможет взаимодействовать с ним.
}



//О ПРОГРАММЕ
void MainWindow::showAbout()
{
    QMessageBox::information(this, tr("О программе"),
                             tr("Программа \"Аптека\" разработана для управления информацией об отделах аптеки и лекарствах, которые в них продаются. "
                                "Она предоставляет функциональность для добавления, удаления и редактирования отделов и лекарств, а также осуществляет поиск лекарств по различным критериям.<br><br>"
                                "<b>Контактная информация:</b><br>"
                                "Почта: vyachic007@gmail.com."));
}

//ЗАКРЫТЬ
void MainWindow::exitApplication()
{
    qApp->quit();
}






// ОТКРЫТИЕ ОКНА ПОИСКА
void MainWindow::openSearchWindow()
{
    //Создание нового диалогового окна
    QDialog* searchWindow = new QDialog(this);

    //Установка заголовка диалогового окна
    searchWindow->setWindowTitle("Поиск");

    //Создание виджетов для интерфейса поиска
    QCheckBox* nameCheckBox = new QCheckBox("Поиск по названию");
    QLineEdit* nameLineEdit = new QLineEdit();
    QGroupBox* typeGroupBox = new QGroupBox("Тип лекарства:");
    QVBoxLayout* typeLayout = new QVBoxLayout();
    QRadioButton* allTypeRadio = new QRadioButton("Все");
    QRadioButton* antibioticTypeRadio = new QRadioButton("Антибиотик");
    QRadioButton* vitaminsTypeRadio = new QRadioButton("Витамины");
    QRadioButton* antipyreticTypeRadio = new QRadioButton("Жаропонижающее");
    typeLayout->addWidget(allTypeRadio);
    typeLayout->addWidget(antibioticTypeRadio);
    typeLayout->addWidget(vitaminsTypeRadio);
    typeLayout->addWidget(antipyreticTypeRadio);
    typeGroupBox->setLayout(typeLayout);
    QCheckBox* priceCheckBox = new QCheckBox("Поиск по цене");
    QLineEdit* priceLineEdit = new QLineEdit();
    QPushButton* searchButton = new QPushButton("Выполнить поиск");

    //Компоновка виджетов
    QVBoxLayout* layout = new QVBoxLayout(searchWindow);
    layout->addWidget(nameCheckBox);
    layout->addWidget(nameLineEdit);
    layout->addWidget(typeGroupBox);
    layout->addWidget(priceCheckBox);
    layout->addWidget(priceLineEdit);
    layout->addWidget(searchButton);

    //Подключение сигнала нажатия кнопки к слоту выполнения поиска
    connect(searchButton, &QPushButton::clicked, this, [=]
            {
                performSearch(nameLineEdit, allTypeRadio, antibioticTypeRadio, vitaminsTypeRadio, antipyreticTypeRadio, priceLineEdit, nameCheckBox, priceCheckBox);
            });

    //Показ окна поиска
    searchWindow->exec();
}




//ПОКАЗАТЬ РЕЗУЛЬТАТЫ ПОИСКА
void MainWindow::showSearchResults(const QVector<Drug*>& results, const QString& searchType)
{
    // Проверка, есть ли результаты поиска
    if (results.isEmpty()) {
        QMessageBox::information(this, "Поиск", "Совпадений не найдено.");
        return;
    }

    // Создание нового окна или диалогового окна для отображения результатов
    QDialog* resultsWindow = new QDialog(this);
    resultsWindow->setWindowTitle("Результаты поиска");

    // Определение количества столбцов в таблице
    int columnCount = 5;    // Базовые столбцы: Название, Тип, Цена, Количество, Отдел
    if (searchType == "Antibiotic")
        columnCount += 1; // Добавление столбца "Побочные эффекты"
    else if (searchType == "Vitamin")
        columnCount += 1; // Добавление столбца "Витаминный комплекс"
    else if (searchType == "Antipyretic")
        columnCount += 1; // Добавление столбца "Максимальная доза"

    // Создание таблицы с нужным количеством столбцов
    QTableWidget* resultsTable = new QTableWidget(resultsWindow);
    resultsTable->setColumnCount(columnCount);

    // Установка заголовков столбцов
    QStringList headers = {"Название", "Тип", "Цена", "Количество", "Отдел"};
    if (searchType == "Antibiotic")
        headers << "Побочные эффекты";
    else if (searchType == "Vitamin")
        headers << "Витаминный комплекс";
    else if (searchType == "Antipyretic")
        headers << "Максимальная доза";
    resultsTable->setHorizontalHeaderLabels(headers);

    // Заполнение таблицы данными из результатов поиска
    for (Drug* drug : results)
    {
        int row = resultsTable->rowCount();
        resultsTable->insertRow(row);
        resultsTable->setItem(row, 0, new QTableWidgetItem(drug->getName()));
        resultsTable->setItem(row, 1, new QTableWidgetItem(drug->getType()));
        resultsTable->setItem(row, 2, new QTableWidgetItem(QString::number(drug->getPrice())));
        resultsTable->setItem(row, 3, new QTableWidgetItem(QString::number(drug->getQuantity())));

        // Поиск отдела, которому принадлежит лекарство
        QString departmentName;
        Department* currentDepartment = firstDepartment;
        while (currentDepartment)
        {
            DrugNode* currentNode = currentDepartment->getDrugsHead();
            while (currentNode)
            {
                if (currentNode->getDrug() == drug)
                {
                    departmentName = currentDepartment->getName();
                    break;
                }
                currentNode = currentNode->getNext();
            }
            if (!departmentName.isEmpty())
            {
                break;
            }
            currentDepartment = currentDepartment->getNext();
        }
        // Добавление названия отдела в таблицу
        resultsTable->setItem(row, 4, new QTableWidgetItem(departmentName));

        // Добавление дополнительной информации в зависимости от типа лекарства
        if (searchType == "Antibiotic")
        {
            Antibiotic* antibiotic = dynamic_cast<Antibiotic*>(drug);
            if (antibiotic)
                resultsTable->setItem(row, 5, new QTableWidgetItem(antibiotic->getSideEffects()));
        }
        else if (searchType == "Vitamin")
        {
            Vitamin* vitamin = dynamic_cast<Vitamin*>(drug);
            if (vitamin)
                resultsTable->setItem(row, 5, new QTableWidgetItem(vitamin->getVitaminComplex()));
        }
        else if (searchType == "Antipyretic")
        {
            Antipyretic* antipyretic = dynamic_cast<Antipyretic*>(drug);
            if (antipyretic)
                resultsTable->setItem(row, 5, new QTableWidgetItem(QString::number(antipyretic->getMaxDosage())));
        }
    }

    // Добавление таблицы в макет окна и показ окна
    QVBoxLayout* layout = new QVBoxLayout(resultsWindow);
    layout->addWidget(resultsTable);
    resultsWindow->exec();
}




//ВЫПОЛЕНИЕ ПОИСКА
void MainWindow::performSearch(QLineEdit* nameLineEdit, QRadioButton* allTypeRadio, QRadioButton* antibioticTypeRadio, QRadioButton* vitaminsTypeRadio, QRadioButton* antipyreticTypeRadio, QLineEdit* priceLineEdit, QCheckBox* nameCheckBox, QCheckBox* priceCheckBox)
{
    // Получение данных из полей ввода
    QString searchName = nameLineEdit->text(); //Получение текста из поля ввода имени
    bool searchByName = nameCheckBox->isChecked(); //Проверка, выбран ли чекбокс поиска по имени

    // Определение типа лекарства для поиска на основе выбранного радиокнопкой
    QString searchType;
    if (allTypeRadio->isChecked()) // Если выбрана радиокнопка "Все"...
    {
        searchType = "Все";
    }
    else if (antibioticTypeRadio->isChecked()) //Если выбрана радиокнопка "Антибиотик"...
    {
        searchType = "Antibiotic";
    }
    else if (vitaminsTypeRadio->isChecked()) //Если выбрана радиокнопка "Витамины"...
    {
        searchType = "Vitamin";
    }
    else if (antipyreticTypeRadio->isChecked()) //Если выбрана радиокнопка "Жаропонижающее"...
    {
        searchType = "Antipyretic";
    }
    bool searchByType = (searchType != "Все");    //Проверка, выбран ли поиск по типу

    int searchPrice = priceLineEdit->text().toInt(); //Получение цены из поля ввода цены
    bool searchByPrice = priceCheckBox->isChecked(); //Проверка, выбран ли чекбокс поиска по цене

    //Инициализация контейнера для хранения результатов поиска
    QVector<Drug*> searchResults;

    //Выполнение поиска в динамических структурах данных (линейный, проходит через каждый элемент данных по очереди), не гарантиров. сортировка
    Department* currentDepartment = firstDepartment; // Начало с первого отдела
    while (currentDepartment)    // Пока есть отделы...
    {
        DrugNode* currentNode = currentDepartment->getDrugsHead(); // Начало с головы списка лекарств
        while (currentNode)     // Пока есть лекарства...
        {
            Drug* drug = currentNode->getDrug(); // Текущее лекарство
            bool match = true;    // Флаг совпадения
            if (searchByName && !drug->getName().contains(searchName, Qt::CaseInsensitive)) // Если выбран поиск по имени и имя не совпадает...
            {
                match = false;    // ...установить флаг совпадения в false
            }
            if (searchByType && drug->getType() != searchType) // Если выбран поиск по типу и тип не совпадает...
            {
                match = false;
            }
            if (searchByPrice && drug->getPrice() != searchPrice) // Если выбран поиск по цене и цена не совпадает...
            {
                match = false;
            }
            if (match) // Если все критерии совпадают...
            {
                searchResults.append(drug); // ...добавить лекарство в результаты поиска
            }
            currentNode = currentNode->getNext(); // Переход к следующему лекарству
        }
        currentDepartment = currentDepartment->getNext(); // Переход к следующему отделу
    }

    // Отображение результатов поиска в новом окне
    showSearchResults(searchResults, searchType);
}


//НАЖАТИЕ САМОЙ КНОПКИ ПОИСКА
void MainWindow::onSearchButtonClicked()
{
    //Открытие окна поиска
    openSearchWindow();
}









//ОЧИСТКА ДАННЫХ
void MainWindow::clearData()
{
    //Очистка списка отделов
    Department* currentDepartment = firstDepartment;
    while (currentDepartment)
    {
        Department* nextDepartment = currentDepartment->getNext();

        //Удаление всех лекарств в отделе
        DrugNode* currentNode = currentDepartment->getDrugsHead();
        while (currentNode)
        {
            DrugNode* nextNode = currentNode->getNext();
            delete currentNode->getDrug();
            delete currentNode;
            currentNode = nextNode;
        }
        currentDepartment->setDrugsHead(nullptr);
        currentDepartment->setDrugsTail(nullptr);

        //Удаление текущего отдела
        delete currentDepartment;
        currentDepartment = nextDepartment;
    }
    firstDepartment = nullptr;

    //Очистка таблицы
    ui->departmentComboBox->clear();
    ui->tableWidget->setRowCount(0);
}






//ИНФОРМАЦИЯ ОБ ОТДЕЛЕ
void MainWindow::onDepartmentComboBoxIndexChanged(int index)
{
    // Получение текущиего выбранного отдела
    Department* currentDepartment = firstDepartment;
    for (int i = 0; i < index && currentDepartment; ++i)
        currentDepartment = currentDepartment->getNext();

    if (currentDepartment) // Если отдел выбран…
    {
        // Обновление информации об отделе
        ui->departmentNameLabel->setText(currentDepartment->getName());
        ui->pharmacistNameLabel->setText(currentDepartment->getPharmacist());
        ui->phoneNumberLabel->setText(currentDepartment->getPhoneNumber());
    }
}








