#ifndef LOGIN_H
#define LOGIN_H
#include <dbclass.h>
#include <QMainWindow>
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <selection.h>
#include <admin.h>
QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

extern QString sname;
extern QString semail;
extern QString snumber;
extern int sreward;
class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_subotton_clicked();

    void on_pushButton_clicked();

private:
    Ui::login *ui;
};
#endif // LOGIN_H
