#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "Colaborador.h"
#include <QSqlDatabase>
#include <QIcon>

class global_variables
{
public:

    static QSqlDatabase bancoDeDados;
    static bool isLogged;
    static Colaborador colaboradorLogado;

    global_variables();
};

// Colocar código abaixo no construtor do mainWindow.cpp

// QString local_db = qApp->applicationDirPath();
// QString nome_db = "/db/aula83.db";
// QString banco = local_db + nome_db;
// global_variables::bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
// global_variables::bancoDeDados.setDatabaseName(banco);

#endif // GLOBAL_VARIABLES_H
