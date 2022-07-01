#include "selection.h"
#include "ui_selection.h"
#include "login.h"

QString busname = "";
QString from = "";
QString to = "";
QString dtime = "";
QString id = "";
QString ddate = "";
int fare = 0;
selection::selection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selection)
{
    //Initial setup of page

    ui->setupUi(this);

    ui->fromcombo->addItem("Dhaka");
    ui->fromcombo->addItem("Chittagong");
    ui->fromcombo->addItem("Sylhet");
    ui->fromcombo->addItem("Khulna");
    ui->fromcombo->addItem("Rajshahi");
    ui->fromcombo->addItem("Barishal");

    ui->tocombo->addItem("Chittagong");
    ui->tocombo->addItem("Dhaka");
    ui->tocombo->addItem("Sylhet");
    ui->tocombo->addItem("Khulna");
    ui->tocombo->addItem("Rajshahi");
    ui->tocombo->addItem("Barishal");

    ui->typecombo->addItem("AC");
    ui->typecombo->addItem("Non AC");

    ui->dateset->setCalendarPopup(true);
    ui->dateset->setDisplayFormat("dd.MM.yyyy");
    ui->dateset->setMinimumDate(QDate::currentDate());
    ui->dateset->setMaximumDate(QDate::currentDate().addMonths(2));

    ui->namelabel->setText(sname);
    ui->pointshow->setNum(sreward);

    ui->bustable->hide();
}

selection::~selection()
{
    delete ui;
}


void selection::on_inputgo_clicked()
{
    //buslist after user chooses the criteria.

    dbclass db;
    db.connect();

    ifrom = ui->fromcombo->currentText();
    ito = ui->tocombo->currentText();
    ac = ui->typecombo->currentText();


    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT name, fare, time FROM bus WHERE bfrom = '"+ifrom+"' AND bto = '"+ito+"' AND ac = '"+ac+"'");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, tr("BUS Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Fare (BDT)"));
    model->setHeaderData(2, Qt::Horizontal, tr("Departure Time"));
    ui->bustable->setModel(model);
    ui->bustable->show();
    ui->bustable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    db.disconnect();
}

void selection::on_bustable_clicked(const QModelIndex &index)
{
    // User choosed a bus and clicked it

    dbclass db;
    db.connect();
    QSqlQueryModel *model1 = new QSqlQueryModel;
    QSqlQuery *query1 = new QSqlQuery;
    query1->prepare("SELECT * FROM bus WHERE bfrom = '"+ifrom+"' AND bto = '"+ito+"' AND ac = '"+ac+"'");
    query1->exec();
    model1->setQuery(*query1);
    QSqlRecord record = model1->record(index.row());
    busname = record.value(0).toString();
    from = record.value(1).toString();
    to = record.value(2).toString();
    fare = record.value(3).toInt();
    dtime = record.value(5).toString();
    id = record.value(6).toString();
    ddate = ui->dateset->date().toString();
    db.disconnect();

    //Going to checkout window
    this->hide();
    checkout *checkoutwindow;
    checkoutwindow = new checkout(this);
    checkoutwindow->show();
}

void selection::on_logoutbutton_clicked()
{
    //logout

    this->hide();
    login *loginwindow;
    loginwindow = new login(this);
    loginwindow->show();
}

