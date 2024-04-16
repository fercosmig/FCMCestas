#include "global_variables.h"

global_variables::global_variables() {}

// VARIÁVEL GLOBAL PARA ACESSO AO BANCO DE DADOS
QSqlDatabase global_variables::bancoDeDados;

// VARIÁVEL GLOBAL QUE RETORNA O STATUS DA AUTENTICAÇÃO
bool global_variables::isLogged;

//VARIÁVEL GLOBAL QUE ARMAZENA DADOS DO COLABORADOR LOGADO
Colaborador global_variables::colaboradorLogado;
