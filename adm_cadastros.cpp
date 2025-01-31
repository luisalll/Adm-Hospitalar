#include "adm_cadastros.h"
#include "ui_adm_cadastros.h"
#include "QDebug"
#include "QMessageBox"
#include <QtSql>

#include "adm_inicio.h"
#include "adm_atendimentos.h"
#include "adm_material.h"
#include "login.h"
#include "adm_cadastro_editar.h"

//Inicializando a tela de Cadastros - ADM
ADM_cadastros::ADM_cadastros(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ADM_cadastros)
{
    ui->setupUi(this);

    //qDebug para acompanhar o progresso
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Cadastros - ADM";

    //Estabelecendo para quando a tela seja aberta, já apareça a lista de cadastros com a query que lista as linhas de pacientes e médicos:
    QSqlQuery query;
    query.prepare("SELECT 'Médico' AS tabela, * FROM medicos UNION ALL SELECT 'Paciente' AS tabela, * FROM pacientes;");
    if(query.exec()){
        qDebug()<<"Cadastros acessados";
        int linha=0;
        ui->tw_Cadastros->setColumnCount(6);

        //While para inserir todas as linhas
        while(query.next()){
            ui->tw_Cadastros->insertRow(linha);
            ui->tw_Cadastros->setItem(linha,0,new QTableWidgetItem(query.value(0).toString()));   //Item da 1a coluna: Tipo de cadastro
            ui->tw_Cadastros->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));   //Item da 2a coluna: Id do cadastro
            ui->tw_Cadastros->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));   //Item da 3a coluna: Nome cadastrado
            ui->tw_Cadastros->setItem(linha,3,new QTableWidgetItem(query.value(3).toString()));   //Item da 4a coluna: Username cadastrado
            ui->tw_Cadastros->setItem(linha,4,new QTableWidgetItem(query.value(4).toString()));   //Item da 5a coluna: Senha cadastrada
            ui->tw_Cadastros->setItem(linha,5,new QTableWidgetItem(query.value(5).toString()));   //Item da 6a coluna: Especialidade cadastrada
            ui->tw_Cadastros->setRowHeight(linha,20);
            linha++;    //Próxima linha
        }

        //Largura das colunas e cabeçalhos
        ui->tw_Cadastros->setColumnWidth(0,70);
        ui->tw_Cadastros->setColumnWidth(1,3);
        ui->tw_Cadastros->setColumnWidth(2,365);
        ui->tw_Cadastros->setColumnWidth(3,100);
        ui->tw_Cadastros->setColumnWidth(4,100);
        ui->tw_Cadastros->setColumnWidth(5,100);
        QStringList cabecalho={"Tipo","Id","Nome","Username","Senha","Especialidade"};
        ui->tw_Cadastros->setHorizontalHeaderLabels(cabecalho);
        ui->tw_Cadastros->verticalHeader()->setVisible(false);

        //Determinando a seleção por linha
        ui->tw_Cadastros->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_Cadastros->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_Cadastros->setStyleSheet("QTableView {selection-background-color:grey}");
    }else{
        //Mensagem de erro caso os banco de dados não seja acessado corretamente
        QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
        qDebug()<<"Não foi possível listar os cadastros";
    }
}

//Fechando a interface
ADM_cadastros::~ADM_cadastros()
{
    delete ui;
}

    //Botões para outras telas:

//Botão para tela de início
void ADM_cadastros::on_botaoInicio_clicked()
{
    ADM_inicio *irInicio = new ADM_inicio(this);
    close();
    irInicio->show();
    //qDebug para acompanhar o progresso
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - ADM";
}

//Botão para tela de Atendimentos - ADM
void ADM_cadastros::on_botaoAtendimentos_clicked()
{
    ADM_atendimentos *irAtendimentos = new ADM_atendimentos(this);
    close();
    irAtendimentos->show();
}

//Botão para tela de Material - ADM
void ADM_cadastros::on_botaoMaterial_clicked()
{
    ADM_material *irMaterial = new ADM_material(this);
    close();
    irMaterial->show();
}

//Botão para a tela de Login (botaoSair)
void ADM_cadastros::on_botaoSair_clicked()
{
    Login *irLogin = new Login(this);
    close();
    irLogin->show();
}

    //Guia de cadastros antigos

