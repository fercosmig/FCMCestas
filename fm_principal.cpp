#include "fm_principal.h"
#include "ui_fm_principal.h"
#include "global_variables.h"
#include "fm_autenticacao.h"
#include <QMessageBox>
#include "fm_produtos.h"
#include "fm_colaboradores.h"
#include "fm_nova_cesta.h"
#include "global_functions.h"
#include "CestaController.h"
#include "fm_edita_cesta.h"

fm_principal::fm_principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::fm_principal)
{
    ui->setupUi(this);

    fm_principal::inicializa_fm_principal();
}

fm_principal::~fm_principal()
{
    delete ui;
}

/* *** *** *** ***
 * MINHAS FUNÇÕES
 * *** *** *** ***/

void fm_principal::inicializa_fm_principal()
{
    // variáveis & objetos
    QString local_db, nome_db, banco;

    // configura o banco de dados
    local_db = qApp->applicationDirPath();
    nome_db = "/db/fcm_cestas.db";
    banco = local_db + nome_db;
    global_variables::bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    global_variables::bancoDeDados.setDatabaseName(banco);

    // inicializa com o login sendo false;
    global_variables::isLogged = false;

    // adiciona versão
    ui->label_versao->setText("Versão: " + fm_principal::versao);

    // adiciona o botão e a label no statusbar
    ui->statusbar->addWidget(ui->pushButton_autenticacao);
    ui->statusbar->addWidget(ui->label_colaborador_logado);

    // configura o botão e o conteúdo da label de autenticação
    fm_principal::configura_autenticacao();

    // oculta o conteúdo do formulario caso não esteja logado
    fm_principal::habilitar_formulario();

    // carre lista de cestas
    fm_principal::atualizaTableWidget();
}

void fm_principal::configura_autenticacao()
{
    // variáveis & objetos
    QIcon cadeadoAberto;
    QIcon cadeadoFechado;
    QString texto_statusbar;

    // adiciona as imagens aos objetos
    cadeadoAberto.addFile(":/icons/images/open.png");
    cadeadoFechado.addFile(":/icons/images/close.png");

    if (global_variables::isLogged)
    {
        ui->pushButton_autenticacao->setIcon(cadeadoAberto);
        texto_statusbar = global_variables::colaboradorLogado.getGrupo().getSigla();
        texto_statusbar += " | ";
        texto_statusbar += global_variables::colaboradorLogado.getNome();
    }
    else
    {
        ui->pushButton_autenticacao->setIcon(cadeadoFechado);
        texto_statusbar = "Autentique-se!";
    }
    ui->label_colaborador_logado->setText(texto_statusbar);

    fm_principal::habilitar_formulario();
}

void fm_principal::atualizaTableWidget()
{
    QVector<Cesta> listaCestas;
    CestaController cesta_controller;
    listaCestas = cesta_controller.buscaTodos();

    fm_principal::populaTableWidget(listaCestas);
}

void fm_principal::populaTableWidget(QVector<Cesta> listaCestas)
{
    Cesta cesta;
    fm_principal::cabecalho = {"ID", "Nome", "Descrição", "Custo", "Valor"};
    global_functions::formatTableWidget(ui->tableWidget_cestas, cabecalho);

    for (int i = 0; i < listaCestas.size(); ++i)
    {
        cesta = listaCestas[i];
        ui->tableWidget_cestas->insertRow(i);
        ui->tableWidget_cestas->setItem(i, 0, new QTableWidgetItem(QString::number(cesta.getId())));
        ui->tableWidget_cestas->setItem(i, 1, new QTableWidgetItem(cesta.getNome()));
        ui->tableWidget_cestas->setItem(i, 2, new QTableWidgetItem(cesta.getDescricao()));
        ui->tableWidget_cestas->setItem(i, 3, new QTableWidgetItem(global_functions::formatDoubleToString(cesta.getCusto())));
        ui->tableWidget_cestas->setItem(i, 4, new QTableWidgetItem(global_functions::formatDoubleToString(cesta.getValor())));
        ui->tableWidget_cestas->setRowHeight(i, 20);
    }
}

