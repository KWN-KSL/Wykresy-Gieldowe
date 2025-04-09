#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

struct date
{
    int dzien;
    int miesiac;
    int rok;
};

struct swieca
{
    date data;
    float open;
    float close;
    float high;
    float low;
};

struct wysokosciSwiecy
{
    float wysokoscLow;
    float wysokoscHigh;
    float wysokoscOpenClose;
    float odlegloscGora;
    float odlegloscDol;
};

void naglowek(int wysokoscWykresu, char zakresCzasu, date dataPoczatkowa, date dataKoncowa, string plikWejsciowy, string plikWyjsciowy);
void menuDoWykresu();
void ustawianieZakresuDat(date& dataPoczatkowa, date& dataKoncowa, string plikWejsciowy);
bool czyDataIstnieje(string plikWejsciowy, date dataDoSprawdzenia);
int iloscLiniiWPliku(string plikWejsciowy);
void szerokoscWykresu(date dataPoczatkowa, date dataKoncowa, int& iloscSwiec, int& iloscLinii, string plikWejsciowy);
void wypiszWykres(int wysokoscWykresu, date dataPoczatkowa, date dataKoncowa, string plikWejsciowy, string plikWyjsciowy, char zakresCzasu);
wysokosciSwiecy sprawdzanieWysokosciSwiecy(swieca element, float skala, float maxHigh, float minLow);
void rysowanieSwiecy(int wysokoscWykresu, swieca tablicaSwiec[], float skala, float maxHigh, float minLow, int iloscSwiec, string plikWyjsciowy);

int main()
{
    int wysokoscWykresu = 50;
    char zakresCzasu = 'D';
    date dataPoczatkowa = { 0, 0, 0 };
    date dataKoncowa = { 0, 0, 0 };
    char przypadek;
    string plikWejsciowy = "intc_us_data.csv";
    string plikWyjsciowy = "chart.txt";
    naglowek(wysokoscWykresu, zakresCzasu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy);
    while (cin >> przypadek)
    {
        switch (przypadek)
        {
        case 'g':
        case 'G':
            system("cls");
            wypiszWykres(wysokoscWykresu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy, zakresCzasu);
            menuDoWykresu();
            while (cin >> przypadek)
            {
                switch (przypadek)
                {
                case 'z':
                case 'Z':
                    system("cls");
                    main();
                    break;
                case 'q':
                case 'Q':
                    cout << "Program zostal zamkniety!" << endl;
                    exit(0);
                    break;
                case 'g':
                case 'G':
                    system("cls");
                    wypiszWykres(wysokoscWykresu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy, zakresCzasu);
                    menuDoWykresu();
                    break;
                default:
                    cout << "Podano nieprawidlowe dane!" << endl;
                    break;
                }
            }
            break;
        case 'q':
        case 'Q':
            cout << "Program zostal zamkniety!" << endl;
            exit(0);
            break;
        case '1':
            cout << "Podaj sciezke lub nazwe pliku wejsciowego: ";
            cin >> plikWejsciowy;
            dataPoczatkowa = { 0, 0, 0 };
            dataKoncowa = { 0, 0, 0 };
            system("cls");
            naglowek(wysokoscWykresu, zakresCzasu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy);
            break;
        case '2':
            cout << "Podaj sciezke lub nazwe pliku wyjsciowego (bez rozszerzenia '.txt'): ";
            cin >> plikWyjsciowy;
            plikWyjsciowy = plikWyjsciowy + ".txt";
            system("cls");
            naglowek(wysokoscWykresu, zakresCzasu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy);
            break;
        case '3':
            cout << "Podaj wysokosc wykresu [10-300]: ";
            cin >> wysokoscWykresu;
            while (!cin.good() or (wysokoscWykresu < 10 or wysokoscWykresu > 300))
            {
                cout << "podano nieprawidlowa wysokosc wykresu!" << endl << "podaj wysokosc wykresu [10-300]: " << endl;
                cin.clear();
                cin.ignore();
                cin >> wysokoscWykresu;
            }
            system("cls");
            naglowek(wysokoscWykresu, zakresCzasu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy);
            break;
        case '4':
            ustawianieZakresuDat(dataPoczatkowa, dataKoncowa, plikWejsciowy);
            system("cls");
            naglowek(wysokoscWykresu, zakresCzasu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy);
            break;
        case '5':
            cout << "Podaj zakres czasu reprezentowanego przez jedna swiece:" << endl;
            cout << "'D' - dzien" << endl;
            cout << "'T' - tydzien (5 dni)" << endl;
            cout << "'M' - miesiac (20 dni)" << endl;
            while (true)
            {
                cin >> zakresCzasu;
                if (zakresCzasu == 'D' or zakresCzasu == 'T' or zakresCzasu == 'M')
                {
                    break;
                }
                cin.clear();
                cin.ignore();
                cout << "Podano nieprawidlowe dane!" << endl;
                cout << "Podaj zakres czasu reprezentowanego przez jedna swiece:" << endl;
            }
            system("cls");
            naglowek(wysokoscWykresu, zakresCzasu, dataPoczatkowa, dataKoncowa, plikWejsciowy, plikWyjsciowy);
            break;
        case 'r':
        case 'R':
            system("cls");
            main();
            break;
        default:
            cout << "Podano nieprawidlowe dane!" << endl;
            break;
        }
    }
    return 0;
}

