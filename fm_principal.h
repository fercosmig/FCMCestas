#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>
#include "Cesta.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class fm_principal;
}
QT_END_NAMESPACE

class fm_principal : public QMainWindow
{
    Q_OBJECT

public:
    fm_principal(QWidget *parent = nullptr);
    ~fm_principal();

    QStringList cabecalho;
    QString versao = "3.0";

    void inicializa_fm_principal();
    void configura_autenticacao();
    void atualizaTableWidget();
    void populaTableWidget(QVector<Cesta> listaCestas);
    void limpaFormulario();
    void habilitar_formulario();


private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_autenticacao_clicked();

    void on_actionSair_triggered();

    void on_actionSobre_triggered();

    void on_actionProdutos_triggered();

    void on_actionColaboradores_triggered();

    void on_pushButton_nova_cesta_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_pushButton_ver_cesta_clicked();

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
