#include "medico_inicio.h"
#include "ui_medico_inicio.h"
#include "QDebug"
#include "QMessageBox"
#include <QSql>

#include "medico_atendimentos.h"
#include "medico_cadastro.h"
#include "login.h"

Medico_inicio::Medico_inicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Medico_inicio)
{
    ui->setupUi(this);
}

Medico_inicio::~Medico_inicio()
{
    delete ui;
}

//Botão para a tela de Atendimentos - Médicos (botaoAtendimentos)
//Utilizando do método mudarId da classe Medico_atendimentos para passagem do Id do médico correto (herança)
void Medico_inicio::on_botaoAtendimentos_clicked()
{
    QString id = ui->label_id->text();
    Medico_atendimentos *irAtendimentos = new Medico_atendimentos(this);
    close();
    irAtendimentos->show();
    irAtendimentos->mudarId(id);
}

//Botão para a tela de Cadastro - Médicos (botaoCadastro)
//Utilizando do método mudarId da classe Medico_cadastro para passagem do Id do médico correto (herança)
void Medico_inicio::on_botaoCadastro_clicked()
{
    QString id = ui->label_id->text();
    Medico_cadastro *irCadastro = new Medico_cadastro(this);
    close();
    irCadastro->mudarId(id);
    irCadastro->show();
}

//Botão para a tela de Login (botaoSair)
void Medico_inicio::on_botaoSair_clicked()
{
    Login *voltarLogin = new Login(this);
    close();
    voltarLogin->show();
}

//Método para receber o Id do médico correto, vindo de acordo com o username e senha da tela de Login (herança)
void Medico_inicio::mudarNomeId(const QString &id)
{
    ui->label_id->setText(id);

    //Query para indicar o médico correto de acordo com o Id fornecido
    QSqlQuery query_nome;
    query_nome.prepare("SELECT nome FROM medicos WHERE id = :id");
    query_nome.bindValue(":id", id);

    if(query_nome.exec()){
        if (query_nome.next()){
            QString nome_medico = query_nome.value(0).toString();
            ui->label_nome->setText(nome_medico);
            qDebug()<<"Nome do médico: "<<nome_medico;
        }
    }
}

