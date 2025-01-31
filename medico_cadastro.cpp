#include "medico_cadastro.h"
#include "ui_medico_cadastro.h"
#include "QMessageBox"
#include "QDebug"

#include "medico_inicio.h"
#include "medico_atendimentos.h"
#include "login.h"

//Inicializando a tela de Cadastro - Médico
Medico_cadastro::Medico_cadastro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Medico_cadastro)
{
    ui->setupUi(this);
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Cadastro - Médicos";
}

//Fechando a interface
Medico_cadastro::~Medico_cadastro()
{
    delete ui;
}

//Botão para a tela de Início - Médicos (botaoInicio)
//Utilizando do método mudarNomeId da classe Medico_inicio para passagem do Id do médico correto (herança)
void Medico_cadastro::on_botaoIncio_clicked()
{
    QString id = ui->label_num_id->text();
    Medico_inicio *irInicio = new Medico_inicio(this);
    close();
    irInicio->show();
    irInicio->mudarNomeId(id);
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - Médicos";
}

//Botão para a tela de Atendimentos - Médicos (botaoAtendimentos)
//Utilizando do método mudarId da classe Medico_atendimentos para passagem do Id do médico correto (herança)
void Medico_cadastro::on_botaoAtendimentos_clicked()
{
    QString id = ui->label_num_id->text();
    Medico_atendimentos *irAtendimentos = new Medico_atendimentos(this);
    close();
    irAtendimentos->show();
    irAtendimentos->mudarId(id);
}

//Botão para a tela de Login (botaoSair)
void Medico_cadastro::on_botaoSair_clicked()
{
    Login *voltarLogin = new Login(this);
    close();
    voltarLogin->show();
}

//Método para receber o Id do médico correto, vindo da tela anterior (herança)
void Medico_cadastro::mudarId (const QString &id)
{
    ui->label_num_id->setText(id);
    //Query para colocar o nome correspondente ao médico certo
    QSqlQuery query_nome;
    query_nome.prepare("SELECT nome FROM medicos WHERE id = :id");
    query_nome.bindValue(":id",id);
    if (query_nome.exec()){
        if(query_nome.next()){
            //Nome colocado no lineEdit do nome
            QString nome_paciente = query_nome.value(0).toString();
            ui->txt_nome->setText(nome_paciente);
        }
    }

    //Query para colocar o username correspondente ao médico certo
    QSqlQuery query_username;
    query_username.prepare("SELECT username FROM medicos WHERE id = :id");
    query_username.bindValue(":id",id);
    if (query_username.exec()){
        if(query_username.next()){
            //Username colocado no lineEdit do username
            QString username_paciente = query_username.value(0).toString();
            ui->txt_username->setText(username_paciente);
        }
    }

    //Query para colocar a senha correspondente ao médico certo
    QSqlQuery query_senha;
    query_senha.prepare("SELECT senha FROM medicos WHERE id = :id");
    query_senha.bindValue(":id",id);
    if (query_senha.exec()){
        if(query_senha.next()){
            //Senha colocad no lineEdit da senha
            QString senha_paciente = query_senha.value(0).toString();
            ui->txt_senha->setText(senha_paciente);
        }
    }
}

//Botão cancelar, colocando as informações de antes de serem editadas (botaoCancelar)
void Medico_cadastro::on_botaoCancelar_clicked()
{
    int id = ui->label_num_id->text().toInt();

    //Query para colocar o nome correspondente ao médico certo
    QSqlQuery query_nome;
    query_nome.prepare("SELECT nome FROM medicos WHERE id = :id");
    query_nome.bindValue(":id",id);
    if (query_nome.exec()){
        if(query_nome.next()){
            //Nome colocado no lineEdit do nome
            QString nome_paciente = query_nome.value(0).toString();
            ui->txt_nome->setText(nome_paciente);
        }
    }

    //Query para colocar o username correspondente ao médico certo
    QSqlQuery query_username;
    query_username.prepare("SELECT username FROM medicos WHERE id = :id");
    query_username.bindValue(":id",id);
    if (query_username.exec()){
        if(query_username.next()){
            //Username colocado no lineEdit do username
            QString username_paciente = query_username.value(0).toString();
            ui->txt_username->setText(username_paciente);
        }
    }

    //Query para colocar a senha correspondente ao médico certo
    QSqlQuery query_senha;
    query_senha.prepare("SELECT senha FROM medicos WHERE id = :id");
    query_senha.bindValue(":id",id);
    if (query_senha.exec()){
        if(query_senha.next()){
            //Senha colocad no lineEdit da senha
            QString senha_paciente = query_senha.value(0).toString();
            ui->txt_senha->setText(senha_paciente);
        }
    }
}

