# Algorytmy grafowe

W plikach `bst.c`, `graph.c`,`adjacency_matrix.h` oraz `edge_list.h` znajdują się linie `TODO` do uzupełnienia.

# Krótkie omówienie kodu

## `bst.c`

- Kod zawiera gotową implementację drzewa BST zawierającą dodawanie elementów oraz niepełny szkielet funkcji umożliwiających przegląd drzewa w porządku pre-, in- oraz post-order
- W katalogu `data/` znajdują się zestawy danych wejściowych do generowania drzew oraz prawidłowe wyniki przechodzenia przez nie w każdym z porządków
- Funkcja `main()` w pliku `bst.c` akceptuje dowolną listę plików i należy uruchamiając program podawać ścieżki do plików `data/*.txt` np.:

  ```
  ./bst data/10.txt
  ./bst data/*.txt
  ```
- Dla każdego argumentu wejściowego, program utworzy BST i zacznie przechodzić przez nie w każdym z porządków przy okazji sprawdzając czy wynik takiego przejścia zgodny jest z oczekiwanym
- Prawidłowe zakończenie programu `./bst` wypisze linie `pre-order`, `in-order` i `post-order` bez żadnego błędu

## `fifo.h`

- Jest to gotowa implementacja kolejki typu FIFO jednorazowego użytku (działa dla `n` elementów, po ich dodaniu i usunięciu lista nie resetuje się tylko trzeba tworzyć nową)
- Kolejka FIFO, czyli first-in-first-out pozwala na dodawanie elementów jak do listy, ale definiuje również operację pobierania elementu, a pobieranie to odbywa się w kolejności dodawania
- Ta struktura danych potrzebna jest do implementacji algorytmu BFS
- Aby skorzystać z kolejki FIFO, należy:
  - Stworzyć kolejkę:

    ```c
    struct fifo *fifo_create(int);
    ```
  - Dodawać do niej elementy:

    ```c
    void fifo_enqueue(struct fifo *, int);
    ```
  - Pobierać z niej elementy:

    ```c
    int fifo_dequeue(struct fifo *);
    ```

  - Sprawdzać czy kolejka jest pusta:

    ```c
    bool fifo_is_empty(struct fifo *);
    ```

  - Na koniec zwolnić zasoby:

    ```c
    void fifo_destroy(struct fifo *);
    ```

## `graph.c`, `adjacency_matrix.h` i `edge_list.h`

- Pliki `adjacency_matrix.h` oraz `edge_lists.h` zawierają implementację grafu jako kolejno macierz sąsiedztwa oraz listy krawędzi
- Oba pliki nieco inaczej definiują typ `struct graph`, ale poza tym oferują spójny interfejs tzn. funkcje o takich samych nazwach, które trzeba zaimplementować:
  - `struct graph *graph_create(size_t)`: funkcja ma stworzyć obiekt opisujący graf w danej implementacji o podanej liczbie wierzchołków
  - `void graph_destroy(struct graph*)`: funkcja ma zwolnić zasoby zajmowane przez graf
  - `void graph_add_edge(struct graph *, int, int)`: dodawanie krawędzi do grafu
  - `bool graph_has_edge(struct graph *, int, int)`: sprawdzenie czy krawędź w grafie istnieje
  - `void dfs(struct graph *, int, int*)`: przejście przez graf metodą DFS
  - `void bfs(struct graph *, int*)`: przejście przez graf metodą BFS
- Plik `graph.c` warunkowo używa albo macierzy sąsiedztwa albo list krawędzi:
  - `Makefile` tworzy oba pliki wykonywalne `adjacency_matrix` oraz `edge_list`, więc można budować projekt uruchamiając po prostu `make`
  - Ewentualnie można kompilować plik `graph.c` z flagą `-DADJ_MATRIX` lub z flagą `-DEDGE_LIST` by wybrać implementację grafu
  - Można też w pliku `graph.c` przed linią nr 9 dodać `#define ADJ_MATRIX` lub `#define EDGE_LIST` by wybrać implementację bez zmiany flag kompilatora
- W pliku `graph.c` znajduje się implementacja dwóch pomocniczych funkcji:
  - `graph_fill_edges` wypełnia graf do zadanej gęstości w sposób losowy, ale gwarantujący spójność grafu (tzn. że od każdego wierzchołka da się ostatecznie dostać do każdego innego wierzchołka). Funkcja ta wykorzystuje `graph_add_edge` i `graph_has_edge`, więc muszą być one poprawnie zaimplementowane w plikach `adjacency_matrix.h` i `edge_list.h`
  - `graph_check` sprawdza czy graf jest nieskierowany i czy posiada prawidłową liczbę krawędzi
- Funkcja `main` w pliku `graph.c`:
  - Dla każdej gęstości grafu ze zbioru 12.5%, 37.5%, 50%, 62.5%, 87.5%:
    - Dla każdej liczby wierzchołków ze zbioru `ns`: (należy to dobrać odpowiednio!)
      - Tworzy graf w bieżącej implementacji
      - Wypełnia go krawędziami
      - Sprawdza czy graf jest prawidłowy
      - Przechodzi graf z wykorzystaniem DFS
      - Przechodzi graf z wykorzystaniem BFS

# Zadania

- [2 pkt] Zaimplementuj funkcje `graph_create` i `graph_destroy` dla obu reprezentacji grafu
- [2 pkt] Zaimplementuj funkcje `graph_add_edge` i `graph_has_edge` dla obu reprezentacji grafu
- [2 pkt] Zaimplementuj funkcję `dfs` dla obu reprezentacji grafu
- [2 pkt] Zaimplementuj funkcję `bfs` dla obu reprezentacji grafu
