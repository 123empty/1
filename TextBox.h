#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;
    wstring text;
    bool isSelected;
    bool showCursor;
    int cursorPos;

public:
    TextBox(int x, int y, int width, int height, int maxWord)
        : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0)
    {
    }

    const wstring& getText() const
    {
        return text;
    }

    bool getSelect() const
    {
        return isSelected;
    }

    bool isEmpty() const
    {
        return text.empty();
    }

    void clear()
    {
        setText(L"");
    }

    void setText(const wstring& newText)
    {
        text = newText;
        cursorPos = text.length();
    }

    void draw();

    bool checkClick(int mouseX, int mouseY);

    void keyInput(wchar_t ch);

    void updateCursor();
};