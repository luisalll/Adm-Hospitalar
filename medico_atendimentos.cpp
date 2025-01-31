#include "medico_atendimentos.h"
#include "ui_medico_atendimentos.h"
#include "QMessageBox"
#include "QDebug"

#include "medico_inicio.h"
#include "medico_cadastro.h"
#include "login.h"

//Inicializando a tela de Atendimentos - Médico
Medico_atendimentos::Medico_atendimentos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Medico_atendimentos)
{
    //qDebug para acompanhamento
    ui->setupUi(this);
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Atendimentos - Médicos";

    //QUery para mostrar os pacientes na tw_pacientes
    QSqlQuery query_pacientes;

    query_pacientes.prepare("select * from pacientes");
    if(query_pacientes.exec()){
        qDebug()<<"Cadastros de pacientes acessados";
        int linha = 0;
        ui->tw_pacientes->setColumnCount(2);
        //Enquanto existem pacientes cadastrados, eles são listados a Table Widget (tw_pacientes)
        while(query_pacientes.next()){
            ui->tw_pacientes->insertRow(linha);
            ui->tw_pacientes->setItem(linha,0,new QTableWidgetItem(query_pacientes.value(0).toString()));   //Item da 1a coluna: Id do paciente
            ui->tw_pacientes->setItem(linha,1,new QTableWidgetItem(query_pacientes.value(1).toString()));   //Item da 2a coluna: Nome do paciente
            ui->tw_pacientes->setRowHeight(linha,20);
            linha++;    //Próxima linha
        }

        //Largura das coluna e cabeçalho
        ui->tw_pacientes->setColumnWidth(0,3);
        ui->tw_pacientes->setColumnWidth(1,700);
        QStringList cabecalho={"Id","Nome"};
        ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
        ui->tw_pacientes->verticalHeader()->setVisible(false);

        //Determinando a seleção por linha
        ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_pacientes->setStyleSheet("QTableView {selection-background-color:grey}");
    }else{
        //Mensagem de erro caso os banco de dados não seja acessado corretamente
        QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
        qDebug()<<"Não foi possível listar os cadastros";
    }
}

//Fechando a interface
Medico_atendimentos::~Medico_atendimentos()
{
    delete ui;
}

//Botão para a tela de Início - Médicos (botaoInicio)
//Utilizando do método mudarNomeId da classe Medico_inicio para passagem do Id do médico correto (herança)
void Medico_atendimentos::on_botaoInicio_clicked()
{
    QString id = ui->label_num_id->text();
    Medico_inicio *irInicio = new Medico_inicio(this);
    close();
    irInicio->show();
    irInicio->mudarNomeId(id);
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - Médicos";
}

//Botão para a tela de Cadastro - Médicos (botaoCadastro)
//Utilizando do método mudarId da classe Medico_cadastro para passagem do Id do médico correto (herança)
void Medico_atendimentos::on_botaoCadastro_clicked()
{
    QString id = ui->label_num_id->text();
    Medico_cadastro *irCadastro = new Medico_cadastro(this);
    close();
    irCadastro->show();
    irCadastro->mudarId(id);
}

//Botão para a tela de Login (botaoSair)
void Medico_atendimentos::on_botaoSair_clicked()
{
    Login *voltarLogin = new Login(this);
    close();
    voltarLogin->show();
}

//Método para receber o Id do médico correto, vindo da tela anterior (herança)
void Medico_atendimentos::mudarId(const QString &id)
{
    ui->label_num_id->setText(id);
}

        //Aba de Marcar um novo Atendimento:

