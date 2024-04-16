#include "fm_autenticacao.h"
#include "ui_fm_autenticacao.h"
#include "Colaborador.h"
#include "ColaboradorController.h"
#include "global_functions.h"
#include <QMessageBox>

fm_autenticacao::fm_autenticacao(QWidget *parent) : QDialog(parent), ui(new Ui::fm_autenticacao)
{
    ui->setupUi(this);

    fm_autenticacao::inicializa_fm_autenticacao();
}

fm_autenticacao::~fm_autenticacao()
{
    delete ui;
}

/* *** *** *** ***
 * MINHAS FUNÇÕES
 * *** *** *** ***/

void fm_autenticacao::inicializa_fm_autenticacao()
{
    // GAMBIARRA
    // ui->lineEdit_email->setText("fercosmig@gmail.com");
    // ui->lineEdit_senha->setText("123");
}

void fm_autenticacao::limpa_formulario()
{
    ui->lineEdit_email->clear();
    ui->lineEdit_senha->clear();
    ui->lineEdit_email->setFocus();
}

/* *** *** *** ***
 * SLOTS
 * *** *** *** ***/

void fm_autenticacao::on_pushButton_fechar_clicked()
{
    close();
}


void fm_autenticacao::on_pushButton_autenticar_clicked()
{
    QString email, senha;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;

    email = ui->lineEdit_email->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();

    if (!global_functions::validatesSizeString(email, 7) || !global_functions::validatesSizeString(senha, 3)){
        QMessageBox::warning(this, "", "Quantidade mínima de caracteres: E-mail: 7 | Senha: 3");
        return;
    }

    colaborador.setEmail(email);
    colaborador.setSenha(senha);

    colaborador = colaborador_controller.autenticacao(colaborador);

    if (colaborador.getId() != 0){
        global_variables::colaboradorLogado = colaborador;
        global_variables::isLogged = true;
        close();
    } else
        QMessageBox::warning(this, "", "E-mail ou Senha inválidos!");
}