//Função para quando abrir a guia de cadastros antigos, o novo cadastro feito já seja carregado
void ADM_cadastros::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0){
        //Fazer com que o botão radio "Todos" (rabotaoTodos) esteja clicado e não os outros
        ui->rabotaoTodos->setChecked(true);
        ui->rdbotaoMedico->setChecked(false);
        ui->rdbotaoPaciente->setChecked(false);

        //Igual a como a tela 'Cadastros - ADM' é inicializada:

        //Estabelecendo para quando a tela seja aberta, já apareça a lista de cadastros com a query que lista as linhas de pacientes e médicos:
        QSqlQuery query;
        query.prepare("SELECT 'Médico' AS tabela, * FROM medicos UNION ALL SELECT 'Paciente' AS tabela, * FROM pacientes;");
        if(query.exec()){
            qDebug()<<"Cadastros acessados";
            int linha=0;

            //Limpando a table widget de cadastros e estabelecendo a nova quantidade de colunas (tw_Cadastros)
            ui->tw_Cadastros->setRowCount(0);
            ui->tw_Cadastros->clearContents();
            ui->tw_Cadastros->setColumnCount(6);

            //While para inserir todas as linhas
            while(query.next()){
                //Inserindo as linha
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->setItem(linha,0,new QTableWidgetItem(query.value(0).toString()));   //Item da 1a coluna: Tipo de cadastro
                ui->tw_Cadastros->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));   //Item da 2a coluna: Id do cadastro
                ui->tw_Cadastros->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));   //Item da 3a coluna: Nome cadastrado
                ui->tw_Cadastros->setItem(linha,3,new QTableWidgetItem(query.value(3).toString()));   //Item da 4a coluna: Username cadastrado
                ui->tw_Cadastros->setItem(linha,4,new QTableWidgetItem(query.value(4).toString()));   //Item da 5a coluna: Senha cadastrada
                ui->tw_Cadastros->setItem(linha,5,new QTableWidgetItem(query.value(5).toString()));   //Item da 6a coluna: Especialidade cadastrada
                ui->tw_Cadastros->setRowHeight(linha,20);
                linha++;    //Próxima linh
            }

            //Largura e cabeçalho
            ui->tw_Cadastros->setColumnWidth(0,70);
            ui->tw_Cadastros->setColumnWidth(1,3);
            ui->tw_Cadastros->setColumnWidth(2,365);
            ui->tw_Cadastros->setColumnWidth(3,100);
            ui->tw_Cadastros->setColumnWidth(4,100);
            ui->tw_Cadastros->setColumnWidth(5,100);
            QStringList cabecalho={"Tipo","Id","Nome","Username","Senha","Especialidade"};
            ui->tw_Cadastros->setHorizontalHeaderLabels(cabecalho);
            ui->tw_Cadastros->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_Cadastros->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_Cadastros->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_Cadastros->setStyleSheet("QTableView {selection-background-color:grey}");
        }else{
            //Mensagem de erro caso os banco de dados não seja acessado corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }
}

