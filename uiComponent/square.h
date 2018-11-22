#ifndef SQUARE_H
#define SQUARE_H

#include <QPushButton>
#include <QString>

#include <map>

#include "Type.h"

typedef std::map<std::string, std::string> StyleMap;

class Square : public QPushButton
{
    Q_OBJECT
public:
    Square(QWidget* parent=nullptr, int _row=0, int _col=0);
    void set_highlighted(bool value, std::string color="black");
    bool get_highlighted() const;
    void setStyle(std::string key, std::string value);
    void applyStyle();
    void set_orb(Type type);
    char get_orb() const;

private:
    void render();

    int row, col;
    StyleMap style;
    bool is_highlighted;
    Type type;

    static const int OFFSET_X = 0;
    static const int OFFSET_Y = 0;
    static const int SQUARE_WIDTH = 80;
    static const int SQUARE_HEIGHT = 80;

    static Square* selected;

signals:
    void clicked_with_pos(int row, int col);

private slots:
    void clicked_handler();
};

#endif // SQUARE_H
