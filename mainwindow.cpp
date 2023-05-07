#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++){
                QString butName = "button" + QString::number(i);
                numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
                connect(numButtons[i], SIGNAL(released()), this,SLOT(numbPressed()));
        }
    connect(ui->enter, SIGNAL(released()), this,SLOT(enterPressed()));

    ui->screen1->setPlainText("Wpisz ilu klientow chcesz wczytac: ");

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::numbPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    ui->screen1->setPlainText(butVal);
}

void MainWindow::enterPressed(){
    if(scena1==false){
        ui->screen2->clear();
        QString qChoice = ui->screen1->toPlainText();
        int intChoice = qChoice.toInt();

        ui->screen1->clear();
        ifstream base;
        base.open(path);
        string line;
        for (int i=0;i<intChoice;i++) {
            getline(base, line);
            char* text = &line[0];

            imie = strtok(text, " ");
            nazwisko = strtok(NULL, " ");
            rok = stoi(strtok(NULL, " "));
            nrKonta = strtok(NULL, " ");
            nazwaBanku = strtok(NULL, " ");
            kwota = stod(strtok(NULL, " "));

            KlientBanku* klient = new KlientBanku(imie, nazwisko, rok, nrKonta, nazwaBanku, kwota);
            baza.emplace_back(klient);
            nowaLiczbaKlientow++;


            QString qimie = QString::fromStdString(imie);
            ui->screen2->insertPlainText(qimie+"\n");
            QString qnazwisko = QString::fromStdString(nazwisko);
            ui->screen2->insertPlainText(qnazwisko+"\n");
            QString qrok = QString::number(rok);
            ui->screen2->insertPlainText(qrok+"\n");
            QString qnrKonta = QString::fromStdString(nrKonta);
            ui->screen2->insertPlainText(qnrKonta+"\n");
            QString qnazwaBanku = QString::fromStdString(nazwaBanku);
            ui->screen2->insertPlainText(qnazwaBanku+"\n");
            QString qkwota = QString::number(kwota);
            ui->screen2->insertPlainText(qkwota+"\n\n");
        }
        base.close();
        scena1 = true;
        menu();
    } else if (scena1==true && zmianaKwoty==false && exist==false && zmienKwote==false && drukowanie==false && modyfikacja==false && modyfikacja2==false){
        ui->screen2->clear();
        QString qChoice = ui->screen1->toPlainText();
        int intChoice = qChoice.toInt();
        switch(intChoice){
        case 1:
            for (int i = 0; i < nowaLiczbaKlientow; i++) {
                drukujKlientBanku(baza[i]);
            }
            menu();
            break;
        case 2:
            for(int i=0;i<nowaLiczbaKlientow;i++){
                obecnaWKwota = baza[i]->kwota;
                if (obecnaWKwota>najwKwota){
                    najwKwota=obecnaWKwota;
                }
            }
            for(int i=0;i<nowaLiczbaKlientow;i++){
                if(najwKwota<=baza[i]->kwota)
                    drukujKlientBanku(baza[i]);
            }

            menu();
            break;
        case 3:
            for(int i=0;i<nowaLiczbaKlientow;i++){
                obecnaNKwota = baza[i]->kwota;
                if(obecnaNKwota<najnKwota){
                    najnKwota=obecnaNKwota;
                }
            }
            for(int i=0;i<nowaLiczbaKlientow;i++){
                if(najnKwota>=baza[i]->kwota){
                    drukujKlientBanku(baza[i]);
                }
            }

            menu();
            break;

        case 4:
            ui->screen1->clear();
            ui->screen2->setPlainText("Podaj, na pierwszym ekranie, numer konta ktorego stan konta chcesz zmienic");
            zmianaKwoty = true;

            break;

        case 5:
            ui->screen1->clear();
            ui->screen2->setPlainText("Podaj, na pierwszym ekranie, numer konta klienta ktorego chcesz wydrukowac.");
            drukowanie=true;

            break;

        case 6:
            ui->screen1->clear();
            ui->screen2->setPlainText("Podaj, na pierwszym ekranie, numer konta klienta ktorego chcesz zmodyfikowac");
            modyfikacja=true;

            break;

        case 7:
            qApp->quit();
            break;

        default:
            ui->screen2->setPlainText("Podaj prawidlowa wartosc!");
            menu();
            break;
        }

    } else if(zmianaKwoty==true){
        QString displayVal = ui->screen1->toPlainText();
        nowyNrKonta = displayVal.toStdString();
        for (int i=0;i<nowaLiczbaKlientow;i++){
            if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                exist = true;
                zmianaKwoty=false;
            }
        }
        if(exist==true){
            ui->screen1->clear();
            ui->screen2->setPlainText("Podaj na pierwszym ekranie kwote jaka chcesz dodac.");
            zmienKwote=true;
            exist=false;
        } else{
            ui->screen2->setPlainText("Podany numer konta nie istnieje.");
            zmianaKwoty=false;
            menu();
        }
    } else if(zmienKwote==true){
        QString displayVal = ui->screen1->toPlainText();
        nowaKwota = displayVal.toDouble();
        ui->screen1->clear();
        ui->screen2->clear();
        for (int i=0;i<nowaLiczbaKlientow;i++){
            if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                baza[i]->kwota=baza[i]->kwota+nowaKwota;
                drukujKlientBanku(baza[i]);
            }
        }
        zmienKwote=false;
        menu();
    } else if(drukowanie==true){
        ui->screen2->clear();
        QString displayVal = ui->screen1->toPlainText();
        nowyNrKonta = displayVal.toStdString();
        for(int i=0;i<nowaLiczbaKlientow;i++){
            if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                drukujKlientBanku(baza[i]);
            }
        }
        drukowanie=false;
        menu();

    } else if(modyfikacja==true){
        ui->screen2->clear();
        QString displayVal = ui->screen1->toPlainText();
        nowyNrKonta = displayVal.toStdString();
        for(int i=0;i<nowaLiczbaKlientow;i++){
            if(nowyNrKonta.compare(baza[i]->nrKonta)==0){
                exist2=true;
                wklient=i;
            }
        }
        if(exist2==true){
            modyfikacja=false;
            modyfikacja2=true;
            ui->screen2->setPlainText("Prosze wcisnac enter jeszcze raz.");
        } else {
            ui->screen2->setPlainText("Podano zly numer konta.");
            modyfikacja=false;
            menu();
        }

    } else if(modyfikacja2==true){
        modyfikacjaKlienta(baza[wklient]);
        stage++;
    }
}

