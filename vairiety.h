#ifndef VAIRIETY_H
#define VAIRIETY_H

#include <QWidget>

namespace Ui {
class vairiety;
}

class vairiety : public QWidget
{
    Q_OBJECT

public:
    explicit vairiety(QWidget *parent = 0);
    ~vairiety();

private:
    Ui::vairiety *ui;
};

#endif // VAIRIETY_H
