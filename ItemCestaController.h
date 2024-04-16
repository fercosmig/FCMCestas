#ifndef ITEMCESTACONTROLLER_H
#define ITEMCESTACONTROLLER_H

#include "ItemCesta.h"
#include "Conexao.h"
#include <QtSql>

class ItemCestaController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    ItemCestaController() {}

    ItemCesta insere(ItemCesta item_cesta);
    QVector<Produto> buscaProdutosQueNaoTemNaCesta(Cesta cesta);
    QVector<ItemCesta> buscaPorIdCesta(Cesta cesta);
    void removeItensPorCesta(Cesta cesta);
    void remove(ItemCesta item_cesta);
};

inline ItemCesta ItemCestaController::insere(ItemCesta item_cesta)
{
    sql = "INSERT INTO tb_itens_cestas ";
    sql += "( quantidade, id_cesta, id_produto ) ";
    sql += "VALUES ";
    sql += "( :quantidade, :id_cesta, :id_produto )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":quantidade", QString::number(item_cesta.getQuantidade()));
        query.bindValue(":id_cesta", QString::number(item_cesta.getCesta().getId()));
        query.bindValue(":id_produto", item_cesta.getProduto().getId());

        if (query.exec()){
            sql = "SELECT id FROM tb_itens_cestas ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec()){
                if (query.next())
                    item_cesta.setId(query.record().value("id").toInt());
            } else
                qDebug() << "ItemCestaController::insere() query.exec retorno: " << query.lastError().text();
        } else
            qDebug() << "ItemCestaController::insere() query.exec: " << query.lastError().text();
    }
    query.exec("COMMIT");

    conn.close();
    return item_cesta;
}

inline QVector<Produto> ItemCestaController::buscaProdutosQueNaoTemNaCesta(Cesta cesta)
{
    sql = "SELECT ";
    sql += "tb_produtos.id, ";
    sql += "tb_produtos.nome, ";
    sql += "tb_produtos.descricao, ";
    sql += "tb_produtos.custo, ";
    sql += "tb_produtos.valor ";
    sql += "FROM ";
    sql += "tb_produtos ";
    sql += "WHERE ";
    sql += "tb_produtos.id ";
    sql += "NOT IN ";
    sql += "( SELECT ";
    sql += "tb_itens_cestas.id_produto ";
    sql += "FROM ";
    sql += "tb_itens_cestas ";
    sql += "WHERE ";
    sql += "tb_itens_cestas.id_cesta = :id_cesta ) ";
    sql += "ORDER BY ";
    sql += "tb_produtos.nome ";
    sql += "ASC";

    if (!conn.isOpen())
        conn.open();

    Produto produto;
    QVector<Produto> listaProdutos;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id_cesta", cesta.getId());

        if (query.exec()){
            if (query.next()){
                do {
                    produto.setId(query.record().value("id").toString());
                    produto.setNome(query.record().value("nome").toString());
                    produto.setDescricao(query.record().value("descricao").toString());
                    produto.setCusto(query.record().value("custo").toDouble());
                    produto.setValor(query.record().value("valor").toDouble());

                    listaProdutos.push_back(produto);
                    contador++;
                } while(query.next());
            }
            qDebug() << "ItemCestaController::buscaProdutosQueNaoTemNaCesta(): " << contador << " registros";
        } else
            qDebug() << "ItemCestaController::buscaProdutosQueNaoTemNaCesta() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline QVector<ItemCesta> ItemCestaController::buscaPorIdCesta(Cesta cesta)
{
    sql = "SELECT ";
    sql += "tb_itens_cestas.id, ";
    sql += "tb_itens_cestas.quantidade, ";
    sql += "tb_cestas.id as id_cesta, ";
    sql += "tb_cestas.nome as nome_cesta, ";
    sql += "tb_cestas.descricao as descricao_cesta, ";
    sql += "tb_cestas.custo as custo_cesta, ";
    sql += "tb_cestas.valor as valor_cesta, ";
    sql += "tb_produtos.id as id_produto, ";
    sql += "tb_produtos.nome as nome_produto, ";
    sql += "tb_produtos.descricao as descricao_produto, ";
    sql += "tb_produtos.custo as custo_produto, ";
    sql += "tb_produtos.valor as valor_produto ";
    sql += "FROM ";
    sql += "tb_itens_cestas ";
    sql += "INNER JOIN ";
    sql += "tb_cestas ";
    sql += "ON ";
    sql += "tb_itens_cestas.id_cesta = tb_cestas.id ";
    sql += "INNER JOIN ";
    sql += "tb_produtos ";
    sql += "ON ";
    sql += "tb_itens_cestas.id_produto = tb_produtos.id ";
    sql += "WHERE ";
    sql += "tb_cestas.id = :id_cesta ";
    sql += "ORDER BY ";
    sql += "tb_produtos.nome ";
    sql += "ASC";

    if (!conn.isOpen())
        conn.open();

    Produto produto;
    QVector<ItemCesta> listaItensCesta;
    ItemCesta item_cesta;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id_cesta", cesta.getId());

        if (query.exec()){
            if (query.next()){
                do {
                    produto.setId(query.record().value("id_produto").toString());
                    produto.setNome(query.record().value("nome_produto").toString());
                    produto.setDescricao(query.record().value("descricao_produto").toString());
                    produto.setCusto(query.record().value("custo_produto").toDouble());
                    produto.setValor(query.record().value("valor_produto").toDouble());

                    cesta.setId(query.record().value("id_cesta").toInt());
                    cesta.setNome(query.record().value("nome_cesta").toString());
                    cesta.setDescricao(query.record().value("descricao_cesta").toString());
                    cesta.setCusto(query.record().value("custo_cesta").toDouble());
                    cesta.setValor(query.record().value("valor_cesta").toDouble());

                    item_cesta.setId(query.record().value("id").toInt());
                    item_cesta.setQuantidade(query.record().value("quantidade").toInt());
                    item_cesta.setCesta(cesta);
                    item_cesta.setProduto(produto);

                    listaItensCesta.push_back(item_cesta);
                    contador++;
                } while(query.next());
            }
            qDebug() << "ItemCestaController::buscaPorIdCesta(): " << contador << " registros";
        } else
            qDebug() << "ItemCestaController::buscaPorIdCesta() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaItensCesta;
}

inline void ItemCestaController::removeItensPorCesta(Cesta cesta)
{
    sql = "DELETE FROM tb_itens_cestas WHERE id_cesta = :id_cesta";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id_cesta", QString::number(cesta.getId()));

        if (!query.exec())
            qDebug() << "ItemCestaController::removeItensPorCesta() query.exec: " << query.lastError().text();
    }
    conn.close();
}

inline void ItemCestaController::remove(ItemCesta item_cesta)
{
    sql = "DELETE FROM tb_itens_cestas WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", QString::number(item_cesta.getId()));

        if (!query.exec())
            qDebug() << "ItemCestaController::remove() query.exec: " << query.lastError().text();
    }
    conn.close();
}

#endif // ITEMCESTACONTROLLER_H
