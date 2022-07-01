#include "login.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //showing splash screen
    QPixmap pixmap(":/resources/resources/splash.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->setPixmap(pixmap.scaled(1024, 768, Qt::KeepAspectRatio));
    splash->show();

    login w;
    QTimer::singleShot(3000, splash,SLOT(close()));
    QTimer::singleShot(3000, &w, SLOT(show()));

    return a.exec();
}
