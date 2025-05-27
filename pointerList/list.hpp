#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include "listexception.hpp"
#include <iostream>

/**
 * Kétszeresen láncolt lista implementáció
 */

template <class T> /// Jelezzük, hogy ez egy "T" típusú templates osztály lesz
class List
{
private:
    /** A szerkezetet felépítő belső osztály, kívülről nem látszik
     *
     * A láncoláshoz minden elem tartalmaz egy a következőre, és egy az
     * előzőre mutató pointert, valamint magát az adatot.
     */
    struct Node
    {
        T data;     // Azt szeretnénk, hogy az eltárolt érték típusát megadhassuk
        Node *prev; // Az előző elemre mutató pointer
        Node *next; // A következő elemre mutató pointer

        // Konstruktor, ami beállít egy értéket, és lenullázza a mutatókat
        Node(T data0) : data(data0), prev(nullptr), next(nullptr) {}
        // Konstuktor, ami beállítja az értéket, és beállítja a mutatókat
        Node(T data0, Node *prev0, Node *next0)
            : data(data0), prev(prev0), next(next0) {}
    };
    Node *head; // A lista elejére mutató pointer
    Node *tail; // A lista végére mutató pointer
    Node *cur;  // A lista aktuális elemére mutató pointer

public:
    template <class U>
    friend std::ostream &operator<<(std::ostream &, const List<U> &);

    List();

    List(const List<T> &list);
    List &operator=(const List<T> &list);
    ~List();

    /// Az aktuális (cur) elemet befolyásoló metódusok
    /// Nehézkesebb API, mint az iterátor, inkább az javasolt.
    void toFirst();
    void toLast();
    void stepNext();

    void stepPrev();
    T getValue() const;

    void setValue(T e);

    /// A lista állapotát lekérdező metódusok

    // Üres-e a lista?
    bool isEmpty() const;

    // A lista aktuális mutatója az utolsó elemen áll-e?
    bool isLast() const;

    // A lista aktuális mutatója az első helyen áll-e?
    bool isFirst() const;

    // A lista aktuális mutatója mutat-e elemre?
    bool isCurNull() const;

    /// Beszúró metódusok

    // Új T típusú elem hozzáfűzése a lista elejéhez
    void insertFirst(T e);
    void insertLast(T e); // Új T típusú elem hozzáfűzése a lista végéhez

    void insertBefore(T e); // T típusú elem beszúrása az aktuális elem elé
    void insertAfter(T e);  // T típusú elem beszúrása az aktuális elem mögé

    /// Törlő metódusok
    // Az alábbi metódusok érvénytelenné teszik az adott elemre mutató
    // iterátorokat (azokat a továbbiakban használni undefined reference).
    void removeFirst(); // A lista első elemének törlése
    void removeLast();  // A lista utolsó elemének törlése
    void removeCur();   // Az aktuális elem törlése
    void clear();       // A lista törléséhez egy segéd metódus

    /// Kiegészítő eljárás
    void print() const; // kiíratás
    // Nem része a lista adatszerkezetnek, csak nekünk segítség!
};

/// ----- Most következnek a metódus implementációk ----- ///

// Alap konstruktor, üres listát hoz létre
template <class T>
List<T>::List()
{
    head = tail = cur = nullptr; // A mutatókat mind nullptr-ra állítjuk
}

// Másoló konstruktor: Új lista létrehozása egy már meglévő alapján. (klónozás)
// A másoláshoz át kell tenni az elemeket, egy másik memóriaterületre
template <class T>
List<T>::List(const List<T> &list)
{
    head = tail = cur = nullptr; // A mutatókat mind nullptr-ra állítjuk
    // Egy i pointer fut végig az elemeken, amíg a tail után ki nem fut a listából
    for (Node *i = list.head; i != nullptr; i = i->next)
        insertLast(i->data);
    cur = list.cur;
}

// Értékadó operátor: Az eredeti lista elemeit cseréli le
template <class T>
List<T> &List<T>::operator=(const List<T> &list)
{
    // Ha a kapott lista megegyezik az eredetivel, akkor készen vagyunk
    if (&list == this)
    {
        return *this;
    }
    // Egyébként ki kell ürítenünk a már meglévő listánkat, ha nem üres
    if (!isEmpty())
    {
        clear();
    }
    for (Node *i = list.head; i != nullptr; i = i->next)
    {
        insertLast(i->data); // Sorban belemásoljuk az elemeket
    }
    cur = list.cur;
    return *this;
}

