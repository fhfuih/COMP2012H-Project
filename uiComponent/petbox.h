#ifndef PETBOX_H
#define PETBOX_H

#include <QPushButton>

#include "Utils.h"

class PetBox : public QPushButton
{
    Q_OBJECT
    /* Wrapper of clickable pet monster button on the SelectionWindow
     * provides a simple interface to change its border
     * and emit signals on MounseEnter for SelectionWindow to display
     * correct thumbnail */
public:
    PetBox(int id, QWidget* parent = nullptr);
    int get_id();
    bool get_selected();
    void set_selected(bool s);

private:
    int id;
    bool selected;

signals:
    void mouse_entered(int id);
    void mouse_clicked(int id);

private slots:
    virtual void enterEvent(QEvent* event) override;
    void on_self_clicked();
};

#endif // PETBOX_H