void naglowek(int wysokoscWykresu, char zakresCzasu, date dataPoczatkowa, date dataKoncowa, string plikWejsciowy, string plikWyjsciowy)
{
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
    cout << "         |**|       |**|  |**|        |**|  |**|  |**|  |*******|     |********|    |********|   |**|        |**|      " << endl;
    cout << "         |**|       |**|   |**|      |**|   |**| |**|   |**  _ **|    |**|         |***|   |**|   |**|      |**|       " << endl;
    cout << "         |**|       |**|    |**|    |**|    |** **|     |** |*| **|   |**|_____   |***|            |**|    |**|        " << endl;
    cout << "         |**|  ___  |**|     |**|  |**|     |***|       |**    **|    |********|    |*****|         |**|  |**|         " << endl;
    cout << "         |**| |***| |**|      |**|**|       |** **|     |*******|     |********|       |*****|        |**|**|          " << endl;
    cout << "         |**||**|**||**|       |***|        |** |**|    |**|  |**|    |**|                 |***|       |***|           " << endl;
    cout << "         |**|**| |**|**|       |***|        |**  |**|   |**|   |**|   |**|_____    |**|   |***|        |***|           " << endl;
    cout << "          |***|   |***|        |***|        |**   |**|  |**|    |**|  |********|    |********|         |***|           " << endl << endl;
    cout << "      |********|    |**|       |**|  |******|  |********|    |*******|    |********|    |**|       |**|  |********|    " << endl;
    cout << "     |***|   |**|   |**|       |**|    |**|    |**|         |**|         |**|    |**|   |**|       |**|  |**|          " << endl;
    cout << "    |***|           |**|       |**|    |**|    |**|_____   |**|         |**|      |**|  |**|       |**|  |**|_____     " << endl;
    cout << "      |*****|       |**|  ___  |**|    |**|    |********|  |**|         |**|      |**|  |**|  ___  |**|  |********|    " << endl;
    cout << "         |*****|    |**| |***| |**|    |**|    |********|  |**|         |**|      |**|  |**| |***| |**|  |********|    " << endl;
    cout << "             |***|  |**||**|**||**|    |**|    |**|        |**|         |**|      |**|  |**||**|**||**|  |**|          " << endl;
    cout << "     |**|   |***|   |**|**| |**|**|    |**|    |**|_____    |**|         |**|    |**|   |**|**| |**|**|  |**|_____     " << endl;
    cout << "      |********|     |***|   |***|   |******|  |********|    |*******|    |********|     |***|   |***|   |********|    " << endl << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
    cout << setw(72) << "Witaj w Wykresach Swiecowych!" << endl;
    cout << setw(89) << "Wykresy Swiecowe zostaly wykonane przez: Kewina Kisiela, ACiR, s197866" << endl << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
    cout << setw(62) << "MENU" << endl << endl;
    cout << "G/g - pobiera dane z pliku csv, generuje wykres i zapisuje do pliku txt" << endl << endl;
    cout << "Q/q - konczy dzialanie programu" << endl << endl; cout << "Z/z - powrot do menu" << endl << endl;
    cout << "1 - wybor pliku wejsciowego (podac plik w pierwszej kolejnosci)" << endl << endl;
    cout << "2 - wybor pliku wyjsciowego" << endl << endl;
    cout << "3 - wybor wysokosci wykresu." << endl << endl;
    cout << "4 - wybor zakresu dat." << endl << endl;
    cout << "5 - wybor zakresu czasowego reprezentowanego przez jedna swiece." << endl << endl;
    cout << "R - przywrocenie wszystkich danych na domyslne" << endl << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
    cout << "Wysokosc wygenerowanego wykresu: " << wysokoscWykresu << endl;
    cout << "Zakres czasu reprezentowanego przez jedna swiece: " << zakresCzasu << endl;
    cout << "Zakres dat wygenerowanego wykresu: ";
    if (dataPoczatkowa.rok != 0 and dataKoncowa.rok != 0)
    {
        cout << "od " << dataPoczatkowa.rok << "-" << dataPoczatkowa.miesiac << "-" << dataPoczatkowa.dzien;
        cout << " do " << dataKoncowa.rok << "-" << dataKoncowa.miesiac << "-" << dataKoncowa.dzien << endl;
    }
    else
    {
        cout << "domyslna (ostatnie 200 dni)" << endl;
    }
    cout << "Plik wejsciowy: " << plikWejsciowy << endl;
    cout << "Plik wyjsciowy: " << plikWyjsciowy << endl;
}

