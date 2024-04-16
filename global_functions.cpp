#include "global_functions.h"

global_functions::global_functions() {}

bool global_functions::validatesSizeString(QString texto, int quantidade_caracteres)
{
    if (texto.length() < quantidade_caracteres)
        return false;
    return true;
}

void global_functions::formatTableWidget(QTableWidget *tw, QStringList cabecalho)
{
    int columns = cabecalho.size();

    tw->clear();
    tw->setRowCount(0);

    // quantidade de colunas
    tw->setColumnCount(columns);

    // insere cabeçalho
    tw->setHorizontalHeaderLabels(cabecalho);

    // desabilitando edição
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // seleção de toda a linha
    tw->setSelectionBehavior(QAbstractItemView::SelectRows);

    // remove nº linha
    tw->verticalHeader()->setVisible(false);

    // selecionando somente uma linha
    tw->setSelectionMode(QAbstractItemView::SingleSelection);

    // formata largura da coluna conforme conteudo
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // formata largura da coluna conforme tamanho do tableWidget
    //tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QString global_functions::formatDoubleToString(double valor)
{
    QString formatado;
    try {
        formatado = QString("%1").arg(valor, 0, 'f', 2);
    } catch (const std::exception &e) {
        qDebug() << "fd (formata_double): " << e.what();
    }
    return formatado;
}

QString global_functions::calculaPorcentagemLucroToString(double custo, double valor)
{
    double porcentagem;
    QString resposta;

    porcentagem = 100 * ( (valor - custo) / custo );

    resposta = global_functions::formatDoubleToString(porcentagem) + "%";

    return resposta;
}

double global_functions::calculaTotalTableWidget(QTableWidget *tw, int coluna)
{
    int linhas;
    double total;

    linhas = tw->rowCount();
    total = 0;

    for (int i = 0; i < linhas; i++) {
        total += tw->item(i, coluna)->text().toDouble();
    }

    return total;
}
