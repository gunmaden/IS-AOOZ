#include "admin_addus.h"
#include "ui_admin_addus.h"
#include "admin_users.h"
#include "QSqlQueryModel"
#include <QSqlRecord>
#include <QUuid>
#include <QSqlQuery>
#include <QDebug>
#include "admin.h"
#include <QMessageBox>

QStringList userTypesNameRu, userTypesId;


Admin_addus::Admin_addus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_addus)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление пользователей");
    QRegExp fio("^[а-яА-ЯёЁa-zA-Z \.]+$");
    QRegExp rx("^[а-яА-ЯёЁa-zA-Z0-9]+$");
    QValidator *validator = new QRegExpValidator(rx, this);
    QValidator *validator2 = new QRegExpValidator(fio, this);

    ui->lineEdit->setValidator(validator2);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    userTypesNameRu.clear();
    ui->comboBox->clear();

    QSqlQueryModel typesModel;
        QString s = QString("SELECT * FROM \"Dostup\"");

    typesModel.setQuery(s);
    for (int i=0;i<typesModel.rowCount();i++){
        userTypesNameRu<<typesModel.record(i).value("name").toString();
        userTypesId<<typesModel.record(i).value("id_dostup").toString();
    }
    ui->comboBox->addItems(userTypesNameRu);
}

Admin_addus::~Admin_addus()
{
    delete ui;
}



void Admin_addus::on_pushButton_clicked(){
    QUuid uuid;
    QString userId = uuid.createUuid().toString();
    QString login, password, fio, userType;

    fio = ui->lineEdit->text();
    login = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();
    userType=userTypesId.at(ui->comboBox->currentIndex());


    qDebug()<<userType;

    QSqlQueryModel model1;
    QString d = QString("Select * From \"Users\" Where login = '%1'").arg(ui->lineEdit_2->text());
    model1.setQuery(d);
    if (model1.rowCount()==0)
    {
        if (ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0)
    {


        QSqlQuery q;
        q.prepare("INSERT INTO \"Users\" (\"id_user\",\"FIO\",\"dostup\",\"login\",\"pass\") VALUES(?,?,?,?,?)");
        q.addBindValue(userId);
        q.addBindValue(fio);
        q.addBindValue(userType);
        q.addBindValue(login);
        q.addBindValue(password);

        q.exec();

        QMessageBox::information(this, "Успешно!", "Пользователь был успешно добавлен");


        Admin_users *w2 = new Admin_users();
        w2->show();
        close();
    }

        else
        {
            QMessageBox::information(this, "Ошибка!", "Заполните поля ввода ФИО,логин, пароль");

        }
    }

   else
    {
        QMessageBox::information(this, "Ошибка!", "Пользователь с таким логином уже существует!");
    }


}

void Admin_addus::on_pushButton_2_clicked()
{
    Admin_users *w2 = new Admin_users();
    w2->show();
    close();
}
