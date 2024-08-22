#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include "Drug.h"
#include "Department.h"

namespace Ui    // Объявление пространства имен Ui
{
class MainWindow;  // Объявление класса MainWindow в пространстве имен Ui
}


class MainWindow : public QMainWindow  // Объявление класса MainWindow, наследуемого от QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);  // Конструктор класса
    ~MainWindow();  // Деструктор класса



private slots:
    void onAddDrugButtonClicked();
    void onDeleteButtonClicked();
    void onEditButtonClicked();
    void onCreateDepartmentClicked();
    void onDeleteDepartmentClicked();
    void onDepartmentChanged(int index);
    void createFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void showGuide();
    void showAbout();
    void exitApplication();
    void openSearchWindow();
    void performSearch(QLineEdit* nameLineEdit, QRadioButton* allTypeRadio, QRadioButton* antibioticTypeRadio, QRadioButton* vitaminsTypeRadio, QRadioButton* antipyreticTypeRadio, QLineEdit* priceLineEdit, QCheckBox* nameCheckBox, QCheckBox* priceCheckBox);
   void showSearchResults(const QVector<Drug*>& results, const QString& searchType);
    void onSearchButtonClicked();
void onEditDepartmentButtonClicked();
void onDepartmentComboBoxIndexChanged(int index);

protected:
void closeEvent(QCloseEvent *event) override;


private:
    Ui::MainWindow *ui;   //Указатель на объект интерфейса пользователя
    Department* firstDepartment;    //Указатель на первый отдел в списке
    void updateUI();       //Функция для обновления интерфейса пользователя
    void updateDepartmentList();    //Функция для обновления списка отделов
    QString currentFileName;     //Имя текущего файла
    void clearData();      //Функция для очистки данных
    void addDrugsToTable(DrugNode* drugNode, int column);  //Функция для добавления лекарств в таблицу
    //счетчик для лекарств
    int antibioticCount = 0;
    int vitaminCount = 0;
    int antipyreticCount = 0;



};



#endif
