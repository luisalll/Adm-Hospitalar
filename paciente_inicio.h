#ifndef PACIENTE_INICIO_H
#define PACIENTE_INICIO_H

#include <QMainWindow>

namespace Ui {
class Paciente_inicio;
}

class Paciente_inicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paciente_inicio(QWidget *parent = nullptr);
    ~Paciente_inicio();

    void mudarNomeId(const QString &id);

private slots:

    void on_botaoAtendimentos_clicked();

    void on_botaoCadastro_clicked();

    void on_botaoSair_clicked();


private:
    Ui::Paciente_inicio *ui;
};

#endif // PACIENTE_INICIO_H
