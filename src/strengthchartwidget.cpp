#include "strengthchartwidget.h"
#include <QPainter>
#include <QPaintEvent>

StrengthChartWidget::StrengthChartWidget(QWidget *parent)
    : QWidget(parent), m_useGradient(false)
{
    setMinimumHeight(200);
}

void StrengthChartWidget::setData(const QList<Cocktail> &cocktails)
{
    m_cocktails = cocktails;
    update();
}

void StrengthChartWidget::toggleColorMode()
{
    m_useGradient = !m_useGradient;
    update();
}

void StrengthChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor("#f4f4f4"));

    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    if (m_cocktails.isEmpty()) return;

    int padding = 20;
    int labelHeight = 25;
    int availableWidth = width() - padding * 2;
    int barWidth = availableWidth / m_cocktails.size();
    int maxBarHeight = height() - padding * 2 - labelHeight;

    for (int i = 0; i < m_cocktails.size(); ++i) {
        int strength = m_cocktails[i].strength;
        if (strength > 100) strength = 100;

        int barHeight = (strength * maxBarHeight) / 100;
        int x = padding + (i * barWidth) + (barWidth / 4);
        int y = height() - padding - labelHeight - barHeight;
        int w = barWidth / 2;

        QColor barColor;
        if (m_useGradient) {
            barColor = QColor("#3498db");
        } else {
            if (strength < 20) barColor = QColor("#2ecc71");
            else if (strength < 40) barColor = QColor("#f1c40f");
            else barColor = QColor("#e74c3c");
        }

        painter.setBrush(barColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(x, y, w, barHeight);

        painter.setPen(Qt::black);
        painter.drawText(x - 15, height() - labelHeight, w + 30, labelHeight, Qt::AlignCenter, m_cocktails[i].name);
    }
}