void menuDoWykresu()
{
    cout << "G/g - pobiera dane z pliku csv, generuje wykres i zapisuje do pliku txt" << endl;
    cout << "Q/q - konczy dzialanie programu" << endl;
    cout << "Z/z - powrot do menu" << endl;
}

void ustawianieZakresuDat(date& dataPoczatkowa, date& dataKoncowa, string plikWejsciowy)
{
    cout << "Podaj date poczatku wykresu." << endl;
    cout << "Podaj rok: ";
    cin >> dataPoczatkowa.rok;
    while (dataPoczatkowa.rok < 1900 or dataPoczatkowa.rok>2024)
    {
        cin.clear();
        cin.ignore();
        cout << "Podano nieprawidlowe dane!" << endl;
        cout << "Podaj rok: ";
        cin >> dataPoczatkowa.rok;
    }
    cout << "Podaj miesiac: ";
    cin >> dataPoczatkowa.miesiac;
    while (dataPoczatkowa.miesiac > 12 or dataPoczatkowa.miesiac < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "Podano nieprawidlowe dane!" << endl;
        cout << "Podaj miesiac: ";
        cin >> dataPoczatkowa.miesiac;
    }
    cout << "Podaj dzien: ";
    cin >> dataPoczatkowa.dzien;
    while (dataPoczatkowa.dzien > 31 or dataPoczatkowa.dzien < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "Podano nieprawidlowe dane!" << endl;
        cout << "Podaj dzien: ";
        cin >> dataPoczatkowa.dzien;
    }
    if (!czyDataIstnieje(plikWejsciowy, dataPoczatkowa))
    {
        cout << "Taka data nie istnieje!" << endl;
        cout << "Nacisnij dowolny przycisk i enter aby kontynuowac" << endl;
        string temp;
        cin >> temp;
        system("cls");
        dataPoczatkowa = { 0, 0, 0 };
        return;
    }
    cout << "Podaj date konca wykresu." << endl;
    cout << "Podaj rok: ";
    cin >> dataKoncowa.rok;
    while (dataKoncowa.rok < 2000 or dataKoncowa.rok>2024)
    {
        cin.clear();
        cin.ignore();
        cout << "Podano nieprawidlowe dane!" << endl;
        cout << "Podaj rok: ";
        cin >> dataKoncowa.rok;
    }
    cout << "Podaj miesiac: ";
    cin >> dataKoncowa.miesiac;
    while (dataKoncowa.miesiac > 12 or dataKoncowa.miesiac < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "Podano nieprawidlowe dane!" << endl;
        cout << "Podaj miesiac: ";
        cin >> dataKoncowa.miesiac;
    }
    cout << "Podaj dzien: ";
    cin >> dataKoncowa.dzien;
    while (dataKoncowa.dzien > 31 or dataKoncowa.dzien < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "Podano nieprawidlowe dane!" << endl;
        cout << "Podaj dzien: ";
        cin >> dataKoncowa.dzien;
    }
    bool error = false;
    if (!czyDataIstnieje(plikWejsciowy, dataKoncowa))
    {
        cout << "Taka data nie istnieje!" << endl;
        cout << "Nacisnij dowolny przycisk i enter aby kontynuowac" << endl;
        string temp;
        cin >> temp;
        system("cls");
        dataPoczatkowa = { 0, 0, 0 };
        dataKoncowa = { 0, 0, 0 };
    }
    else if (dataKoncowa.rok < dataPoczatkowa.rok)
    {
        error = true;
    }
    else if (dataKoncowa.rok == dataPoczatkowa.rok and dataKoncowa.miesiac < dataPoczatkowa.miesiac)
    {
        error = true;
    }
    else if (dataKoncowa.rok == dataPoczatkowa.rok and dataKoncowa.miesiac == dataPoczatkowa.miesiac and dataKoncowa.dzien <= dataPoczatkowa.dzien)
    {
        error = true;
    }
    if (error)
    {
        cout << "Data koncowa jest mniejsza lub rowna od daty poczatkowej" << endl;
        cout << "Nacisnij dowolny przycisk i enter aby kontynuowac" << endl;
        string temp;
        cin >> temp;
        system("cls");
        dataPoczatkowa = { 0, 0, 0 };
        dataKoncowa = { 0, 0, 0 };
    }
}

