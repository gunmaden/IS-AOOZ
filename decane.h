#ifndef DECANE_H
#define DECANE_H

#include <QWidget>

namespace Ui {
class Decane;
}

class Decane : public QWidget
{
    Q_OBJECT

public:
    explicit Decane(QWidget *parent = 0);
    ~Decane();

private:
    Ui::Decane *ui;
};

#endif // DECANE_H
