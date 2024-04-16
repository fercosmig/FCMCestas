#ifndef ITEMCESTA_H
#define ITEMCESTA_H

#include "Cesta.h"
#include "Produto.h"

class ItemCesta
{
private:
    int id;
    double quantidade;
    Cesta cesta;
    Produto produto;

protected:
public:
    ItemCesta() {}

    int getId() const;
    void setId(int newId);
    double getQuantidade() const;
    void setQuantidade(double newQuantidade);
    Cesta getCesta() const;
    void setCesta(const Cesta &newCesta);
    Produto getProduto() const;
    void setProduto(const Produto &newProduto);
};

inline int ItemCesta::getId() const
{
    return id;
}

inline void ItemCesta::setId(int newId)
{
    id = newId;
}

inline double ItemCesta::getQuantidade() const
{
    return quantidade;
}

inline void ItemCesta::setQuantidade(double newQuantidade)
{
    quantidade = newQuantidade;
}

inline Cesta ItemCesta::getCesta() const
{
    return cesta;
}

inline void ItemCesta::setCesta(const Cesta &newCesta)
{
    cesta = newCesta;
}

inline Produto ItemCesta::getProduto() const
{
    return produto;
}

inline void ItemCesta::setProduto(const Produto &newProduto)
{
    produto = newProduto;
}

#endif // ITEMCESTA_H
