#ifndef GRUPO_H
#define GRUPO_H

#include <QString>

class Grupo
{
private:
    int id;
    QString nome;
    QString sigla;

protected:
public:
    Grupo() {}

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getSigla() const;
    void setSigla(const QString &newSigla);
};

inline int Grupo::getId() const
{
    return id;
}

inline void Grupo::setId(int newId)
{
    id = newId;
}

inline QString Grupo::getNome() const
{
    return nome;
}

inline void Grupo::setNome(const QString &newNome)
{
    nome = newNome;
}

inline QString Grupo::getSigla() const
{
    return sigla;
}

inline void Grupo::setSigla(const QString &newSigla)
{
    sigla = newSigla;
}
#endif // GRUPO_H
