#ifndef ADM_MATERIAL_EDITAR_H
#define ADM_MATERIAL_EDITAR_H

#include <QDialog>

namespace Ui {
class ADM_material_editar;
}

class ADM_material_editar : public QDialog
{
    Q_OBJECT

public:
    explicit ADM_material_editar(QWidget *parent = nullptr);
    ~ADM_material_editar();

    void mudarTextos (const QString &tipo, const QString &id, int quantidade);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ADM_material_editar *ui;
};

#endif // ADM_MATERIAL_EDITAR_H
