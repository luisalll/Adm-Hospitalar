#include "adm_cadastro_editar.h"
#include "ui_adm_cadastro_editar.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

#include "adm_cadastros.h"

//Inicalizando a tela de Editar Cadastros - ADM
ADM_cadastro_editar::ADM_cadastro_editar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ADM_cadastro_editar)
{
    ui->setupUi(this);
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Editar Cadastro - ADM";
}

//Fechando a interface
ADM_cadastro_editar::~ADM_cadastro_editar()
{
    delete ui;
}

//Método para inserir o nome correto para ser editado (vindo da seleção na tela de Cadastros - ADM)
void ADM_cadastro_editar::mudarTexto_nome (const QString &nome_antiga)
{
    ui->txt_NovoNome->setText(nome_antiga);
    qDebug()<<"Você está mudando o cadastro de "<<nome_antiga;
}
//Método para inserir o username correto para ser editado (vindo da seleção na tela de Cadastros - ADM)
void ADM_cadastro_editar::mudarTexto_username (const QString &username_antiga)
{
    ui->txt_NovoUsername->setText(username_antiga);
}
//Método para inserir a senha correta para ser editada (vindo da seleção na tela de Cadastros - ADM)
void ADM_cadastro_editar::mudarTexto_senha (const QString &senha_antiga)
{
    ui->txt_NovoSenha->setText(senha_antiga);
}

//Método para inserir o tipo de cadastro e id correto(vindo da seleção na tela de Cadastros - ADM)
void ADM_cadastro_editar::mudarLabels(const QString &tipo, const QString &id)
{
    ui->label_tipo->setText(tipo);
    ui->label_id->setText(id);
}

