#include "adm_inicio.h"
#include "ui_adm_inicio.h"
#include <QMessageBox>
#include <QDebug>

#include "adm_atendimentos.h"
#include "adm_cadastros.h"
#include "adm_material.h"
#include "login.h"


//Inicalizando a tela Início - ADM
ADM_inicio::ADM_inicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ADM_inicio)
{
    ui->setupUi(this);
}

//Fechando a interface
ADM_inicio::~ADM_inicio()
{
    delete ui;
}

//Botão para a tela de Atendimentos - ADM
void ADM_inicio::on_botaoAtendimentos_clicked()
{
    ADM_atendimentos *irAtendimentos = new ADM_atendimentos(this);
    close();
    irAtendimentos->show();
}

//Botão para tela de Cadastros - ADM
void ADM_inicio::on_botaoCadastros_clicked()
{
    ADM_cadastros *irCadastro = new ADM_cadastros(this);
    close();
    irCadastro->show();
}

//Botão para tela de Material - ADM
void ADM_inicio::on_botaoMaterial_clicked()
{
    ADM_material *irMaterial = new ADM_material(this);
    close();
    irMaterial->show();
}

//Botão para a tela de Login (botaoSair)
void ADM_inicio::on_botaoSair_clicked()
{
    Login *irLogin = new Login(this);
    close();
    irLogin->show();
}
