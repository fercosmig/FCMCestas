#ifndef COLABORADORCONTROLLER_H
#define COLABORADORCONTROLLER_H

#include "Colaborador.h"
#include "Conexao.h"
#include <QtSql>

class ColaboradorController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    //CONSTRUCTOR
    ColaboradorController() {}

    // METHODS
    Colaborador insere(Colaborador colaborador);
    QVector<Colaborador> buscaTodos();
    Colaborador buscaPorId(Colaborador colaborador);
    QVector<Colaborador> buscaPorNome(Colaborador colaborador);
    bool verificaDuplicidade(Colaborador colaborador);
    Colaborador autenticacao(Colaborador colaborador);
    bool altera(Colaborador colaborador);
    bool remove(Colaborador colaborador);
};

inline Colaborador ColaboradorController::insere(Colaborador colaborador)
{
    sql = "INSERT INTO tb_colaboradores ";
    sql += "( nome, email, senha, id_grupo ) ";
    sql += "VALUES ( :nome, :email, :senha, :id_grupo )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", QString::number(colaborador.getGrupo().getId()));

         if (query.exec()){
            sql = "SELECT id FROM tb_colaboradores ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec()){
                if (query.next())
                    colaborador.setId(query.record().value("id").toInt());
            } else
                qDebug() << "ColaboradorController::insere() query.exec retorno: " << query.lastError().text();
         } else
             qDebug() << "ColaboradorController::insere() query.exec: " << query.lastError().text();

         query.exec("COMMIT");
    }
    conn.close();
    return colaborador;
}

inline QVector<Colaborador> ColaboradorController::buscaTodos()
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.nome as nome_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM ";
    sql += "tb_colaboradores ";
    sql += "INNER JOIN ";
    sql += "tb_grupos ";
    sql += "ON ";
    sql += "tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "ORDER BY tb_colaboradores.nome ASC";

    Grupo grupo;
    Colaborador colaborador;
    int contador = 0;
    QVector<Colaborador> listaColaboradores;

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.prepare(sql);

        if (query.exec()) {
            if(query.next()) {
                do {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setNome(query.record().value("nome_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    listaColaboradores.push_back(colaborador);
                    contador++;
                } while (query.next());
                qDebug() << "ColaboradorController::buscaTodos() query.next() " << contador << " registros.";
            }
        } else
            qDebug() << "ColaboradorController::buscaTodos() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaColaboradores;
}

inline Colaborador ColaboradorController::buscaPorId(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.nome as nome_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM ";
    sql += "tb_colaboradores ";
    sql += "INNER JOIN ";
    sql += "tb_grupos ";
    sql += "ON ";
    sql += "tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE ";
    sql += "tb_colaboradores.id = :id ";

    Grupo grupo;

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", colaborador.getId());

        if (query.exec()) {
            if(query.next()) {
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setNome(query.record().value("nome_grupo").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                colaborador.setEmail(query.record().value("email").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);

                qDebug() << "ColaboradorController::buscaPorId(): Colaborador: " <<  colaborador.getId() << "-" << colaborador.getNome();
            }
        } else {
            colaborador.setId(0);
            qDebug() << "ColaboradorController::buscaPorId() query.exec: " << query.lastError().text();
        }
    }
    conn.close();
    return colaborador;
}

inline QVector<Colaborador> ColaboradorController::buscaPorNome(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.nome as nome_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM ";
    sql += "tb_colaboradores ";
    sql += "INNER JOIN ";
    sql += "tb_grupos ";
    sql += "ON ";
    sql += "tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE ";
    sql += "tb_colaboradores.nome LIKE :nome ";
    sql += "ORDER BY tb_colaboradores.nome ASC";

    Grupo grupo;
    int contador = 0;
    QVector<Colaborador> listaColaboradores;

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":nome", "%" + colaborador.getNome() + "%");

        if (query.exec()) {
            if(query.next()) {
                do {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setNome(query.record().value("nome_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    listaColaboradores.push_back(colaborador);
                    contador++;
                } while (query.next());
                qDebug() << "ColaboradorController::buscaPorNome() query.next() " << contador << " registros.";
            }
        } else
            qDebug() << "ColaboradorController::buscaPorNome() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaColaboradores;
}

inline bool ColaboradorController::verificaDuplicidade(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "id ";
    sql += "FROM ";
    sql += "tb_colaboradores ";
    sql += "WHERE ";
    sql += "email = :email";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":email", colaborador.getEmail());

        if (query.exec()) {
            if(query.next()) {
                retorno = true;
                qDebug() << "ColaboradorController::verificaDuplicidade(): query.next(): E-mail já existe no banco de dados";
            }
        }
    }
    conn.close();
    return retorno;
}

inline Colaborador ColaboradorController::autenticacao(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.nome as nome_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM ";
    sql += "tb_colaboradores ";
    sql += "INNER JOIN ";
    sql += "tb_grupos ";
    sql += "ON ";
    sql += "tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE ";
    sql += "tb_colaboradores.email = :email ";
    sql += "AND ";
    sql += "tb_colaboradores.senha = :senha";

    Grupo grupo;

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());

        if (query.exec()) {
            if(query.next()) {
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setNome(query.record().value("nome_grupo").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                colaborador.setEmail(query.record().value("email").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);

                qDebug() << "ColaboradorController::autenticacao(): Colaborador: " <<  colaborador.getId() << "-" << colaborador.getNome();
            } else {
                colaborador.setId(0);
                qDebug() << "ColaboradorController::autenticacao() query.next: colaborador não encontrado. Nome ou senha inválidos.";
            }
        } else {
            colaborador.setId(0);
            qDebug() << "ColaboradorController::autenticacao() query.exec: " << query.lastError().text();
        }
    }
    conn.close();
    return colaborador;
}

inline bool ColaboradorController::altera(Colaborador colaborador)
{
    sql = "UPDATE tb_colaboradores SET ";
    sql += "nome = :nome, ";
    sql += "email = :email, ";
    sql += "senha = :senha, ";
    sql += "id_grupo = :id_grupo ";
    sql += "WHERE id = :id ";


    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", QString::number(colaborador.getGrupo().getId()));
        query.bindValue(":id", colaborador.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ColaboradorController::altera() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ColaboradorController::remove(Colaborador colaborador)
{
    sql = "DELETE FROM tb_colaboradores WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", colaborador.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ColaboradorController::remove() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // COLABORADORCONTROLLER_H
