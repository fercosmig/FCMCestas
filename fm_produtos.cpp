#include "fm_produtos.h"
#include "ui_fm_produtos.h"
#include "ProdutoController.h"
#include "global_functions.h"
#include <QMessageBox>

fm_produtos::fm_produtos(QWidget *parent) : QDialog(parent), ui(new Ui::fm_produtos)
{
    ui->setupUi(this);

    fm_produtos::inicializa_fm_produtos();
}

fm_produtos::~fm_produtos()
{
    delete ui;
}

/* *** *** *** ***
 * MEUS MÉTODOS
 * *** *** *** ***/

void fm_produtos::inicializa_fm_produtos()
{
    fm_produtos::cabecalho = {"ID", "Nome", "Descrição", "R$ Custo", "R$ Venda", "Lucro"};
    fm_produtos::atualizaTableWidget();

    ui->label_selected_row->setText("-1");
    ui->label_selected_row->setVisible(false);
}

void fm_produtos::atualizaTableWidget()
{
    ProdutoController produto_controller;
    QVector<Produto> listaProdutos;
    listaProdutos = produto_controller.buscaTodos();
    fm_produtos::populaTableWidget(listaProdutos);
}

void fm_produtos::populaTableWidget(QVector<Produto> listaProdutos)
{
    Produto produto;
    QString lucro;

    global_functions::formatTableWidget(ui->tableWidget_produtos, fm_produtos::cabecalho);

    for (int i = 0; i < listaProdutos.size(); i++){
        produto = listaProdutos[i];
        ui->tableWidget_produtos->insertRow(i);
        ui->tableWidget_produtos->setItem(i, 0, new QTableWidgetItem(produto.getId()));
        ui->tableWidget_produtos->setItem(i, 1, new QTableWidgetItem(produto.getNome()));
        ui->tableWidget_produtos->setItem(i, 2, new QTableWidgetItem(produto.getDescricao()));
        ui->tableWidget_produtos->setItem(i, 3, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getCusto())));
        ui->tableWidget_produtos->setItem(i, 4, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getValor())));

        lucro = global_functions::calculaPorcentagemLucroToString(produto.getCusto(), produto.getValor());

        ui->tableWidget_produtos->setItem(i, 5, new QTableWidgetItem(lucro));
        ui->tableWidget_produtos->setRowHeight(i, 20);
    }
}

void fm_produtos::limpaFormularioAlteracao()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_descricao->clear();
    ui->lineEdit_custo->clear();
    ui->lineEdit_valor->clear();
    ui->lineEdit_nome->setFocus();
    ui->label_selected_row->setText("-1");
    ui->pushButton_excluir->setEnabled(false);
}

void fm_produtos::limpaFormularioPesquisa()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_pesquisar->setFocus();
}

/* *** *** *** ***
 * SLOTS
 * *** *** *** ***/

void fm_produtos::on_pushButton_fechar_clicked()
{
    close();
}

void fm_produtos::on_tableWidget_produtos_itemSelectionChanged()
{
    int row;
    QString id, nome, descricao, custo, valor;

    row = ui->tableWidget_produtos->currentRow();

    id = ui->tableWidget_produtos->item(row, 0)->text();
    nome = ui->tableWidget_produtos->item(row, 1)->text();
    descricao = ui->tableWidget_produtos->item(row, 2)->text();
    custo = ui->tableWidget_produtos->item(row, 3)->text();
    valor = ui->tableWidget_produtos->item(row, 4)->text();

    ui->lineEdit_id->setText(id);
    ui->lineEdit_nome->setText(nome);
    ui->lineEdit_descricao->setText(descricao);
    ui->lineEdit_custo->setText(custo);
    ui->lineEdit_valor->setText(valor);

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setEnabled(false);
    ui->pushButton_excluir->setEnabled(true);
}

void fm_produtos::on_pushButton_cancelar_clicked()
{
    fm_produtos::limpaFormularioAlteracao();
    ui->lineEdit_id->setEnabled(true);
}

