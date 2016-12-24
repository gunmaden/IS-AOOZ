#ifndef DECANE_H
#define DECANE_H

#include <QWidget>
#include <QSqlDatabase>

extern QSqlDatabase sdb;
extern QSqlQuery query;
extern bool ok;

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

private slots:
    void on_pushButton_clicked();
//    void on_pushButton_2_clicked();
//    void on_pushButton_3_clicked();
//    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
};

#endif // DECANE_H
