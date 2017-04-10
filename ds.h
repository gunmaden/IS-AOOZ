#ifndef DS_H
#define DS_H

#include <QWidget>

namespace Ui {
class DS;
}

class DS : public QWidget
{
    Q_OBJECT

public:
    explicit DS(QWidget *parent = 0);
    ~DS();

private:
    Ui::DS *ui;
};

#endif // DS_H
