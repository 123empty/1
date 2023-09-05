#include "Sys.h"
void Sys::addPage(IMAGE* page)
{
    pages.push_back(page);
    buttons.push_back({});
    textBoxs.push_back({});
    labels.push_back({});
    tables.push_back({});
}

void Sys::addButton(int index, Button* button)
{
    if (index >= 0 && index < buttons.size())
    {
        buttons[index].push_back(button);
    }
}

void Sys::addTextBox(int index, TextBox* textBox)
{
    if (index >= 0 && index < textBoxs.size())
    {
        textBoxs[index].push_back(textBox);
    }
}

void Sys::addLabel(int index, Label* label)
{
    if (index >= 0 && index < labels.size())
    {
        labels[index].push_back(label);
    }
}

void Sys::addTable(int index, TableWidget* table)
{
    if (index >= 0 && index < tables.size())
    {
        tables[index].push_back(table);
    }
}

void Sys::setCurrentIndex(int index)
{
    if (index >= 0 && index < pages.size())
    {
        currentIndex = index;
    }
}

void Sys::mouseClick(int mouseX, int mouseY)
{
    if (currentIndex >= 0 && currentIndex < buttons.size())
    {
        for (Button* button : buttons[currentIndex])
        {
            if (button->checkClick(mouseX, mouseY))
            {
                break;
            }
        }
    }
    if (currentIndex >= 0 && currentIndex < textBoxs.size())
    {
        for (auto textbox : textBoxs[currentIndex])
        {
            textbox->checkClick(mouseX, mouseY);
        }
    }
    if (currentIndex >= 0 && currentIndex < tables.size())
    {
        for (auto table : tables[currentIndex])
        {
            table->handleMouseClick(mouseX, mouseY);
        }
    }
}

void Sys::mouseMove(int mouseX, int mouseY)
{

    if (currentIndex >= 0 && currentIndex < buttons.size())
    {
        for (Button* button : buttons[currentIndex])
        {
            button->checkMouseOver(mouseX, mouseY);
        }
    }
}

void Sys::mouseWheel(int mouseX, int mouseY, int wheel)
{
    if (currentIndex >= 0 && currentIndex < tables.size())
    {
        for (auto table:tables[currentIndex])
        {
            table->scroll(mouseX, mouseY, wheel);
        }
    }
}

void Sys::keyInput(wchar_t ch)
{
    if (currentIndex >= 0 && currentIndex < textBoxs.size())
    {
        for (auto textbox : textBoxs[currentIndex])
        {
            if (textbox->getSelect())
            {
                textbox->keyInput(ch);
            }
        }
    }
}

void Sys::draw()
{
    if (currentIndex >= 0 && currentIndex < pages.size())
    {
        putimage(0, 0, pages[currentIndex]);

        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                button->draw();
            }
        }

        if (currentIndex >= 0 && currentIndex < textBoxs.size())
        {
            for (auto textbox : textBoxs[currentIndex])
            {
                if (textbox->getSelect())
                {
                    textbox->updateCursor();
                }
                textbox->draw();
            }
        }

        if (currentIndex >= 0 && currentIndex < labels.size())
        {
            for (auto label : labels[currentIndex])
            {
                label->draw();
            }
        }

        if (currentIndex >= 0 && currentIndex < tables.size())
        {
            for (auto table : tables[currentIndex])
            {
                table->draw();
            }
        }
    }
}

void Sys::load()
{
    wstring name, password;
    wifstream wfin;
    wfin.imbue(std::locale("chs"));
    wfin.open(READER);
    if (wfin.is_open()) {
        while (!wfin.eof()) {
            wfin >> name >> password;
            if (!name.empty()) {
                readerPassword[name] = password;
            }
        }
        wfin.close();
    }
    
    wfin.open(ADMIN);
    if (wfin.is_open()) {
        while (!wfin.eof()) {
            wfin >> name >> password;
            if (!name.empty()) {
                adminPassword[name] = password;
            }
        }
        wfin.close();
    }

    wfin.open(BOOK);
    if (wfin.is_open()) {
        while (!wfin.eof()) {
            Book* book = new Book;
            wfin >> book->ID >> book->Name>> book->Author>> book->Publish>> book->publishDate
                >> book->price>> book->num>> book->borrowNum;
            if (book->ID.empty()) {
                delete book;
            }
            else {
                books[book->ID] = book;
            }
        }
        wfin.close();
    }

    wfin.open(BORROW);
    if (wfin.is_open()) {
        while (!wfin.eof()) {
            wstring name, id;
            wfin >> name >> id;
            if (!name.empty()) {
                borrow.push_back({ name,id });
            }
        }
        wfin.close();
    }
}

