#include "paciente_atendimentos.h"
#include "ui_paciente_atendimentos.h"
#include "QMessageBox"
#include "QDebug"

#include "paciente_inicio.h"
#include "paciente_cadastro.h"
#include "login.h"

//Inicializando a tela de Atendimentos - Pacientes
Paciente_atendimentos::Paciente_atendimentos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Paciente_atendimentos)
{
    ui->setupUi(this);
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Atendimentos - Pacientes";

    //Query para mostrar os médicos na tw_medicos
    QSqlQuery query_medicos;
    query_medicos.prepare("select * from medicos");
    if(query_medicos.exec()){
        qDebug()<<"Cadastros de médicos acessados";
        int linha = 0;
        ui->tw_medicos->setColumnCount(3);

        //Enquanto existem médicos cadastrados, eles são listados a Table Widget (tw_medicos)
        while(query_medicos.next()){
            ui->tw_medicos->insertRow(linha);
            ui->tw_medicos->setItem(linha,0,new QTableWidgetItem(query_medicos.value(0).toString()));
            ui->tw_medicos->setItem(linha,1,new QTableWidgetItem(query_medicos.value(1).toString()));
            ui->tw_medicos->setItem(linha,2,new QTableWidgetItem(query_medicos.value(4).toString()));

            ui->tw_medicos->setRowHeight(linha,20);
            linha++;
        }

        //Largura das coluna e cabeçalho
        ui->tw_medicos->setColumnWidth(0,3);
        ui->tw_medicos->setColumnWidth(1,500);
        ui->tw_medicos->setColumnWidth(2,200);
        QStringList cabecalho={"Id","Nome", "Especialidade"};
        ui->tw_medicos->setHorizontalHeaderLabels(cabecalho);
        ui->tw_medicos->verticalHeader()->setVisible(false);

        //Determinando a seleção por linha
        ui->tw_medicos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_medicos->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_medicos->setStyleSheet("QTableView {selection-background-color:grey}");
    }else{
        //Mensagem de erro caso os banco de dados não seja acessado corretamente
        QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
        qDebug()<<"Não foi possível listar os cadastros";
    }
}

//Fechando a interface
Paciente_atendimentos::~Paciente_atendimentos()
{
    delete ui;
}

//Botão para a tela de Início - Pacientes (botaoInicio)
//Utilizando do método mudarNomeId da classe Paciente_inicio para passagem do Id do paciente correto (herança)
void Paciente_atendimentos::on_botaoInicio_clicked()
{
    QString id = ui->label_num_id->text();
    Paciente_inicio *irInicio = new Paciente_inicio(this);
    close();
    irInicio->show();
    irInicio->mudarNomeId(id);
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - Pacientes";
}

//Botão para a tela de Cadastro - Pacientes (botaoCadastro)
//Utilizando do método mudarId da classe Paciente_cadastro para passagem do Id do paciente correto (herança)
void Paciente_atendimentos::on_botaoCadastro_clicked()
{
    QString id = ui->label_num_id->text();
    Paciente_cadastro *irCadastro = new Paciente_cadastro(this);
    close();
    irCadastro->show();
    irCadastro->mudarId(id);
}

//Botão para a tela de Login (botaoSair)
void Paciente_atendimentos::on_botaoSair_clicked()
{
    Login *voltarLogin = new Login(this);
    close();
    voltarLogin->show();
}

//Método para receber o Id do paciente correto, vindo da tela anterior (herança)
void Paciente_atendimentos::mudarId(const QString &id)
{
    ui->label_num_id->setText(id);
}

        //Aba de Marcar um novo Atendimento:

