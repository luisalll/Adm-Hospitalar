#include "adm_material.h"
#include "ui_adm_material.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

#include "adm_inicio.h"
#include "adm_atendimentos.h"
#include "adm_cadastros.h"
#include "login.h"
#include "adm_material_editar.h"

//Inicializando a tela de Material - ADM
ADM_material::ADM_material(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ADM_material)
{
    ui->setupUi(this);
    //qDebug para acompanhar o progresso
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Material - ADM";

    //Estabelecendo para quando a tela seja aberta, já apareça a lista de materiais:
    QSqlQuery query;
    //Query para mostrar dados da tabela 'material' do banco de dados
    query.prepare("select * from material;");
    if(query.exec()){
        qDebug()<<"Estoque acessados";
        int linha=0;
        ui->tw_Material->setColumnCount(3);

        //While para inserir todas as linhas de materiais
        while(query.next()){
            ui->tw_Material->insertRow(linha);
            ui->tw_Material->setItem(linha,0,new QTableWidgetItem(query.value(0).toString()));  //Item da 1a coluna: Id do material
            ui->tw_Material->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));  //Item da 2a coluna: Nome do material
            ui->tw_Material->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));  //Item da 3a coluna: Quantidade do material
            ui->tw_Material->setRowHeight(linha,20);
            linha++;    //Próxima linha
        }

        //Largura das colunas e cabeçalho
        ui->tw_Material->setColumnWidth(0,3);
        ui->tw_Material->setColumnWidth(1,650);
        ui->tw_Material->setColumnWidth(2,80);
        QStringList cabecalho={"Id","Tipo","Quantidade"};
        ui->tw_Material->setHorizontalHeaderLabels(cabecalho);
        ui->tw_Material->verticalHeader()->setVisible(false);

        //Determinando a seleção por linha
        ui->tw_Material->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_Material->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_Material->setStyleSheet("QTableView {selection-background-color:grey}");
    }else{
        //Mensagem de erro caso os banco de dados não seja acessado corretamente
        QMessageBox::warning(this,"ERRO","Erro ao pesquisar no estoque");
        qDebug()<<"Não foi possível listar os cadastros";
    }
}

//Fechando a interface
ADM_material::~ADM_material()
{
    delete ui;
}

//Botão para a tela de Início - ADM
void ADM_material::on_botaoInicio_clicked()
{
    ADM_inicio *irInicio = new ADM_inicio(this);
    close();
    irInicio->show();
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - ADM";
}

//Botão para a tela de Atendimentos - ADM
void ADM_material::on_botaoAtendimentos_clicked()
{
    ADM_atendimentos *irAtendimentos = new ADM_atendimentos(this);
    close();
    irAtendimentos->show();
}

//Botão para tela de Cadastros - ADM
void ADM_material::on_botaoCadastros_clicked()
{
    ADM_cadastros *irCadastro = new ADM_cadastros(this);
    close();
    irCadastro->show();
}

//Botão para a tela de Login (botaoSair)
void ADM_material::on_botaoSair_clicked()
{
    Login *irLogin = new Login(this);
    close();
    irLogin->show();
}

//Botão para editar a quantidade de um material (botaoEditar)
void ADM_material::on_botaoEditar_clicked()
{
    //Linha selecionada
    int linha_selecionada=ui->tw_Material->currentRow();

    //Mensagem de erro caso nenhum material for selecionado
    if (ui->tw_Material->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um material.");
    }else{
        //Variáveis e abertura da tela Editar Materiais - ADM
        QString id_material=ui->tw_Material->item(linha_selecionada,0)->text();
        QString tipo_material=ui->tw_Material->item(linha_selecionada,1)->text();
        int quantidade=ui->tw_Material->item(linha_selecionada,2)->text().toInt();

        ADM_material_editar *tela_edicao_material = new ADM_material_editar;
        close();
        tela_edicao_material->show();

        //Passagem dos dados para a tela de Editar Material - ADM recorrendo ao método mudarTextos da classe ADM_material_editar (herança)
        tela_edicao_material->mudarTextos(tipo_material,id_material,quantidade);
    }
}

