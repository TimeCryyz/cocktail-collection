#include "mainwindow.h"
#include <QMenuBar>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QWidget>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_listView(nullptr), m_model(nullptr), m_chart(nullptr), m_timer(nullptr)
{
    setupUi();
    updateChartData();

    m_timer = new QTimer(this);
    m_timer->setInterval(2000);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::animateChart);
    m_timer->start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    setWindowTitle("Коллекция рецептов коктейлей (Вариант 15)");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    m_listView = new QListView(this);
    m_model = new CocktailModel(this);
    m_listView->setModel(m_model);
    layout->addWidget(m_listView, 1);

    m_chart = new StrengthChartWidget(this);
    layout->addWidget(m_chart, 1);

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
    toolBar->setMovable(true);

    QAction *toolAddAction = toolBar->addAction("Добавить");
    connect(toolAddAction, &QAction::triggered, this, &MainWindow::onAddCocktail);

    QAction *toolDelAction = toolBar->addAction("Удалить");
    connect(toolDelAction, &QAction::triggered, this, &MainWindow::onDeleteCocktail);

    QAction *toolClearAction = toolBar->addAction("Снять выделение");
    connect(toolClearAction, &QAction::triggered, this, &MainWindow::clearSelection);

    toolBar->addSeparator();

    QAction *toolColorAction = toolBar->addAction("Сменить цвет графика");
    connect(toolColorAction, &QAction::triggered, this, [this]() {
        if (m_chart) {
            m_chart->toggleColorMode();
            statusBar()->showMessage("Цвет графика изменен", 2000);
        }
    });

    QAction *toolTimerAction = toolBar->addAction("Стоп/Старт мигания");
    connect(toolTimerAction, &QAction::triggered, this, &MainWindow::toggleTimer);

    statusBar()->showMessage("Готово к работе.");
}

void MainWindow::updateChartData()
{
    if (m_chart && m_model) {
        m_chart->setData(m_model->getCocktails());
    }
}

void MainWindow::animateChart()
{
    if (m_chart) {
        m_chart->toggleColorMode();
    }
}

void MainWindow::toggleTimer()
{
    if (m_timer->isActive()) {
        m_timer->stop();
        statusBar()->showMessage("Мигание графика остановлено", 2000);
    } else {
        m_timer->start();
        statusBar()->showMessage("Мигание графика запущено", 2000);
    }
}

void MainWindow::clearSelection()
{
    m_listView->clearSelection();
    statusBar()->showMessage("Выделение снято", 2000);
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
    updateChartData();
    statusBar()->showMessage("Коктейль добавлен!", 3000);
}

void MainWindow::onDeleteCocktail()
{
    QModelIndex index = m_listView->currentIndex();
    if (index.isValid()) {
        m_model->removeCocktail(index.row());
        updateChartData();
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
                       "<p><b>Студент:</b> Филатов Вячеслав Викторович</p>"
                       "<p>Добавлены элементы ЛР3: QTimer, лямбда-слоты, QPainter.</p>");
}