void Sys::saveReader()
{
    wofstream wfout;
    wfout.open(READER);
    if (wfout.is_open()) {
        wfout.imbue(std::locale("chs"));
        for (auto& reader : readerPassword) {
            wfout << reader.first << " " << reader.second << endl;
        }
        wfout.close();
    }
}

void Sys::saveBook()
{
    wofstream wfout;
    wfout.open(BOOK);
    if (wfout.is_open()) {
        wfout.imbue(std::locale("chs"));
        for (auto &book :books) {
            wfout << book.second->ID << " " << book.second->Name << " " << book.second->Author
                << " " << book.second->Publish << " " << book.second->publishDate
                << " " << book.second->price << " " << book.second->num << " " << book.second->borrowNum << endl;
        }
        wfout.close();
    }
}

void Sys::saveBorrow()
{
    wofstream wfout;
    wfout.open(BORROW);
    if (wfout.is_open()) {
        wfout.imbue(std::locale("chs"));
        for (auto i : borrow) {
            wfout << i.at(0) << " " << i.at(1) << endl;
        }
        wfout.close();
    }
}

void Sys::updataBookTable()
{
    bookTable.clear();
    bookTable.push_back({ L"编号",L"书名",L"作者",L"出版社",L"出版日期",L"价格",L"馆藏数",L"借阅数" });
    for (auto &book : books) {
        vector<wstring> temp;
        temp.push_back(book.second->ID);
        temp.push_back(book.second->Name);
        temp.push_back(book.second->Author);
        temp.push_back(book.second->Publish);
        temp.push_back(book.second->publishDate);
        temp.push_back(book.second->price);
        temp.push_back(book.second->num);
        temp.push_back(book.second->borrowNum);
        bookTable.push_back(temp);
    }
}

void Sys::updataBorrowTable()
{
    borrowTable.clear();
    borrowTable.push_back({ L"编号",L"书名",L"作者",L"出版社" });
    for (auto b : borrow) {
        if (b.at(0) == currentUser) {
            borrowTable.push_back({ books[b.at(1)]->ID,books[b.at(1)]->Name,books[b.at(1)]->Author,
                books[b.at(1)] ->Publish});
        }
    }
}

