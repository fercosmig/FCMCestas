#include "fm_colaboradores.h"
#include "ui_fm_colaboradores.h"
#include "Grupo.h"
#include "GrupoController.h"
#include "global_functions.h"
#include "ColaboradorController.h"
#include <QMessageBox>

fm_colaboradores::fm_colaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_colaboradores)
{
    ui->setupUi(this);

    fm_colaboradores::inicializa_fm_colaboradores();
}

fm_colaboradores::~fm_colaboradores()
{
    delete ui;
}

/* ***** ***** ***** *****
 * MEUS MÉTODOS
 * ***** ***** ***** *****/

void fm_colaboradores::inicializa_fm_colaboradores()
{
    fm_colaboradores::cabecalho = {"ID", "Nome", "E-mail", "Senha", "ID Grupo", "Grupo"};
    fm_colaboradores::atualizaTableWidget();

    fm_colaboradores::preencheComboBoxGrupo();

    ui->label_selected_row->setText("-1");
    ui->label_selected_row->setVisible(false);

}

void fm_colaboradores::limpaFormularioAlteracao()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_senha->clear();
    ui->comboBox_grupo->setCurrentIndex(0);
    ui->pushButton_excluir->setEnabled(false);
    ui->label_selected_row->setText("-1");
}

void fm_colaboradores::limpaFormularioPesquisa()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_pesquisar->setFocus();
}

void fm_colaboradores::preencheComboBoxGrupo()
{
    QVector<Grupo> listaGrupos;
    GrupoController grupo_controller;

    listaGrupos = grupo_controller.buscaTodos();

    ui->comboBox_grupo->addItem("Selecione", 0);

    for (Grupo grupo : listaGrupos) {
        ui->comboBox_grupo->addItem(grupo.getSigla() + " | " + grupo.getNome(), grupo.getId());
    }
}

void fm_colaboradores::atualizaTableWidget()
{
    QVector<Colaborador> listaColaboradores;
    ColaboradorController colaborador_controller;

    listaColaboradores = colaborador_controller.buscaTodos();

    fm_colaboradores::populaTableWidget(listaColaboradores);
}

