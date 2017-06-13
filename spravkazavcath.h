#ifndef SPRAVKAZAVCATH_H
#define SPRAVKAZAVCATH_H

#include <QWidget>

namespace Ui {
class SpravkaZavCath;
}

class SpravkaZavCath : public QWidget
{
    Q_OBJECT

public:
    explicit SpravkaZavCath(QWidget *parent = 0);
    ~SpravkaZavCath();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SpravkaZavCath *ui;
};

#endif // SPRAVKAZAVCATH_H
