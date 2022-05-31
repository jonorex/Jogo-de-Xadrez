#include "janela.h"
#include <QPushButton>
#include <QDebug>
#include "tabuleiro.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QVector>
#include "adicionartropa.h"
#include <QInputDialog>


QString local = "C:/Users/joaov/Documents/xadreizinho/";


Janela::Janela(QWidget *parent) : QMainWindow(parent), tabuleiro(new Tabuleiro(this)){

    //tabuleiro->setGeometry(0,0,400,400);
    setCentralWidget(tabuleiro);

    setWindowTitle(tr("Xadreizinho"));
    resize(400, 400);

    setGeometry(0,0,400,400);
    setFixedSize(400,400);

    inicaMenu();


}

Janela* Janela::instancia = NULL;



void Janela::inicaMenu(){
    QMenuBar *barra = new QMenuBar(this);
    QMenu *menuArquivo = new QMenu("Arquivo", this);
    QMenu *tropas = new QMenu("Tropas", this);
    barra->addMenu(menuArquivo);
    barra->addMenu(tropas);


    QAction *acaoSalvar = new QAction("Salvar", this);
    QAction *acaoAbrir = new QAction("Abrir",this);
    QAction *acaoAdicionar = new QAction("Adiconar",this);
    QAction *acaoExcluir = new QAction("Excluir",this);
    menuArquivo->addAction(acaoSalvar);
    menuArquivo->addAction(acaoAbrir);
    tropas->addAction(acaoAdicionar);
    tropas->addAction(acaoExcluir);


    connect(acaoSalvar, SIGNAL(triggered(bool)), this, SLOT(Salvar()));
    connect(acaoAbrir, SIGNAL(triggered(bool)), this, SLOT(Abrir()));
    connect(acaoAdicionar, SIGNAL(triggered(bool)), this, SLOT(Adicionar()));
    connect(acaoExcluir, SIGNAL(triggered(bool)),this, SLOT(Excluir()));
}

void Janela::Adicionar(){
    QStringList items;
    items << tr("torre") << tr("bispo") << tr("rainha");
    QString text = QInputDialog::getItem(this, tr("Escolha a tropa"), tr("Tropa:"),items,0,false);
    int x = QInputDialog::getInt(this,tr("Posição x"), tr("x:"), 25, 0, 7);
    int y = QInputDialog::getInt(this,tr("Posição y"), tr("x:"), 25, 0, 7);
 //   qDebug() <<"Janela" << x << y;
    try {
        tabuleiro->adicionarTropa(QPoint(x,y),text);
    }  catch (int e) {
        QMessageBox::warning(this,"Erro", "Erro ao adicionar");
    }

}

void Janela::Clique(){

}

void Janela::Salvar(){
   QString salvarArquivo=QFileDialog::getSaveFileName(this,"Abrir Arquivos",local);
   QFile arquivo(salvarArquivo);

   if(!arquivo.open(QFile::WriteOnly|QFile::Text)){
      QMessageBox::warning(this, "ERRO", "Erro ao abrir arquivo");
   }

   QTextStream saida(&arquivo);

   QString texto = tabuleiro->getSave();
   saida << texto;
   arquivo.flush();
   arquivo.close();
}

void Janela::Abrir(){
    QString filtros = "Arquivos txt (*.txt)";
    QString abrirArquivo=QFileDialog::getOpenFileName(this,"Abrir Arquivos",local, filtros);
    QFile arquivo(abrirArquivo);
    if(!arquivo.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Erro", "Erro ao abrir o arquivo");
    }
    QTextStream stream(&arquivo);
      int j = 0;
      QString line;
      QVector<QString> v;
      while (!stream.atEnd()){
           line = stream.readLine();
           v.push_back(line);
          j++;
      }
      tabuleiro->abrirArquivo(v);
      arquivo.close();
   }

void Janela::Excluir(){
    int x = QInputDialog::getInt(this,tr("Posição x"), tr("x:"), 25, 0, 7);
    int y = QInputDialog::getInt(this,tr("Posição y"), tr("x:"), 25, 0, 7);
    try {
        tabuleiro->excluir(QPoint(x,y));
    }  catch (int e) {
       QMessageBox::warning(this,"Erro", "Casa vazia");
    }
}


