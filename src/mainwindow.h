#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QListView>
#include <QTimer>
#include "models/cocktailmodel.h"
#include "src/strengthchartwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddCocktail();
    void onDeleteCocktail();
    void showAbout();
    void animateChart();
    void toggleTimer();
    void clearSelection();

private:
    void setupUi();
    void updateChartData();

    QListView *m_listView;
    CocktailModel *m_model;
    StrengthChartWidget *m_chart;
    QTimer *m_timer;
};

#endif // MAINWINDOW_H