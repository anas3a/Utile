#ifndef CONFIRMATION_H
#define CONFIRMATION_H
#include <selection.h>
#include <QDialog>
#include <checkout.h>

namespace Ui {
class confirmation;
}

class confirmation : public QDialog
{
    Q_OBJECT

public:
    explicit confirmation(QWidget *parent = nullptr);
    ~confirmation();

private slots:
    void on_okbutton_clicked();

private:
    Ui::confirmation *ui;
};

#endif // CONFIRMATION_H
