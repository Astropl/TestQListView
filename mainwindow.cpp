#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    countriesListModel = new QStringListModel(this); // tworzenie nowego obiektu modelu

    countriesListModel->setStringList(
        {"Polska", "Czechy", "Słowacja"} // dodaję parę początkowych pozycji
        );

    ui->countriesList->setModel(countriesListModel); // podpinam model pod kontrolkę QListView

    ui->countriesList->setEditTriggers(
        QAbstractItemView::AnyKeyPressed | // edycja zaznaczonego elementu na dowolny znak tekstowy
        QAbstractItemView::DoubleClicked   // edycja elementu po dwukrotnym kliknięciu lewym przyciskiem myszy
        );

    int row = countriesListModel->rowCount(); // pobieram liczbę wierszy

    countriesListModel->insertRow(row); // wstawiam dodatkowy wiersz na końcu
    QModelIndex index = countriesListModel->index(row, 0); // pobieram obiekt wstawionego indeksu
    countriesListModel->setData(index, QVariant("*")); // i ustawiam jego tekst

    // podpięcie sygnału dataChanged obiektu countriesListModel pod slot countryDataChanged okna głównego
    QObject::connect(countriesListModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(countryDataChanged(QModelIndex,QModelIndex,QVector<int>)));
    // tworzę skrót klawiaturowy podpięty pod kontrolkę QListView
    QShortcut* shDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->countriesList);
    // podpinam sygnał obiektu shDelete pod slot onDeleteItem okna głównego
    connect(shDelete, SIGNAL(activated()), this, SLOT(onDeleteItem()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::countryDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
    if(topLeft != bottomRight) // jak więcej niż dwa elementy są edytowane to nie wykonuj dalszych działań
        return;

    int rowCount = countriesListModel->rowCount(); // pobieram liczbę wierszy
    // jeżeli tekst jest pusty
    if(topLeft.data().toString() == ""){
        countriesListModel->setData(topLeft, country); // to przywracam pierwotne ustawienie
        return;
    }
    // wyszukuję elementy pasujące do wprowadzonego tekstu
    QModelIndexList finded = countriesListModel->match(countriesListModel->index(0, 0), Qt::DisplayRole, topLeft.data(), -1, Qt::MatchExactly);
    // jak znaleziono więcej niż jeden to znaczy, że taki element już istniał
    if(finded.size() > 1){
        //QMessageBox::warning(this, "Uwaga!", "Kraj o nazwie: " + topLeft.data().toString() + " już jest na liście");
        countriesListModel->setData(topLeft, country);
    }else if(topLeft.row() == rowCount - 1){ // jeżeli edytowany był ostatni element
        if(topLeft.data().toString() != "*"){ // i tekst nie jest "*" to
            countriesListModel->insertRow(rowCount); // dodaję nową pozycję
            QModelIndex index = countriesListModel->index(rowCount, 0); // pobieram jej obiekt
            countriesListModel->setData(index, QVariant("*")); // i ustawiam tekst na "*"
        }
    }
}

void MainWindow::on_countriesList_doubleClicked(const QModelIndex &index)
{
    country = index.data().toString(); // zapamiętywanie początkowej wartości edytowanego indeksu
}

void MainWindow::onDeleteItem(){
    int row = ui->countriesList->currentIndex().row(); // pobieram indeks
    if(row != countriesListModel->rowCount() - 1){ // jak nie jest równy ostatniemu elementowi to
        countriesListModel->removeRow(row); // usuwam wiersz
    }
}

void MainWindow::on_countriesList_pressed(const QModelIndex &index)
{
    country = index.data().toString(); // zapamiętywanie początkowej wartości edytowanego indeksu
}

void MainWindow::on_pushButton_clicked()
{
    int rowCount = countriesListModel->rowCount();
    countriesListModel->insertRow(rowCount);
     QModelIndex index = countriesListModel->index(rowCount, 0); // pobieram jej obiekt
     countriesListModel->setData(index, QVariant("Cos innego")); // i ustawiam tekst na "*"
}
