#ifndef PRODUTOCONTROLLER_H
#define PRODUTOCONTROLLER_H

#include "Produto.h"
#include "Conexao.h"
#include <QtSql>
#include <Cesta.h>

class ProdutoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    ProdutoController() {}

    bool insere(Produto produto);
    QVector<Produto> buscaTodos();
    QVector<Produto> buscaPorId(Produto produto);
    QVector<Produto> buscaPorNome(Produto produto);
    QVector<Produto> buscaPorDescricao(Produto produto);
    QVector<Produto> buscaPorNomeDescricao(Produto produto);
    bool verificaDuplicidade(Produto produto);
    bool altera(Produto produto);
    bool remove(Produto produto);
};

inline bool ProdutoController::insere(Produto produto)
{
    sql = "INSERT INTO tb_produtos ";
    sql += "( id, nome, descricao, custo, valor ) ";
    sql += "VALUES ";
    sql += "( :id, :nome, :descricao, :custo, :valor )";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", produto.getId());
        query.bindValue(":nome", produto.getNome());
        query.bindValue(":descricao", produto.getDescricao());
        query.bindValue(":custo", QString::number(produto.getCusto()));
        query.bindValue(":valor", QString::number(produto.getValor()));

        if(query.exec())
            retorno = true;
        else
            qDebug() << "ProdutoController::insere() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline QVector<Produto> ProdutoController::buscaTodos()
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "descricao, ";
    sql += "custo, ";
    sql += "valor ";
    sql += "FROM ";
    sql += "tb_produtos";

    if (!conn.isOpen())
        conn.open();

    Produto produto;
    QVector<Produto> listaProdutos;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);

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
            qDebug() << "ProdutoController::buscaTodos(): " << contador << " registros";
        } else
            qDebug() << "ProdutoController::buscaTodos() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline QVector<Produto> ProdutoController::buscaPorId(Produto produto)
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "descricao, ";
    sql += "custo, ";
    sql += "valor ";
    sql += "FROM ";
    sql += "tb_produtos ";
    sql += "WHERE ";
    sql += "id LIKE :id ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<Produto> listaProdutos;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", "%" + produto.getId() + "%");

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
            qDebug() << "ProdutoController::buscaporId(): " << contador << " registros";
        } else
            qDebug() << "ProdutoController::buscaporId() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline QVector<Produto> ProdutoController::buscaPorNome(Produto produto)
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "descricao, ";
    sql += "custo, ";
    sql += "valor ";
    sql += "FROM ";
    sql += "tb_produtos ";
    sql += "WHERE ";
    sql += "nome LIKE :nome ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<Produto> listaProdutos;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome", "%" + produto.getNome() + "%");

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
            qDebug() << "ProdutoController::buscaPorNome(): " << contador << " registros";
        } else
            qDebug() << "ProdutoController::buscaPorNome() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline QVector<Produto> ProdutoController::buscaPorDescricao(Produto produto)
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "descricao, ";
    sql += "custo, ";
    sql += "valor ";
    sql += "FROM ";
    sql += "tb_produtos ";
    sql += "WHERE ";
    sql += "descricao LIKE :descricao ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<Produto> listaProdutos;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":descricao", "%" + produto.getDescricao() + "%");

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
            qDebug() << "ProdutoController::buscaPorDescricao(): " << contador << " registros";
        } else
            qDebug() << "ProdutoController::buscaPorDescricao() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline QVector<Produto> ProdutoController::buscaPorNomeDescricao(Produto produto)
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "descricao, ";
    sql += "custo, ";
    sql += "valor ";
    sql += "FROM ";
    sql += "tb_produtos ";
    sql += "WHERE ";
    sql += "nome LIKE :nome OR ";
    sql += "descricao LIKE :descricao ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<Produto> listaProdutos;
    int contador = 0;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome", "%" + produto.getNome() + "%");
        query.bindValue(":descricao", "%" + produto.getDescricao() + "%");

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
            qDebug() << "ProdutoController::buscaPorNomeDescricao(): " << contador << " registros";
        } else
            qDebug() << "ProdutoController::buscaPorNomeDescricao() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline bool ProdutoController::verificaDuplicidade(Produto produto)
{
    sql = "SELECT ";
    sql += "id ";
    sql += "FROM ";
    sql += "tb_produtos ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", produto.getId());

        if (query.exec()){
            if (query.next()){
                retorno = true;
                qDebug() << "ProdutoController::verificaDuplicidade(): registro duplicado";
            }
        } else
            qDebug() << "ProdutoController::verificaDuplicidade() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ProdutoController::altera(Produto produto)
{
    sql = "UPDATE tb_produtos SET ";
    sql += "nome = :nome, ";
    sql += "descricao = :descricao, ";
    sql += "custo = :custo, ";
    sql += "valor = :valor ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome", produto.getNome());
        query.bindValue(":descricao", produto.getDescricao());
        query.bindValue(":custo", QString::number(produto.getCusto()));
        query.bindValue(":valor", QString::number(produto.getValor()));
        query.bindValue(":id", produto.getId());

        if(query.exec())
            retorno = true;
        else
            qDebug() << "ProdutoController::altera() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ProdutoController::remove(Produto produto)
{
    sql = "DELETE FROM tb_produtos ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", produto.getId());

        if(query.exec())
            retorno = true;
        else
            qDebug() << "ProdutoController::remove() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // PRODUTOCONTROLLER_H