bool czyDataIstnieje(string plikWejsciowy, date dataDoSprawdzenia)
{
    fstream plik;
    plik.open(plikWejsciowy);
    if (!plik.is_open())
    {
        cout << "Blad z otwarciem pliku." << endl;
        return false;
    }
    plik.ignore(256, '\n');
    while (true)
    {
        string dane;
        plik >> dane;
        if (plik.eof() or dane.empty()) break;
        date sprawdzanaData = { 0, 0, 0 };
        sprawdzanaData.rok = atoi(dane.substr(0, 4).c_str());
        sprawdzanaData.miesiac = atoi(dane.substr(5, 7).c_str());
        sprawdzanaData.dzien = atoi(dane.substr(8, 10).c_str());

        if (sprawdzanaData.rok == dataDoSprawdzenia.rok and sprawdzanaData.miesiac == dataDoSprawdzenia.miesiac and sprawdzanaData.dzien == dataDoSprawdzenia.dzien)
        {
            return true;
        }
    }
    return false;
}

int iloscLiniiWPliku(string plikWejsciowy)
{
    int iloscLinii = 0;
    fstream plik;
    plik.open(plikWejsciowy);
    while (!plik.eof())
    {
        string dane;
        plik >> dane;
        if (dane.empty()) break;
        iloscLinii++;
    }
    plik.close();
    return iloscLinii;
}

void szerokoscWykresu(date dataPoczatkowa, date dataKoncowa, int& iloscSwiec, int& iloscLinii, string plikWejsciowy)
{
    fstream plik;
    plik.open(plikWejsciowy);
    int i = 0;
    plik.ignore(256, '\n');
    while (!plik.eof())
    {
        i++;
        string dane;
        plik >> dane;
        if (dane.empty()) break;
        string sprawdzanyString;
        sprawdzanyString = dane.substr(0, dane.find(','));
        date sprawdzanaData = { 0, 0, 0 };
        sprawdzanaData.rok = atoi(sprawdzanyString.substr(0, 4).c_str());
        sprawdzanaData.miesiac = atoi(sprawdzanyString.substr(5, 7).c_str());
        sprawdzanaData.dzien = atoi(sprawdzanyString.substr(8, 10).c_str());

        if (sprawdzanaData.rok == dataPoczatkowa.rok and sprawdzanaData.miesiac == dataPoczatkowa.miesiac and sprawdzanaData.dzien == dataPoczatkowa.dzien)
        {
            iloscLinii = i;
        }
        if (sprawdzanaData.rok == dataKoncowa.rok and sprawdzanaData.miesiac == dataKoncowa.miesiac and sprawdzanaData.dzien == dataKoncowa.dzien)
        {
            iloscSwiec = i - iloscLinii + 1;
            break;
        }
    }
}

