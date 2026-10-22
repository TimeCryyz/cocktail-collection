#include "cocktailmodel.h"

CocktailModel::CocktailModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_cocktails.append({"Мохито", "Ром, мята, лайм, содовая", 15});
    m_cocktails.append({"Маргарита", "Текила, ликер, сок лайма", 25});
}

int CocktailModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_cocktails.size();
}

QVariant CocktailModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_cocktails.size())
        return QVariant();

    const Cocktail &cocktail = m_cocktails.at(index.row());

    if (role == Qt::DisplayRole) {
        return QString("%1 (Крепость: %2%)\nИнгредиенты: %3")
            .arg(cocktail.name)
            .arg(cocktail.strength)
            .arg(cocktail.ingredients);
    }
    return QVariant();
}

void CocktailModel::addCocktail(const Cocktail &cocktail)
{
    beginInsertRows(QModelIndex(), m_cocktails.size(), m_cocktails.size());
    m_cocktails.append(cocktail);
    endInsertRows();
}

void CocktailModel::removeCocktail(int row)
{
    if (row < 0 || row >= m_cocktails.size()) return;

    beginRemoveRows(QModelIndex(), row, row);
    m_cocktails.removeAt(row);
    endRemoveRows();
}