#ifndef PRODUTO_H
#define PRODUTO_H

#include <QString>

class Produto
{
private:
    QString id;
    QString nome;
    QString descricao;
    double custo;
    double valor;

protected:
public:
    Produto() {}


    QString getId() const;
    void setId(const QString &newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
    double getCusto() const;
    void setCusto(double newCusto);
    double getValor() const;
    void setValor(double newValor);
};

inline QString Produto::getId() const
{
    return id;
}

inline void Produto::setId(const QString &newId)
{
    id = newId;
}

inline QString Produto::getNome() const
{
    return nome;
}

inline void Produto::setNome(const QString &newNome)
{
    nome = newNome;
}

inline QString Produto::getDescricao() const
{
    return descricao;
}

inline void Produto::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

inline double Produto::getCusto() const
{
    return custo;
}

inline void Produto::setCusto(double newCusto)
{
    custo = newCusto;
}

inline double Produto::getValor() const
{
    return valor;
}

inline void Produto::setValor(double newValor)
{
    valor = newValor;
}

#endif // PRODUTO_H
