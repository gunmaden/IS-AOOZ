#ifndef PREPARE_H
#define PREPARE_H

#include <QWidget>

extern QStringList groups;
extern QStringList students;

namespace Ui {
class prepare;
}

class prepare : public QWidget
{
    Q_OBJECT

public:
    explicit prepare(QWidget *parent = 0);
    ~prepare();

private:
    Ui::prepare *ui;
};

#endif // PREPARE_H
