#ifndef FM_COLABORADORES_H
#define FM_COLABORADORES_H

#include <QDialog>
#include "Colaborador.h"

namespace Ui {
class fm_colaboradores;
}

class fm_colaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_colaboradores(QWidget *parent = nullptr);
    ~fm_colaboradores();

    // VARIAVEIS DE FORMULÁRIO
    QStringList cabecalho;

    // MEUS MÉTODOS
    void inicializa_fm_colaboradores();
    void limpaFormularioAlteracao();
    void limpaFormularioPesquisa();
    void preencheComboBoxGrupo();
    void atualizaTableWidget();
    void populaTableWidget(QVector<Colaborador> listaColaboradores);

private slots:
    void on_pushButton_fechar_clicked();

    void on_tableWidget_colaboradores_itemSelectionChanged();

    void on_pushButton_limpar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_pushButton_excluir_clicked();

private:
    Ui::fm_colaboradores *ui;
};

#endif // FM_COLABORADORES_H
