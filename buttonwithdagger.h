#ifndef BUTTONWITHDAGGER_H
#define BUTTONWITHDAGGER_H

#include <QWidget>

namespace Ui {
class ButtonWithDagger;
}

class ButtonWithDagger : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonWithDagger(const QString& text = "PushButton", QWidget *parent = nullptr);
    ~ButtonWithDagger() override;

    void setText(const QString& text);

    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::ButtonWithDagger *ui;

signals:
    void clicked();

private slots:
    void on_pressingButton();
};

#endif // BUTTONWITHDAGGER_H
