#ifndef FM_PRODUTOS_H
#define FM_PRODUTOS_H

#include <QDialog>
#include "Produto.h"

namespace Ui {
class fm_produtos;
}

class fm_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit fm_produtos(QWidget *parent = nullptr);
    ~fm_produtos();

    // Minhas variáveis de formulário
    QStringList cabecalho;

    // Meus métodos
    void inicializa_fm_produtos();
    void atualizaTableWidget();
    void populaTableWidget(QVector<Produto> listaProdutos);
    void limpaFormularioAlteracao();
    void limpaFormularioPesquisa();

private slots:
    void on_pushButton_fechar_clicked();

    void on_tableWidget_produtos_itemSelectionChanged();

    void on_pushButton_cancelar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_excluir_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

private:
    Ui::fm_produtos *ui;
};

#endif // FM_PRODUTOS_H
