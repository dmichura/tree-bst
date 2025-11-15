#ifndef BST_H
#define BST_H

#include <string>
#include <fstream>

using namespace std;

/**
 * @struct Node
 * @brief Reprezentuje pojedynczy wezel w drzewie BST.
 * * Przechowuje wartosc (data) oraz wskazniki na lewe i prawe dziecko.
 */
struct Node {
    int data; //!< Wartosc przechowywana w wezle.
    Node* left; //!< Wskaznik na lewe dziecko.
    Node* right; //!< Wskaznik na prawe dziecko.
    
    /**
     * @brief Konstruktor wezla.
     * @param value Wartosc do przechowania w nowym wezle.
     */
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

/**
 * @class BST
 * @brief Implementuje binarne drzewo poszukiwan (BST).
 * * Zapewnia operacje dodawania, usuwania, wyswietlania oraz zapisu/odczytu z pliku.
 */
class BST {
private:
    Node* root; //!< Wskaznik na korzen drzewa.

    // --- Prywatne metody pomocnicze ---
    // Pelna dokumentacja znajduje sie w pliku implementacji (.cpp)

    //! Prywatny pomocnik rekursywny do usuwania.
    Node* removeRecursive(Node* node, int value);
    
    //! Prywatny pomocnik do znajdowania minimum w poddrzewie.
    Node* findMin(Node* node);
    
    //! Prywatny pomocnik rekursywny do dodawania.
    Node* addRecursive(Node* node, int value);
    
    //! Prywatny pomocnik rekursywny do zapisu do pliku (pre-order).
    void saveRecursive(Node* node, ofstream& outFile);
    
    //! Prywatny pomocnik rekursywny do czyszczenia drzewa.
    void clearRecursive(Node* node);

    //! Prywatny pomocnik rekursywny do wyswietlania in-order.
    void inorderRecursive(Node* node);
    
    //! Prywatny pomocnik rekursywny do wyswietlania pre-order.
    void preorderRecursive(Node* node);
    
    //! Prywatny pomocnik rekursywny do wyswietlania post-order.
    void postorderRecursive(Node* node);
    
    //! Prywatny pomocnik rekursywny do wyswietlania graficznego.
    void displayGraphicalRecursive(Node* node, const string& prefix, bool isLeft, bool isRoot);

public:
    /** @brief Konstruktor domyslny. */
    BST();
    
    /** @brief Destruktor. */
    ~BST();

    /** @brief Usuwa wszystkie wezly z drzewa. */
    void clear();
    
    /** * @brief Sprawdza, czy drzewo jest puste. 
     * @return true jesli puste, false w przeciwnym razie. 
     */
    bool isEmpty();

    /** * @brief Dodaje nowa wartosc do drzewa. 
     * @param value Wartosc do dodania. 
     */
    void add(int value); 
    
    /** * @brief Usuwa wezel o podanej wartosci. 
     * @param value Wartosc do usuniecia. 
     */
    void remove(int value); 

    /** @brief Wyswietla drzewo w kolejnosci in-order (LKP). */
    void displayInorder();
    
    /** @brief Wyswietla drzewo w kolejnosci pre-order (KLP). */
    void displayPreorder();
    
    /** @brief Wyswietla drzewo w kolejnosci post-order (LPK). */
    void displayPostorder();
    
    /** @brief Wyswietla graficzna (tekstowa) reprezentacje drzewa. */
    void displayGraphical();

    /** * @brief Zapisuje drzewo binarnie do pliku (pre-order). 
     * @param filename Nazwa pliku wyjsciowego. 
     */
    void saveToFile(const string& filename);
    
    /** * @brief Wczytuje drzewo z pliku binarnego. 
     * @param filename Nazwa pliku wejsciowego. 
     */
    void loadFromFile(const string& filename);

};

#endif