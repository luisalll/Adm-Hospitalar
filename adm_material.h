#ifndef ADM_MATERIAL_H
#define ADM_MATERIAL_H

#include <QMainWindow>

namespace Ui {
class ADM_material;
}

class ADM_material : public QMainWindow
{
    Q_OBJECT

public:
    explicit ADM_material(QWidget *parent = nullptr);
    ~ADM_material();

private slots:
    void on_botaoInicio_clicked();

    void on_botaoAtendimentos_clicked();

    void on_botaoCadastros_clicked();

    void on_botaoSair_clicked();

    void on_botaoEditar_clicked();

private:
    Ui::ADM_material *ui;
};

#endif // ADM_MATERIAL_H
