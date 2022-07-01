#ifndef SELECTION_H
#define SELECTION_H
#include <QDate>
#include <QDialog>
#include <dbclass.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QMessageBox>
#include <checkout.h>
#include <login.h>
#include <QObject>
#include <QSqlRecord>

extern QString busname;
extern QString from;
extern QString to;
extern QString dtime;
extern QString id;
extern QString ddate;
extern int fare;

namespace Ui {
class selection;
}

class selection : public QDialog
{
    Q_OBJECT

public:
    explicit selection(QWidget *parent = nullptr);
    ~selection();

private slots:

    void on_inputgo_clicked();

    void on_bustable_clicked(const QModelIndex &index);

    void on_logoutbutton_clicked();

private:
    Ui::selection *ui;
    QString ifrom;
    QString ito;
    QString ac;
};

#endif // SELECTION_H
