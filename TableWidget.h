#pragma once
#include <graphics.h>
#include <string>
#include <vector>
using namespace std;

class TableWidget {
private:
    int x;
    int y;
    int width;
    int height;
    int visibleRowCount;
    int rowHeight;
    int scrollOffset;
    vector<vector<wstring>> data;
    vector<int> columnWidths;
    int selectedRow;
    int scrollbarWidth;
    int handleHeight;
    int handleY;

public:
    TableWidget(int x, int y, int width, int height, int visibleRowCount)
        : x(x), y(y), width(width), height(height), visibleRowCount(visibleRowCount) {
        data = { {} };
        rowHeight = height / visibleRowCount;
        selectedRow = -1;
        scrollOffset = 0;
        scrollbarWidth = 20;
        handleHeight = 30;
        handleY = 0;
    }

    int getSelectedRow() const
    {
        return selectedRow;
    }

    wstring getSelectedInfo(int col) const
    {
        return data[selectedRow][col];
    }

    void setData(const vector<vector<wstring>>& newData)
    {
        data = newData;
        calculateColumnWidths();
    }

    void calculateColumnWidths();

    void scrollUp();

    void scrollDown();

    void scroll(int mouseX, int mouseY, int wheel);

    void handleMouseClick(int mouseX, int mouseY);

    void draw();
};
