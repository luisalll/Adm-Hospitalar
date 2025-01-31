#ifndef PACIENTE_CADASTRO_H
#define PACIENTE_CADASTRO_H

#include <QMainWindow>

namespace Ui {
class Paciente_cadastro;
}

class Paciente_cadastro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paciente_cadastro(QWidget *parent = nullptr);
    ~Paciente_cadastro();

    void mudarId (const QString &id);

private slots:


    void on_botaoInicio_clicked();

    void on_botaoAtendimentos_clicked();

    void on_botaoSair_clicked();


    void on_botaoCancelar_clicked();

    void on_botaoAtualizar_clicked();

private:
    Ui::Paciente_cadastro *ui;
};

#endif // PACIENTE_CADASTRO_H
