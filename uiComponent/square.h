#ifndef SQUARE_H
#define SQUARE_H

#include <QPushButton>
#include <QString>

#include <map>

#include "Utils.h"

typedef std::map<std::string, std::string> StyleMap;

class Square : public QPushButton
{
    Q_OBJECT
public:
    Square(int _row, int _col, Type _type, QWidget* parent = nullptr);

    /* Style manipulations
     *
     * only settings of highlight and type (image) are provided
     */
    void set_highlighted(bool value, std::string color="red");
    bool get_highlighted() const;
    Type get_type() const;
    void set_type(Type type);

    /* Coordinate getters */
    int get_row() const;
    int get_col() const;

private:
    /* Geometry and style data */
    int row, col;
    StyleMap style;
    bool is_highlighted;
    Type type;

    static const int OFFSET_X = 50;
    static const int OFFSET_Y = 50;
    static const int SQUARE_WIDTH = 80;
    static const int SQUARE_HEIGHT = 80;

    /* Underlying style manipulations
     *
     * including settings of raw stylesheet and geometries
     */
    void setStyle(std::string key, std::string value);
    void applyStyle();
    void render();
    void render_image();

    /* Event Handler
     *
     * Translation of clicked event,
     * so that the coordinates are passed along the signal */
signals:
    void clicked_with_pos(int row, int col);

private slots:
    void clicked_handler();
};

#endif // SQUARE_H
