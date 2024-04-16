#include "fm_edita_cesta.h"
#include "ui_fm_edita_cesta.h"
#include "CestaController.h"
#include "global_functions.h"
#include "ItemCestaController.h"
#include <QMessageBox>

fm_edita_cesta::fm_edita_cesta(QWidget *parent, int id_cesta) : QDialog(parent), ui(new Ui::fm_edita_cesta)
{
    ui->setupUi(this);
    fm_edita_cesta::id = id_cesta;

    fm_edita_cesta::inicializa_fm_edita_cesta();
}

fm_edita_cesta::~fm_edita_cesta()
{
    delete ui;
}

/* ***** ***** *****
 * MY METHODS
 * ***** ***** *****/

void fm_edita_cesta::inicializa_fm_edita_cesta()
{
    CestaController cesta_controller;
    fm_edita_cesta::cesta.setId(fm_edita_cesta::id);
    fm_edita_cesta::cesta = cesta_controller.buscaPorId(fm_edita_cesta::cesta);

    ui->lineEdit_id->setText(QString::number(fm_edita_cesta::cesta.getId()));
    ui->lineEdit_nome->setText(fm_edita_cesta::cesta.getNome());
    ui->lineEdit_descricao->setText(fm_edita_cesta::cesta.getDescricao());
    ui->lineEdit_custo->setText(global_functions::formatDoubleToString(fm_edita_cesta::cesta.getCusto()));
    ui->lineEdit_valor->setText(global_functions::formatDoubleToString(fm_edita_cesta::cesta.getValor()));

    fm_edita_cesta::atualizaTableWidgetProdutos();
    fm_edita_cesta::atualizaTableWidgetItensCesta();
}

void fm_edita_cesta::atualizaTableWidgetProdutos()
{
    QVector<Produto> listaProdutos;
    ItemCestaController item_cesta_controller;
    listaProdutos = item_cesta_controller.buscaProdutosQueNaoTemNaCesta(fm_edita_cesta::cesta);

    fm_edita_cesta::populaTableWidgetProdutos(listaProdutos);
}

void fm_edita_cesta::populaTableWidgetProdutos(QVector<Produto> listaProdutos)
{
    Produto produto;
    fm_edita_cesta::cabecalho = {"Nome", "Valor", "id", "Descrição", "Custo"};
    global_functions::formatTableWidget(ui->tableWidget_produtos, cabecalho);

    for (int i = 0; i < listaProdutos.size(); ++i) {
        produto = listaProdutos[i];
        ui->tableWidget_produtos->insertRow(i);
        ui->tableWidget_produtos->setItem(i, 0, new QTableWidgetItem(produto.getNome()));
        ui->tableWidget_produtos->setItem(i, 1, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getValor())));
        ui->tableWidget_produtos->setItem(i, 2, new QTableWidgetItem(produto.getId()));
        ui->tableWidget_produtos->setItem(i, 3, new QTableWidgetItem(produto.getDescricao()));
        ui->tableWidget_produtos->setItem(i, 4, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getCusto())));
        ui->tableWidget_produtos->setRowHeight(i, 20);
    }
}

void fm_edita_cesta::atualizaTableWidgetItensCesta()
{
    QVector<ItemCesta> listaItensCesta;
    ItemCestaController item_cesta_controller;
    listaItensCesta = item_cesta_controller.buscaPorIdCesta(fm_edita_cesta::cesta);

    fm_edita_cesta::populaTableWidgetItensCesta(listaItensCesta);
}