void fm_principal::limpaFormulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_pesquisar->setFocus();
}

void fm_principal::habilitar_formulario()
{
    ui->lineEdit_pesquisar->setEnabled(global_variables::isLogged);
    ui->pushButton_pesquisar->setEnabled(global_variables::isLogged);
    ui->pushButton_mostrar_todos->setEnabled(global_variables::isLogged);
    ui->tableWidget_cestas->setEnabled(global_variables::isLogged);
    ui->pushButton_ver_cesta->setEnabled(global_variables::isLogged);
    ui->pushButton_nova_cesta->setEnabled(global_variables::isLogged);
}

/* *** *** *** ***
 * SLOTS
 * *** *** *** ***/

void fm_principal::on_pushButton_fechar_clicked()
{
    QApplication::quit();
}

void fm_principal::on_pushButton_autenticacao_clicked()
{
    if (global_variables::isLogged)
    {
        global_variables::isLogged = false;
    }
    else
    {
        fm_autenticacao f_autenticacao;
        f_autenticacao.exec();
    }
    fm_principal::configura_autenticacao();
}

void fm_principal::on_actionSair_triggered()
{
    QApplication::quit();
}

void fm_principal::on_actionSobre_triggered()
{
    QString informacoes;
    informacoes = "Sistema de cestas de café da manhã - FCMCestas\n\n";
    informacoes += "Desenvolvido por Fernando Costa Migliorini\n\n";
    informacoes += "entre 20/03/2024 e 07/04/2024.\n\n";
    informacoes +="Desenvolvido em C++ (QtCreator) & SQLITE\n\n";
    informacoes +="Versão: " + fm_principal::versao;
    QMessageBox::information(this, "Sistema FCMCestas", informacoes);
}

void fm_principal::on_actionProdutos_triggered()
{
    if (global_variables::isLogged)
    {
            fm_produtos f_produtos;
            f_produtos.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Efetuar autenticação no sistema!");
    }
}

void fm_principal::on_actionColaboradores_triggered()
{
    if (global_variables::isLogged)
    {
        if (global_variables::colaboradorLogado.getGrupo().getSigla() == "A")
        {
            fm_colaboradores f_colaboradores;
            f_colaboradores.exec();
        }
        else
        {
            QMessageBox::warning(this, "", "Sem permissão de acesso!");
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Efetuar autenticação no sistema!");
    }
}

void fm_principal::on_pushButton_nova_cesta_clicked()
{
    if (global_variables::isLogged)
    {
        fm_nova_cesta f_nova_cesta;
        f_nova_cesta.exec();

        fm_principal::atualizaTableWidget();
    }
    else
    {
        QMessageBox::warning(this, "", "Efetuar autenticação no sistema!");
    }
}

void fm_principal::on_pushButton_pesquisar_clicked()
{
    QString texto;
    Cesta cesta;
    CestaController cesta_controller;
    QVector<Cesta> listaCestas;

    texto = ui->lineEdit_pesquisar->text().trimmed();

    if (global_functions::validatesSizeString(texto, 3))
    {
        cesta.setNome(texto);
        cesta.setDescricao(texto);
        listaCestas = cesta_controller.buscaPorNomeDescricao(cesta);
        fm_principal::populaTableWidget(listaCestas);
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres");
    }

    fm_principal::limpaFormulario();
}

void fm_principal::on_pushButton_mostrar_todos_clicked()
{
    fm_principal::atualizaTableWidget();
    fm_principal::limpaFormulario();
}

void fm_principal::on_pushButton_ver_cesta_clicked()
{
    if (!global_variables::isLogged)
    {
        QMessageBox::warning(this, "", "Efetuar autenticação no sistema!");
        return;
    }

    int row, id_cesta;

    row = ui->tableWidget_cestas->currentRow();

    if (row >= 0)
    {
        id_cesta = ui->tableWidget_cestas->item(row, 0)->text().toInt();
        fm_edita_cesta f_edita_cesta(this, id_cesta);
        f_edita_cesta.exec();

        fm_principal::atualizaTableWidget();
    }
    else
    {
        QMessageBox::warning(this, "", "Selecione uma cesta!");
    }
}
