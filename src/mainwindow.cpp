#include "mainwindow.h"
#include <QMenuBar>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QWidget>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_listView(nullptr), m_model(nullptr)
{
    setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    setWindowTitle("Коллекция рецептов коктейлей (Вариант 15)");
    resize(700, 500);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    m_listView = new QListView(this);
    m_model = new CocktailModel(this);
    m_listView->setModel(m_model);

    layout->addWidget(m_listView);
    setCentralWidget(centralWidget);

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    QAction *exitAction = fileMenu->addAction("Выход");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    QMenu *editMenu = menuBar()->addMenu("Правка");
    QAction *addAction = editMenu->addAction("Добавить коктейль");
    connect(addAction, &QAction::triggered, this, &MainWindow::onAddCocktail);

    QMenu *helpMenu = menuBar()->addMenu("Справка");
    QAction *aboutAction = helpMenu->addAction("О программе");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

    QToolBar *toolBar = addToolBar("Главная панель");
    toolBar->setMovable(false);

    QAction *toolAddAction = toolBar->addAction("Добавить");
    connect(toolAddAction, &QAction::triggered, this, &MainWindow::onAddCocktail);

    QAction *toolDelAction = toolBar->addAction("Удалить");
    connect(toolDelAction, &QAction::triggered, this, &MainWindow::onDeleteCocktail);

    toolBar->addSeparator();

    statusBar()->showMessage("Готово к работе.");
}

void MainWindow::onAddCocktail()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Новый коктейль", "Название:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString ingredients = QInputDialog::getText(this, "Новый коктейль", "Ингредиенты:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    int strength = QInputDialog::getInt(this, "Новый коктейль", "Крепость (%):", 0, 0, 100, 1, &ok);
    if (!ok) return;

    m_model->addCocktail({name, ingredients, strength});
    statusBar()->showMessage("Коктейль добавлен!", 3000);
}

void MainWindow::onDeleteCocktail()
{
    QModelIndex index = m_listView->currentIndex();
    if (index.isValid()) {
        m_model->removeCocktail(index.row());
        statusBar()->showMessage("Коктейль удален!", 3000);
    } else {
        QMessageBox::warning(this, "Внимание", "Сначала выберите коктейль в списке!");
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "О программе",
                       "<h2>Сквозной проект</h2>"
                       "<p><b>Тема:</b> Коллекция рецептов коктейлей (Вариант 15)</p>"
                       "<p><b>Студент:</b> timecryyz</p>"
                       "<p>Этап 2: Model-View</p>");
}