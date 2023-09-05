#include "Button.h"
void Button::checkMouseOver(int mouseX, int mouseY)
{
    isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

    if (isMouseOver) {
        scale = 0.9f;
    }
    else {
        scale = 1.0f;
    }
}

bool Button::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        onClick();
        isMouseOver = false;
        scale = 1.0f;
        return true;
    }
    return false;
}

void Button::draw()
{
    int scaledWidth = width * scale;
    int scaledHeight = height * scale;
    int scaledX = x + (width - scaledWidth) / 2;
    int scaledY = y + (height - scaledHeight) / 2;

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215));
        setfillcolor(RGB(229, 241, 251));

    }
    else
    {
        setlinecolor(RGB(173, 173, 173));
        setfillcolor(RGB(225, 225, 225));
    }

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(20 * scale, 0, _T("Î¢ÈíÑÅºÚ"));
    int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2;
    int textY = scaledY + (scaledHeight - textheight(_T("Î¢ÈíÑÅºÚ"))) / 2;
    outtextxy(textX, textY, text.c_str());
}