#ifndef FM_EDITA_CESTA_H
#define FM_EDITA_CESTA_H

#include <QDialog>
#include "Cesta.h"
#include "Produto.h"
#include "ItemCesta.h"

namespace Ui {
class fm_edita_cesta;
}

class fm_edita_cesta : public QDialog
{
    Q_OBJECT

public:
    explicit fm_edita_cesta(QWidget *parent = nullptr, int id_cesta = 0);
    ~fm_edita_cesta();

    int id;
    Cesta cesta;
    QStringList cabecalho;

    void inicializa_fm_edita_cesta();
    void atualizaTableWidgetProdutos();
    void populaTableWidgetProdutos(QVector<Produto> listaProdutos);
    void atualizaTableWidgetItensCesta();
    void populaTableWidgetItensCesta(QVector<ItemCesta> listaItensCesta);
    void removeProduto();
    void adicionaItemCesta(ItemCesta item_cesta);
    void removeItemCesta();
    void adicionaProduto(Produto produto);

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_adicionar_clicked();

    void on_pushButton_retirar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_excluir_clicked();

private:
    Ui::fm_edita_cesta *ui;
};

#endif // FM_EDITA_CESTA_H
