#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QListView>
#include "models/cocktailmodel.h"

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

private:
    void setupUi();

    QListView *m_listView;
    CocktailModel *m_model;
};

#endif // MAINWINDOW_H