//Botão aceito (para editar o cadastro)
void ADM_cadastro_editar::on_buttonBox_accepted()
{
    //Querys para editar o cadastro e varáveis usadas
    QSqlQuery editar;
    QSqlQuery consultar;
    QSqlQuery checando;
    int contagem = 0;

    QString tipo = ui->label_tipo->text();
    int id = ui->label_id->text().toInt();
    QString novo_nome = ui->txt_NovoNome->text();
    QString novo_username = ui->txt_NovoUsername->text();
    QString novo_senha = ui->txt_NovoSenha->text();

    ADM_cadastros *voltarCadastros = new ADM_cadastros;

    //Se algum dos campos estiver vazio, aparece uma mensagem de erro e não é salvo o novo cadastro
    if(novo_nome==""||novo_username==""||novo_senha==""){
        QMessageBox::warning(this,"ERRO","Todos os campos precisam estar preenchidos.");
        ADM_cadastros *voltarCadastros = new ADM_cadastros;
        close();
        voltarCadastros->show();
    }else{
        //Mudança de um cadastro de paciente
        if(tipo == "Paciente"){
            consultar.prepare("SELECT username FROM pacientes where id = :id");
            consultar.bindValue(":id", id);
            if (consultar.exec()){
                if (consultar.next()){
                    QString username = consultar.value(0).toString();
                    //Se o username permanecer igual, o sistema atualiza os espaços de nom e senha do cadastro
                    if (novo_username == username){
                        editar.prepare("UPDATE pacientes SET nome = :nomeNova, senha = :senhaNova where id = :id");
                        editar.bindValue(":nomeNova", novo_nome);
                        editar.bindValue(":senhaNova", novo_senha);
                        editar.bindValue(":id", id);

                        if (editar.exec()){
                            //qDebug para acopanhamento e volta para a tela de Cadastros - ADM
                            qDebug()<<"Você mudou o cadastro de "<<novo_nome;
                            QMessageBox::information(this,"","Cadastro editado com sucesso");
                            voltarCadastros->show();

                        }else{
                            //Mensagem de erro caso o cadastro não seja realizado e volta para a tela de Cadastros - ADM
                            QMessageBox::warning(this,"ERRO","Não foi possível realizar o cadastro.");
                            voltarCadastros->show();
                        }
                    }else{
                        //Checando se já existe algum cadastro entre os pacientes com o username escolhido
                        checando.prepare("SELECT * FROM pacientes where username = :username");
                        checando.bindValue(":username",novo_username);
                        contagem = 0;
                        if (checando.exec()){
                            while (checando.next()){
                                contagem++;
                            }
                            //Caso exista, ocorre uma mensagem de erro e volta para a tela de Cadastros - ADM (cadastro não realizado)
                            if (contagem>0){
                                QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                                voltarCadastros->show();
                            }else{
                                //Checando se já existe algum cadastro entre os médicos com o username escolhido
                                checando.prepare("SELECT * FROM medicos where username = :username");
                                checando.bindValue(":username",novo_username);
                                contagem = 0;
                                if (checando.exec()){
                                    while (checando.next()){
                                        contagem++;
                                    }
                                    //Caso exista, ocorre uma mensagem de erro e volta para a tela de Cadastros - ADM (cadastro não realizado)
                                    if (contagem>0){
                                        QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                                        voltarCadastros->show();
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
                                            voltarCadastros->show();
                                        }else{
                                            QMessageBox::warning(this,"ERRO","Não foi possível realizar o cadastro.");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        //Mudança de cadastro do médico
        }else{
            consultar.prepare("SELECT username FROM medicos where id = :id");
            consultar.bindValue(":id", id);
            if (consultar.exec()){
                if (consultar.next()){
                    QString username = consultar.value(0).toString();
                    //Seu o username permanecer igual, o sistema atualiza os espaços de nom e senha do cadastro
                    if (novo_username == username){
                        editar.prepare("UPDATE medicos SET nome = :nomeNova, senha = :senhaNova where id = :id");
                        editar.bindValue(":nomeNova", novo_nome);
                        editar.bindValue(":senhaNova", novo_senha);
                        editar.bindValue(":id", id);

                        if (editar.exec()){
                            //qDebug para acopanhamento e volta para a tela de Cadastros - ADM
                            qDebug()<<"Você mudou o cadastro de "<<novo_nome;
                            QMessageBox::information(this,"","Cadastro editado com sucesso");
                            voltarCadastros->show();

                        }else{
                            //Mensagem de erro caso o cadastro não seja realizado e volta para a tela de Cadastros - ADM
                            QMessageBox::warning(this,"ERRO","Não foi possível realizar o cadastro.");
                            voltarCadastros->show();

                        }
                    }else{
                        //Checando se já existe algum cadastro entre os pacientes com o username escolhido
                        checando.prepare("SELECT * FROM pacientes where username = :username");
                        checando.bindValue(":username",novo_username);
                        contagem = 0;
                        if (checando.exec()){
                            while (checando.next()){
                                contagem++;
                            }
                            //Caso exista, ocorre uma mensagem de erro e volta para a tela de Cadastros - ADM (cadastro não realizado)
                             if (contagem>0){
                                QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                                voltarCadastros->show();
                            }else{
                                 //Checando se já existe algum cadastro entre os médicos com o username escolhido
                                checando.prepare("SELECT * FROM medicos where username = :username");
                                checando.bindValue(":username",novo_username);
                                contagem = 0;
                                if (checando.exec()){
                                    while (checando.next()){
                                        contagem++;
                                    }
                                    //Caso exista, ocorre uma mensagem de erro e volta para a tela de Cadastros - ADM (cadastro não realizado)
                                    if (contagem>0){
                                        QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                                        voltarCadastros->show();
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
                                            voltarCadastros->show();
                                        }else{
                                            QMessageBox::warning(this,"ERRO","Não foi possível realizar o cadastro.");
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
}


//Botão rejeitado (volta a tela "ADM_cadastros")
void ADM_cadastro_editar::on_buttonBox_rejected()
{
    ADM_cadastros *voltarCadastros = new ADM_cadastros;
    close();
    voltarCadastros->show();
}

