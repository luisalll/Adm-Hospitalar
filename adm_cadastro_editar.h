#ifndef ADM_CADASTRO_EDITAR_H
#define ADM_CADASTRO_EDITAR_H

#include <QDialog>

namespace Ui {
class ADM_cadastro_editar;
}

class ADM_cadastro_editar : public QDialog
{
    Q_OBJECT

public:
    explicit ADM_cadastro_editar(QWidget *parent = nullptr);
    ~ADM_cadastro_editar();

    void mudarTexto_nome (const QString &nome_antiga);
    void mudarTexto_username (const QString &username_antiga);
    void mudarTexto_senha (const QString &senha_antiga);

    void mudarLabels(const QString &tipo, const QString &id);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ADM_cadastro_editar *ui;
};

#endif // ADM_CADASTRO_EDITAR_H