//Botão Marcar Consulta (botaoMarcar)
void Paciente_atendimentos::on_botaoMarcar_clicked()
{
    //Variáveis de reconhecimento do médico e do paciente
    int id_paciente = ui->label_num_id->text().toInt();
    int linha_medico = ui->tw_medicos->currentRow();

    //Mensagem de erro caso nenhum médico seja selecionado
    if (ui->tw_medicos->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um paciente.");
        return;
    }

    //Outras variáveis para marcar a consulta
    int id_medico = ui->tw_medicos->item(linha_medico, 0)->text().toInt();
    QString nome_medico = ui->tw_medicos->item(linha_medico, 1)->text();
    QDate data_selecionada = ui->calendario->selectedDate();
    QString data = data_selecionada.toString("dd-MM-yyyy");
    QTime hora_selecionada = ui->time_edit->time();
    QString hora = hora_selecionada.toString("HH");

    //Querys (checar se o horário está disponível, se há material suficiente, para marcar o atendimento e reservar o material)
    QSqlQuery query_checarHorario;
    int numero_checar_horario = 0;
    QSqlQuery query_checarMaterial;
    int numero_checar_material = 0;
    QSqlQuery query_marcar;
    QSqlQuery query_retirarMaterial;

    //Preparando query que checa se o horário está disponível para o paciente e o médico
    query_checarHorario.prepare("SELECT * FROM atendimentos WHERE horario = :hora AND dia = :data AND (medico_id = :id_medico OR paciente_id = :id_paciente)");
    qDebug()<<data<<hora<<id_medico<<id_paciente;
    query_checarHorario.bindValue(":id_medico", id_medico);
    query_checarHorario.bindValue(":id_paciente", id_paciente);
    query_checarHorario.bindValue(":data", data);
    query_checarHorario.bindValue(":hora", hora);

    if (query_checarHorario.exec()){
        numero_checar_horario = 0;
        while(query_checarHorario.next()){
            numero_checar_horario++;
        }

        if (numero_checar_horario>0){
            //Mensagem de erro caso o paciente ou o médicos estejam ocupados no horário estejam selecionados
            QMessageBox::warning(this,"ERRO","Horário indisponível! Faça outra seleção!");
        }else{
            //Preparando query para garantir que há material suficiente no estoque
            query_checarMaterial.prepare("SELECT * FROM material where quantidade = 0");
            if(query_checarMaterial.exec()){
                numero_checar_material = 0;
                while(query_checarMaterial.next()){
                    numero_checar_material++;
                }
                //Mensagem de erro caso falte material
                if(numero_checar_material>0){
                    QMessageBox::warning(this,"ERRO","Material insuficiente para atendimento!");
                }else{
                    //Preparando query para marcar consulta
                    query_marcar.prepare("insert into atendimentos (medico_id,paciente_id,dia,horario,tipo) values"
                                         "(:id_medico , :id_paciente , :data , :hora , :tipo)");
                    query_marcar.bindValue(":id_medico", id_medico);
                    query_marcar.bindValue(":id_paciente", id_paciente);
                    query_marcar.bindValue(":data", data);
                    query_marcar.bindValue(":hora", hora);
                    query_marcar.bindValue(":tipo", "Consulta");

                    //Se executa, a consulta é colocada no banco de dados e a aba de marcar atendimento é limpa
                    if(query_marcar.exec()){
                        QMessageBox::information(this,"","Nova consulta marcada com sucesso");
                        qDebug()<<"Nova consulta marcada com o médico "<<nome_medico<<", para o dia "<<data<<" às "<<hora<<" horas.";

                        ui->tw_medicos->clearSelection();
                        ui->tw_medicos->setCurrentCell(-1, -1);
                        ui->calendario->setSelectedDate(QDate(1,1,1));
                        ui->time_edit->setTime(QTime(0, 0));

                        //Query que reserva o material para a consulta
                        query_retirarMaterial.prepare("UPDATE material SET quantidade = quantidade - 1");
                        if (query_retirarMaterial.exec()){
                            qDebug()<<"Material para o atendimento reservado";
                        }
                    }
                }
            }
        }
    }
}

        //Aba de Atendimentos marcados

