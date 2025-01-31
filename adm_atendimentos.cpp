#include "adm_atendimentos.h"
#include "ui_adm_atendimentos.h"
#include <QMessageBox>
#include <QDebug>
#include <QButtonGroup>

#include "adm_inicio.h"
#include "adm_cadastros.h"
#include "adm_material.h"
#include "login.h"

//Inicializando a tela de Atendimentos - ADM
ADM_atendimentos::ADM_atendimentos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ADM_atendimentos)
{
    ui->setupUi(this);
    //qDebug para acompanhar o progresso
    qDebug()<< "-------------------";
    qDebug()<< "Você está em Atendimentos - ADM";

        //Listando os cadastros de pacientes e médicos para marcar um atendimento

    //Query no banco de dados para listar a tabela de Pacientes
    QSqlQuery query_pacientes;
    query_pacientes.prepare("select * from pacientes");
    if(query_pacientes.exec()){ //Caso o banco de dados seja acessdo, o qDebug vai confirmar
        qDebug()<<"Cadastros de pacientes acessados";
        int linha = 0;
        ui->tw_pacientes->setColumnCount(2);

        //Enquanto existem linhas no banco de dados, elas vão ser inseridas em ordem na Table Widget de Pacientes (tw_pacientes)
        while(query_pacientes.next()){
            ui->tw_pacientes->insertRow(linha);
            ui->tw_pacientes->setItem(linha,0,new QTableWidgetItem(query_pacientes.value(0).toString()));   //Item da 1a coluna: Id do paciente
            ui->tw_pacientes->setItem(linha,1,new QTableWidgetItem(query_pacientes.value(1).toString()));   //Item da 2a coluna: Nome do Paciente

            ui->tw_pacientes->setRowHeight(linha,20);
            linha++;    //Número da próxima linha
        }

        //Definindo comprimento das colunas e cabeçalho
        ui->tw_pacientes->setColumnWidth(0,3);
        ui->tw_pacientes->setColumnWidth(1,700);
        QStringList cabecalho={"Id","Nome"};
        ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
        ui->tw_pacientes->verticalHeader()->setVisible(false);

        //Removendo a seleção por item e determinando a seleção por linha
        ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_pacientes->setStyleSheet("QTableView {selection-background-color:grey}");

    }else{
        //Mensagem de erro caso os banco de dados não seja acessado corretamente
        QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
        qDebug()<<"Não foi possível listar os cadastros";
    }

    //Query no banco de dados para listar a tabela de Médicos
    QSqlQuery query_medicos;
    query_medicos.prepare("select * from medicos");
    if(query_medicos.exec()){    //Caso o banco de dados seja acessdo, o qDebug vai confirmar
        qDebug()<<"Cadastros de médicos acessados";
        int linha = 0;
        ui->tw_medicos->setColumnCount(3);

        //Enquanto existem linhas no banco de dados, elas vão ser inseridas em ordem na Table Widget de Médicos (tw_medicos)
        while(query_medicos.next()){
            ui->tw_medicos->insertRow(linha);
            ui->tw_medicos->setItem(linha,0,new QTableWidgetItem(query_medicos.value(0).toString()));   //Item da 1a coluna: Id do médico
            ui->tw_medicos->setItem(linha,1,new QTableWidgetItem(query_medicos.value(1).toString()));   //Item da 2a coluna: Nome do médico
            ui->tw_medicos->setItem(linha,2,new QTableWidgetItem(query_medicos.value(4).toString()));   //Item da 3a coluna: Especialidade do médico

            ui->tw_medicos->setRowHeight(linha,20);
            linha++;    //Número da próxima linha
        }

        //Definindo comprimento das colunas e cabeçalho
        ui->tw_medicos->setColumnWidth(0,3);
        ui->tw_medicos->setColumnWidth(1,500);
        ui->tw_medicos->setColumnWidth(2,200);
        QStringList cabecalho={"Id","Nome", "Especialidade"};
        ui->tw_medicos->setHorizontalHeaderLabels(cabecalho);
        ui->tw_medicos->verticalHeader()->setVisible(false);

        //Removendo a seleção por item e determinando a seleção por linha
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
ADM_atendimentos::~ADM_atendimentos()
{
    delete ui;
}

//Botão para a tela de Início - ADM
void ADM_atendimentos::on_botaoInicio_clicked()
{
    ADM_inicio *irInicio = new ADM_inicio(this);
    close();
    irInicio->show();
    //qDebug para acompanhar o progresso
    qDebug()<< "-------------------";
    qDebug()<< "Você está na tela de Início - ADM";
}

//Botão para tela de Cadastros - ADM
void ADM_atendimentos::on_botaoCadastros_clicked()
{
    ADM_cadastros *irCadastros = new ADM_cadastros(this);
    close();
    irCadastros->show();
}

//Botão para tela de Material - ADM
void ADM_atendimentos::on_botaoMaterial_clicked()
{
    ADM_material *irMaterial = new ADM_material(this);
    close();
    irMaterial->show();
}

//Botão para a tela de Login (botaoSair)
void ADM_atendimentos::on_botaoSair_clicked()
{
    Login *irLogin = new Login(this);
    close();
    irLogin->show();
}

    //Aba de marcar atendimentos

//Botão para marcar um atendimento
void ADM_atendimentos::on_botaoMarcar_clicked()
{
    //Definindo o grupo de botões para marca a consulta e cirurgia (para que ambos estejam desmarcados no começo, e se dermarquem quando marcar um atendimento)
    QButtonGroup* grupo_botoes = new QButtonGroup(this);
    grupo_botoes->addButton(ui->rdbotaoCirurgia); //Botão de Cirurgia
    grupo_botoes->addButton(ui->rdbotaoConsulta); //Botão de Consulta
    ui->rdbotaoCirurgia->setChecked(false);
    ui->rdbotaoConsulta->setChecked(false);
    grupo_botoes->setExclusive(false);

    int linha_paciente = ui->tw_pacientes->currentRow();    //Linha do paciente selecionado para o atendimento

    //Caso a linha selecionada seja número '-1' (estado do "currentRow" quando nenhum paciente do banco de dados é selecionado), é enviada um aviso para escolher um paciente
    if (ui->tw_pacientes->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um paciente.");
        return;
    }

    //Recolhendo as informações de Id e Nome do paciente selecionado
    int id_paciente = ui->tw_pacientes->item(linha_paciente, 0)->text().toInt();
    QString nome_paciente = ui->tw_pacientes->item(linha_paciente, 1)->text();

    int linha_medico = ui->tw_medicos->currentRow();    //Linha do médico selecionado para o atendimento


    //Caso a linha selecionada seja número '-1' (estado do "currentRow" quando nenhum paciente do banco de dados é selecionado), é enviada um aviso para escolher um paciente
    if (ui->tw_medicos->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um médico.");
        return;
    }

    //Recolhendo as informações de Id e Nome do médico selecionado
    int id_medico = ui->tw_medicos->item(linha_medico, 0)->text().toInt();
    QString nome_medico = ui->tw_medicos->item(linha_medico, 1)->text();

    //Recolhendo as informações da data e horário selecionado
    QDate data_selecionada = ui->calndario->selectedDate();
    QString data = data_selecionada.toString("dd-MM-yyyy");
    QTime hora_selecionada = ui->time_edit->time();
    QString hora = hora_selecionada.toString("HH");

    //Estabelecendo as querys para checar se o horário está disponível, se existe material suficiente no estoque e para tirar o material para ser usado no procedimento
    QSqlQuery query_checarHorario;
    int numero_checar_horario = 0;
    QSqlQuery query_checarMaterial;
    int numero_checar_material = 0;
    QSqlQuery query_marcar;
    QSqlQuery query_retirarMaterial;

    //Preparando a query para checar se o horário está disponível
    query_checarHorario.prepare("SELECT * FROM atendimentos WHERE (horario = :hora AND dia = :data) AND (medico_id = :id_medico OR paciente_id = :id_paciente)");
    query_checarHorario.bindValue(":id_medico", id_medico);
    query_checarHorario.bindValue(":id_paciente", id_paciente);
    query_checarHorario.bindValue(":data", data);
    query_checarHorario.bindValue(":hora", hora);

    if (query_checarHorario.exec()){
        numero_checar_horario = 0;
        //Caso o paciente ou o médico estejam indisponíveis nesse horário, a variável  numero_checar_horário aumenta 1
        while(query_checarHorario.next()){
            numero_checar_horario++;
        }
        //Caso a variável não permaneça como 0, o sistema manda uma mensagem de erro e não marca o atendimento
        if (numero_checar_horario>0){
            QMessageBox::warning(this,"ERRO","Horário indisponível! Faça outra seleção!");
        }else{
            //Caso o contrario, é preparada a query de para checar se existe material suficiente para o atendimento
            query_checarMaterial.prepare("SELECT * FROM material where quantidade = 0");
            if(query_checarMaterial.exec()){
                numero_checar_material = 0;
                //Achando se existem materiais em falta no estoque
                while(query_checarMaterial.next()){
                    numero_checar_material++;
                }
                //Se algum deles estiver em falta, o sitema manda uma mensagem de erro e não marca o atendimento
                if(numero_checar_material>0){
                    QMessageBox::warning(this,"ERRO","Material insuficiente para atendimento!");
                //Caso contrário, tenta marcar um atendimento
                }else{
                    //Confere se deve marcar uma consulta e prepara a query
                    if(ui->rdbotaoConsulta->isChecked()){
                        query_marcar.prepare("insert into atendimentos (medico_id,paciente_id,dia,horario,tipo) values"
                                             "(:id_medico , :id_paciente , :data , :hora , :tipo)");
                        query_marcar.bindValue(":id_medico", id_medico);
                        query_marcar.bindValue(":id_paciente", id_paciente);
                        query_marcar.bindValue(":data", data);
                        query_marcar.bindValue(":hora", hora);
                        query_marcar.bindValue(":tipo", "Consulta");

                        if(query_marcar.exec()){
                            //Se executa, a consulta é marcada e todas as seleções são desmarcadas
                            QMessageBox::information(this,"","Nova consulta marcada com sucesso");
                            qDebug()<<"Nova consulta marcada para o paciente "<<nome_paciente<<" e o médico "<<nome_medico<<", para o dia "<<data<<" às "<<hora<<" horas.";

                            ui->rdbotaoConsulta->setChecked(false);
                            ui->rdbotaoCirurgia->setChecked(false);
                            ui->tw_pacientes->clearSelection();
                            ui->tw_pacientes->setCurrentCell(-1, -1);
                            ui->tw_medicos->clearSelection();
                            ui->tw_medicos->setCurrentCell(-1, -1);
                            ui->calndario->setSelectedDate(QDate(1,1,1));
                            ui->time_edit->setTime(QTime(0, 0));

                            //Query que reserva uma unidade da cada material para a consulta
                            query_retirarMaterial.prepare("UPDATE material SET quantidade = quantidade - 1");
                            if (query_retirarMaterial.exec()){
                                qDebug()<<"Material para o atendimento reservado";
                            }
                        }
                    //Confere se deve marcar uma cirurgia e prepara a query
                    }else if(ui->rdbotaoCirurgia->isChecked()){
                        query_marcar.prepare("insert into atendimentos (medico_id,paciente_id,dia,horario,tipo) values"
                                             "(:id_medico , :id_paciente , :data , :hora , :tipo)");
                        query_marcar.bindValue(":id_medico", id_medico);
                        query_marcar.bindValue(":id_paciente", id_paciente);
                        query_marcar.bindValue(":data", data);
                        query_marcar.bindValue(":hora", hora);
                        query_marcar.bindValue(":tipo", "Cirurgia");

                        //Se executa, a cirurgia é marcada e todas as seleções são desmarcadas
                        if(query_marcar.exec()){
                            QMessageBox::information(this,"","Nova cirurgia marcada com sucesso");
                            qDebug()<<"Nova cirurgia marcada para o paciente "<<nome_paciente<<" e o médico "<<nome_medico<<", para o dia "<<data<<" às "<<hora<<" horas.";

                            ui->rdbotaoConsulta->setChecked(false);
                            ui->rdbotaoCirurgia->setChecked(false);
                            grupo_botoes->setExclusive(true);
                            grupo_botoes->setExclusive(false);
                            ui->tw_pacientes->clearSelection();
                            ui->tw_pacientes->setCurrentCell(-1, -1);
                            ui->tw_medicos->clearSelection();
                            ui->tw_medicos->setCurrentCell(-1, -1);
                            ui->calndario->setSelectedDate(QDate(1,1,1));
                            ui->time_edit->setTime(QTime(0, 0));

                            //Query que reserva uma unidade da cada material para a cirurgia
                            query_retirarMaterial.prepare("UPDATE material SET quantidade = quantidade - 1");
                            if (query_retirarMaterial.exec()){
                                qDebug()<<"Material para o atendimento reservado";
                            }
                        }
                    //Se algum dos campos não for selecionado corretamente, o sistema expõe uma mensagem de erro e não marca um atendimento
                    }else if((!ui->rdbotaoCirurgia->isChecked() && !ui->rdbotaoConsulta->isChecked()) || ui->tw_pacientes->currentRow() == -1 || ui->tw_medicos->currentRow() == -1 || ui->calndario->selectedDate() == QDate(1, 1, 1)){
                        QMessageBox::warning(this,"ERRO","É necessário que todos os campos estejam selecionados!");
                    }
                }
            }
        }
    }
}


//Aba de atendimentos já marcados

//Botão para pesquisar atendimentos já marcados
void ADM_atendimentos::on_botaoPesquisar_clicked()
{
    //Se o botão rádio "Todos" (rdbotaoEscolher_Todos) estiver marcado, vai ser feita a pesquisa de todos os atendimentos da data selecionada
    if (ui->rdbotaoEscolher_Todos->isChecked()){

        ui->tw_atendimentos->clearSelection();

        QDate data_selecionada = ui->calendario_marcados->selectedDate();
        QString data = data_selecionada.toString("dd-MM-yyyy");

        //Query para mostrar todos os atendimentos na Table Widget de Atendimentos (tw_atendimentos)
        QSqlQuery query_pesquisa;

        query_pesquisa.prepare("SELECT atendimentos.id, pacientes.nome AS nome_paciente, medicos.nome AS nome_medico, atendimentos.horario,  atendimentos.tipo "
                               "FROM atendimentos "
                               "JOIN pacientes ON atendimentos.paciente_id = pacientes.id "
                               "JOIN medicos ON atendimentos.medico_id = medicos.id "
                               "WHERE atendimentos.dia = :data "
                               "ORDER BY atendimentos.horario ASC ");
        query_pesquisa.bindValue(":data", data);
        int linha = 0;

        //Limpando a table widget de cadastros (tw_atendimentos), para mostrar apenas os atendimentos do dia escolhido e estabelecendo a quantidade de colunas
        ui->tw_atendimentos->setRowCount(0);
        ui->tw_atendimentos->clearContents();
        ui->tw_atendimentos->setColumnCount(5);

        //Enquanto existem linhas no banco de dados, elas vão ser inseridas em ordem na Table Widget de Atendimentos (tw_atendimentos) com as informações corretas
        if (query_pesquisa.exec()){
            while(query_pesquisa.next()){
                ui->tw_atendimentos->insertRow(linha);
                ui->tw_atendimentos->setItem(linha,0,new QTableWidgetItem(query_pesquisa.value(0).toString())); //Item da 1a coluna: Id do atendimento
                ui->tw_atendimentos->setItem(linha,1,new QTableWidgetItem(query_pesquisa.value(1).toString())); //Item da 2a coluna: Nome do paciente
                ui->tw_atendimentos->setItem(linha,2,new QTableWidgetItem(query_pesquisa.value(2).toString())); //Item da 3a coluna: Nome do médico
                ui->tw_atendimentos->setItem(linha,3,new QTableWidgetItem(query_pesquisa.value(3).toString())); //Item da 4a coluna: Horário do atendimento
                ui->tw_atendimentos->setItem(linha,4,new QTableWidgetItem(query_pesquisa.value(4).toString())); //Item da 5a coluna: Tipo de atendimento

                ui->tw_atendimentos->setRowHeight(linha,20);
                linha++;    //Linha do próximo atendimento
            }

            //qDebug de acompanhamento do sistema
            qDebug()<<"Você acessou todos os atendimentos do dia "<<data;

            //Definindo comprimento das colunas, cabeçalho e limpando a linha selecionada
            ui->tw_atendimentos->setColumnWidth(0,3);
            ui->tw_atendimentos->setColumnWidth(1,260);
            ui->tw_atendimentos->setColumnWidth(2,260);
            ui->tw_atendimentos->setColumnWidth(3,105);
            ui->tw_atendimentos->setColumnWidth(4,105);
            QStringList cabecalho={"Id","Paciente","Médico","Horário","Tipo"};
            ui->tw_atendimentos->setHorizontalHeaderLabels(cabecalho);
            ui->tw_atendimentos->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_atendimentos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_atendimentos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_atendimentos->setStyleSheet("QTableView {selection-background-color:grey}");
        }else{
            //Mensagem de erro caso os banco de dados não seja acessado corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }

    //Se o botão rádio "Consulta" (rdbotaoEscolher_Consulta) estiver marcado, vai ser feita a pesquisa das consultas marcadas na data selecionada
    if (ui->rdbotaoEscolher_Consulta->isChecked()){

        ui->tw_atendimentos->clearSelection();

        QDate data_selecionada = ui->calendario_marcados->selectedDate();
        QString data = data_selecionada.toString("dd-MM-yyyy");

        //Query para mostrar as consultas na Table Widget de Atendimentos (tw_atendimentos)
        QSqlQuery query_pesquisa;

        query_pesquisa.prepare("SELECT atendimentos.id, pacientes.nome AS nome_paciente, medicos.nome AS nome_medico, atendimentos.horario "
                               "FROM atendimentos "
                               "JOIN pacientes ON atendimentos.paciente_id = pacientes.id "
                               "JOIN medicos ON atendimentos.medico_id = medicos.id "
                               "WHERE atendimentos.dia = :data and atendimentos.tipo = :tipo "
                               "ORDER BY atendimentos.horario ASC ");

        query_pesquisa.bindValue(":data", data);
        query_pesquisa.bindValue(":tipo", "Consulta");
        int linha = 0;

        //Limpando a table widget de cadastros (tw_atendimentos), para mostrar apenas as consultas do dia escolhido e estabelecendo a quantidade de colunas
        ui->tw_atendimentos->setRowCount(0);
        ui->tw_atendimentos->clearContents();
        ui->tw_atendimentos->setColumnCount(4);

        //Enquanto existem linhas no banco de dados, elas vão ser inseridas em ordem na Table Widget de Atendimentos (tw_atendimentos) com as informações corretas
        if (query_pesquisa.exec()){
            while(query_pesquisa.next()){
                ui->tw_atendimentos->insertRow(linha);
                ui->tw_atendimentos->setItem(linha,0,new QTableWidgetItem(query_pesquisa.value(0).toString())); //Item da 1a coluna: Id do atendimento
                ui->tw_atendimentos->setItem(linha,1,new QTableWidgetItem(query_pesquisa.value(1).toString())); //Item da 2a coluna: Nome do paciente
                ui->tw_atendimentos->setItem(linha,2,new QTableWidgetItem(query_pesquisa.value(2).toString())); //Item da 3a coluna: Nome do médico
                ui->tw_atendimentos->setItem(linha,3,new QTableWidgetItem(query_pesquisa.value(3).toString())); //Item da 4a coluna: Horário do atendimento
                ui->tw_atendimentos->setRowHeight(linha,20);
                linha++;    //Linha do próximo atendimento
            }

            //qDebug de acompanhamento do sistema
            qDebug()<<"Você acessou as consultas marcadas para o dia "<<data;

            //Definindo comprimento das colunas e cabeçalho
            ui->tw_atendimentos->setColumnWidth(0,3);
            ui->tw_atendimentos->setColumnWidth(1,310);
            ui->tw_atendimentos->setColumnWidth(2,310);
            ui->tw_atendimentos->setColumnWidth(3,110);
            QStringList cabecalho={"Id","Paciente","Médico","Horário"};
            ui->tw_atendimentos->setHorizontalHeaderLabels(cabecalho);
            ui->tw_atendimentos->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_atendimentos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_atendimentos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_atendimentos->setStyleSheet("QTableView {selection-background-color:grey}");
        }else{
            //Mensagem de erro caso os banco de dados não seja acessado corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }
    //Se o botão rádio "Cirurgia" (rdbotaoEscolher_Cirurgia) estiver marcado, vai ser feita a pesquisa das cirurgias marcadas na data selecionada
    if (ui->rdbotaoEscolher_Cirurgia->isChecked()){

        ui->tw_atendimentos->clearSelection();

        QDate data_selecionada = ui->calendario_marcados->selectedDate();
        QString data = data_selecionada.toString("dd-MM-yyyy");

        //Query para mostrar as cirurgias na Table Widget de Atendimentos (tw_atendimentos)
        QSqlQuery query_pesquisa;

        query_pesquisa.prepare("SELECT atendimentos.id, pacientes.nome AS nome_paciente, medicos.nome AS nome_medico, atendimentos.horario "
                               "FROM atendimentos "
                               "JOIN pacientes ON atendimentos.paciente_id = pacientes.id "
                               "JOIN medicos ON atendimentos.medico_id = medicos.id "
                               "WHERE atendimentos.dia = :data and atendimentos.tipo = :tipo "
                               "ORDER BY atendimentos.horario ASC ");

        query_pesquisa.bindValue(":data", data);
        query_pesquisa.bindValue(":tipo", "Cirurgia");
        int linha = 0;

        //Limpando a table widget de cadastros (tw_atendimentos), para mostrar apenas as cirurgias do dia escolhido e estabelecendo a quantidade de colunas
        ui->tw_atendimentos->setRowCount(0);
        ui->tw_atendimentos->clearContents();
        ui->tw_atendimentos->setColumnCount(4);

        //Enquanto existem linhas no banco de dados, elas vão ser inseridas em ordem na Table Widget de Atendimentos (tw_atendimentos) com as informações corretas
        if (query_pesquisa.exec()){
            while(query_pesquisa.next()){
                ui->tw_atendimentos->insertRow(linha);
                ui->tw_atendimentos->setItem(linha,0,new QTableWidgetItem(query_pesquisa.value(0).toString())); //Item da 1a coluna: Id do atendimento
                ui->tw_atendimentos->setItem(linha,1,new QTableWidgetItem(query_pesquisa.value(1).toString())); //Item da 2a coluna: Nome do paciente
                ui->tw_atendimentos->setItem(linha,2,new QTableWidgetItem(query_pesquisa.value(2).toString())); //Item da 3a coluna: Nome do médico
                ui->tw_atendimentos->setItem(linha,3,new QTableWidgetItem(query_pesquisa.value(3).toString())); //Item da 4a coluna: Horário do atendimento
                ui->tw_atendimentos->setRowHeight(linha,20);
                linha++;    //Linha do próximo atendimento
            }

            //qDebug de acompanhamento do sistema
            qDebug()<<"Você acessou as cirurgias marcadas para o dia "<<data;

            //Definindo comprimento das colunas e cabeçalho
            ui->tw_atendimentos->setColumnWidth(0,3);
            ui->tw_atendimentos->setColumnWidth(1,310);
            ui->tw_atendimentos->setColumnWidth(2,310);
            ui->tw_atendimentos->setColumnWidth(3,110);
            QStringList cabecalho={"Id","Paciente","Médico","Horário"};
            ui->tw_atendimentos->setHorizontalHeaderLabels(cabecalho);
            ui->tw_atendimentos->verticalHeader()->setVisible(false);

            //Determinando a seleção por linha
            ui->tw_atendimentos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_atendimentos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_atendimentos->setStyleSheet("QTableView {selection-background-color:grey}");
        }else{
            //Mensagem de erro caso os banco de dados não seja acessado corretamente
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar cadastros");
            qDebug()<<"Não foi possível listar os cadastros";
        }
    }

}

//Botão de Excluir um atendimento
void ADM_atendimentos::on_botaoExcluir_clicked()
{
    int linha_selecionada = ui->tw_atendimentos->currentRow();

    //Caso a linha selecionada na Table Widget de Atendimentos (tw_atendimentos) seja "-1", o programa retorna uma mensagem de erro e não exclui um atendimento
    if (ui->tw_atendimentos->currentRow()==-1){
        QMessageBox::warning(this,"","Escolha um atendimento.");
        return;
    }

    int id_selecionado = ui->tw_atendimentos->item(linha_selecionada, 0)->text().toInt();

    //Querys para exluirem o atendimento selecionado e devolver o material selecionado ao estoque
    QSqlQuery query_excluirAtendimento;
    QSqlQuery query_addMaterial;

    query_excluirAtendimento.prepare("delete from atendimentos where id = :id ");
    query_excluirAtendimento.bindValue(":id", id_selecionado);

    //Caso o atendimento seja excluído, a query de retornar o material é executada e o q Debug confirma o processo
    if (query_excluirAtendimento.exec()){
        ui->tw_atendimentos->removeRow(linha_selecionada);
        QMessageBox::information(this,"","Registro excluído");
        qDebug()<<"Você excluíu um atendimento!";

        query_addMaterial.prepare("UPDATE material SET quantidade = quantidade + 1");
        if (query_addMaterial.exec()){
            qDebug()<<"Estoque atualizado!";
        }

        ui->tw_atendimentos->clearSelection();
        ui->tw_atendimentos->setCurrentCell(-1, -1);
    }
}

