#ifndef CESTA_H
#define CESTA_H

#include <QString>

class Cesta
{
private:
    int id;
    QString nome;
    QString descricao;
    double custo;
    double valor;

    /*
     * int id;              Integer, autoincrement, somente um id.
     * QString nome;        Nome da cesta.
     * QString descricao;   Descrição da cesta, com detalhes e alguma história.
     * double custo;        Valor gasto para produzir a cesta.
     * double valor;        Valor de venda da cesta.
    */

protected:
public:
    // CONSTRUCTOR
    Cesta() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
    double getCusto() const;
    void setCusto(double newCusto);
    double getValor() const;
    void setValor(double newValor);
};

inline int Cesta::getId() const
{
    return id;
}

inline void Cesta::setId(int newId)
{
    id = newId;
}

inline QString Cesta::getNome() const
{
    return nome;
}

inline void Cesta::setNome(const QString &newNome)
{
    nome = newNome;
}

inline QString Cesta::getDescricao() const
{
    return descricao;
}

inline void Cesta::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

inline double Cesta::getCusto() const
{
    return custo;
}

inline void Cesta::setCusto(double newCusto)
{
    custo = newCusto;
}

inline double Cesta::getValor() const
{
    return valor;
}

inline void Cesta::setValor(double newValor)
{
    valor = newValor;
}

#endif // CESTA_H
