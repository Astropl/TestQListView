#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QStringListModel *countriesListModel; // model, który zostanie podpięty pod kontrolkę QListView
    QString country; // pomocnicza zmienna konieczna do przechowywania informacji o tekście zawartym w danym elemencie kontrolki przed jego modyfikacją
    QShortcut *shDelete; // skrót klawiaturowy do podpięcia slotu onDeleteItem
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // slot podpięty pod sygnał wysyłany, gdy tekst w elementach kontrolki został zmieniony
    void countryDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int> ());
    // slot podpięty pod sygnał wysyłany, gdy element w kontrolce został kliknięty dwa razy (co będzie oznaczało edycję tekstu kontrolki
    void on_countriesList_doubleClicked(const QModelIndex &index);
    // slot podpięty pod skrót klawiaturowy oznaczający usuwanie elementu zaznaczonego
    void onDeleteItem();
    // slot podpięty pod sygnał wysyłany, gdy wcześniej zaznaczony na liście element został nadpisany poprzez rozpoczęcie wpisywania tekstu
    void on_countriesList_pressed(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
