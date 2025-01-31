#ifndef MEDICO_ATENDIMENTOS_H
#define MEDICO_ATENDIMENTOS_H

#include <QMainWindow>

namespace Ui {
class Medico_atendimentos;
}

class Medico_atendimentos : public QMainWindow
{
    Q_OBJECT

public:
    explicit Medico_atendimentos(QWidget *parent = nullptr);
    ~Medico_atendimentos();

    void mudarId (const QString &id);

private slots:
    void on_botaoInicio_clicked();

    void on_botaoSair_clicked();

    void on_botaoCadastro_clicked();

    void on_botaoMarcar_clicked();

    void on_botaoPesquisar_clicked();

    void on_botaoExcluir_clicked();

private:
    Ui::Medico_atendimentos *ui;
};

#endif // MEDICO_ATENDIMENTOS_H