//Botão rádio "Todos" (mostra cadastros de médicos e pacientes)
void ADM_cadastros::on_rabotaoTodos_clicked(bool checked)
{

    if (checked){

        //Igual a como a tela 'Cadastros - ADM' é inicializada:

        //Estabelecendo para quando a tela seja aberta, já apareça a lista de cadastros com a query que lista as linhas de pacientes e médicos:
        QSqlQuery query;
        query.prepare("SELECT 'Médico' AS tabela, * FROM medicos UNION ALL SELECT 'Paciente' AS tabela, * FROM pacientes;");
        if(query.exec()){
            qDebug()<<"Cadastros acessados";
            int linha=0;

            //Limpando a table widget de cadastros e estabelecendo a nova quantidade de colunas (tw_Cadastros)
            ui->tw_Cadastros->setRowCount(0);
            ui->tw_Cadastros->clearContents();
            ui->tw_Cadastros->setColumnCount(6);

            //While para inserir todas as linhas de cadastros
            while(query.next()){
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->setItem(linha,0,new QTableWidgetItem(query.value(0).toString()));   //Item da 1a coluna: Tipo de cadastro
                ui->tw_Cadastros->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));   //Item da 2a coluna: Id do cadastro
                ui->tw_Cadastros->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));   //Item da 3a coluna: Nome cadastrado
                ui->tw_Cadastros->setItem(linha,3,new QTableWidgetItem(query.value(3).toString()));   //Item da 4a coluna: Username cadastrado
                ui->tw_Cadastros->setItem(linha,4,new QTableWidgetItem(query.value(4).toString()));   //Item da 5a coluna: Senha cadastrada
                ui->tw_Cadastros->setItem(linha,5,new QTableWidgetItem(query.value(5).toString()));   //Item da 6a coluna: Especialidade cadastrada
                ui->tw_Cadastros->setRowHeight(linha,20);
                linha++;    //Próxima linha
            }

            //Largura e cabeçalho
            ui->tw_Cadastros->setColumnWidth(0,70);
            ui->tw_Cadastros->setColumnWidth(1,3);
            ui->tw_Cadastros->setColumnWidth(2,365);
            ui->tw_Cadastros->setColumnWidth(3,100);
            ui->tw_Cadastros->setColumnWidth(4,100);
            ui->tw_Cadastros->setColumnWidth(5,100);
            QStringList cabecalho={"Tipo","Id","Nome","Username","Senha","Especialidade"};
            ui->tw_Cadastros->setHorizontalHeaderLabels(cabecalho);
            ui->tw_Cadastros->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_Cadastros->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_Cadastros->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_Cadastros->setStyleSheet("QTableView {selection-background-color:grey}");
        }else{
            //Mensagem de erro caso os banco de dados não seja acessado corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }
}