KlientBanku::KlientBanku(const string& im, const string& naz, const int r, const string& nr, const string& nazwa, const double kw)
{
    imie = im;
    nazwisko = naz;
    rok = r;
    nrKonta = nr;
    nazwaBanku = nazwa;
    kwota = kw;
}
void MainWindow::menu(){
    ui->screen1->setPlainText("1.Wyswietl wszystkich\n2.Pokaz najbogatszego\n3.Pokaz najbiedniejszego\n4.Modyfikuj kwote\n5.Drukuj klienta\n6.Modyfikuj klienta\n7.Zakoncz program\nWybierz co chcesz zrobic:");
}


void MainWindow::drukujKlientBanku(KlientBanku *klient) const
{
    QString qimie = QString::fromStdString(klient->imie);
    ui->screen2->insertPlainText(qimie+"\n");
    QString qnazwisko = QString::fromStdString(klient->nazwisko);
    ui->screen2->insertPlainText(qnazwisko+"\n");
    QString qrok = QString::number(klient->rok);
    ui->screen2->insertPlainText(qrok+"\n");
    QString qnrKonta = QString::fromStdString(klient->nrKonta);
    ui->screen2->insertPlainText(qnrKonta+"\n");
    QString qnazwaBanku = QString::fromStdString(klient->nazwaBanku);
    ui->screen2->insertPlainText(qnazwaBanku+"\n");
    QString qkwota = QString::number(klient->kwota);
    ui->screen2->insertPlainText(qkwota+"\n\n");
}


void MainWindow::modyfikacjaKlienta(KlientBanku *klient)
{
    switch(stage){
    case 0:
        ui->screen1->clear();
        ui->screen2->setPlainText("Nowe imie.(pierwszy ekran).");
        break;
    case 1:{
        QString displayVal = ui->screen1->toPlainText();
        ui->screen1->clear();
        schowek = displayVal.toStdString();
        klient->imie=schowek;
        ui->screen2->setPlainText("Nowe nazwisko. (pierwszy ekran)");
        break;
    }
    case 2: {
        QString displayVal = ui->screen1->toPlainText();
        ui->screen1->clear();
        schowek = displayVal.toStdString();
        klient->nazwisko=schowek;
        ui->screen2->setPlainText("Nowe rok urodzenia. (pierwszy ekran)");
        break;
    }
    case 3: {
        QString displayVal = ui->screen1->toPlainText();
        ui->screen1->clear();
        schowek1 = displayVal.toInt();
        klient->rok=schowek1;
        ui->screen2->setPlainText("Nowy numer konta. (pierwszy ekran)");
        break;
    }
    case 4: {
        QString displayVal = ui->screen1->toPlainText();
        ui->screen1->clear();
        schowek = displayVal.toStdString();
        klient->nrKonta=schowek;
        ui->screen2->setPlainText("Nowy bank. (pierwszy ekran)");
        break;
    }
    case 5: {
        QString displayVal = ui->screen1->toPlainText();
        ui->screen1->clear();
        schowek = displayVal.toStdString();
        klient->nazwaBanku=schowek;
        ui->screen2->setPlainText("Nowa kwota. (pierwszy ekran)");
        break;
    }
    case 6: {
        QString displayVal = ui->screen1->toPlainText();
        ui->screen1->clear();
        schowek3 = displayVal.toDouble();
        klient->kwota=schowek3;
        stage=0;
        modyfikacja2=false;
        ui->screen2->clear();
        menu();
        break;
    }
    }
}