// Destructor
template <class T>
List<T>::~List() { clear(); }

// A lista kiürítése
template <class T>
void List<T>::clear()
{
    // Ha üres a lista akkor nincsen dolgunk
    if (isEmpty())
    {
        return;
    }
    for (Node *i = head; i != nullptr;
         /*A ciklus változó inkrementálása nem itt lesz*/)
    {
        Node *tmp = i;
        // Itt inkrementálunk, mivel most még meg van a törlendő elem, rá tudunk
        // lépni a rákövetkezőre
        i = i->next;
        delete tmp;
    }
    head = tail = cur = nullptr;
}

/// Az aktuális (cur) elemet befolyásoló metódusok implementációi
// Az aktuális elemet az elsõ lista elemre állítja
template <class T>
void List<T>::toFirst()
{
    cur = head; // Az aktuális mutasson az első elemre
}

// Az aktuális elemet az utolsó lista elemre állítja
template <class T>
void List<T>::toLast()
{
    cur = tail; // Az aktuálsi mutasson az utolsó elemre
}

// Az aktuális mutatót (ha nem nullptr az értéke) egy elemmel hátrébb állítja
// Vegyük észre, hogy ez az eljárás nullptr-á teheti az cur-ot! (Ha cur = tail
// volt)
template <class T>
void List<T>::stepNext()
{
    if (cur)             // Ha az aktuális mutató érvényes elemre mutat
        cur = cur->next; // akkor az aktuálist egyel hátrább léptetjük
}

// Az aktuális mutatót (ha nem nullptr az értéke) egy elemmel előrébb állítja
// Vegyük észre, hogy ez az eljárás nullptr-á teheti az cur-ot! (Ha cur = head
// volt)
template <class T>
void List<T>::stepPrev()
{
    if (cur)             // Ha az aktuális mutató érvényes elemre mutat
        cur = cur->prev; // akkor az aktuálist egyel előrébb léptetjük
}

// Visszaadja az aktuális elem értékét
template <class T>
T List<T>::getValue() const
{
    if (isEmpty())                   // Ha üres a lista
        throw(UnderFlowException()); // akkor egy UnderFlowException-t dobunk
    if (!cur)                        // Ha nem üres, mert nem dobtunk kivételt, de az cur = nullptr
        throw(CurNullException());   // akkor egy CurNullException-t dobunk
    return cur->data;                // Ha minden rendbe, mert nem volt kivétel, akkor visszadjuk
    // az aktuális elem értékét
}

// Beállítjuk az aktuális elem értékét
template <class T>
void List<T>::setValue(T e)
{
    if (isEmpty())                   // Ha üres a lista
        throw(UnderFlowException()); // akkor egy UnderFlowException-t dobunk
    if (!cur)                        // Ha nem üres, mert nem dobtunk kivételt, de az cur = nullptr
        throw(CurNullException());   // akkor egy CurNullExceptiont dobunk
    // Ha minden rendben, akkor be tudjuk állítani az aktuális elem értékét
    cur->data = e;
}

/// A lista állapotát lekérdező metódusok implementációi
// Megvizsgálja, hogy üres-e a lista (TRUE: ha üres, FALSE: ha nem üres)
template <class T>
bool List<T>::isEmpty() const
{
    return head == nullptr; // Visszaadjuk, hogy a head nullptr-e, mert az csak
    // akkor nullptr, ha üres a lista.
}

// Megvizsgálja, hogy az aktuális elem-e az utolsó (TRUE: ha igen, FALSE: ha nem)
template <class T>
bool List<T>::isLast() const { return cur == tail; }

// Megvizsgálja, hogy az aktuális elem-e az első (TRUE: ha igen, FALSE: ha nem)
template <class T>
bool List<T>::isFirst() const { return cur == head; }

// Megvizsgáljuk, hogy a lista végén vagyunk-e (TRUE: ha igen, FALSE: ha nem)
template <class T>
bool List<T>::isCurNull() const { return cur == nullptr; }

