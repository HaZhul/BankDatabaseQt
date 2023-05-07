#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <string.h>
#include<QDebug>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <QFile>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class KlientBanku
{
public:
    string imie;
    string nazwisko;
    int rok;
    string nrKonta;
    string nazwaBanku;
    double kwota;
    KlientBanku(const string& im, const string& naz, const int r, const string& nr, const string& nazwaB, const double kw);
    KlientBanku();
    ~KlientBanku();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    string path = "C:/Users/Dominik/Desktop/Inne/Zadanie2/baza_danych.txt";

    int rok;
    double kwota;
    vector<KlientBanku*> baza;
    string imie, nazwisko, nrKonta, nazwaBanku;
    void drukujKlientBanku(KlientBanku *klient) const;
    void modyfikacjaKlienta(KlientBanku *klient);

    int nowaLiczbaKlientow = 0;
    double najwKwota = 0;
    double obecnaWKwota;
    double obecnaNKwota;
    double najnKwota = 1000000;
    bool zmianaKwoty = false;
    string nowyNrKonta;
    double nowaKwota;
    bool exist = false;
    bool scena1 = false;
    bool zmienKwote=false;
    bool drukowanie=false;
    bool modyfikacja=false;
    bool modyfikacja2=false;
    bool exist2;
    int stage=0;
    string schowek;
    int wklient;
    int schowek1;
    double schowek3;


private:
    Ui::MainWindow *ui;

private slots:
    void enterPressed();
    void numbPressed();
    void menu();

};
#endif // MAINWINDOW_H
