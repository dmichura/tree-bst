#ifndef BST_CPP
#define BST_CPP

#include "BST.h"
#include <iostream>
// Zakladam, ze BST.h zawiera definicje Node oraz deklaracje klasy BST
// np. #include <fstream> dla ifstream/ofstream
// using namespace std; jest juz ponizej

using namespace std;

/**
 * @brief Konstruktor domyslny.
 * * Inicjalizuje puste drzewo, ustawiajac korzen (root) na nullptr.
 */
BST::BST() : root(nullptr) {}

/**
 * @brief Destruktor.
 * * @note W biezacej implementacji jest pusty. 
 * Poprawny destruktor powinien wywolac clear() do zwolnienia pamieci.
 * np. BST::~BST() { clear(); }
 */
BST::~BST() {
}

/**
 * @brief Rekursywny pomocnik do usuwania wszystkich wezlow drzewa.
 * * Przechodzi przez drzewo w kolejnosci post-order i usuwa kazdy wezel.
 * * @param node Wskaznik na biezacy wezel do przetworzenia.
 */
void BST::clearRecursive(Node* node) {
    if (node == nullptr) {
        return;
    }
    clearRecursive(node->left);
    clearRecursive(node->right);
    delete node;
}

/**
 * @brief Usuwa wszystkie wezly z drzewa.
 * * Po wykonaniu tej metody drzewo staje sie puste (root = nullptr).
 */
void BST::clear() {
    clearRecursive(root);
    root = nullptr;
}

/**
 * @brief Sprawdza, czy drzewo jest puste.
 * * @return true jesli drzewo jest puste (root == nullptr), false w przeciwnym razie.
 */
bool BST::isEmpty() {
    return root == nullptr;
}

/**
 * @brief Publiczna metoda usuwajaca wezel o podanej wartosci.
 * * Rozpoczyna rekursywne usuwanie od korzenia.
 * * @param value Wartosc do usuniecia z drzewa.
 */
void BST::remove(int value) {
    if (root == nullptr) {
        cout << "Drzewo jest puste. Nie mozna usunac\n";
        return;
    }
    root = removeRecursive(root, value);
}

/**
 * @brief Rekursywny pomocnik do usuwania wezla o podanej wartosci.
 * * Przeszukuje drzewo w poszukiwaniu wartosci i usuwa ja,
 * zachowujac wlasnosci drzewa BST.
 * * @param node Wskaznik na korzen poddrzewa, z ktorego usuwamy.
 * @param value Wartosc do usuniecia.
 * @return Wskaznik na korzen zmodyfikowanego poddrzewa.
 */
Node* BST::removeRecursive(Node* node, int value) {

    if (node == nullptr) {
        cout << "Element " << value << " nie istnieje w drzewie\n";
        return nullptr;
    }

    // Szukanie wezla
    if (value < node->data) {
        node->left = removeRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = removeRecursive(node->right, value);
    } 
    // Znaleziono wezel
    else {
        // Przypadek 1: Lisc (brak dzieci)
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            cout << "Usunieto lisc " << value << ".\n";
            return nullptr;
        }
        
        // Przypadek 2: Jedno dziecko
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            cout << "Usunieto " << value << " (mial jedno dziecko).\n";
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            cout << "Usunieto " << value << " (mial jedno dziecko).\n";
            return temp;
        }

        // Przypadek 3: Dwoje dzieci
        // Znajdz nastepnika (najmniejszy element w prawym poddrzewie)
        Node* successor = findMin(node->right);
        // Skopiuj wartosc nastepnika do biezacego wezla
        node->data = successor->data;
        cout << "Usunieto " << value << " (mial dwoje dzieci, zastapiono przez " << successor->data << ").\n";
        // Usun nastepnika z prawego poddrzewa
        node->right = removeRecursive(node->right, successor->data);
    }
    return node;
}

/**
 * @brief Znajduje wezel o minimalnej wartosci w danym poddrzewie.
 * * Przechodzi w lewo tak daleko, jak to mozliwe.
 * * @param node Wskaznik na korzen poddrzewa do przeszukania.
 * @return Wskaznik na wezel o minimalnej wartosci.
 */
Node* BST::findMin(Node* node) {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/**
 * @brief Publiczna metoda dodajaca nowa wartosc do drzewa.
 * * Rozpoczyna rekursywne dodawanie od korzenia.
 * * @param value Wartosc do dodania.
 */
void BST::add(int value) {
    root = addRecursive(root, value);
}

/**
 * @brief Rekursywny pomocnik do dodawania nowej wartosci.
 * * Znajduje odpowiednie miejsce w drzewie i wstawia nowy wezel,
 * zachowujac wlasnosci drzewa BST.
 * * @param node Wskaznik na korzen poddrzewa, do ktorego wstawiamy.
 * @param value Wartosc do wstawienia.
 * @return Wskaznik na korzen zmodyfikowanego poddrzewa.
 */
Node* BST::addRecursive(Node* node, int value) {
    // Znaleziono miejsce do wstawienia
    if (node == nullptr) {
        return new Node(value);
    }

    // Szukanie miejsca
    if (value < node->data) {
        node->left = addRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = addRecursive(node->right, value);
    }
    // Wartosc juz istnieje (w tej implementacji nic nie robimy)

    return node;
}

/**
 * @brief Wczytuje drzewo z pliku binarnego.
 * * Drzewo jest czyszczone przed wczytaniem. Dane sa czytane 
 * jako sekwencja wartosci typu int i dodawane do drzewa.
 * * @param filename Nazwa pliku do odczytu.
 */
void BST::loadFromFile(const string& filename) {

    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << filename << " do odczytu\n";
        return;
    }

    clear(); // Czyscimy istniejace drzewo
    int value;
    
    // Odczytuj wartosci int az do konca pliku
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        add(value);
    }

    if (inFile.eof()) {
        cout << "Pomyslnie wczytano drzewo z pliku " << filename << "\n";
    } else if (inFile.fail()) {
        // Blad mogl wystapic jesli plik nie konczyl sie dokladnie na granicy int-a
        cout << "Blad podczas odczytu danych z pliku (niepoprawny format?)\n";
    }
    
    inFile.close();
}

