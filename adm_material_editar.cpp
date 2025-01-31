#include "adm_material_editar.h"
#include "ui_adm_material_editar.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

#include "adm_material.h"

//Inicializando a tela de Editar Material - ADM
ADM_material_editar::ADM_material_editar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ADM_material_editar)
{
    ui->setupUi(this);
    qDebug()<<"Você está editando o estoque";
}

//Fechando a interface
ADM_material_editar::~ADM_material_editar()
{
    delete ui;
}

//Função para mudar labels e a quantidade de acordo com o material selecionado na tela Material - ADM (herança)
void ADM_material_editar ::mudarTextos (const QString &tipo, const QString &id, int quantidade)
{
    ui->label_tipoMaterial->setText(tipo);
    ui->label_idMaterial->setText(id);
    ui->spinBox_quantidade->setValue(quantidade);
}

//Botão aceito (atualiza a quantidade de material no estoque)
void ADM_material_editar::on_buttonBox_accepted()
{
    //Variáveis para atualização (nova quantidade, tipo de material e id)
    int nova_quantidade = ui->spinBox_quantidade->value();
    QString tipo = ui->label_tipoMaterial->text();
    QString id = ui->label_idMaterial->text();

    //Query para atualização
    QSqlQuery query_quantidade;
    query_quantidade.prepare("UPDATE material SET quantidade = :nova_quantidade where id = :id");
    query_quantidade.bindValue(":nova_quantidade", nova_quantidade);
    query_quantidade.bindValue(":id", id);

    if (query_quantidade.exec()){
        QMessageBox::information(this,"","Quantidade de material atualizada!");
        qDebug()<<"Você mudou a quantidade de "<<tipo<<" para "<<nova_quantidade;

        //Volta para tela Material - ADM
        ADM_material *voltarMaterial = new ADM_material;
        close();
        voltarMaterial->show();
    }else{
        QMessageBox::warning(this,"ERRO","Não foi possível atualizar a quantidade no estoque");
        ADM_material *voltarMaterial = new ADM_material;
        close();
        voltarMaterial->show();
    }

}

//Botão rejeitado (volta para a tela Material - ADM)
void ADM_material_editar::on_buttonBox_rejected()
{
    ADM_material *voltarMaterial = new ADM_material;
    close();
    voltarMaterial->show();
}