void wypiszWykres(int wysokoscWykresu, date dataPoczatkowa, date dataKoncowa, string plikWejsciowy, string plikWyjsciowy, char zakresCzasu)
{
    int iloscSwiec = 0;
    int iloscLinii = 0;
    if (dataPoczatkowa.rok == 0)
    {
        iloscLinii = iloscLiniiWPliku(plikWejsciowy);
        if (iloscLinii >= 200)
        {
            iloscSwiec = 200;
            iloscLinii = iloscLinii - (iloscSwiec + 1);
        }
        else
        {
            iloscSwiec = iloscLinii - 1;
            iloscLinii = 1;
        }
    }
    else
    {
        szerokoscWykresu(dataPoczatkowa, dataKoncowa, iloscSwiec, iloscLinii, plikWejsciowy);
    }
    swieca* tablicaSwiec = new swieca[iloscSwiec];

    fstream plik;
    plik.open(plikWejsciowy);

    if (!plik.is_open())
    {
        string temp;
        cout << "Wystapil problem z odczytaniem pliku" << endl;
        cout << "Nacisnij dowolny przycisk i enter aby kontynuowac";
        cin >> temp;
        main();
    }

    for (int i = 0; i < iloscLinii; i++)
    {
        plik.ignore(256, '\n');
    }

    for (int i = 0; i < iloscSwiec; i++)
    {
        string dane;
        plik >> dane;
        string trescLinii[5];
        for (int i = 0; i < 5; i++)
        {
            trescLinii[i] = dane.substr(0, dane.find(','));
            dane = dane.substr(dane.find(',') + 1);
        }
        tablicaSwiec[i].data.rok = atoi(trescLinii[0].substr(0, 4).c_str());
        tablicaSwiec[i].data.miesiac = atoi(trescLinii[0].substr(5, 7).c_str());
        tablicaSwiec[i].data.dzien = atoi(trescLinii[0].substr(8, 10).c_str());

        tablicaSwiec[i].open = atof(trescLinii[1].c_str());
        tablicaSwiec[i].high = atof(trescLinii[2].c_str());
        tablicaSwiec[i].low = atof(trescLinii[3].c_str());
        tablicaSwiec[i].close = atof(trescLinii[4].c_str());
    }
    float maxHigh = 0;
    for (int i = 0; i < iloscSwiec; i++)
    {
        if (tablicaSwiec[i].high > maxHigh)
        {
            maxHigh = tablicaSwiec[i].high;
        }
    }
    float minLow = tablicaSwiec[0].low;
    for (int i = 1; i < iloscSwiec; i++)
    {
        if (tablicaSwiec[i].low < minLow)
        {
            minLow = tablicaSwiec[i].low;
        }
    }
    float skala = (maxHigh - minLow) / wysokoscWykresu;

    if (zakresCzasu == 'D') rysowanieSwiecy(wysokoscWykresu, tablicaSwiec, skala, maxHigh, minLow, iloscSwiec, plikWyjsciowy);

    if (zakresCzasu == 'T')
    {
        int liczbaTygodni = iloscSwiec / 5;
        if (iloscSwiec % 5 > 0) liczbaTygodni++;
        swieca* tablicaTygodni = new swieca[liczbaTygodni];

        for (int i = 0; i < liczbaTygodni; i++)
        {
            float highTygodnia = tablicaSwiec[i * 5].high;
            float lowTygodnia = tablicaSwiec[i * 5].low;
            for (int j = 1; j < 5; j++)
            {
                if (i * 5 + j >= iloscSwiec)
                {
                    break;
                }
                if (tablicaSwiec[i * 5 + j].high > highTygodnia)
                {
                    highTygodnia = tablicaSwiec[i * 5 + j].high;
                }
                if (tablicaSwiec[i * 5 + j].low < lowTygodnia)
                {
                    lowTygodnia = tablicaSwiec[i * 5 + j].low;
                }
            }
            tablicaTygodni[i].open = tablicaSwiec[i * 5].open;
            if (i * 5 + 4 < iloscSwiec)
            {
                tablicaTygodni[i].close = tablicaSwiec[i * 5 + 4].close;
            }
            else
            {
                tablicaTygodni[i].close = tablicaSwiec[i * 5 + iloscSwiec % 5 - 1].close;
            }
            tablicaTygodni[i].low = lowTygodnia;
            tablicaTygodni[i].high = highTygodnia;
        }
        rysowanieSwiecy(wysokoscWykresu, tablicaTygodni, skala, maxHigh, minLow, liczbaTygodni, plikWyjsciowy);
        delete[] tablicaTygodni;
    }

    if (zakresCzasu == 'M')
    {
        int liczbaMiesiecy = iloscSwiec / 20;
        if (iloscSwiec % 20 > 0) liczbaMiesiecy++;
        swieca* tablicaMiesiecy = new swieca[liczbaMiesiecy];

        for (int i = 0; i < liczbaMiesiecy; i++)
        {
            float highMiesiaca = tablicaSwiec[i * 20].high;
            float lowMiesiaca = tablicaSwiec[i * 20].low;
            for (int j = 1; j < 20; j++)
            {
                if (i * 20 + j >= iloscSwiec)
                {
                    break;
                }
                if (tablicaSwiec[i * 20 + j].high > highMiesiaca)
                {
                    highMiesiaca = tablicaSwiec[i * 20 + j].high;
                }
                if (tablicaSwiec[i * 20 + j].low < lowMiesiaca)
                {
                    lowMiesiaca = tablicaSwiec[i * 20 + j].low;
                }
            }
            tablicaMiesiecy[i].open = tablicaSwiec[i * 20].open;
            if (i * 20 + 19 < iloscSwiec)
            {
                tablicaMiesiecy[i].close = tablicaSwiec[i * 20 + 19].close;
            }
            else
            {
                tablicaMiesiecy[i].close = tablicaSwiec[i * 20 + iloscSwiec % 20 - 1].close;
            }
            tablicaMiesiecy[i].low = lowMiesiaca;
            tablicaMiesiecy[i].high = highMiesiaca;
        }
        rysowanieSwiecy(wysokoscWykresu, tablicaMiesiecy, skala, maxHigh, minLow, liczbaMiesiecy, plikWyjsciowy);
        delete[] tablicaMiesiecy;
    }
    delete[] tablicaSwiec;
    plik.close();
}