void fm_produtos::on_pushButton_salvar_clicked()
{
    int row, rowcount;
    QString id, nome, descricao, mensagem, lucro;
    double custo, valor;
    Produto produto;
    ProdutoController produto_controller;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text();
    nome = ui->lineEdit_nome->text();
    descricao = ui->lineEdit_descricao->text();
    custo = ui->lineEdit_custo->text().replace(",", ".").toDouble();
    valor = ui->lineEdit_valor->text().replace(",", ".").toDouble();

    if (!(global_functions::validatesSizeString(nome, 3)) || !(global_functions::validatesSizeString(descricao, 3)) || !(custo > 0) || !(valor > custo)) {
        mensagem = "Nome e descrição devem ter no mínimo 3 caracteres.\n";
        mensagem += "Custo deve ser maior que 0.\n";
        mensagem += "Valor deve ser maior que o custo.";
        QMessageBox::warning(this, "", mensagem);
        return;
    }

    produto.setId(id);
    produto.setNome(nome);
    produto.setDescricao(descricao);
    produto.setCusto(custo);
    produto.setValor(valor);

    if(row == -1) { // INCLUSÃO DE PRODUTOS

        if (produto_controller.verificaDuplicidade(produto)) {
            QMessageBox::warning(this, "", "Produto já existe no banco de dados");
            fm_produtos::limpaFormularioAlteracao();
            return;
        }

        if(produto_controller.insere(produto)) {
            QMessageBox::information(this, "", "Produto inserido com sucesso!");

            rowcount = ui->tableWidget_produtos->rowCount();
            ui->tableWidget_produtos->insertRow(rowcount);
            ui->tableWidget_produtos->setItem(rowcount, 0, new QTableWidgetItem(produto.getId()));
            ui->tableWidget_produtos->setItem(rowcount, 1, new QTableWidgetItem(produto.getNome()));
            ui->tableWidget_produtos->setItem(rowcount, 2, new QTableWidgetItem(produto.getDescricao()));
            ui->tableWidget_produtos->setItem(rowcount, 3, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getCusto())));
            ui->tableWidget_produtos->setItem(rowcount, 4, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getValor())));

            lucro = global_functions::calculaPorcentagemLucroToString(produto.getCusto(), produto.getValor());

            ui->tableWidget_produtos->setItem(rowcount, 5, new QTableWidgetItem(lucro));
            ui->tableWidget_produtos->setRowHeight(rowcount, 20);

            fm_produtos::limpaFormularioAlteracao();
        } else
            QMessageBox::warning(this, "", "Erro ao tentar incluir o produto.");

    } else{ // ALTERAÇÃO DE PRODUTOS

        if(produto_controller.altera(produto)) {
            QMessageBox::information(this, "", "Produto alterado com sucesso!");
            ui->tableWidget_produtos->item(row, 1)->setText(produto.getNome());
            ui->tableWidget_produtos->item(row, 2)->setText(produto.getDescricao());
            ui->tableWidget_produtos->item(row, 3)->setText(global_functions::formatDoubleToString(produto.getCusto()));
            ui->tableWidget_produtos->item(row, 4)->setText(global_functions::formatDoubleToString(produto.getValor()));

            lucro = global_functions::calculaPorcentagemLucroToString(produto.getCusto(), produto.getValor());

            ui->tableWidget_produtos->item(row, 5)->setText(lucro);

            fm_produtos::limpaFormularioAlteracao();
            ui->lineEdit_id->setEnabled(true);
        } else
            QMessageBox::warning(this, "", "Erro ao tentar alterar o produto.");
    }
}

void fm_produtos::on_pushButton_excluir_clicked()
{
    int row;
    QString id;
    Produto produto;
    ProdutoController produto_controller;

    row = ui->label_selected_row->text().toInt();
    id = ui->tableWidget_produtos->item(row, 0)->text();

    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "", "Tem certeza que deseja excluir?", QMessageBox::Yes | QMessageBox::No);
    if (resposta == QMessageBox::Yes) {
        produto.setId(id);
        if (produto_controller.remove(produto)) {
            QMessageBox::information(this, "", "Produto removido com sucesso!");
            ui->tableWidget_produtos->removeRow(row);
        } else
            QMessageBox::warning(this, "", "Erro ao tentar remover o produto.");
    }
}

void fm_produtos::on_pushButton_pesquisar_clicked()
{
    QString texto_pesquisa;
    QVector<Produto> listaProdutos;

    texto_pesquisa = ui->lineEdit_pesquisar->text().trimmed();
    if (global_functions::validatesSizeString(texto_pesquisa, 3)){

        Produto produto;
        ProdutoController produto_controller;

        if (ui->radioButton_id->isChecked()) {
            produto.setId(texto_pesquisa);
            listaProdutos = produto_controller.buscaPorId(produto);
        }
        if (ui->radioButton_nome->isChecked()) {
            produto.setNome(texto_pesquisa);
            listaProdutos = produto_controller.buscaPorNome(produto);
        }
        if (ui->radioButton_descricao->isChecked()) {
            produto.setDescricao(texto_pesquisa);
            listaProdutos = produto_controller.buscaPorDescricao(produto);
        }
        if (ui->radioButton_nome_descricao->isChecked()) {
            produto.setNome(texto_pesquisa);
            produto.setDescricao(texto_pesquisa);
            listaProdutos = produto_controller.buscaPorNomeDescricao(produto);
        }
        fm_produtos::populaTableWidget(listaProdutos);
        fm_produtos::limpaFormularioPesquisa();

    } else
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres para pesquisar.");
}

void fm_produtos::on_pushButton_mostrar_todos_clicked()
{
    fm_produtos::atualizaTableWidget();
}

