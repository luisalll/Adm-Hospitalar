#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>

#include "adm_inicio.h"
#include "medico_inicio.h"
#include "paciente_inicio.h"


//Banco de dados
static QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");

//Inicializando a tela de Login
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    //Conexão com o banco de dados
    QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    //Caminho para o banco de dados (alterar para cada computador)
    bancoDeDados.setDatabaseName("C:/Users/luisa/Documents/.SI/2024.2/Est. de Dados Orientada a Objetos/Adm. Hospitalar/Qt/BDadm_hospitalar_final.db");

    //Checando se o banco de dados foi aberto ou não e mandando o sinal pelo qDebug
    if(!bancoDeDados.open()){
        qDebug()<< "-------------------";
        qDebug()<<"Não foi possível abrir o banco de dados!";
        qDebug()<< "-------------------";

    }else{
        qDebug()<< "-------------------";
        qDebug()<<"Banco de dados aberto com sucesso";
        qDebug()<< "-------------------";

    }

    //Sinal no qDebug para acompanhar o progresso
    qDebug()<< "Você está no Login";

}

//Fechando a interface
Login::~Login()
{
    delete ui;
}

//Botão Entrar (botaoEntrar)
void Login::on_botaoEntrar_clicked()
{
    //Variáveis de username e senha escritas nas caixas de texto
    QString username=ui->txtUsername->text();
    QString senha=ui->txtSenha->text();

    //Ponteiros para passagem à tela de início correta
    ADM_inicio *inicioADM=new ADM_inicio(this);
    Medico_inicio *inicioMEDICO=new Medico_inicio(this);
    Paciente_inicio *inicioPACIENTE=new Paciente_inicio(this);

    int cont1 = 0;
    int cont2 = 0;

    //Querys para determinar se é um cadastro de paciente ou médico
    QSqlQuery query;
    QSqlQuery query_2;

    //Query para checar se o login e senha correspondem ao cadastro de algum médico
    if(query.exec("select * from medicos where username ='"+username+"' and senha='"+senha+"'")){
        cont1 = 0;
        //While para achar o login na tabela de médicos (se achar, vai achar apenas um)
        while(query.next()){
            cont1++;
        }
        //Caso o login ocorra, o qDebug manda uma mensagem de progresso e indica o programa para tela de Início - Médicos
        if(cont1>0){
            qDebug()<<"Login Médicos";
            qDebug()<< "-------------------";
            qDebug()<< "Você está na tela de Início - Médicos";

            //Seleção do Id do médico que fez login para a passagem de dados correta, utilizando o método 'mudarNomeId' da classe Medico_inicio (herança)
            if(query_2.exec("select id from medicos where username ='"+username+"' and senha='"+senha+"'")){
                if (query_2.next()){
                    QString id = query_2.value(0).toString();
                    inicioMEDICO->mudarNomeId(id);
                }
            }

            //Fechamento da tela de login para abrir a tela de Início - Médico
            close();
            inicioMEDICO->show();
        }
    }

    //Query para checar se o login e senha correspondem ao cadastro de algum paciente
    if(query.exec("select * from pacientes where username ='"+username+"' and senha='"+senha+"'")){
        cont2 = 0;
        //While para achar o login na tabela de pacientes (se achar, vai achar apenas um)
        while(query.next()){
            cont2++;
        }
        //Caso o login ocorra, o qDebug manda uma mensagem de progresso e o programa é indicado para tela de Início - Pacientes
        if(cont2>0){
            qDebug()<<"Login Paciente";
            qDebug()<< "-------------------";
            qDebug()<< "Você está na tela de Início - Pacientes";

            //Seleção do Id do paciente que fez login para a passagem de dados correta, utilizando o método 'mudarNomeId' da classe Paciente_inicio (herança)
            if(query_2.exec("select id from pacientes where username ='"+username+"' and senha='"+senha+"'")){
                if (query_2.next()){
                    QString id = query_2.value(0).toString();
                    inicioPACIENTE->mudarNomeId(id);
                }
            }

            //Fechamento da tela de login para abrir a tela de Início - Médico
            close();
            inicioPACIENTE->show();
        }
    }

    //Caso o que for escrito for o login e senha do ADM, o qDebug manda uma mensagem de progresso e o programa é indicado para tela de Início - ADM
    if(username=="adm_hospital" && senha=="adm_hospital"){
        qDebug()<<"Você fez login com ADM";
        qDebug()<< "-------------------";
        qDebug()<< "Você está na tela de Início - ADM";
        close();
        inicioADM->show();
    }
    //Caso nenhuma das alternaticas execute, o programa manda um sinal de erro e limpa os espaços de escrita
    if(cont1==0 && cont2==0 && username!="adm_hospital" && senha!="adm_hospital"){
        QMessageBox::warning(this,"Login","Senha ou login incorreto");
        ui->txtUsername->clear();
        ui->txtSenha->clear();
        ui->txtUsername->setFocus();
    }
}