/**
 * @brief Rekursywny pomocnik do zapisu drzewa do pliku (pre-order).
 * * Zapisuje wartosc biezacego wezla, nastepnie rekursywnie
 * lewe i prawe poddrzewo.
 * * @param node Biezacy wezel do zapisu.
 * @param outFile Strumien pliku wyjsciowego (binarny).
 */
void BST::saveRecursive(Node* node, ofstream& outFile) {
    if (node == nullptr) {
        return;
    }
    
    // Zapisujemy wartosc biezacego wezla (Pre-order)
    outFile.write(reinterpret_cast<const char*>(&node->data), sizeof(int));
    
    saveRecursive(node->left, outFile);
    saveRecursive(node->right, outFile);
}

/**
 * @brief Zapisuje drzewo do pliku binarnego.
 * * Uzywa kolejnosci pre-order do zapisu, co pozwala na 
 * odtworzenie tej samej struktury drzewa przy ponownym wczytaniu.
 * * @param filename Nazwa pliku do zapisu.
 */
void BST::saveToFile(const string& filename) {
    ofstream outFile(filename, ios::binary); 
    if (!outFile.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << filename << " do zapisu\n";
        return;
    }

    if (isEmpty()) {
        cout << "Drzewo jest puste. Zapisano pusty plik\n";
        outFile.close();
        return;
    }

    saveRecursive(root, outFile);
    outFile.close();
    cout << "Drzewo zostalo zapisane binarnie do pliku " << filename << "\n";
}

/**
 * @brief Wyswietla zawartosc drzewa w kolejnosci in-order (LKP).
 */
void BST::displayInorder() {
    cout << "In-order (LKP):  ";
    if (isEmpty()) cout << "[PUSTE]";
    inorderRecursive(root);
    cout << "\n";
}

/**
 * @brief Rekursywny pomocnik do wyswietlania in-order (LKP).
 * * @param node Biezacy wezel do przetworzenia.
 */
void BST::inorderRecursive(Node* node) {
    if (node == nullptr) return;
    inorderRecursive(node->left);
    cout << node->data << " ";
    inorderRecursive(node->right);
}

/**
 * @brief Wyswietla zawartosc drzewa w kolejnosci pre-order (KLP).
 */
void BST::displayPreorder() {
    cout << "Pre-order (KLP): ";
    if (isEmpty()) cout << "[PUSTE]";
    preorderRecursive(root);
    cout << "\n";
}

/**
 * @brief Rekursywny pomocnik do wyswietlania pre-order (KLP).
 * * @param node Biezacy wezel do przetworzenia.
 */
void BST::preorderRecursive(Node* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

/**
 * @brief Wyswietla zawartosc drzewa w kolejnosci post-order (LPK).
 */
void BST::displayPostorder() {
    cout << "Post-order (LPK):";
    if (isEmpty()) cout << "[PUSTE]";
    postorderRecursive(root);
    cout << "\n";
}

/**
 * @brief Rekursywny pomocnik do wyswietlania post-order (LPK).
 * * @param node Biezacy wezel do przetworzenia.
 */
void BST::postorderRecursive(Node* node) {
    if (node == nullptr) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    cout << node->data << " ";
}

/**
 * @brief Wyswietla graficzna (tekstowa) reprezentacje drzewa.
 * * Drzewo jest obrocone o 90 stopni w lewo (korzen po lewej, 
 * prawe dziecko u gory, lewe na dole).
 */
void BST::displayGraphical() {
    cout << "Graficzna reprezentacja drzewa:\n";
    cout << "------------------------------------------------------\n";
    if (isEmpty()) {
        cout << "[DRZEWO PUSTE]\n";
    } else {
        // Rozpoczynamy z korzeniem (isRoot = true)
        displayGraphicalRecursive(root, "", false, true);
    }
    cout << "------------------------------------------------------\n";
}

/**
 * @brief Rekursywny pomocnik do wyswietlania graficznej reprezentacji.
 * * Uzywa "odwroconego" przejscia in-order (PKL), aby wydrukowac
 * drzewo od prawej do lewej.
 * * @param node Biezacy wezel do wyswietlenia.
 * @param prefix Prefiks (wciecie i linie) do wydrukowania przed wezlem.
 * @param isLeft Informacja, czy biezacy wezel jest lewym dzieckiem.
 * @param isRoot Informacja, czy biezacy wezel jest korzeniem calego drzewa.
 */
void BST::displayGraphicalRecursive(Node* node, const string& prefix, bool isLeft, bool isRoot) {
    if (node == nullptr) {
        return;
    }

    // Najpierw prawe dziecko (bedzie na gorze)
    displayGraphicalRecursive(node->right, prefix + (isLeft ? "|   " : "    "), false, false);

    // Drukuj biezacy wezel
    cout << prefix;
    if (isRoot) {
        cout << "K-- "; // Korzen
    } else {
        cout << (isLeft ? "L-- " : "R-- "); // Lewe lub Prawe
    }
    cout << node->data << "\n";

    // Na koniec lewe dziecko (bedzie na dole)
    displayGraphicalRecursive(node->left, prefix + (isLeft ? "    " : "|   "), true, false);
}

#endif