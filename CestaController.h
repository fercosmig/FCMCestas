#ifndef CESTACONTROLLER_H
#define CESTACONTROLLER_H

#include "Cesta.h"
#include "Conexao.h"
#include <QtSql>

class CestaController
{
private:

    // Variavel para armazernar as instruções SQL.
    QString sql;

    // Objeto que manipula instruções SQL.
    QSqlQuery query;

    // Objeto que cria conexão com o banco de dados.
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    CestaController() {}

    // METHODS CRUD
    Cesta insere(Cesta cesta);
    QVector<Cesta> buscaTodos();
    QVector<Cesta> buscaPorNomeDescricao(Cesta cesta);
    Cesta buscaPorId(Cesta cesta);
    bool altera(Cesta cesta);
    bool remove(Cesta cesta);
};

inline Cesta CestaController::insere(Cesta cesta)
{
    sql = "INSERT INTO tb_cestas ";
    sql += "( nome, descricao, custo, valor ) ";
    sql += "VALUES ";
    sql += "( :nome, :descricao, :custo, :valor )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", cesta.getNome());
        query.bindValue(":descricao", cesta.getDescricao());
        query.bindValue(":custo", cesta.getCusto());
        query.bindValue(":valor", cesta.getValor());

        if (query.exec()){
            sql = "SELECT id FROM tb_cestas ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec()){
                if (query.next())
                    cesta.setId(query.record().value("id").toInt());
            } else
                qDebug() << "CestaController::insere() query.exec retorno: " << query.lastError().text();
        } else
            qDebug() << "CestaController::insere() query.exec: " << query.lastError().text();

        query.exec("COMMIT");
    }
    conn.close();
    return cesta;
}

inline QVector<Cesta> CestaController::buscaTodos()
{
    sql = "SELECT id, nome, descricao, custo, valor ";
    sql += "FROM tb_cestas";

    if (!conn.isOpen())
        conn.open();

    int contador = 0;
    Cesta cesta;
    QVector<Cesta> listaCestas;

    if (conn.isOpen()) {
        query.prepare(sql);

        if (query.exec()){
            if (query.next()){
                do {
                    cesta.setId(query.record().value("id").toInt());
                    cesta.setNome(query.record().value("nome").toString());
                    cesta.setDescricao(query.record().value("descricao").toString());
                    cesta.setCusto(query.record().value("custo").toDouble());
                    cesta.setValor(query.record().value("valor").toDouble());

                    listaCestas.push_back(cesta);
                    contador++;
                } while (query.next());
                qDebug() << "CestaController::buscaTodos() query.next: " << contador << " registros";
            } else
                qDebug() << "CestaController::buscaTodos() query.next: 0 registros";

        } else
            qDebug() << "CestaController::buscaTodos() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaCestas;
}

inline QVector<Cesta> CestaController::buscaPorNomeDescricao(Cesta cesta)
{
    sql = "SELECT id, nome, descricao, custo, valor ";
    sql += "FROM tb_cestas ";
    sql += "WHERE ";
    sql += "nome LIKE :nome OR ";
    sql += "descricao LIKE :descricao";

    if (!conn.isOpen())
        conn.open();

    int contador = 0;
    QVector<Cesta> listaCestas;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":nome", "%" + cesta.getNome() + "%");
        query.bindValue(":descricao", "%" + cesta.getDescricao() + "%");

        if (query.exec()){
            if (query.next()){
                do {
                    cesta.setId(query.record().value("id").toInt());
                    cesta.setNome(query.record().value("nome").toString());
                    cesta.setDescricao(query.record().value("descricao").toString());
                    cesta.setCusto(query.record().value("custo").toDouble());
                    cesta.setValor(query.record().value("valor").toDouble());

                    listaCestas.push_back(cesta);
                    contador++;
                } while (query.next());
                qDebug() << "CestaController::buscaPorNome() query.next: " << contador << " registros";
            } else
                qDebug() << "CestaController::buscaPorNome() query.next: 0 registros";

        } else
            qDebug() << "CestaController::buscaPorNome() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaCestas;
}

inline Cesta CestaController::buscaPorId(Cesta cesta)
{
    sql = "SELECT id, nome, descricao, custo, valor ";
    sql += "FROM tb_cestas ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", cesta.getId());

        if (query.exec()){
            if (query.next()){
                cesta.setId(query.record().value("id").toInt());
                cesta.setNome(query.record().value("nome").toString());
                cesta.setDescricao(query.record().value("descricao").toString());
                cesta.setCusto(query.record().value("custo").toDouble());
                cesta.setValor(query.record().value("valor").toDouble());
            }

        } else
            qDebug() << "CestaController::buscaPorNome() query.next: 0 registros";

    } else
        qDebug() << "CestaController::buscaPorNome() query.exec: " << query.lastError().text();

    conn.close();
    return cesta;
}

inline bool CestaController::altera(Cesta cesta)
{
    sql = "UPDATE tb_cestas SET ";
    sql += "nome = :nome, ";
    sql += "descricao = :descricao, ";
    sql += "custo = :custo, ";
    sql += "valor = :valor ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":nome", cesta.getNome());
        query.bindValue(":descricao", cesta.getDescricao());
        query.bindValue(":custo", cesta.getCusto());
        query.bindValue(":valor", cesta.getValor());
        query.bindValue(":id", cesta.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "CestaController::altera() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool CestaController::remove(Cesta cesta)
{
    sql = "DELETE FROM tb_cestas WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":id", cesta.getId());

        if (query.exec())
            retorno = true;
         else
             qDebug() << "CestaController::remove() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // CESTACONTROLLER_H
