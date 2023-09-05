#include "Label.h"

void Label::setText(const std::wstring& newText)
{
    text = newText;
}

void Label::draw()
{
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(height * 0.8, 0, _T("ËÎÌו"));
    int textX = x + (width - textwidth(text.c_str())) / 2;
    int textY = y + (height - textheight(_T("ËÎÌו"))) / 2;
    outtextxy(textX, textY, text.c_str());
}