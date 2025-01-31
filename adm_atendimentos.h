#ifndef ADM_ATENDIMENTOS_H
#define ADM_ATENDIMENTOS_H

#include <QMainWindow>

namespace Ui {
class ADM_atendimentos;
}

class ADM_atendimentos : public QMainWindow
{
    Q_OBJECT

public:
    explicit ADM_atendimentos(QWidget *parent = nullptr);
    ~ADM_atendimentos();

private slots:
    void on_botaoInicio_clicked();

    void on_botaoCadastros_clicked();

    void on_botaoMaterial_clicked();

    void on_botaoSair_clicked();

    void on_botaoMarcar_clicked();

    void on_botaoPesquisar_clicked();

    void on_botaoExcluir_clicked();

private:
    Ui::ADM_atendimentos *ui;
};

#endif // ADM_ATENDIMENTOS_H
