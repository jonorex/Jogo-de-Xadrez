#ifndef JANELA_H
#define JANELA_H

#include <QMainWindow>

class Tabuleiro;

class Janela : public QMainWindow
{
    Q_OBJECT
    static Janela *instancia;
    QWidget quadro;
    int teste;
    explicit Janela(QWidget *parent = nullptr);
    Janela(const Janela &);
    Janela operator=(Janela);
public:
    static Janela *getInstancia(){
        if(instancia==NULL){
            instancia = new Janela();
        }
        return instancia;
    }

signals:

public slots:
    void Clique();
    void Salvar();
    void Abrir();
    void Adicionar();
    void Excluir();

private:
    Tabuleiro *tabuleiro;

    void inicaMenu();

};



#endif // JANELA_H
