#ifndef ADM_INICIO_H
#define ADM_INICIO_H

#include <QMainWindow>

namespace Ui {
class ADM_inicio;
}

class ADM_inicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit ADM_inicio(QWidget *parent = nullptr);
    ~ADM_inicio();

private slots:

    void on_botaoAtendimentos_clicked();

    void on_botaoCadastros_clicked();

    void on_botaoMaterial_clicked();

    void on_botaoSair_clicked();

private:
    Ui::ADM_inicio *ui;
};

#endif // ADM_INICIO_H
