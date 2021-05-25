#include <iostream>
#include "StringBuilderClass.h"
#include "FileManagerClass.h"
#include "ClassMenu.h"
#include "StudentDBClass.h"
#include "StudentClass.h"
#include "ClassEdit.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Курсовая работа запущена...\n";
    StudentDBClass* sdb = new StudentDBClass();
    StudentDBClass* sdb1 = new StudentDBClass();
    StudentDBClass* sdb2 = new StudentDBClass();
    sdb->FileName = "DB.txt";
    sdb->loadDataFromFile();
    ClassMenu* mainMenu = new ClassMenu();
    ClassMenu* varMenu = new ClassMenu();
    mainMenu->addTitleItem("Главное меню");
    mainMenu->addItem("Просмотреть список студетов (удалить или изменить данные)");
    mainMenu->addItem("Добавить данные о студенте в БД"); 
    mainMenu->addItem("Сохранить БД студентов в файл");
    mainMenu->addItem("Выполнить вариант 40");
    mainMenu->addItem("Выход");
    int resultSelectedItem = 0;
    int exitInt = 3;
    ClassMenu* studentsMenu = new ClassMenu();
    studentsMenu->addTitleItem("Список студентов");
    int resultStudentSelectedItem = 1;
    int resultVarSelectedItem = 1;
    const int exitIntStudentMenu = 0;
    const int exitIntVarMenu = 0;
    StudentNode* sn;
    StudentClass* st = new StudentClass();
    ClassMenu* delStudentsMenu = new ClassMenu();
    int curCount;
    ClassEdit* ce = new  ClassEdit();
    int startYear = 0;
    int endYear = 0;
    int year = 0;
    StringBuilderClass* sb = new StringBuilderClass();
    while (resultSelectedItem != exitInt) {
        mainMenu->run();
        resultSelectedItem = mainMenu->getSelectedItem();
        switch (resultSelectedItem) {
        case 0:
            resultStudentSelectedItem = 1;
            while (resultStudentSelectedItem != exitIntStudentMenu) {
                studentsMenu->eraseItem();
                studentsMenu->addItem("Выход");
                studentsMenu->addItem("Удалить данные о студенте");
                sn = sdb->getInit();
                while (sn) { // добавить пункты меню ФИО студентов
                    string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                    studentsMenu->addItem(tmpString); //добавить в меню студентов
                    sn = sn->next;
                }
                studentsMenu->run();
                resultStudentSelectedItem = studentsMenu->getSelectedItem();
                if (resultStudentSelectedItem == exitIntStudentMenu) {
                    break;
                }
                if (resultStudentSelectedItem == 1) //удаление данных о студенте
                {
                    delStudentsMenu->eraseAll();
                    delStudentsMenu->addTitleItem("Выберите студента для удаления данных");
                    delStudentsMenu->addItem("Выход");
                    int resultDel = 1;
                    const int exitDel = 0;
                    sn = sdb->getInit();
                    while (sn) { // добавить пункты меню ФИО студентов
                        string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                        delStudentsMenu->addItem(tmpString); //добавить в меню студентов
                        sn = sn->next;
                    }
                    while (resultDel != exitDel) {
                        delStudentsMenu->run();
                        resultDel = delStudentsMenu->getSelectedItem();
                        int num = resultDel - 1;
                    }
                }
                if (resultStudentSelectedItem > 1)
                {
                    int num = resultStudentSelectedItem - 2; //!
                    sn = sdb->getStudentNode(num);
                    string oldRecordCardNumber = "";
                    oldRecordCardNumber = sn->recordCardNumber;
                    st->editStudent(sn);

                    if (sdb->getSameRecordCardNumber(sn->recordCardNumber) > 1)
                    {
                        sn->recordCardNumber = oldRecordCardNumber;
                        cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                        _getch();
                    }
                }
            }
            break;
        case 1:
            sn = new StudentNode();
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 10; j++)
                    sn->examsRecordsData[i][j].isEmpty = true;
            st->editStudent(sn);
            if (sdb->getSameRecordCardNumber(sn->recordCardNumber) == 1)
            {
                cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                _getch();
            }
            else
            {
                sdb->Add(sn);
            }
            break;
        case 2: //Сохранить в файл
            sdb->saveDataToFile(sdb->FileName);
            break;
        case 3: //Вариант 40
            varMenu->eraseItem();
            varMenu->addTitleItem("Выберите по какому семестру отсортировать студентов");
            varMenu->addItem("Выход");
            varMenu->addItem("Семестр 1");
            varMenu->addItem("Семестр 2");
            varMenu->addItem("Семестр 3");
            varMenu->addItem("Семестр 4");
            varMenu->addItem("Семестр 5");
            varMenu->addItem("Семестр 6");
            varMenu->addItem("Семестр 7");
            varMenu->addItem("Семестр 8");
            varMenu->addItem("Семестр 9");
            while (resultVarSelectedItem != exitIntVarMenu) {
                varMenu->run();
                resultSelectedItem = varMenu->getSelectedItem();
                if (resultVarSelectedItem == exitIntVarMenu)
                    break;
                if (varMenu->getSelectedItem() >= 1) {
                    sdb->updateAvrMarksSem(varMenu->getSelectedItem() - 1);
                    system("cls");
                    cout << "Полный список студентов" << endl;
                    sdb->printAllSurName_Name_MName_sex_avrMarks();
                    cout << endl;
                    sdb->sortByAvrMarks();
                    cout << "Отсортированный список студентов" << endl;
                    sdb->printAllSurName_Name_MName_sex_avrMarks();
                    sn = sdb->getInit();
                    sdb1->Erase();
                    sdb2->Erase();
                    _getch();
                }
            }
        default:
            break;
        }
    }
}