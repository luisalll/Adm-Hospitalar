#ifndef ADM_CADASTROS_H
#define ADM_CADASTROS_H

#include <QMainWindow>

namespace Ui {
class ADM_cadastros;
}

class ADM_cadastros : public QMainWindow
{
    Q_OBJECT

public:
    explicit ADM_cadastros(QWidget *parent = nullptr);
    ~ADM_cadastros();

private slots:

    //Cadastros antigos

    void on_botaoInicio_clicked();

    void on_botaoAtendimentos_clicked();

    void on_botaoMaterial_clicked();

    void on_botaoSair_clicked();

    void on_rabotaoTodos_clicked(bool checked);

    void on_rdbotaoPaciente_clicked(bool checked);

    void on_rdbotaoMedico_clicked(bool checked);

    void on_botaoExcluir_clicked();

    void on_botaoEditar_clicked();


    //Novos Cadastros

    void on_botaoConcluir_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_botaoCancelar_clicked();

private:
    Ui::ADM_cadastros *ui;
};

#endif // ADM_CADASTROS_H
