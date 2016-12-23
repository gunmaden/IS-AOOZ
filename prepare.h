#ifndef PREPARE_H
#define PREPARE_H

#include <QWidget>

extern QStringList groups;
extern QStringList disciples;

namespace Ui {
class prepare;
}

class prepare : public QWidget
{
    Q_OBJECT

public:
    explicit prepare(QWidget *parent = 0);
    ~prepare();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::prepare *ui;
    void fillTable(QList<QStringList> lst);
    void prepareTable(QStringList students, QList<QStringList> studResults);
    QStringList getStudents();
    QList<QStringList> getMarks(QStringList students);
    void fillGroupBox();
};

#endif // PREPARE_H
