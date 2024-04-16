#ifndef CONEXAO_H
#define CONEXAO_H

#include "global_variables.h"
#include <QDebug>
#include <QSqlError>

class Conexao
{
private:
protected:
public:
    Conexao() {}

    void open();
    bool isOpen();
    void close();
};

inline void Conexao::open()
{
    if (!global_variables::bancoDeDados.isOpen()){
        if (!global_variables::bancoDeDados.open())
            qDebug() << "Conexao::open() - Error: " << global_variables::bancoDeDados.lastError().text();
    }
}

inline bool Conexao::isOpen()
{
    if (global_variables::bancoDeDados.isOpen())
        return true;
    return false;
}

inline void Conexao::close()
{
    if(global_variables::bancoDeDados.isOpen())
        global_variables::bancoDeDados.close();
}
#endif // CONEXAO_H