//Botão atualizar (botaoAtualizar)
void Medico_cadastro::on_botaoAtualizar_clicked()
{
    //Variáveis para atualização do cadastro
    int id = ui->label_num_id->text().toInt();
    QString novo_nome = ui->txt_nome->text();
    QString novo_username = ui->txt_username->text();
    QString novo_senha = ui->txt_senha->text();

    //Querys para atualização do cadastro
    QSqlQuery consultar;
    QSqlQuery checando;
    int contagem = 0;
    QSqlQuery editar;

    //Se algum dos campos estiver vazio, aparece uma mensagem de erro e não é salvo o novo cadastro
    if(novo_nome==""||novo_username==""||novo_senha==""){
        QMessageBox::warning(this,"ERRO","Todos os campos precisam estar preenchidos.");
    }else{
        consultar.prepare("SELECT username FROM medicos where id = :id");
        consultar.bindValue(":id", id);
        if (consultar.exec()){
            if (consultar.next()){
                QString username = consultar.value(0).toString();
                //Caso o username permaneça o mesmo, ele atualiza o nome e a senha do cadastro
                if (novo_username == username){
                    editar.prepare("UPDATE medicos SET nome = :nomeNova, senha = :senhaNova where id = :id");
                    editar.bindValue(":nomeNova", novo_nome);
                    editar.bindValue(":senhaNova", novo_senha);
                    editar.bindValue(":id", id);
                    //qDebug de acompanhamento
                    if (editar.exec()){
                        qDebug()<<"Você mudou o cadastro de "<<novo_nome;
                        QMessageBox::information(this,"","Cadastro editado com sucesso");
                    }else{
                        QMessageBox::warning(this,"ERRO","Não foi possível realizar o cadastro.");
                    }
                }else{
                    //Checando se o username já existe na tabela de pacientes
                    checando.prepare("SELECT * FROM pacientes where username = :username");
                    checando.bindValue(":username",novo_username);
                    contagem = 0;

                    if (checando.exec()){
                        while (checando.next()){
                            contagem++;
                        }
                        //Caso exista, ocorre uma mensagem de erro
                        if (contagem>0){
                            QMessageBox::warning(this, "ERRO", "Esse username já existe!");

                        }else{
                            //Checando se o username já existe na tabela de médicos
                            checando.prepare("SELECT * FROM medicos where username = :username");
                            checando.bindValue(":username",novo_username);
                            contagem = 0;
                            if (checando.exec()){
                                while (checando.next()){
                                    contagem++;
                                }
                                //Caso exista, ocorre uma mensagem de erro
                                if (contagem>0){
                                    QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                                }else{
                                    //Query que atualiza o novo cadastro do médico
                                    editar.prepare("UPDATE medicos SET nome = :nomeNova, username = :usernameNova, senha = :senhaNova where id = :id");
                                    editar.bindValue(":nomeNova", novo_nome);
                                    editar.bindValue(":usernameNova", novo_username);
                                    editar.bindValue(":senhaNova", novo_senha);
                                    editar.bindValue(":id", id);

                                    if (editar.exec()){
                                        qDebug()<<"Você mudou o cadastro de "<<novo_nome;
                                        QMessageBox::information(this,"","Cadastro editado com sucesso");
                                    }else{
                                        QMessageBox::warning(this,"ERRO","Não foi possível realizar o cadastro");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
