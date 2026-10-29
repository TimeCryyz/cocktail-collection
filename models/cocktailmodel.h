#ifndef COCKTAILMODEL_H
#define COCKTAILMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QList>

struct Cocktail {
    QString name;
    QString ingredients;
    int strength;
};

class CocktailModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CocktailModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addCocktail(const Cocktail &cocktail);
    void removeCocktail(int row);

    QList<Cocktail> getCocktails() const { return m_cocktails; }

private:
    QList<Cocktail> m_cocktails;
};

#endif // COCKTAILMODEL_H