#include "login.h"

#include <QApplication>

//Executa a aplicação
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}
