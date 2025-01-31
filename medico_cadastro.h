#ifndef MEDICO_CADASTRO_H
#define MEDICO_CADASTRO_H

#include <QMainWindow>

namespace Ui {
class Medico_cadastro;
}

class Medico_cadastro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Medico_cadastro(QWidget *parent = nullptr);
    ~Medico_cadastro();

    void mudarId (const QString &id);

private slots:
    void on_botaoIncio_clicked();

    void on_botaoAtendimentos_clicked();

    void on_botaoSair_clicked();

    void on_botaoCancelar_clicked();

    void on_botaoAtualizar_clicked();

private:
    Ui::Medico_cadastro *ui;
};

#endif // MEDICO_CADASTRO_H
