#include "login.h"
#include "ui_login.h"

QString sname = " ";
QString semail= " ";
QString snumber = " ";
int sreward = 0;
login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_subotton_clicked()
{
    //signup button clicked

    QString name = ui->suname->text();
    QString contact = ui->sucontact->text();
    QString email = ui->suemail->text();
    QString password = ui->supass->text();
    if (email == "" || password == "")
    {
        QMessageBox::warning(this, "info", "Email or Password field is empty");
    }
    else
    {
        dbclass db;
        db.connect();

        QSqlQuery query, query1;
        query.exec("SELECT * FROM user WHERE email = '"+email+"'");
        {
            if (query.next())
                QMessageBox::warning(this, "Sign up", "Email already in use!");
            else
            {
                //adding user to databse

                 query1.exec("INSERT INTO user (name, number, email, password, reward) VALUES ('"+name+"', '"+contact+"', '"+email+"', '"+password+"', '100')");
                 qDebug() << "signup worked" << Qt::endl;
                 QMessageBox::information(this, "info", "Sign Up successful!\n  Plaease login.");
                 ui->suname->clear();
                 ui->sucontact->clear();
                 ui->suemail->clear();
                 ui->supass->clear();
             }
         }
        db.disconnect();
    }
}

void login::on_pushButton_clicked()
{
    QString email = ui->liemail->text();
    QString password = ui->lipass->text();

    if (email == "admin" && password == "321")
    {
        //for admin panel access

        this->hide();
        admin *adminwindow;
        adminwindow = new admin(this);
        adminwindow->show();

    }
    else
    {
        //user login.

        dbclass db;
        db.connect();

        QSqlQuery query;
        bool flag = false;
        if(query.exec("SELECT * FROM user WHERE email = '"+email+"' AND password = '"+password+"'"))
        {
            qDebug() << "login worked" << Qt::endl;
            if (query.next())
                flag = true;
            if (flag)
            {
                sname = query.value(0).toString();
                snumber = query.value(1).toString();
                semail = query.value(2).toString();
                sreward = query.value(4).toInt();

                //Going to selection window

                selection *selectwindow;
                selectwindow = new selection(this);
                this->hide();
                selectwindow->show();
            }
            else
                QMessageBox::warning(this, "Log in", "Incorrect email or password.");
        }

        db.disconnect();
    }
}