//Botão rádio "Pacientes" (mostra apenas cadastros de pacientes)
void ADM_cadastros::on_rdbotaoPaciente_clicked(bool checked)
{
    if (checked){

        QSqlQuery query;
        //Query para mostrar linhas de pacientes
        query.prepare("select * from pacientes");
        if(query.exec()){
            //qDegug para acompanhar o processo
            qDebug()<<"Cadastros dos pacientes acessados";
            int linha=0;

            //Limpando a table widget de cadastros e determinando as novas colunas (tw_Cadastros)
            ui->tw_Cadastros->setRowCount(0);
            ui->tw_Cadastros->clearContents();
            ui->tw_Cadastros->setColumnCount(5);

            //While para inserir os cadastros de pacientes
            while(query.next()){
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->setItem(linha,0,new QTableWidgetItem(query.value(0).toString())); //Item da 1a coluna: Id do Paciente
                ui->tw_Cadastros->setItem(linha,1,new QTableWidgetItem(query.value(1).toString())); //Item da 2a coluna: Nome do Paciente
                ui->tw_Cadastros->setItem(linha,2,new QTableWidgetItem(query.value(2).toString())); //Item da 3a coluna: Username do Paciente
                ui->tw_Cadastros->setItem(linha,3,new QTableWidgetItem(query.value(3).toString())); //Item da 4a coluna: Senha do Paciente
                ui->tw_Cadastros->setItem(linha,4,new QTableWidgetItem(query.value(4).toString())); //Item da 5a coluna: Especialidade do Paciente
                ui->tw_Cadastros->setRowHeight(linha,20);
                linha++;    //Próxima linha
            }

            //Definindo largura das colunas e cabeçalho
            ui->tw_Cadastros->setColumnWidth(0,3);
            ui->tw_Cadastros->setColumnWidth(1,350);
            ui->tw_Cadastros->setColumnWidth(2,150);
            ui->tw_Cadastros->setColumnWidth(3,150);
            ui->tw_Cadastros->setColumnWidth(4,90);
            QStringList cabecalho_pacientes={"Id","Nome","Username","Senha","Especialidade"};
            ui->tw_Cadastros->setHorizontalHeaderLabels(cabecalho_pacientes);
            ui->tw_Cadastros->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_Cadastros->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_Cadastros->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_Cadastros->setStyleSheet("QTableView {selection-background-color:grey}");
        }else{
            //Mesagem de erro caso cadastros de pacientes não sejam acessados corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }
}

//Botão radio "Médicos" (mostra apenas cadastros  de médicos)
void ADM_cadastros::on_rdbotaoMedico_clicked(bool checked)
{
    if (checked){

        QSqlQuery query;
        //Query para mostrar linhas de médicos;
        query.prepare("select * from medicos");
        if(query.exec()){
            qDebug()<<"Cadastros dos médicos acessados";
            int linha=0;

            //Limpando a table widget de cadastros e colocando as novas colunas (tw_Cadastros)
            ui->tw_Cadastros->setRowCount(0);
            ui->tw_Cadastros->clearContents();
            ui->tw_Cadastros->setColumnCount(5);

            //While para inserir os cadastros dos médicos
            while(query.next()){
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->insertRow(linha);
                ui->tw_Cadastros->setItem(linha,0,new QTableWidgetItem(query.value(0).toString())); //Item da 1a coluna: Id do Paciente
                ui->tw_Cadastros->setItem(linha,1,new QTableWidgetItem(query.value(1).toString())); //Item da 2a coluna: Nome do Paciente
                ui->tw_Cadastros->setItem(linha,2,new QTableWidgetItem(query.value(2).toString())); //Item da 3a coluna: Username do Paciente
                ui->tw_Cadastros->setItem(linha,3,new QTableWidgetItem(query.value(3).toString())); //Item da 4a coluna: Senha do Paciente
                ui->tw_Cadastros->setItem(linha,4,new QTableWidgetItem(query.value(4).toString())); //Item da 5a coluna: Especialidade do Paciente
                ui->tw_Cadastros->setRowHeight(linha,20);
                linha++;    //Próxima linha
            }

            //Definindo largura das colunas e cabeçalho
            ui->tw_Cadastros->setColumnWidth(0,3);
            ui->tw_Cadastros->setColumnWidth(1,350);
            ui->tw_Cadastros->setColumnWidth(2,150);
            ui->tw_Cadastros->setColumnWidth(3,150);
            ui->tw_Cadastros->setColumnWidth(4,90);
            QStringList cabecalho_pacientes={"Id","Nome","Username","Senha","Especialidade"};
            ui->tw_Cadastros->setHorizontalHeaderLabels(cabecalho_pacientes);
            ui->tw_Cadastros->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_Cadastros->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_Cadastros->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_Cadastros->setStyleSheet("QTableView {selection-background-color:grey}");

        }else{
            //Mesagem de erro caso cadastros de pacientes não sejam acessados corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }
}

//Botão para excluir um cadastro (botaoExcluir)
void ADM_cadastros::on_botaoExcluir_clicked()
{
    //Definindo a variável da linha selecionada
    int linha_selecionada=ui->tw_Cadastros->currentRow();

    //Caso nenhum cadastro seja selecionado (currentRow == -1), é colocada uma mensagem para escolher. Nenhum cadastro é excluído
    if (ui->tw_Cadastros->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um cadastro.");
        return;
    }

    //Definindo outras variáveis relacionadas com a linha selecionada (username, nome e tipo de cadastro)
    QString username_selecionado=ui->tw_Cadastros->item(linha_selecionada,3)->text();
    QString nome_selecionado=ui->tw_Cadastros->item(linha_selecionada,2)->text();
    QString tipo_cadastro=ui->tw_Cadastros->item(linha_selecionada,0)->text();

    //Caso botão rádio Médicos ou Pacietes esteja selecionado, as variáveis de username e nome serão diferentes pois estão em colunas diferentes na tabela
    if (ui->rdbotaoMedico->isChecked()||ui->rdbotaoPaciente->isChecked()){
        QString username_selecionado=ui->tw_Cadastros->item(linha_selecionada,2)->text();
        QString nome_selecionado=ui->tw_Cadastros->item(linha_selecionada,1)->text();
    }

    //Caso o botão "Todos" esteja marcado:
    if(ui->rabotaoTodos->isChecked()){
        //Confere se é médico ou paciente pela coluna de "Tipo"
        if(tipo_cadastro=="Médico"){
            QSqlQuery query_medico;
            //Query para remover a linha selecionada de 'medicos'
            query_medico.prepare("delete from medicos where username = :username");
            query_medico.bindValue(":username",username_selecionado);

            if(query_medico.exec()){
                //Se executa, remove essa linha da Table Widget de Cadastros e anuncia por uma QMessageBox e um qDebug
                ui->tw_Cadastros->removeRow(linha_selecionada);
                QMessageBox::information(this,"","Registro excluído");
                qDebug()<<"Você excluíu o cadastro de"<<nome_selecionado;
            }
            ui->tw_Cadastros->clearSelection();
            ui->tw_Cadastros->setCurrentCell(-1, -1);


        }else{
            QSqlQuery query_paciente;
            //Query para remover a linha selecionada de 'pacientes'
            query_paciente.prepare("delete from pacientes where username = :username");
            query_paciente.bindValue(":username",username_selecionado);

            if(query_paciente.exec()){
                //Se executa, remove essa linha da Table Widget de Cadastros e anuncia por uma QMessageBox e um qDebug
                ui->tw_Cadastros->removeRow(linha_selecionada);
                QMessageBox::information(this,"","Registro excluído");
                qDebug()<<"Você excluíu o cadastro de"<<nome_selecionado;
            }
            ui->tw_Cadastros->clearSelection();
            ui->tw_Cadastros->setCurrentCell(-1, -1);

        }

    //Caso o botão "Pacientes" esteja marcado é removida a linha da tabela de pacientes do banco de dados
    }else if(ui->rdbotaoPaciente->isChecked()){
        QSqlQuery query_paciente;
        //Query para remover a linha selecionada de 'pacientes'
        query_paciente.prepare("delete from pacientes where username = :username");
        query_paciente.bindValue(":username",username_selecionado);

        if(query_paciente.exec()){
            //Se executa, remove essa linha da Table Widget de Cadastros e anuncia por uma QMessageBox e um qDebug
            ui->tw_Cadastros->removeRow(linha_selecionada);
            QMessageBox::information(this,"","Registro excluído");
            qDebug()<<"Você excluíu o cadastro de"<<nome_selecionado;
        }
        ui->tw_Cadastros->clearSelection();
        ui->tw_Cadastros->setCurrentCell(-1, -1);


    //Caso, contrário, o botão de "Médicos" vai estar marcado, então é removida a linha selecionada da
    }else{
        QSqlQuery query_medico;
        //Query para remover a linha selecionada de 'medicos'
        query_medico.prepare("delete from medicos where username = :username");
        query_medico.bindValue(":username",username_selecionado);

        if(query_medico.exec()){
            //Se executa, remove essa linha da Table Widget de Cadastros e anuncia por uma QMessageBox e um qDebug
            ui->tw_Cadastros->removeRow(linha_selecionada);
            QMessageBox::information(this,"","Registro excluído");
            qDebug()<<"Você excluíu o cadastro de"<<nome_selecionado;
        }
        ui->tw_Cadastros->clearSelection();
        ui->tw_Cadastros->setCurrentCell(-1, -1);

    }
}

//Botão para editar um cadastro selecionado (botaoEditar)
void ADM_cadastros::on_botaoEditar_clicked()
{
    //Variável da linha selecionada
    int linha_selecionada=ui->tw_Cadastros->currentRow();

    //Caso nenhum cadastro seja selecionado (currentRow == -1), é colocada uma mensagem para escolher. A tela de Editar Cadastros - ADM não é aberta
    if (ui->tw_Cadastros->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um cadastro.");
        return;
    }

    //Definindo outras variáveis relacionadas com a linha selecionada (tipo de cadastro, id, nome, username e senha)
    QString tipo=ui->tw_Cadastros->item(linha_selecionada,0)->text();
    QString id=ui->tw_Cadastros->item(linha_selecionada,1)->text();
    QString nome_antiga=ui->tw_Cadastros->item(linha_selecionada,2)->text();
    QString username_antiga=ui->tw_Cadastros->item(linha_selecionada,3)->text();
    QString senha_antiga=ui->tw_Cadastros->item(linha_selecionada,4)->text();

    //Caso o botão rádio Todos (rabotaoTodos)
    if(ui->rabotaoTodos->isChecked()){
        QString tipo=ui->tw_Cadastros->item(linha_selecionada,0)->text();
        QString id=ui->tw_Cadastros->item(linha_selecionada,1)->text();
        QString nome_antiga=ui->tw_Cadastros->item(linha_selecionada,2)->text();
        QString username_antiga=ui->tw_Cadastros->item(linha_selecionada,3)->text();
        QString senha_antiga=ui->tw_Cadastros->item(linha_selecionada,4)->text();

        //Indo para tela de Editar Cadastros - ADM
        ADM_cadastro_editar *tela_edicao = new ADM_cadastro_editar;
        close();
        tela_edicao->show();

        //Recorre a métodos da classe "ADM_cadastro_editar" para que os dados sejam passados para essa classe (herança)
        tela_edicao->mudarTexto_nome(nome_antiga);
        tela_edicao->mudarTexto_username(username_antiga);
        tela_edicao->mudarTexto_senha(senha_antiga);
        tela_edicao->mudarLabels(tipo,id);

    }
    //Caso o botão rádio Pacientes (rdbotaoPaciente)
    if (ui->rdbotaoPaciente->isChecked()){
        QString id=ui->tw_Cadastros->item(linha_selecionada,0)->text();
        QString nome_antiga=ui->tw_Cadastros->item(linha_selecionada,1)->text();
        QString username_antiga=ui->tw_Cadastros->item(linha_selecionada,2)->text();
        QString senha_antiga=ui->tw_Cadastros->item(linha_selecionada,3)->text();
        QString tipo = "Paciente";

        //Indo para tela de Editar Cadastros - ADM
        ADM_cadastro_editar *tela_edicao = new ADM_cadastro_editar;
        close();
        tela_edicao->show();

        //Recorre a métodos da classe "ADM_cadastro_editar" para que os dados sejam passados para essa classe (herança)
        tela_edicao->mudarTexto_nome(nome_antiga);
        tela_edicao->mudarTexto_username(username_antiga);
        tela_edicao->mudarTexto_senha(senha_antiga);
        tela_edicao->mudarLabels(tipo,id);
    }
    //Caso o botão rádio Médicos (rdbotaoMedico)
    if(ui->rdbotaoMedico->isChecked()){
        QString id=ui->tw_Cadastros->item(linha_selecionada,0)->text();
        QString nome_antiga=ui->tw_Cadastros->item(linha_selecionada,1)->text();
        QString username_antiga=ui->tw_Cadastros->item(linha_selecionada,2)->text();
        QString senha_antiga=ui->tw_Cadastros->item(linha_selecionada,3)->text();
        QString tipo = "Médico";

        //Indo para tela de Editar Cadastros - ADM
        ADM_cadastro_editar *tela_edicao = new ADM_cadastro_editar;
        close();
        tela_edicao->show();

        //Recorre a métodos da classe "ADM_cadastro_editar" para que os dados sejam passados para essa classe (herança)
        tela_edicao->mudarTexto_nome(nome_antiga);
        tela_edicao->mudarTexto_username(username_antiga);
        tela_edicao->mudarTexto_senha(senha_antiga);
        tela_edicao->mudarLabels(tipo,id);

    }
}

        //Guia de novos cadastros

//Botão Concluir (botaoConcluir), salvando um novo cadastro
void ADM_cadastros::on_botaoConcluir_clicked()
{
    //Variáveis que serão escritas nas linhas de texto e que serão adicionadas no banco de dados
    QString nome =ui->txt_nome->text();
    QString username =ui->txt_username->text();
    QString senha =ui->txt_senha->text();
    QString especialidade =ui->txt_especialidade->text();

    //Query para o novo cadastro e checar se ele é válido
    QSqlQuery novo_cadastro;
    QSqlQuery checando;
    int contagem = 0;

    //Caso o botão de rádio 'Paciente' (rd_PacienteNOVO), um novo cadastro será criado na tabela 'pacientes'
    if(ui->rd_PacienteNOVO->isChecked()){
        //Mensagem de erro caso um ou mais campos não estejam preenchidos
        if (nome == "" ||username == ""||senha == ""){
            QMessageBox::warning(this,"ERRO","É preciso que todos os campos estejam preenchidos");
        }else{
            //Checando se já existe esse username na tabela de pacientes
            checando.prepare("SELECT * FROM pacientes where username = :username");
            checando.bindValue(":username",username);
            contagem = 0;
            if (checando.exec()){
                while (checando.next()){
                    contagem++;
                }
                //Mensagem de erro caso já exista (o novo cadastron não é realizado)
                if (contagem>0){
                    QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                }else{
                    //Checando se já existe esse username na tabela de médicos
                    checando.prepare("SELECT * FROM medicos where username = :username");
                    checando.bindValue(":username",username);
                    contagem = 0;
                    if (checando.exec()){
                        while (checando.next()){
                            contagem++;
                        }
                        if (contagem>0){
                            QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                        }else{
                            //Query para criar um novo cadastro de paciente, colocando os dados certos nos seus respectivos lugares
                            //Sempre vai ser registrado "XXXXXXXX" na coluna 'especialidade', independente do que for escrito no espaço de escrita (pacientes não tem especialidades consideradas)
                            novo_cadastro.prepare("insert into pacientes (nome,username,senha,especialidade) values"
                                                  "('"+nome+"','"+username+"','"+senha+"','XXXXXXXX')");

                            if(novo_cadastro.exec()){
                                //Se executa, é anunciado por uma QMessageBox e um qDebug além de limpar as áreas de escrita
                                QMessageBox::information(this,"","Registro de novo paciente gravado com sucesso");
                                qDebug()<<"Novo cadastro de paciente:"<<nome;
                                ui->txt_nome->clear();
                                ui->txt_username->clear();
                                ui->txt_senha->clear();
                                ui->txt_especialidade->clear();

                            }else{
                                qDebug()<<"Erro ao registrar novo paciente";
                            }
                       }
                    }
                }
            }
        }
    }

    //Caso o botão de rádio 'Médico' (rd_MedicoNOVO), um novo cadastro será criado na tabela 'medicos'
    if(ui->rd_MedicoNOVO->isChecked()){
        //Mensagem de erro caso um ou mais campos não estejam preenchidos
        if (nome == ""||username == ""||senha == ""||especialidade==""){
            QMessageBox::warning(this,"ERRO","É preciso que todos os campos estejam preenchidos");

        }else{
            //Checando se já existe esse username na tabela de pacientes
            checando.prepare("SELECT * FROM pacientes where username = :username");
            checando.bindValue(":username",username);
            contagem = 0;
            if (checando.exec()){
                while (checando.next()){
                    contagem++;
                }
                if (contagem>0){
                    QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                }else{
                    //Checando se já existe esse username na tabela de médicos
                    checando.prepare("SELECT * FROM medicos where username = :username");
                    checando.bindValue(":username",username);
                    contagem = 0;
                    if (checando.exec()){
                        while (checando.next()){
                            contagem++;
                        }
                        if (contagem>0){
                            QMessageBox::warning(this, "ERRO", "Esse username já existe!");
                        }else{
                            //Query para criar um novo cadastro de médico, colocando os dados certos nos seus respectivos lugares
                            novo_cadastro.prepare("insert into medicos (nome,username,senha,especialidade) values"
                                                  "('"+nome+"','"+username+"','"+senha+"','"+especialidade+"')");

                            if(novo_cadastro.exec()){
                                //Se executa, é anunciado por uma QMessageBox e um qDebug além de limpar as áreas de escrita
                                QMessageBox::information(this,"","Registro de novo médico gravado com sucesso");
                                qDebug()<<"Novo cadastro de paciente:"<<nome;
                                ui->txt_nome->clear();
                                ui->txt_username->clear();
                                ui->txt_senha->clear();
                                ui->txt_especialidade->clear();

                            }else{
                                qDebug()<<"Erro ao registrar novo médico";
                            }
                        }
                    }
                }
            }
        }
    }
}

//Botão Cancelar (limpar as linhas de texto para o modo salvo de acordo com o Id)
void ADM_cadastros::on_botaoCancelar_clicked()
{
    ui->txt_nome->clear();
    ui->txt_username->clear();
    ui->txt_senha->clear();
    ui->txt_especialidade->clear();
}
