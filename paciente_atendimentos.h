#ifndef PACIENTE_ATENDIMENTOS_H
#define PACIENTE_ATENDIMENTOS_H

#include <QMainWindow>

namespace Ui {
class Paciente_atendimentos;
}

class Paciente_atendimentos : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paciente_atendimentos(QWidget *parent = nullptr);
    ~Paciente_atendimentos();

    void mudarId (const QString &id);

private slots:
    void on_botaoInicio_clicked();

    void on_botaoSair_clicked();

    void on_botaoCadastro_clicked();

    void on_botaoMarcar_clicked();

    void on_botaoPesquisar_clicked();

    void on_botaoExcluir_clicked();

private:
    Ui::Paciente_atendimentos *ui;
};

#endif // PACIENTE_ATENDIMENTOS_H
