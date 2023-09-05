#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Button
{
private:
    int x;
    int y;
    int width;
    int height;
    float scale;
    bool isMouseOver;
    wstring text;
    function<void()> onClick;

public:
    Button(int x, int y, int width, int height, const wstring& text, const function<void()>& onClick)
        : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false)
    {
    }

    void checkMouseOver(int mouseX, int mouseY);

    bool checkClick(int mouseX, int mouseY);

    void draw();
};