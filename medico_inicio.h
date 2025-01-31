#ifndef MEDICO_INICIO_H
#define MEDICO_INICIO_H

#include <QMainWindow>

namespace Ui {
class Medico_inicio;
}

class Medico_inicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit Medico_inicio(QWidget *parent = nullptr);
    ~Medico_inicio();

    void mudarNomeId(const QString &id);

private slots:

    void on_botaoAtendimentos_clicked();

    void on_botaoCadastro_clicked();

    void on_botaoSair_clicked();

private:
    Ui::Medico_inicio *ui;
};

#endif // MEDICO_INICIO_H
