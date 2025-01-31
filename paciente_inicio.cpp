#include "paciente_inicio.h"
#include "ui_paciente_inicio.h"
#include "QMessageBox"
#include "QDebug"

#include "paciente_atendimentos.h"
#include "paciente_cadastro.h"
#include "login.h"

Paciente_inicio::Paciente_inicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Paciente_inicio)
{
    ui->setupUi(this);
}

Paciente_inicio::~Paciente_inicio()
{
    delete ui;
}

//Botão para a tela de Atendimentos - Pacientes (botaoAtendimentos)
//Utilizando do método mudarId da classe Paciente_cadastro para passagem do Id do paciente correto (herança)
void Paciente_inicio::on_botaoAtendimentos_clicked()
{
    QString id = ui->label_id->text();
    Paciente_atendimentos *irAtendimentos = new Paciente_atendimentos(this);
    close();        
    irAtendimentos ->show();
    irAtendimentos->mudarId(id);
}

//Botão para a tela de Cadastro - Pacientes (botaoCadastro)
//Utilizando do método mudarId da classe Paciente_cadastro para passagem do Id do paciente correto (herança)
void Paciente_inicio::on_botaoCadastro_clicked()
{
    QString id = ui->label_id->text();
    Paciente_cadastro *irCadastro = new Paciente_cadastro(this);
    close();
    irCadastro->show();
    irCadastro->mudarId(id);
}

//Botão para a tela de Login (botaoSair)
void Paciente_inicio::on_botaoSair_clicked()
{
    Login *voltarLogin = new Login(this);
    close();
    voltarLogin->show();
}

//Método para receber o Id do paciente correto, vindo de acordo com o username e senha da tela de Login (herança)
void Paciente_inicio::mudarNomeId(const QString &id)
{
    ui->label_id->setText(id);

    //Query para indicar o paciente correto de acordo com o Id fornecido
    QSqlQuery query_nome;
    query_nome.prepare("SELECT nome FROM pacientes WHERE id = :id");
    query_nome.bindValue(":id", id);

    if(query_nome.exec()){
        if (query_nome.next()){
            QString nome_paciente = query_nome.value(0).toString();
            ui->label_nome->setText(nome_paciente);
            qDebug()<<"Nome do paciente: "<<nome_paciente;
        }
    }
}