void Sys::init()
{
    initgraph(width, height);

    load();
    updataBookTable();
    updataBorrowTable();

    IMAGE* page1 = new IMAGE(width, height);
    setfillcolor(RGB(240, 240, 240));
    solidrectangle(0, 0, width, height);
    getimage(page1, 0, 0, width, height);
    addPage(page1);

    Label* label1_1 = new Label(200, 100, 400, 80, L"图书管理系统");
    Label* label1_2 = new Label(250, 250, 50, 40, L"账户");
    TextBox* textbox1_1 = new TextBox(330, 260, 200, 25, 12);
    Label* label1_3 = new Label(250, 350, 50, 40, L"密码");
    TextBox* textbox1_2 = new TextBox(330, 360, 200, 25, 12);
    addLabel(0, label1_1);
    addLabel(0, label1_2);
    addLabel(0, label1_3);
    addTextBox(0, textbox1_1);
    addTextBox(0, textbox1_2);
    Button* button1_1 = new Button(230, 450, 80, 30, L"用户注册", [&]() {
        setCurrentIndex(1);   //跳转到注册界面
        });
    Button* button1_2 = new Button(330, 450, 80, 30, L"用户登录", [&]() {
        wstring name = textBoxs[0][0]->getText();
        wstring password = textBoxs[0][1]->getText();
        if (readerPassword.find(name) != readerPassword.end() && readerPassword[name] == password) {
            textBoxs[0][0]->clear();
            textBoxs[0][1]->clear();
            currentUser = name;
            updataBorrowTable();
            setCurrentIndex(4);
        }
        else {
            MessageBox(GetHWnd(), L"登录失败", L"警告", MB_ICONWARNING | MB_OK);
        }
        });
    Button* button1_3 = new Button(430, 450, 100, 30, L"管理员登录", [&]() {
        wstring name = textBoxs[0][0]->getText();
        wstring password = textBoxs[0][1]->getText();
        if (adminPassword.find(name) != adminPassword.end() && adminPassword[name] == password) {
            textBoxs[0][0]->clear();
            textBoxs[0][1]->clear();
            setCurrentIndex(2);
        }
        else {
            MessageBox(GetHWnd(), L"登录失败", L"警告", MB_ICONWARNING | MB_OK);
        }
        });
    addButton(0, button1_1);
    addButton(0, button1_2);
    addButton(0, button1_3);

    addPage(page1);
    Label* label2_1 = new Label(250, 250, 50, 40, L"账户");
    TextBox* textbox2_1 = new TextBox(330, 260, 200, 25, 12);
    Label* label2_2 = new Label(250, 350, 50, 40, L"密码");
    TextBox* textbox2_2 = new TextBox(330, 360, 200, 25, 12);
    addLabel(1, label2_1);
    addLabel(1, label2_2);
    addTextBox(1, textbox2_1);
    addTextBox(1, textbox2_2);

    Button* button2_1 = new Button(30, 500, 80, 30, L"返回", [&] {
        textBoxs[1][0]->clear();
        textBoxs[1][1]->clear();
        setCurrentIndex(0);
        });
    Button* button2_2 = new Button(700, 500, 80, 30, L"确定", [&] {
        wstring name = textBoxs[1][0]->getText();
        wstring password = textBoxs[1][1]->getText();
        if (readerPassword.find(name) != readerPassword.end()) {
            MessageBox(GetHWnd(), L"注册失败，该账户已存在", L"警告", MB_ICONWARNING | MB_OK);
        }
        else {
            readerPassword[name] = password;
            MessageBox(GetHWnd(), L"注册成功", L"成功", MB_OK);
            textBoxs[1][0]->clear();
            textBoxs[1][1]->clear();
            saveReader();
            setCurrentIndex(0);
        }
        });
    addButton(1, button2_1);
    addButton(1, button2_2);

    addPage(page1);
    TableWidget* table3_1 = new TableWidget(10, 100, 650, 450, 10);
    table3_1->setData(bookTable);
    Label* label3_1 = new Label(0, 30, 50, 30, L"书名");
    TextBox* text3_1 = new TextBox(0, 60, 150, 25, 12);
    Label* label3_2= new Label(200, 30, 50, 30, L"作者");
    TextBox* text3_2 = new TextBox(210, 60, 120, 25, 8);
    Label* label3_3 = new Label(400, 30, 50, 30, L"出版社");
    TextBox* text3_3 = new TextBox(410, 60, 150, 25, 8);
    addLabel(2, label3_1);
    addTextBox(2, text3_1);
    addLabel(2, label3_2);
    addTextBox(2, text3_2);
    addLabel(2, label3_3);
    addTextBox(2, text3_3);
    addTable(2, table3_1);

    Button* button3_1 = new Button(700, 100, 55, 30, L"添加", [&]() {
        setCurrentIndex(3);
        });
    Button* button3_2 = new Button(700, 200, 55, 30, L"删除", [&]() {
        if (tables[2][0]->getSelectedRow() >= 0) {
            wstring id = tables[2][0]->getSelectedInfo(0);
            if (books[id]->borrowNum!=L"0") {
                MessageBox(GetHWnd(), L"删除失败", L"警告", MB_ICONWARNING | MB_OK);
            }
            else {
                delete books[id];
                books.erase(id);
                MessageBox(GetHWnd(), L"删除成功", L"成功", MB_OK);
                updataBookTable();
                tables[2][0]->setData(bookTable);
                saveBook();
            }
        }
        });
    Button* button3_3 = new Button(700, 300, 55, 30, L"修改", [&]() {
        
        });
    Button* button3_4 = new Button(700, 400, 55, 30, L"查找", [&]() {
        wstring name = textBoxs[2][0]->getText();
        wstring writer = textBoxs[2][1]->getText();
        wstring publish = textBoxs[2][2]->getText();
        vector<vector<wstring>> temp;
        temp.push_back({ L"编号",L"书名",L"作者",L"出版社",L"出版日期",L"价格",L"馆藏数",L"借阅数" });
        for (auto i = bookTable.begin()+1; i != bookTable.end(); ++i) {
            bool flag = false;
            if (name != L""&& i->at(1) != name) {
                flag = true;
            }
            if (writer != L""&&i->at(2)!=writer) {
                flag = true;
            }
            if (publish != L"" && i->at(3) != publish) {
                flag = true;
            }
            if (!flag) {
                temp.push_back(*i);
            }
        }
        tables[2][0]->setData(temp);
        });
    Button* button3_5 = new Button(700, 500, 55, 30, L"返回", [&]() {
        setCurrentIndex(0);
        });

    addButton(2, button3_1);
    addButton(2, button3_2);
    addButton(2, button3_3);
    addButton(2, button3_4);
    addButton(2, button3_5);

    addPage(page1);
    Label* label4_1 = new Label(50, 30, 50, 30, L"编号");
    TextBox* text4_1 = new TextBox(130, 33, 200, 25, 12);
    Label* label4_2 = new Label(50, 110, 50, 30, L"书名");
    TextBox* text4_2 = new TextBox(130, 113, 200, 25, 12);
    Label* label4_3 = new Label(50, 190, 50, 30, L"作者");
    TextBox* text4_3 = new TextBox(130, 193, 200, 25, 12);
    Label* label4_4 = new Label(50, 270, 50, 30, L"出版社");
    TextBox* text4_4 = new TextBox(130, 273, 200, 25, 12);
    Label* label4_5 = new Label(50, 350, 80, 30, L"出版日期");
    TextBox* text4_5 = new TextBox(150, 353, 80, 25, 8);
    Label* label4_6 = new Label(50, 430, 50, 30, L"价格");
    TextBox* text4_6 = new TextBox(130, 433, 80, 25, 8);
    Label* label4_7 = new Label(50, 510, 50, 30, L"数量");
    TextBox* text4_7 = new TextBox(130, 513, 30, 25, 3);
    addLabel(3, label4_1);
    addLabel(3, label4_2);
    addLabel(3, label4_3);
    addLabel(3, label4_4);
    addLabel(3, label4_5);
    addLabel(3, label4_6);
    addLabel(3, label4_7);
    addTextBox(3, text4_1);
    addTextBox(3, text4_2);
    addTextBox(3, text4_3);
    addTextBox(3, text4_4);
    addTextBox(3, text4_5);
    addTextBox(3, text4_6);
    addTextBox(3, text4_7);

    Button* button4_1 = new Button(30, 555, 80, 30, L"返回", [&]() {
        for (auto text : textBoxs[3]) {
            text->clear();
        }
        setCurrentIndex(2);
        });
    Button* button4_2 = new Button(700, 555, 80, 30, L"确定", [&]() {
        wstring id = textBoxs[3][0]->getText();
        if (books.find(id) != books.end()) {
            MessageBox(GetHWnd(), L"添加失败，该图书编号已存在", L"警告", MB_ICONWARNING | MB_OK);
        }
        else {
            Book* book = new Book{ textBoxs[3][0]->getText(),textBoxs[3][1]->getText(),textBoxs[3][2]->getText() ,textBoxs[3][3]->getText() 
            ,textBoxs[3][4]->getText() ,textBoxs[3][5]->getText(),textBoxs[3][6]->getText(),L"0"};
            books[id] = book;
            MessageBox(GetHWnd(), L"添加成功", L"成功", MB_OK);
            updataBookTable();
            tables[2][0]->setData(bookTable);
            saveBook();
        }
        });
    addButton(3, button4_1);
    addButton(3, button4_2);

    addPage(page1);
    Label* label5_1 = new Label(200, 100, 400, 80, L"用户界面");
    Button* button5_1 = new Button(350, 300, 100, 30, L"借阅图书", [&]() {
        updataBookTable();
        tables[2][0]->setData(bookTable);
        setCurrentIndex(5);
        });
    Button* button5_2 = new Button(350, 380, 100, 30, L"归还图书", [&]() {
        updataBorrowTable();
        tables[6][0]->setData(borrowTable);
        setCurrentIndex(6);
        });
    Button* button5_3 = new Button(350, 460, 100, 30, L"返回", [&]() {
        setCurrentIndex(0);
        });
    addLabel(4, label5_1);
    addButton(4, button5_1);
    addButton(4, button5_2);
    addButton(4, button5_3);

    addPage(page1);
    addLabel(5, label3_1);
    addTextBox(5, text3_1);
    addLabel(5, label3_2);
    addTextBox(5, text3_2);
    addLabel(5, label3_3);
    addTextBox(5, text3_3);
    addTable(5, table3_1);
    addButton(5, button3_4);
    Button* button6_1 = new Button(700, 300, 55, 30, L"借阅", [&]() {
        if (tables[2][0]->getSelectedRow() >= 0) {
            int num = _wtoi(tables[2][0]->getSelectedInfo(6).c_str());
            int borrownum = _wtoi(tables[2][0]->getSelectedInfo(7).c_str());
            if (borrownum >= num) {
                MessageBox(GetHWnd(), L"当前可被借阅数目为0，借阅失败", L"警告", MB_ICONWARNING | MB_OK);
            }
            else {
                bool flag = false;
                wstring id = tables[2][0]->getSelectedInfo(0);
                for (auto i : borrowTable) {
                    if (i.at(0)==id) {
                        MessageBox(GetHWnd(), L"已借阅此图书，借阅失败", L"警告", MB_ICONWARNING | MB_OK);
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    books[id]->borrowNum = to_wstring(borrownum + 1);
                    MessageBox(GetHWnd(), L"借阅成功", L"成功", MB_OK);
                    borrow.push_back({ currentUser,id });
                    updataBorrowTable();
                    tables[6][0]->setData(borrowTable);
                    updataBookTable();
                    tables[2][0]->setData(bookTable);
                    saveBook();
                    saveBorrow();
                }
            }
        }
        });
    Button* button6_2 = new Button(700, 500, 55, 30, L"返回", [&]() {
        setCurrentIndex(4);
        });
    addButton(5, button6_1);
    addButton(5, button6_2);

    addPage(page1);
    TableWidget* table7_1 = new TableWidget(10, 100, 650, 450, 10);
    table7_1->setData(borrowTable);
    Button* button7_1 = new Button(700, 300, 55, 30, L"归还", [&]() {
        if (tables[6][0]->getSelectedRow() >= 0) {
            wstring id = tables[6][0]->getSelectedInfo(0);
            for (auto i = borrow.begin(); i != borrow.end(); ++i) {
                if (i->at(1) == id) {
                    borrow.erase(i);
                    break;
                }
            }
            MessageBox(GetHWnd(), L"归还成功", L"成功", MB_OK);
            int borrownum = _wtoi(books[id]->borrowNum.c_str());
            books[id]->borrowNum = to_wstring(borrownum - 1);
            updataBookTable();
            tables[2][0]->setData(bookTable);
            updataBorrowTable();
            tables[6][0]->setData(borrowTable);
            saveBook();
            saveBorrow();
        }
        });
    Button* button7_2 = new Button(700, 500, 55, 30, L"返回", [&]() {
        setCurrentIndex(4);
        });
    addButton(6, button7_1);
    addButton(6, button7_2);
    addTable(6, table7_1);

    currentIndex = 0;
}

void Sys::run()
{
    ExMessage msg;

    BeginBatchDraw();
    while (true)
    {
        if (peekmessage(&msg))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                mouseClick(msg.x, msg.y);
                break;
            case WM_MOUSEMOVE:
                mouseMove(msg.x, msg.y);
                break;
            case WM_MOUSEWHEEL:
                mouseWheel(msg.x, msg.y, msg.wheel);
                break;
            case WM_CHAR:
                keyInput(msg.ch);
                break;
            }
        }
        draw();
        FlushBatchDraw();
        Sleep(5);
    }
    EndBatchDraw();
}

void Sys::close()
{
    closegraph();
}