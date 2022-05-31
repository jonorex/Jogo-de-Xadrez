#include <QApplication>
#include "janela.h"
#include "tropa.h"
int  main(int argc, char *argv[]){
       QApplication app(argc, argv);

       Janela::getInstancia()->show();

       return app.exec();
}
