# Implementacja drzewa BST w języku C++ 

Ten projekt to implementacja struktury danych **Binarnego Drzewa Przeszukań (BST)** w języku C++. Aplikacja jest programem konsolowym, który pozwala na wykonywanie podstawowych operacji na drzewie, takich jak dodawanie, usuwanie, wyświetlanie oraz zapisywanie i wczytywanie stanu drzewa z pliku binarnego

## Funkcjonalności

* **Dodawanie elementów**: Wstawianie nowych wartości do drzewa.
* **Usuwanie elementów**: Wyszukiwanie i usuwanie podanej wartości.
* **Wyświetlanie drzewa**:
    * Graficzna reprezentacja struktury drzewa w konsoli.
    * Wyświetlanie pre-order (KLP).
    * Wyświetlanie in-order (LKP - daje posortowaną listę).
    * Wyświetlanie post-order (LPK).
* **Zarządzanie drzewem**: Opcja usunięcia wszystkich elementów (wyczyszczenia drzewa).
* **Trwałość danych**:
    * Zapisywanie aktualnej struktury drzewa do pliku binarnego.
    * Wczytywanie struktury drzewa z pliku binarnego.

## Wymagania
- Kompilator C++ **g++**
- Doxygen (Opcjonalnie)
## Kompilacja i Uruchomienie (Deployment)

1.  **Sklonuj repozytorium:**
    ```sh
    git clone https://github.com/dmichura/tree-bst.git
    ```
2. **Przejdź do katalogu projektu:**
    ```sh
    cd tree-bst
    ```
3.  **Skompiluj program:**
    * **Dla Linux / macOS (run.sh):**
        ```sh
        ./run.sh
        ```
    * **Dla Windows (run.bat):**
        ```bat
        ./run.bat
        ```

4. **Generowanie doxygen (Opcjonalnie)**
    * Wygeneruj doxygena
        ```sh
        doxygen
        ```
    * Stwórz pdf z latexa
        ```sh
        cd docs/latex && make
        ```


## Autorzy

* Dominik Jonik - [dominikJon](https://github.com/dominikJon)
* Sebastian Tatara - [xSebix10](https://github.com/xSebix10)
* Dawid Michura - [dmichura](https://github.com/dmichura)