void Paciente_atendimentos::on_botaoPesquisar_clicked()
{
    //Variáveis e query de pesquisa
    QDate data_selecionada = ui->calendario_marcados->selectedDate();
    QString data = data_selecionada.toString("dd-MM-yyyy");
    int id_paciente = ui->label_num_id->text().toInt();
    QSqlQuery query_pesquisa;

    //Preparando a query para pesquisar os atendimentos do dia selecionado
    query_pesquisa.prepare("SELECT atendimentos.id, medicos.nome AS nome_medico, atendimentos.horario,  atendimentos.tipo "
                           "FROM atendimentos "
                           "JOIN pacientes ON atendimentos.paciente_id = pacientes.id "
                           "JOIN medicos ON atendimentos.medico_id = medicos.id "
                           "WHERE atendimentos.dia = :data AND atendimentos.paciente_id = :id_paciente "
                           "ORDER BY atendimentos.horario ASC ");

    query_pesquisa.bindValue(":data", data);
    query_pesquisa.bindValue(":id_paciente", id_paciente);
    int linha = 0;

    //Limpando a table widget de cadastros (tw_atendimentos)
    ui->tw_atendimentos->setRowCount(0);
    ui->tw_atendimentos->clearContents();
    ui->tw_atendimentos->setColumnCount(4);

    if (query_pesquisa.exec()){
        //While para inserir todas os atendimentos marcados no dia
        while(query_pesquisa.next()){
            ui->tw_atendimentos->insertRow(linha);
            ui->tw_atendimentos->setItem(linha,0,new QTableWidgetItem(query_pesquisa.value(0).toString()));   //Item da 1a coluna: Id do atendimento
            ui->tw_atendimentos->setItem(linha,1,new QTableWidgetItem(query_pesquisa.value(1).toString()));   //Item da 2a coluna: Nome do médico
            ui->tw_atendimentos->setItem(linha,2,new QTableWidgetItem(query_pesquisa.value(2).toString()));   //Item da 3a coluna: Horário do atendimento
            ui->tw_atendimentos->setItem(linha,3,new QTableWidgetItem(query_pesquisa.value(3).toString()));   //Item da 4a coluna: Tipo de atendimento
            ui->tw_atendimentos->setRowHeight(linha,20);
            linha++;    //Próxima linha
        }

        //qDebug para acompanhar quais atendimentos foram acessados
        qDebug()<<"Você acessou todos os atendimentos do dia "<<data;

        //Largura das colunas e cabeçalho
        ui->tw_atendimentos->setColumnWidth(0,3);
        ui->tw_atendimentos->setColumnWidth(1,500);
        ui->tw_atendimentos->setColumnWidth(2,115);
        ui->tw_atendimentos->setColumnWidth(3,115);
        QStringList cabecalho={"Id","Médico","Horário","Tipo"};
        ui->tw_atendimentos->setHorizontalHeaderLabels(cabecalho);
        ui->tw_atendimentos->verticalHeader()->setVisible(false);

        //Determinando a seleção por linha e tirando a seleção da linha anterior
        ui->tw_atendimentos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_atendimentos->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_atendimentos->setStyleSheet("QTableView {selection-background-color:grey}");
        ui->tw_atendimentos->clearSelection();
        ui->tw_atendimentos->setCurrentCell(-1, -1);

    }else{
        //Mensagem de erro caso os banco de dados não seja acessado corretamente
        QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
        qDebug()<<"Não foi possível listar os cadastros";
    }
}

//Botaoexcluir (botaoExcluir)
void Paciente_atendimentos::on_botaoExcluir_clicked()
{
    //Linha selecionada
    int linha_selecionada = ui->tw_atendimentos->currentRow();

    //Mensagem de erro caso nenhum atendimento seja selecionado
    if (ui->tw_atendimentos->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um atendimento.");
        return;
    }
    //Id do atendimento e querys
    int id_selecionado = ui->tw_atendimentos->item(linha_selecionada, 0)->text().toInt();
    QSqlQuery query_excluirAtendimento;
    QSqlQuery query_addMaterial;
    query_excluirAtendimento.prepare("delete from atendimentos where id = :id ");
    query_excluirAtendimento.bindValue(":id", id_selecionado);

    //Removendo o atendimento do banco de dados
    if (query_excluirAtendimento.exec()){
        ui->tw_atendimentos->removeRow(linha_selecionada);
        QMessageBox::information(this,"","Registro excluído");
        qDebug()<<"Você excluíu um atendimento!";
        ui->tw_atendimentos->clearSelection();
        ui->tw_atendimentos->setCurrentCell(-1, -1);

        //Query para devolver ao estoque o material reservado para o atendimento deletado
        query_addMaterial.prepare("UPDATE material SET quantidade = quantidade + 1");
        if (query_addMaterial.exec()){
            qDebug()<<"Estoque atualizado!";
        }
    }
}