/// Beszúró metódusok implementálása
// A lista elejére szúrja be a paraméterben kapott új értéket
template <class T>
void List<T>::insertFirst(T e)
{
    if (isEmpty())
    {
        head = new Node(e);
        tail = head;
        toFirst();
        return;
    }
    toFirst();
    Node *oldhead = new Node(cur->data, cur->prev, cur->next);
    head->next = oldhead;
    oldhead->prev = head;
    head->data = e;
    toFirst();
}

// A lista végére szúrja be a paraméterben kapott új értéket
template <class T>
void List<T>::insertLast(T e)
{
    if (isEmpty())
    {
        insertFirst(e);
        return;
    }
    toLast();
    Node *newNode = new Node(e, cur, nullptr);
    cur->next = newNode;
    tail = cur->next;
    toLast();
}

// Az aktuális elem elé szúrja be a paraméterben kapott új értéket
template <class T>
void List<T>::insertBefore(T e)
{
    if (isEmpty())
    {
        insertFirst(e);
        return;
    }

    this->stepPrev();
    Node *newNode = new Node(e, cur->prev, cur);
    cur->prev->next = newNode;
    cur->prev = newNode;
    this->stepNext();
}

template <class T>
void List<T>::insertAfter(T e)
{
    if (isEmpty())
    {
        insertFirst(e);
        return;
    }
    Node *newNode = new Node(e, cur, cur ? cur->next : nullptr);
    if (cur)
    {
        if (cur->next)
        {
            cur->next->prev = newNode;
            newNode->next = cur->next;
        }
        else
        {
            tail = newNode;
        }
        cur->next = newNode;
        newNode->prev = cur;
    }
    else
    {
        head = tail = cur = newNode;
    }
}

/// Törlő metódusok implementálása
// Törli a lista első elemét
template <class T>
void List<T>::removeFirst()
{
    if (isEmpty)
    {
        throw UnderFlowException();
    }
    toFirst();
    Node *tmp = head;
    if (head == tail) // Ha csak egy elem van a listában
    {
        head = tail = cur = nullptr; // Akkor mindent nullázzunk
    }
    else // Ha több elem van a listában
    {
        head = head->next;    // Az új head a régi head következője lesz
        head->prev = nullptr; // Az új head előzője legyen nullptr
    }
    delete tmp;
    tmp = nullptr;
}

// Törli a lista utolsó elemét
template <class T>
void List<T>::removeLast()
{
    if (isEmpty())
    {
        throw UnderFlowException();
    }
    toLast();
    Node *tmp = tail;
    if (head == tail)
    {
        head = tail = cur = nullptr; // Ha csak egy elem van a listában
    }
    else // Ha több elem van a listában
    {
        tail = tail->prev;    // Az új tail a régi tail előzője lesz
        tail->next = nullptr; // Az új tail következője legyen nullptr
    }
    delete tmp; // Töröljük a régi tail-t
    tmp = nullptr;
}

// Törli a lista aktuális elemét
template <class T>
void List<T>::removeCur()
{
    if (isEmpty())
    {
        throw UnderFlowException();
    }
    Node *tmp = cur;
    if (cur == head)
    {
        head = tail = cur = nullptr;
    }
    else
    {
        cur->prev->next = cur->next;
        cur->next ? cur->next->prev = cur->prev : nullptr;
    }
    cur = cur->next;
    delete tmp;
    tmp = nullptr;
}

/// Kiegészítő eljárás implementálása
// Kiírja konzolra a lista tartalmát az elejérõl a végéig haladva
template <class T>
void List<T>::print() const
{
    // Egy i pointer fut végig az elemeken, amíg a tail után ki nem fut a listából
    for (Node *i = head; i != nullptr; i = i->next)
    {
        std::cout << i->data << ", "; // és kiírja az aktuális elem értékét
    }
    std::cout << std::endl; // !Ez a sor már nem tartozik a for ciklushoz!
}

template <typename T>
std::ostream &operator<<(std::ostream &o, const List<T> &list)
{
    for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        o << *it << " ";
    }
    return o;
}

#endif // LIST_HPP_INCLUDED