wysokosciSwiecy sprawdzanieWysokosciSwiecy(swieca element, float skala, float maxHigh, float minLow)
{
    wysokosciSwiecy wysokosci = { 0, 0, 0, 0, 0 };
    if (element.close > element.open)
    {
        wysokosci.wysokoscLow = (element.open - element.low);
        wysokosci.wysokoscOpenClose = (element.close - element.open);
        wysokosci.wysokoscHigh = (element.high - element.close);
    }
    else
    {
        wysokosci.wysokoscLow = (element.close - element.low);
        wysokosci.wysokoscOpenClose = (element.open - element.close);
        wysokosci.wysokoscHigh = (element.high - element.open);
    }
    wysokosci.odlegloscGora = (maxHigh - element.high) / skala;
    wysokosci.odlegloscDol = (element.low - minLow) / skala;
    return wysokosci;
}

void rysowanieSwiecy(int wysokoscWykresu, swieca tablicaSwiec[], float skala, float maxHigh, float minLow, int iloscSwiec, string plikWyjsciowy)
{
    ofstream plik2;
    plik2.open(plikWyjsciowy);
    for (int i = wysokoscWykresu; i > 0; i--)
    {
        for (int j = 0; j < iloscSwiec; j++)
        {
            wysokosciSwiecy wysokosci = sprawdzanieWysokosciSwiecy(tablicaSwiec[j], skala, maxHigh, minLow);
            float wysokoscSwiecy = (wysokosci.wysokoscHigh + wysokosci.wysokoscOpenClose + wysokosci.wysokoscLow) / skala;
            if (wysokoscWykresu - wysokosci.odlegloscGora >= i and wysokoscWykresu - (wysokosci.odlegloscGora + wysokoscSwiecy) <= i)
            {
                if (i <= ((wysokosci.wysokoscOpenClose + wysokosci.wysokoscLow) / skala + wysokosci.odlegloscDol) and i >= (wysokosci.wysokoscLow / skala + wysokosci.odlegloscDol))
                {
                    if (tablicaSwiec[j].close > tablicaSwiec[j].open)
                    {
                        cout << "O";
                        plik2 << "O";
                    }
                    else
                    {
                        cout << "#";
                        plik2 << "#";
                    }
                }
                else
                {
                    cout << "|";
                    plik2 << "|";
                }
            }
            else
            {
                cout << " ";
                plik2 << " ";
            }
        }
        cout << endl;
        plik2 << endl;
    }
    plik2.close();
}