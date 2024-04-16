#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <QString>
#include <QTableWidget>
#include <QHeaderView>

class global_functions
{
private:
protected:
public:
    global_functions();

    static bool validatesSizeString(QString texto, int quantidade_caracteres);
    static void formatTableWidget(QTableWidget *tw, QStringList cabecalho);
    static QString formatDoubleToString(double valor);
    static QString calculaPorcentagemLucroToString(double custo, double valor);
    static double calculaTotalTableWidget(QTableWidget *tw, int coluna);
};

#endif // GLOBAL_FUNCTIONS_H
