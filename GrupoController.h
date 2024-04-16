#ifndef GRUPOCONTROLLER_H
#define GRUPOCONTROLLER_H

#include "Grupo.h"
#include "Conexao.h"
#include <QtSql>

class GrupoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    GrupoController() {}

    QVector<Grupo> buscaTodos();
    Grupo buscaPorId(Grupo grupo);
};

inline QVector<Grupo> GrupoController::buscaTodos()
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "sigla ";
    sql += "FROM ";
    sql += "tb_grupos";

    if (!conn.isOpen())
        conn.open();

    Grupo grupo;
    QVector<Grupo> listaGrupos;
    int contador = 0;

    if (conn.isOpen()) {

        query.prepare(sql);
        if (query.exec()) {
            if (query.next()) {
                do {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setNome(query.record().value("nome").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    listaGrupos.push_back(grupo);
                    contador++;
                } while (query.next());
                qDebug() << "GrupoController::buscaTodos() query.next(): " << contador << " registros";
            }
        }
    }
    conn.close();
    return listaGrupos;
}

inline Grupo GrupoController::buscaPorId(Grupo grupo)
{
    sql = "SELECT ";
    sql += "id, ";
    sql += "nome, ";
    sql += "sigla ";
    sql += "FROM ";
    sql += "tb_grupos ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":id", grupo.getId());
        if (query.exec()) {
            if (query.next()) {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setNome(query.record().value("nome").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
            }
        }
    }
    conn.close();
    return grupo;
}

#endif // GRUPOCONTROLLER_H