void fm_edita_cesta::populaTableWidgetItensCesta(QVector<ItemCesta> listaItensCesta)
{
    double subtotal;
    ItemCesta item_cesta;
    fm_edita_cesta::cabecalho = {"qtd", "Nome", "Venda", "Sub-Total", "id_produto", "Descricao", "Custo", "id"};
    global_functions::formatTableWidget(ui->tableWidget_itens_cesta, cabecalho);
     ui->tableWidget_itens_cesta->setColumnHidden(7, true);

    for (int i = 0; i < listaItensCesta.size(); ++i) {
        item_cesta = listaItensCesta[i];
        ui->tableWidget_itens_cesta->insertRow(i);
        ui->tableWidget_itens_cesta->setItem(i, 0, new QTableWidgetItem(QString::number(item_cesta.getQuantidade())));
        ui->tableWidget_itens_cesta->setItem(i, 1, new QTableWidgetItem(item_cesta.getProduto().getNome()));
        ui->tableWidget_itens_cesta->setItem(i, 2, new QTableWidgetItem(global_functions::formatDoubleToString(item_cesta.getProduto().getValor())));

        subtotal = item_cesta.getQuantidade() * item_cesta.getProduto().getValor();

        ui->tableWidget_itens_cesta->setItem(i, 3, new QTableWidgetItem(global_functions::formatDoubleToString(subtotal)));
        ui->tableWidget_itens_cesta->setItem(i, 4, new QTableWidgetItem(item_cesta.getProduto().getId()));
        ui->tableWidget_itens_cesta->setItem(i, 5, new QTableWidgetItem(item_cesta.getProduto().getDescricao()));
        ui->tableWidget_itens_cesta->setItem(i, 6, new QTableWidgetItem(global_functions::formatDoubleToString(item_cesta.getProduto().getCusto())));
        ui->tableWidget_itens_cesta->setItem(i, 7, new QTableWidgetItem(QString::number(item_cesta.getId())));
        ui->tableWidget_itens_cesta->setRowHeight(i, 20);
    }
    ui->label_total->setText("R$ " + global_functions::formatDoubleToString(global_functions::calculaTotalTableWidget(ui->tableWidget_itens_cesta, 3)));
}

void fm_edita_cesta::removeProduto()
{
    int row, quantidade;
    QString id, nome, descricao;
    double custo, valor;
    Produto produto;
    ItemCesta item_cesta;

    row = ui->tableWidget_produtos->currentRow();
    quantidade = ui->spinBox_quantidade->value();

    nome = ui->tableWidget_produtos->item(row, 0)->text();
    valor = ui->tableWidget_produtos->item(row, 1)->text().toDouble();
    id = ui->tableWidget_produtos->item(row, 2)->text();
    descricao = ui->tableWidget_produtos->item(row, 3)->text();
    custo = ui->tableWidget_produtos->item(row, 4)->text().toDouble();

    produto.setId(id);
    produto.setNome(nome);
    produto.setDescricao(descricao);
    produto.setCusto(custo);
    produto.setValor(valor);

    item_cesta.setQuantidade(quantidade);
    item_cesta.setCesta(fm_edita_cesta::cesta);
    item_cesta.setProduto(produto);

    fm_edita_cesta::adicionaItemCesta(item_cesta);

    ui->tableWidget_produtos->removeRow(row);
}

void fm_edita_cesta::adicionaItemCesta(ItemCesta item_cesta)
{
    int row;
    double subtotal;
    ItemCestaController item_cesta_controller;

    row = ui->tableWidget_itens_cesta->rowCount();

    ui->tableWidget_itens_cesta->insertRow(row);
    ui->tableWidget_itens_cesta->setItem(row, 0, new QTableWidgetItem(QString::number(item_cesta.getQuantidade())));
    ui->tableWidget_itens_cesta->setItem(row, 1, new QTableWidgetItem(item_cesta.getProduto().getNome()));
    ui->tableWidget_itens_cesta->setItem(row, 2, new QTableWidgetItem(global_functions::formatDoubleToString(item_cesta.getProduto().getValor())));

    subtotal = item_cesta.getQuantidade() * item_cesta.getProduto().getValor();

    ui->tableWidget_itens_cesta->setItem(row, 3, new QTableWidgetItem(global_functions::formatDoubleToString(subtotal)));
    ui->tableWidget_itens_cesta->setItem(row, 4, new QTableWidgetItem(item_cesta.getProduto().getId()));
    ui->tableWidget_itens_cesta->setItem(row, 5, new QTableWidgetItem(item_cesta.getProduto().getDescricao()));
    ui->tableWidget_itens_cesta->setItem(row, 6, new QTableWidgetItem(global_functions::formatDoubleToString(item_cesta.getProduto().getCusto())));

    item_cesta = item_cesta_controller.insere(item_cesta);

    ui->tableWidget_itens_cesta->setItem(row, 7, new QTableWidgetItem(QString::number(item_cesta.getId())));

    ui->tableWidget_itens_cesta->setRowHeight(row, 20);

    ui->spinBox_quantidade->setValue(1);

    ui->label_total->setText("R$ " + global_functions::formatDoubleToString(global_functions::calculaTotalTableWidget(ui->tableWidget_itens_cesta, 3)));
}

