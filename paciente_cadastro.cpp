#include "paciente_cadastro.h"
#include "ui_paciente_cadastro.h"
#include "QMessageBox"
#include "QDebug"

#include "paciente_inicio.h"
#include "paciente_atendimentos.h"
#include "login.h"

//Inicializando a tela de Cadastro - Paciente
Paciente_cadastro::Paciente_cadastro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Paciente_cadastro)
{
    ui->setupUi(this);
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Cadastro - Pacientes";
}

//Fechando a interface
Paciente_cadastro::~Paciente_cadastro()
{
    delete ui;
}

//Botão para a tela de Início - Pacientes (botaoInicio)
//Utilizando do método mudarNomeId da classe Paciente_inicio para passagem do Id do paciente correto (herança)
void Paciente_cadastro::on_botaoInicio_clicked()
{
    QString id = ui->label_num_id->text();
    Paciente_inicio *irInicio = new Paciente_inicio(this);
    close();
    irInicio->show();
    irInicio->mudarNomeId(id);
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - Pacientes";
}

//Botão para a tela de Atendimentos - Pacientes (botaoAtendimentos)
//Utilizando do método mudarId da classe Paciente_cadastro para passagem do Id do paciente correto (herança)
void Paciente_cadastro::on_botaoAtendimentos_clicked()
{
    QString id = ui->label_num_id->text();
    Paciente_atendimentos *irAtendimentos = new Paciente_atendimentos(this);
    close();
    irAtendimentos ->show();
    irAtendimentos->mudarId(id);
}

//Botão para a tela de Login (botaoSair)
void Paciente_cadastro::on_botaoSair_clicked()
{
    Login *voltarLogin = new Login(this);
    close();
    voltarLogin->show();
}

//Método para receber o Id do paciente correto, vindo da tela anterior e colocar outras informações nos lugares correspondentes(herança)
void Paciente_cadastro::mudarId (const QString &id)
{
    ui->label_num_id->setText(id);

    //Query para colocar o nome correspondente ao paciente certo
    QSqlQuery query_nome;
    query_nome.prepare("SELECT nome FROM pacientes WHERE id = :id");
    query_nome.bindValue(":id",id);
    if (query_nome.exec()){
        if(query_nome.next()){
            //Nome colocado no lineEdit do nome
            QString nome_paciente = query_nome.value(0).toString();
            ui->txt_nome->setText(nome_paciente);
        }
    }

    //Query para colocar o username correspondente ao paciente certo
    QSqlQuery query_username;
    query_username.prepare("SELECT username FROM pacientes WHERE id = :id");
    query_username.bindValue(":id",id);
    if (query_username.exec()){
        //Username colocado no lineEdit do username
        if(query_username.next()){
            QString username_paciente = query_username.value(0).toString();
            ui->txt_username->setText(username_paciente);
        }
    }

    //Query para colocar a senha correspondente ao paciente certo
    QSqlQuery query_senha;
    query_senha.prepare("SELECT senha FROM pacientes WHERE id = :id");
    query_senha.bindValue(":id",id);
    if (query_senha.exec()){
        //Senha colocad no lineEdit da senha
        if(query_senha.next()){
            QString senha_paciente = query_senha.value(0).toString();
            ui->txt_senha->setText(senha_paciente);
        }
    }
}

//Botão cancelar, colocando as informações de antes de serem editadas (botaoCancelar)
void Paciente_cadastro::on_botaoCancelar_clicked()
{
    int id = ui->label_num_id->text().toInt();

    //Query para colocar o nome correspondente ao paciente certo
    QSqlQuery query_nome;
    query_nome.prepare("SELECT nome FROM pacientes WHERE id = :id");
    query_nome.bindValue(":id",id);
    if (query_nome.exec()){
        if(query_nome.next()){
            //Nome colocado no lineEdit do nome
            QString nome_paciente = query_nome.value(0).toString();
            ui->txt_nome->setText(nome_paciente);
        }
    }

    //Query para colocar o username correspondente ao paciente certo
    QSqlQuery query_username;
    query_username.prepare("SELECT username FROM pacientes WHERE id = :id");
    query_username.bindValue(":id",id);
    if (query_username.exec()){
        //Username colocado no lineEdit do username
        if(query_username.next()){
            QString username_paciente = query_username.value(0).toString();
            ui->txt_username->setText(username_paciente);
        }
    }

    //Query para colocar a senha correspondente ao paciente certo
    QSqlQuery query_senha;
    query_senha.prepare("SELECT senha FROM pacientes WHERE id = :id");
    query_senha.bindValue(":id",id);
    if (query_senha.exec()){
        //Senha colocad no lineEdit da senha
        if(query_senha.next()){
            QString senha_paciente = query_senha.value(0).toString();
            ui->txt_senha->setText(senha_paciente);
        }
    }
}

//Botão atualizar (botaoAtualizar)
void Paciente_cadastro::on_botaoAtualizar_clicked()
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
        consultar.prepare("SELECT username FROM pacientes where id = :id");
        consultar.bindValue(":id", id);
        if (consultar.exec()){
            if (consultar.next()){
                QString username = consultar.value(0).toString();
                //Caso o username permaneça o mesmo, ele atualiza o nome e a senha do cadastro
                if (novo_username == username){
                    editar.prepare("UPDATE pacientes SET nome = :nomeNova, senha = :senhaNova where id = :id");
                    editar.bindValue(":nomeNova", novo_nome);
                    editar.bindValue(":senhaNova", novo_senha);
                    editar.bindValue(":id", id);
                    //qDebug de acompanhamento
                    if (editar.exec()){
                        qDebug()<<"Você mudou o cadastro de "<<novo_nome;
                        QMessageBox::information(this,"","Cadastro editado com sucesso");
                    }else{
                        QMessageBox::warning(this,"ERRO","Não foi possível fazer o cadastro");
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
                                    //Query que atualiza o novo cadastro do paciente
                                    editar.prepare("UPDATE pacientes SET nome = :nomeNova, username = :usernameNova, senha = :senhaNova where id = :id");
                                    editar.bindValue(":nomeNova", novo_nome);
                                    editar.bindValue(":usernameNova", novo_username);
                                    editar.bindValue(":senhaNova", novo_senha);
                                    editar.bindValue(":id", id);

                                    if (editar.exec()){
                                        qDebug()<<"Você mudou o cadastro de "<<novo_nome;
                                        QMessageBox::information(this,"","Cadastro editado com sucesso");
                                    }else{
                                        QMessageBox::warning(this,"ERRO","Não foi possível fazer o cadastro.");
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
