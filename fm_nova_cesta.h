#ifndef FM_NOVA_CESTA_H
#define FM_NOVA_CESTA_H

#include <QDialog>
#include "Produto.h"
#include "ItemCesta.h"

namespace Ui {
class fm_nova_cesta;
}

class fm_nova_cesta : public QDialog
{
    Q_OBJECT

public:
    explicit fm_nova_cesta(QWidget *parent = nullptr);
    ~fm_nova_cesta();

    // MINHAS VARIÁVEIS
    QStringList cabecalho;
    Cesta cesta;

    // MY METHODS
    void inicializa_fm_nova_cesta();
    void atualizaTableWidgetProdutos();
    void populaTableWidgetProdutos(QVector<Produto> listaProdutos);
    void removeProduto();
    void adicionaItemCesta(ItemCesta item_cesta);
    void removeItemCesta();
    void adicionaProduto(Produto produto);
    void limpaFormulario();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_adicionar_clicked();

    void on_tableWidget_produtos_itemSelectionChanged();

    void on_tableWidget_itens_cesta_itemSelectionChanged();

    void on_pushButton_retirar_clicked();

    void on_pushButton_salvar_cesta_clicked();

private:
    Ui::fm_nova_cesta *ui;
};

#endif // FM_NOVA_CESTA_H