void fm_edita_cesta::removeItemCesta()
{
    int row, id_item_cesta;
    QString id, nome, descricao;
    double custo, valor;
    Produto produto;
    ItemCesta item_cesta;
    ItemCestaController item_cesta_controller;

    row = ui->tableWidget_itens_cesta->currentRow();
    id_item_cesta = ui->tableWidget_itens_cesta->item(row, 7)->text().toInt();

    id = ui->tableWidget_itens_cesta->item(row, 4)->text();
    nome = ui->tableWidget_itens_cesta->item(row, 1)->text();
    descricao = ui->tableWidget_itens_cesta->item(row, 5)->text();
    custo = ui->tableWidget_itens_cesta->item(row, 6)->text().toDouble();
    valor = ui->tableWidget_itens_cesta->item(row, 2)->text().toDouble();

    produto.setId(id);
    produto.setNome(nome);
    produto.setDescricao(descricao);
    produto.setCusto(custo);
    produto.setValor(valor);

    item_cesta.setId(id_item_cesta);
    item_cesta_controller.remove(item_cesta);

    ui->tableWidget_itens_cesta->removeRow(row);

    ui->label_total->setText("R$ " + global_functions::formatDoubleToString(global_functions::calculaTotalTableWidget(ui->tableWidget_itens_cesta, 3)));

    fm_edita_cesta::adicionaProduto(produto);
}

void fm_edita_cesta::adicionaProduto(Produto produto)
{
    int row;

    row = ui->tableWidget_produtos->rowCount();

    ui->tableWidget_produtos->insertRow(row);
    ui->tableWidget_produtos->setItem(row, 0, new QTableWidgetItem(produto.getNome()));
    ui->tableWidget_produtos->setItem(row, 1, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getValor())));
    ui->tableWidget_produtos->setItem(row, 2, new QTableWidgetItem(produto.getId()));
    ui->tableWidget_produtos->setItem(row, 3, new QTableWidgetItem(produto.getDescricao()));
    ui->tableWidget_produtos->setItem(row, 4, new QTableWidgetItem(global_functions::formatDoubleToString(produto.getCusto())));
    ui->tableWidget_produtos->setRowHeight(row, 20);
}

/* ***** ***** *****
 * SLOTS
 * ***** ***** *****/

void fm_edita_cesta::on_pushButton_fechar_clicked()
{
    close();
}

void fm_edita_cesta::on_pushButton_adicionar_clicked()
{
    int row;
    row = ui->tableWidget_produtos->currentRow();

    if (row >= 0)
        fm_edita_cesta::removeProduto();
    else
        QMessageBox::warning(this, "", "selecione um produto.");
}

void fm_edita_cesta::on_pushButton_retirar_clicked()
{
    int row;
    row = ui->tableWidget_itens_cesta->currentRow();

    if (row >= 0)
        fm_edita_cesta::removeItemCesta();
    else
        QMessageBox::warning(this, "", "Selecione um item.");
}

void fm_edita_cesta::on_pushButton_salvar_clicked()
{
    QString nome, descricao, mensagem;
    double custo, valor;
    CestaController cesta_controller;

    nome = ui->lineEdit_nome->text().trimmed();
    descricao = ui->lineEdit_descricao->text().trimmed();
    custo = ui->lineEdit_custo->text().replace(",", ".").toDouble();
    valor = ui->lineEdit_valor->text().replace(",", ".").toDouble();

    if (!(global_functions::validatesSizeString(nome, 3)) || !(global_functions::validatesSizeString(descricao, 3)) || !(custo > 0) || !(valor > custo) ) {
        mensagem = "Nome e descrição devem ter no mínimo 3 caracteres.\n";
        mensagem += "Custo deve ser maior que zero.\n";
        mensagem += "Valor deve ser maior que o custo.";
        QMessageBox::warning(this, "", mensagem);
        return;
    }

    fm_edita_cesta::cesta.setNome(nome);
    fm_edita_cesta::cesta.setDescricao(descricao);
    fm_edita_cesta::cesta.setCusto(custo);
    fm_edita_cesta::cesta.setValor(valor);

    if (cesta_controller.altera(fm_edita_cesta::cesta)) {
        QMessageBox::warning(this, "", "Cesta alterada com sucesso;");
        close();
    } else
        QMessageBox::warning(this, "", "Erro ao alterar dados da cesta;");
}

void fm_edita_cesta::on_pushButton_excluir_clicked()
{
    CestaController cesta_controller;
    ItemCestaController item_cesta_controller;
    QMessageBox::StandardButton resposta;

    resposta = QMessageBox::question(this, "", "Tem certeza?", QMessageBox::Yes | QMessageBox::No);

    if(resposta == QMessageBox::Yes) {
        cesta_controller.remove(fm_edita_cesta::cesta);
        item_cesta_controller.removeItensPorCesta(fm_edita_cesta::cesta);
        QMessageBox::information(this, "", "Cesta excluida com sucesso!");
        close();
    }
}