void fm_colaboradores::populaTableWidget(QVector<Colaborador> listaColaboradores)
{
    Colaborador colaborador;

    global_functions::formatTableWidget(ui->tableWidget_colaboradores, fm_colaboradores::cabecalho);

    for (int i = 0; i < listaColaboradores.size(); i++) {
        colaborador = listaColaboradores[i];
        ui->tableWidget_colaboradores->insertRow(i);
        ui->tableWidget_colaboradores->setItem(i, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(i, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(i, 2, new QTableWidgetItem(colaborador.getEmail()));
        ui->tableWidget_colaboradores->setItem(i, 3, new QTableWidgetItem(colaborador.getSenha()));
        ui->tableWidget_colaboradores->setItem(i, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
        ui->tableWidget_colaboradores->setItem(i, 5, new QTableWidgetItem(colaborador.getGrupo().getNome()));
        ui->tableWidget_colaboradores->setRowHeight(i, 20);
    }
    ui->tableWidget_colaboradores->setColumnHidden(3,true);
    ui->tableWidget_colaboradores->setColumnHidden(4,true);
}

/* ***** ***** ***** *****
 * SLOTS
 * ***** ***** ***** *****/

void fm_colaboradores::on_pushButton_fechar_clicked()
{
    close();
}

void fm_colaboradores::on_tableWidget_colaboradores_itemSelectionChanged()
{
    int row, id, id_grupo, item_combo;
    QString nome, email, senha;

    row = ui->tableWidget_colaboradores->currentRow();
    ui->label_selected_row->setText(QString::number(row));
    ui->pushButton_excluir->setEnabled(true);

    id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();
    nome = ui->tableWidget_colaboradores->item(row, 1)->text();
    email = ui->tableWidget_colaboradores->item(row, 2)->text();
    senha = ui->tableWidget_colaboradores->item(row, 3)->text();
    id_grupo = ui->tableWidget_colaboradores->item(row, 4)->text().toInt();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_senha->setText(senha);
    item_combo = ui->comboBox_grupo->findData(id_grupo);
    ui->comboBox_grupo->setCurrentIndex(item_combo);
}

void fm_colaboradores::on_pushButton_limpar_clicked()
{
    fm_colaboradores::limpaFormularioAlteracao();
}

void fm_colaboradores::on_pushButton_salvar_clicked()
{
    int row, rowcount, id, id_grupo;
    QString nome, email, senha, mensagem, email_antes;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;
    Grupo grupo;
    GrupoController grupo_controller;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    email = ui->lineEdit_email->text().trimmed().toLower();
    senha = ui->lineEdit_senha->text().trimmed();
    id_grupo = ui->comboBox_grupo->currentData().toInt();

    if (!(global_functions::validatesSizeString(nome, 3)) || !(global_functions::validatesSizeString(email, 7)) || !(global_functions::validatesSizeString(senha, 3)) || !(id_grupo > 0)) {
        mensagem = "Nome e senha devem ter no mínimo 3 caracteres.\n";
        mensagem += "E-mail deve ter no mínimo 7 caracteres.\n";
        mensagem += "Um grupo deve ser selecionado.";
        QMessageBox::warning(this, "", mensagem);
        return;
    }

    grupo.setId(id_grupo);
    grupo = grupo_controller.buscaPorId(grupo);

    colaborador.setId(id);
    colaborador.setNome(nome);
    colaborador.setEmail(email);
    colaborador.setSenha(senha);
    colaborador.setGrupo(grupo);

    if(row == -1) { // INCLUSÃO DE COLABORADORES

        if (colaborador_controller.verificaDuplicidade(colaborador)) {
            QMessageBox::warning(this, "", "E-mail já existe no banco de dados");
            fm_colaboradores::limpaFormularioAlteracao();
            return;
        }

        colaborador = colaborador_controller.insere(colaborador);
        QMessageBox::information(this, "", "Colaborador inserido com sucesso!");

        rowcount = ui->tableWidget_colaboradores->rowCount();
        ui->tableWidget_colaboradores->insertRow(rowcount);
        ui->tableWidget_colaboradores->setItem(rowcount, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(rowcount, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(rowcount, 2, new QTableWidgetItem(colaborador.getEmail()));
        ui->tableWidget_colaboradores->setItem(rowcount, 3, new QTableWidgetItem(colaborador.getSenha()));
        ui->tableWidget_colaboradores->setItem(rowcount, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
        ui->tableWidget_colaboradores->setItem(rowcount, 5, new QTableWidgetItem(colaborador.getGrupo().getNome()));
        ui->tableWidget_colaboradores->setRowHeight(rowcount, 20);

        fm_colaboradores::limpaFormularioAlteracao();

    } else{ // ALTERAÇÃO DE COLABORADORES

        email_antes = ui->tableWidget_colaboradores->item(row, 2)->text();

        if (email_antes != colaborador.getEmail()) {
            if (colaborador_controller.verificaDuplicidade(colaborador)) {
                QMessageBox::warning(this, "", "E-mail já existe no banco de dados");
                return;
            }
        }

        if(colaborador_controller.altera(colaborador)) {
            QMessageBox::information(this, "", "Colaborador alterado com sucesso!");
            ui->tableWidget_colaboradores->item(row, 1)->setText(colaborador.getNome());
            ui->tableWidget_colaboradores->item(row, 2)->setText(colaborador.getEmail());
            ui->tableWidget_colaboradores->item(row, 3)->setText(colaborador.getSenha());
            ui->tableWidget_colaboradores->item(row, 4)->setText(QString::number(colaborador.getGrupo().getId()));
            ui->tableWidget_colaboradores->item(row, 5)->setText(colaborador.getGrupo().getNome());

            fm_colaboradores::limpaFormularioAlteracao();
        } else
            QMessageBox::warning(this, "", "Erro ao tentar alterar o colaborador.");
    }
}

void fm_colaboradores::on_pushButton_pesquisar_clicked()
{
    QString nome;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;
    QVector<Colaborador> listaColaboradores;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global_functions::validatesSizeString(nome, 3)){

        colaborador.setNome(nome);
        listaColaboradores = colaborador_controller.buscaPorNome(colaborador);

        fm_colaboradores::populaTableWidget(listaColaboradores);
        fm_colaboradores::limpaFormularioAlteracao();
        fm_colaboradores::limpaFormularioPesquisa();

    } else
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres para pesquisa.");
}

void fm_colaboradores::on_pushButton_mostrar_todos_clicked()
{
    fm_colaboradores::atualizaTableWidget();
}

void fm_colaboradores::on_pushButton_excluir_clicked()
{
    int row, id;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;
    QMessageBox::StandardButton resposta;

    resposta = QMessageBox::question(this, "", "Tem certeza?", QMessageBox::Yes | QMessageBox::No);

    if(resposta == QMessageBox::Yes) {
        row = ui->label_selected_row->text().toInt();
        id = ui->lineEdit_id->text().toInt();
        colaborador.setId(id);

        if (colaborador_controller.remove(colaborador)) {
            QMessageBox::information(this, "","Colaborador excluido com sucesso!");
            ui->tableWidget_colaboradores->removeRow(row);
            fm_colaboradores::limpaFormularioAlteracao();
        } else
            QMessageBox::warning(this, "","Problema ao tentar excliuir o coalborador!");
    }
}
