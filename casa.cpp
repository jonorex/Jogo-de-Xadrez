#include "casa.h"

#include <QColor>

#define branco Qt::white
#define preto Qt::green


Casa::Casa(QRect R, int X, int Y){
     r = R;
     x= X;
     y = Y;
     if(lastColor){ //não utilizado
         color = Qt::green;
         lastColor = false;
     }else{
         color = Qt::green;
         lastColor = true;
     }
     color = branco;
     ocupado = false;
     select = false;
}

bool Casa::lastColor = false;
