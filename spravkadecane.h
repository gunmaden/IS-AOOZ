#ifndef SPRAVKADECANE_H
#define SPRAVKADECANE_H

#include <QWidget>

namespace Ui {
class SpravkaDecane;
}

class SpravkaDecane : public QWidget
{
    Q_OBJECT

public:
    explicit SpravkaDecane(QWidget *parent = 0);
    ~SpravkaDecane();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SpravkaDecane *ui;
};

#endif // SPRAVKADECANE_H
