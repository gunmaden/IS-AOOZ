#ifndef KLASTER_H
#define KLASTER_H

#include <QWidget>
#include <QSqlDatabase>
extern QSqlDatabase sdb;
extern QSqlQuery query;
extern bool ok;
extern QString FIO;

namespace Ui {
class klaster;
}

class klaster : public QWidget
{
    Q_OBJECT

public:
    explicit klaster(QWidget *parent = 0);
    ~klaster();

public slots:
    void test();

//private slots:

private:
    Ui::klaster *ui;

};

#endif // KLASTER_H
