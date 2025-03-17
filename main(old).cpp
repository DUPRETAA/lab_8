/*
Сформировать двоичный файл из элементов, заданной в ва-рианте структуры, распечатать его содержимое, выполнить удаление 
и добавление элементов в соответствии со своим вариантом, используя для поиска удаляемых или 
добавляе-мых элементов функцию. Формирование, печать, добавление и удаление элементов оформить в виде функций. 
Преду-смотреть сообщения об ошибках при открытии файла и вы-полнении операций ввода/вывода.

20.	Структура "Государство":
-	название;
-	государственный язык;
-	денежная единица;
-	курс валюты относительно $.
Удалить элемент с указанным названием, добавить 2 эле-мента в конец файла.
*/

#include <iostream>
#define SIZE 5

using namespace std;

struct State {
    char name[40]{}, language[40]{}, currency[40]{};
    float curToUSD;

    void showStates() {
        cout << "State: " << name << "\tLanguage: " << language << " \tCurrency: " << currency << "\tExchange rate relative to dollar: " << curToUSD << endl;
    }

    void clear() {
        for(int j=0;j<40;j++)name[j]=0;
        for(int j=0;j<40;j++)language[j]=0;
        for(int j=0;j<40;j++)currency[j]=0;
    }
};

void Create(){
    string names[SIZE] = {"Russia", "Germany", "Italy", "Greece", "Finland"};
    string languages[SIZE] = {"Russian", "German", "Italian", "Greek", "Finnish"};
    string currencies[SIZE] = {"RUB", "EUR", "EUR", "EUR", "EUR"};
    float curToUSDs[SIZE] = {0.011, 1.03, 1.03, 1.03, 1.03};

    State s;
    FILE *fp;
    fp=fopen("t.txt", "wb");
    if (fp==NULL) exit(1);
    else
    for (int i=0;i<SIZE;i++) { 
        if (!ferror(fp)) {
        s.clear();
        for(int j=0;j<names[i].length();j++)s.name[j]=names[i][j];
        for(int j=0;j<languages[i].length();j++)s.language[j]=languages[i][j];
        for(int j=0;j<currencies[i].length();j++)s.currency[j]=currencies[i][j];
        s.curToUSD=curToUSDs[i];
        fwrite(&s, sizeof(State),1,fp);
        }
        else exit(2);  
    }
    fclose(fp);
    return;
}

void Show() {
    FILE *fp;
    State s;
    State mas[SIZE-1];
    int counter = 0;

    fp=fopen( "t.txt", "rb");
    if (fp==NULL) exit(3);
    else while (fread(&s, sizeof(State),1,fp)) s.showStates();
    
    fclose(fp);
    return;
}

void Delete(string stateToDel){
    FILE *fp;
    State s;
    State mas[SIZE-1];
    int counter = 0;

    fp=fopen( "t.txt", "rb");
    if (fp==NULL) exit(3);
    else while (fread(&s, sizeof(State),1,fp)) if (s.name != stateToDel)  mas[counter++]=s;
    fclose(fp);

    fp=fopen("t.txt", "wb");
    if (fp==NULL) exit(1);
    else for (int i=0;i<counter;i++) fwrite(&mas[i], sizeof(State),1,fp);
    fclose(fp);
    return;
}

void Add() {
    State s1,s2;
    FILE *fp;

    s1 = {"Turkey", "Turkish", "TRY", 0.02};
    s2 = {"Sweden", "Swedish", "SEC", 0.1};


    fp=fopen( "t.txt", "ab");
    if (fp==NULL) exit(3);
    else {
        fwrite(&s1, sizeof(State),1,fp);
        fwrite(&s2, sizeof(State),1,fp);
    }
    fclose(fp);
}

int main() {
    Create();
    Show();

    string stateToDel;

    cout << "Введите название страны для удаления из файла: ";
    cin >> stateToDel;

    Delete(stateToDel);

    cout << "Результат удвления записи из файла: " << endl;
    Show();

    Add();

    cout << "Результат добавления двух записей в конец файла: " << endl;
    Show();

    return 0;
}