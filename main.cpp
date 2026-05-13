#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

// Zadanie 1
// Szablon tablicy 1D dla int, z losowaniem w konstruktorze.
template <int NumberOfEl>
class Tablica {
private:
    int Tab[NumberOfEl];

public:
    Tablica() {
        static std::random_device rd;
        thread_local std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 100);

        for (int i = 0; i < NumberOfEl; ++i) {
            Tab[i] = dist(gen);
        }
    }

    int& operator[](int index) {
        if (index < 0 || index >= NumberOfEl) {
            throw std::out_of_range("Index poza zakresem tablicy");
        }
        return Tab[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= NumberOfEl) {
            throw std::out_of_range("Index poza zakresem tablicy");
        }
        return Tab[index];
    }

    int Maksimum() const {
        return *std::max_element(std::begin(Tab), std::end(Tab));
    }

    int Minimum() const {
        return *std::min_element(std::begin(Tab), std::end(Tab));
    }

    void Sortuj() {
        std::sort(std::begin(Tab), std::end(Tab));
    }

    void Wyswietl() const {
        for (int i = 0; i < NumberOfEl; ++i) {
            std::cout << Tab[i] << (i + 1 == NumberOfEl ? '\n' : ' ');
        }
    }
};

// Zadanie 2
// Szablon tablicy 2D dla int.
template <int Rows, int Cols>
class Tablica2D {
private:
    int Tab2D[Rows][Cols];

public:
    Tablica2D() {
        static std::random_device rd;
        thread_local std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 100);

        for (int r = 0; r < Rows; ++r) {
            for (int c = 0; c < Cols; ++c) {
                Tab2D[r][c] = dist(gen);
            }
        }
    }

    int* operator[](int row) {
        if (row < 0 || row >= Rows) {
            throw std::out_of_range("Wiersz poza zakresem tablicy");
        }
        return Tab2D[row];
    }

    const int* operator[](int row) const {
        if (row < 0 || row >= Rows) {
            throw std::out_of_range("Wiersz poza zakresem tablicy");
        }
        return Tab2D[row];
    }

    int Maksimum() const {
        int maksimum = Tab2D[0][0];
        for (int r = 0; r < Rows; ++r) {
            for (int c = 0; c < Cols; ++c) {
                maksimum = std::max(maksimum, Tab2D[r][c]);
            }
        }
        return maksimum;
    }

    int Minimum() const {
        int minimum = Tab2D[0][0];
        for (int r = 0; r < Rows; ++r) {
            for (int c = 0; c < Cols; ++c) {
                minimum = std::min(minimum, Tab2D[r][c]);
            }
        }
        return minimum;
    }

    void Sortuj() {
        std::sort(&Tab2D[0][0], &Tab2D[0][0] + Rows * Cols);
    }

    void Wyswietl() const {
        for (int r = 0; r < Rows; ++r) {
            for (int c = 0; c < Cols; ++c) {
                std::cout << Tab2D[r][c] << (c + 1 == Cols ? '\n' : ' ');
            }
        }
    }
};

// Zadanie 3
class Osoba {
private:
    std::string Imie;
    std::string Nazwisko;

public:
    Osoba() = default;

    Osoba(std::string imie, std::string nazwisko)
        : Imie(std::move(imie)), Nazwisko(std::move(nazwisko)) {}

    bool operator<(const Osoba& other) const {
        if (Nazwisko == other.Nazwisko) {
            return Imie < other.Imie;
        }
        return Nazwisko < other.Nazwisko;
    }

    bool operator>(const Osoba& other) const {
        return other < *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Osoba& osoba) {
        os << osoba.Imie << ' ' << osoba.Nazwisko;
        return os;
    }
};

template <int NumberOfEl, typename Typ>
class TablicaTypowana {
private:
    Typ Tab[NumberOfEl]{};

public:
    TablicaTypowana() = default;

    Typ& operator[](int index) {
        if (index < 0 || index >= NumberOfEl) {
            throw std::out_of_range("Index poza zakresem tablicy");
        }
        return Tab[index];
    }

    const Typ& operator[](int index) const {
        if (index < 0 || index >= NumberOfEl) {
            throw std::out_of_range("Index poza zakresem tablicy");
        }
        return Tab[index];
    }

    const Typ& Maksimum() const {
        return *std::max_element(std::begin(Tab), std::end(Tab));
    }

    const Typ& Minimum() const {
        return *std::min_element(std::begin(Tab), std::end(Tab));
    }

    void Sortuj() {
        std::sort(std::begin(Tab), std::end(Tab));
    }

    void Wyswietl() const {
        for (int i = 0; i < NumberOfEl; ++i) {
            std::cout << Tab[i] << '\n';
        }
    }
};

int main() {
    std::cout << "=== Zadanie 1: Tablica 1D ===\n";
    Tablica<10> T;
    std::cout << "T[9] = " << T[9] << "\n";
    std::cout << "Zawartosc: ";
    T.Wyswietl();
    std::cout << "Minimum: " << T.Minimum() << "\n";
    std::cout << "Maksimum: " << T.Maksimum() << "\n";
    T.Sortuj();
    std::cout << "Po sortowaniu: ";
    T.Wyswietl();

    std::cout << "\n=== Zadanie 2: Tablica 2D ===\n";
    Tablica2D<3, 4> T2D;
    std::cout << "Zawartosc:\n";
    T2D.Wyswietl();
    std::cout << "Minimum: " << T2D.Minimum() << "\n";
    std::cout << "Maksimum: " << T2D.Maksimum() << "\n";
    T2D.Sortuj();
    std::cout << "Po sortowaniu:\n";
    T2D.Wyswietl();

    std::cout << "\n=== Zadanie 3: Osoba + Tablica szablonowa ===\n";
    Osoba osoby[5] = {
        {"Jan", "Nowak"},
        {"Anna", "Kowalska"},
        {"Piotr", "Zielinski"},
        {"Maria", "Adamska"},
        {"Krzysztof", "Baran"}
    };

    TablicaTypowana<5, Osoba> kontener;
    for (int i = 0; i < 5; ++i) {
        kontener[i] = osoby[i];
    }

    std::cout << "Przed sortowaniem:\n";
    kontener.Wyswietl();

    kontener.Sortuj();

    std::cout << "Po sortowaniu:\n";
    kontener.Wyswietl();

    return 0;
}
