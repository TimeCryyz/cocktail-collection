#ifndef STRENGTHCHARTWIDGET_H
#define STRENGTHCHARTWIDGET_H

#include <QWidget>
#include <QColor>
#include "models/cocktailmodel.h"

class StrengthChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StrengthChartWidget(QWidget *parent = nullptr);

    void setData(const QList<Cocktail> &cocktails);
    void toggleColorMode();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<Cocktail> m_cocktails;
    bool m_useGradient;
};

#endif // STRENGTHCHARTWIDGET_H