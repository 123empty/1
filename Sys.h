#pragma once
#include"Button.h"
#include"Label.h"
#include"TableWidget.h"
#include"TextBox.h"
#include<map>
#include<fstream>

#define READER "reader.txt"
#define ADMIN "admin.txt"
#define BOOK "book.txt"
#define BORROW "borrow.txt"

typedef struct {
    wstring ID;
    wstring Name;
    wstring Author;
    wstring Publish;
    wstring publishDate;
    wstring price;
    wstring num;
    wstring borrowNum;
}Book;

class Sys
{
private:
    int width;
    int height;
    int currentIndex;
    vector<IMAGE*> pages;
    vector<vector<Button*>> buttons;
    vector<vector<TextBox*>>textBoxs; 
    vector<vector<TableWidget*>> tables;
    vector<vector<Label*>> labels;

    wstring currentUser;

    map<wstring, wstring> readerPassword;
    map<wstring, wstring> adminPassword;
    map<wstring, Book*>books;
    vector<vector<wstring>>borrow;

    vector<vector<wstring>> bookTable;
    vector<vector<wstring>> borrowTable;

    void addPage(IMAGE* page);

    void addButton(int index, Button* button);

    void addTextBox(int index, TextBox* textBox);

    void addLabel(int index, Label* label);

    void addTable(int index, TableWidget* table);

    void setCurrentIndex(int index);

    void mouseClick(int mouseX, int mouseY);

    void mouseMove(int mouseX, int mouseY);

    void mouseWheel(int mouseX, int mouseY, int wheel);

    void keyInput(wchar_t ch);

    void draw();

    void load();

    void saveReader();

    void saveBook();

    void saveBorrow();

    void updataBookTable();

    void updataBorrowTable();

public:
    Sys(int width, int height)
        :width(width), height(height), currentIndex(-1)
    {
    }
    ~Sys() {}

    void init();

    void run();

    void close();
};

