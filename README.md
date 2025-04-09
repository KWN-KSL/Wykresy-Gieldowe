# 📊 Wykresy Giełdowe — Świece Japońskie 📊
Program generujący wykresy świecowe (tzw. świece japońskie) na podstawie danych giełdowych z plików .csv. Projekt wykonany w języku C++ w ramach zajęć akademickich na 1. semestrze studiów.
## 🖼️ Zrzuty ekranu
## 🧭 Menu programu
## 📈 Przykładowy wykres świecowy
## 📌 Zasady działania programu
* Program odczytuje dane giełdowe (data, open, high, low, close) z pliku .csv.
* Na ich podstawie tworzy wykres świecowy zapisany do pliku .txt, z wykorzystaniem grafiki tekstowej.
## 🔍 Legenda świecy:
## Ciało białe (Open < Close) → O
## Ciało czarne (Open > Close) → #
## Cienie świecy (góra/dół) → |
Przykladowy format danych:
🗃️ Format danych wejściowych (.csv)
Date,Open,High,Low,Close,Volume
2023-11-27,43.65,44.545,43.65,44.08,33339937
2023-11-28,43.69,44.08,43.66,44.02,1967329