//Botão Marcar Atendimento (botaoMarcar)
void Medico_atendimentos::on_botaoMarcar_clicked()
{
    //Variáveis de reconhecimento do médico e do paciente
    int id_medico = ui->label_num_id->text().toInt();
    int linha_paciente = ui->tw_pacientes->currentRow();

    //Mensagem de erro caso nenhum paciente seja selecionado
    if (ui->tw_pacientes->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um paciente.");
        return;
    }

    //Outras variáveis para marcar a o atendimento
    int id_paciente = ui->tw_pacientes->item(linha_paciente, 0)->text().toInt();
    QString nome_paciente = ui->tw_pacientes->item(linha_paciente, 1)->text();
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
    query_checarHorario.prepare("SELECT * FROM atendimentos WHERE (horario = :hora AND dia = :data) AND (medico_id = :id_medico OR paciente_id = :id_paciente)");
    query_checarHorario.bindValue(":id_medico", id_medico);
    query_checarHorario.bindValue(":id_paciente", id_paciente);
    query_checarHorario.bindValue(":data", data);
    query_checarHorario.bindValue(":hora", hora);

    if (query_checarHorario.exec()){
        numero_checar_horario = 0;
        while(query_checarHorario.next()){
            numero_checar_horario++;
        }
        //Mensagem de erro caso o paciente ou o médicos estejam ocupados no horário estejam selecionados
        if (numero_checar_horario>0){
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
                    if(ui->rdbotaoConsulta->isChecked()){
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
                            qDebug()<<"Nova consulta marcada para o paciente "<<nome_paciente<<", para o dia "<<data<<" às "<<hora<<" horas.";

                            ui->rdbotaoConsulta->setChecked(false);
                            ui->rdbotaoCirurgia->setChecked(false);
                            ui->tw_pacientes->clearSelection();
                            ui->tw_pacientes->setCurrentCell(-1, -1);
                            ui->calendario->setSelectedDate(QDate(1,1,1));
                            ui->time_edit->setTime(QTime(0, 0));

                            //Query que reserva o material para a consulta
                            query_retirarMaterial.prepare("UPDATE material SET quantidade = quantidade - 1");
                            if (query_retirarMaterial.exec()){
                                qDebug()<<"Material para o atendimento reservado";
                            }
                        }
                    //Preparando query para marcar cirurgia
                    }else if(ui->rdbotaoCirurgia->isChecked()){
                        query_marcar.prepare("insert into atendimentos (medico_id,paciente_id,dia,horario,tipo) values"
                                             "(:id_medico , :id_paciente , :data , :hora , :tipo)");
                        query_marcar.bindValue(":id_medico", id_medico);
                        query_marcar.bindValue(":id_paciente", id_paciente);
                        query_marcar.bindValue(":data", data);
                        query_marcar.bindValue(":hora", hora);
                        query_marcar.bindValue(":tipo", "Cirurgia");

                        //Se executa, a cirurgia é colocada no banco de dados e a aba de marcar atendimento é limpa
                        if(query_marcar.exec()){
                            QMessageBox::information(this,"","Nova cirurgia marcada com sucesso");
                            qDebug()<<"Nova cirurgia marcada para o paciente "<<nome_paciente<<", para o dia "<<data<<" às "<<hora<<" horas.";

                            ui->rdbotaoConsulta->setChecked(false);
                            ui->rdbotaoCirurgia->setChecked(false);
                            ui->tw_pacientes->clearSelection();
                            ui->tw_pacientes->setCurrentCell(-1, -1);
                            ui->calendario->setSelectedDate(QDate(1,1,1));
                            ui->time_edit->setTime(QTime(0, 0));

                            //Query que reserva o material para a cirurgia
                            query_retirarMaterial.prepare("UPDATE material SET quantidade = quantidade - 1");
                            if (query_retirarMaterial.exec()){
                                qDebug()<<"Material para o atendimento reservado";
                            }
                        }
                    //Mensagem de erro caso um dos campos não seja selecionado
                    }else if((!ui->rdbotaoCirurgia->isChecked() && !ui->rdbotaoConsulta->isChecked()) || ui->tw_pacientes->currentRow() == -1 || ui->calendario->selectedDate() == QDate(1, 1, 1)){
                        QMessageBox::warning(this,"ERRO","É necessário que todos os campos estejam selecionados!");
                    }
                }
            }
        }
    }
}

        //Aba de Atendimentos já marcados

void Medico_atendimentos::on_botaoPesquisar_clicked()
{
    //Variáveis e query de pesquisa
    QDate data_selecionada = ui->calendario_marcados->selectedDate();
    QString data = data_selecionada.toString("dd-MM-yyyy");
    int id_medico = ui->label_num_id->text().toInt();
    QSqlQuery query_pesquisa;

    //Preparando a query para pesquisar os atendimentos ddo dia selecionado
    query_pesquisa.prepare("SELECT atendimentos.id, pacientes.nome AS nome_paciente, atendimentos.horario,  atendimentos.tipo "
                           "FROM atendimentos "
                           "JOIN pacientes ON atendimentos.paciente_id = pacientes.id "
                           "JOIN medicos ON atendimentos.medico_id = medicos.id "
                           "WHERE atendimentos.dia = :data AND atendimentos.medico_id = :id_medico "
                           "ORDER BY atendimentos.horario ASC ");

    query_pesquisa.bindValue(":data", data);
    query_pesquisa.bindValue(":id_medico", id_medico);
    int linha = 0;

    //Limpando a table widget de atendimentos e colocando as novas colunas (tw_atendimentos)
    ui->tw_atendimentos->setRowCount(0);
    ui->tw_atendimentos->clearContents();
    ui->tw_atendimentos->setColumnCount(4);

    //While para inserir todas os atendimentos marcados no dia
    if (query_pesquisa.exec()){
        while(query_pesquisa.next()){
            ui->tw_atendimentos->insertRow(linha);
            ui->tw_atendimentos->setItem(linha,0,new QTableWidgetItem(query_pesquisa.value(0).toString()));   //Item da 1a coluna: Id do atendimento
            ui->tw_atendimentos->setItem(linha,1,new QTableWidgetItem(query_pesquisa.value(1).toString()));   //Item da 2a coluna: Nome do paciente
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
        QStringList cabecalho={"Id","Paciente","Horário","Tipo"};
        ui->tw_atendimentos->setHorizontalHeaderLabels(cabecalho);
        ui->tw_atendimentos->verticalHeader()->setVisible(false);

        //Determinando a seleção por linha e tirando a seleção de linha anterior
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

//Botão excuir (botaoExcluir)
void Medico_atendimentos::on_botaoExcluir_clicked()
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

    //Preparando query para deletar o atendimento
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
