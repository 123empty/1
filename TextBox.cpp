#include "TextBox.h"
void TextBox::draw()
{
    setfillcolor(WHITE);
    if (isSelected)
    {
        setlinecolor(RGB(0, 120, 215));
        fillrectangle(x, y, x + width, y + height);
    }
    else
    {
        setlinecolor(RGB(122, 122, 122));
        fillrectangle(x, y, x + width, y + height);
    }

    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(height * 3 / 4, 0, _T("ËÎÌו"));

    outtextxy(x + 5, y + (height - textheight(_T("ËÎÌו"))) / 2, text.c_str());

    setlinecolor(BLACK);
    if (isSelected && showCursor)
    {
        int cursorX = x + 5 + textwidth(text.substr(0, cursorPos).c_str());
        line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
    }
}

bool TextBox::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        isSelected = true;
        return true;
    }
    else
    {
        isSelected = false;
        cursorPos = text.length();
        return false;
    }
}

void TextBox::keyInput(wchar_t ch)
{
    if (isSelected)
    {
        switch (ch)
        {
        case '\b':
            if (!text.empty() && cursorPos > 0){
                text.erase(cursorPos - 1, 1);
                cursorPos--;
            }
            break;
        case '\r':
        case '\n':
            cursorPos = text.length();
            isSelected = false;
            break;
        default:
            if (text.length() < maxWord){
                text.insert(cursorPos, 1, ch);
                cursorPos++;
            }
        }
    }
}

void TextBox::updateCursor()
{
    static DWORD lastTick = GetTickCount();
    DWORD currentTick = GetTickCount();
    if (currentTick - lastTick >= 500)
    {
        showCursor = !showCursor;
        lastTick = currentTick;
    }
}