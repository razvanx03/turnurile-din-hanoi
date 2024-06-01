#include <iostream>
#include <limits>
#include <vector>
#include <string>

using namespace std;

// stiva
class Stack {
private:
    int* data;
    Stack* next;

public:
    // constructor pentru initializarea stivei
    Stack(int n) : data{ new int{ n } }, next{ nullptr } {}

    // pt stergerea int* data cand sterg un nod
    ~Stack() {
        delete data;
    }

    // functie pe care o folosim sa ajungem in varful stivei
    Stack* getStackTop() {
        Stack* current = this;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current;
    }

    // adauga un numar in varful stivei
    void push(int val)
    {
        Stack* top = getStackTop();
        Stack* newNode = new Stack(val);
        top->next = newNode;
    }

    // sterge elementul din varf
    void pop()
    {
        if (next == nullptr) {
            if (data == nullptr) {
                cerr << "Stack is empty." << endl;
                return;
            }
            delete data;
            data = nullptr;
            return;
        }

        Stack* topNode = getStackTop();
        Stack* prevNode = this;

        while (prevNode->next != topNode) {
            prevNode = prevNode->next;
        }

        prevNode->next = nullptr;
        delete topNode;
    }

    // returneaza valoarea din varful stivei
    int top() {
        Stack* top = this;

        while (top->next != nullptr)
        {
            top = top->next;
        }
        return *top->data;
    }

    // returneaza totalul de elemente din stiva
    int length() {
        int length = 0;
        Stack* current = this;

        while (current->next != nullptr)
        {
            current = current->next;
            length++;
        }
        return length;
    }

    // goleste stiva
    void empty() {
        int current = this->length();

        for (int i = 0; i <= current; i++)
        {
            this->pop();
        }
    }

    // printeaza intreg continutul stivei
    void print() {
        Stack* current = this->next;  // Parcurgem de la primul element, nu de la nodul inițial

        while (current != nullptr) {
            cout << *current->data << ' ';
            current = current->next;
        }
    }

    // printeaza top() pe ecran
    void printTop() {
        cout << this->top();
    }

    // ca sa putem da cout ca la un array normal gen stiva[numar]
    int operator[](int index)
    {
        Stack* current = this;

        if (index == 0 && current->data == nullptr) {
            cerr << "Out of stack." << endl;
            return -1;
        }

        for (int i = 0; i < index; i++)
        {
            if (current->next == nullptr) {
                cerr << "Out of stack." << endl;
                return -1;
            }
            current = current->next;
        }
        return *current->data;
    }
};

// coada
class Queue {
private:
    int queue[100];

public:
    // constructor pentru a umple coada cu valori care nu sunt "valide"
    // echivalentul la nullptr pentru pointer
    Queue()
    {
        for (int i = 0; i < 100; i++)
        {
            queue[i] = -1;
        }
    }

    // verifica daca coada este goala si returneaza "true" daca este
    bool empty()
    {
        for (int i = 0; i < 100; i++)
        {
            if (queue[i] != -1) {
                return false;
            }
        }
        return true;
    }

    // returneaza numarul de elemente din coada
    int size()
    {
        int counter = 0;
        while (queue[counter] != -1) {
            counter++;
        }
        return counter;
    }

    // returneaza primul element din coada
    int front() {
        if (queue[0] == -1) {
            cout << "Coada este goala. ";
            return 0;
        }
        return queue[0];
    }

    // returneaza ultimul element din coada
    int back() {

        for (int i = 0; i < 100; i++)
        {
            if (queue[i] == -1) {
                if (queue[i] == queue[0]) {
                    cout << "Sirul este gol. ";
                    return 0;
                }
                else
                    return queue[i - 1];
            }
        }
    }

    // adauga un element in coada
    void push(int number) {

        for (int i = 0; i < 100; i++)
        {
            if (queue[i] == -1)
            {
                queue[i] = number;
                break;
            }
        }
    }

    // printeaza coada pe ecran
    void print() {
        int i = 0;
        while (queue[i] != -1) {
            cout << queue[i] << ' ';
            i = i + 1;
        }
    }

    // sterge primul element din coada
    void pop() {

        int size = this->size();

        for (int i = 0; i <= size; i++)
        {
            queue[i] = queue[i + 1];
        }
    }
};

struct Moves {

    Queue mutari;

    vector<string> turnul_1;

    vector<string> turnul_2;

    void printMoves() {

        cout << "Mutarile jucatorului in ordine:\n";

        int mutariTotale = mutari.size();

        for (int i = 0; i < mutariTotale; i++)
        {
            cout << "Mutarea " << i + 1 << ": de la " << turnul_1[i] << " la " << turnul_2[i]
                << " avand valoarea " << mutari.front() << '\n';
            mutari.pop();
        }
    }
};

int isValid(char usage)
{
    int input;
    if (!(cin >> input)) {
        cout << "Input invalid! Introduceti un numar intreg.\n";
        cin.clear();  // Reseteaza starea fluxului de intrare
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora restul liniilor
        switch (usage)
        {
        case 'F':
            cout << "De pe tija: ";
            break;
        case 'T':
            cout << "Pe tija: ";
            break;
        case 'N':
            cout << "\nIntroduceti numarul de discuri: \n";
            break;
        }
        return isValid(usage);
    }
    else if (input <= 0)
    {
        cout << "Numarul inserat trebuie sa fie mai mare decat 0! \n";
        switch (usage)
        {
        case 'F':
            cout << "De pe tija: ";
            break;
        case 'T':
            cout << "Pe tija: ";
            break;
        case 'N':
            cout << "\nIntroduceti numarul de discuri: ";
            break;
        }
        return isValid(usage);
    }
    return input;
}
int main() {
    int numDisks;

    cout << "Turnurile din Hanoi\n\n";
    cout << "Introduceti numarul de discuri: ";
    numDisks = isValid('N');

    Stack towerA(numDisks);  // Turnul de pornire (turnul A)
    Stack towerB(0);        // Turnul intermediar (turnul B)
    Stack towerC(0);        // Turnul destinatie (turnul C)

    Moves mutari;
    mutari.turnul_1.resize(100);
    mutari.turnul_2.resize(100);

    // Initializare stiva initiala (turnul A)
    for (int i = numDisks; i > 0; i--) {
        towerA.push(i);
    }

    int moves = 0;  // Contor pentru numarul de mutari efectuate

    while (true)
    {
        cout << "-------------------------\n";
        cout << "Starea curenta a turnurilor:\n";
        cout << "Turnul A: ";
        towerA.print();
        cout << "\nTurnul B: ";
        towerB.print();
        cout << "\nTurnul C: ";
        towerC.print();
        cout << "\n-------------------------\n";

        // Citirea mutarii de la utilizator
        int from, to;
        cout << "Mutare #" << moves + 1 << "\n";
        cout << "De pe tija: ";
        from = isValid('F');
        cout << "Pe tija: ";
        to = isValid('T');

        // Verificare mutare valida
        Stack* sourceTower;
        Stack* destTower;

        if (from == 1) {
            sourceTower = &towerA;
            mutari.turnul_1[moves] = "Turnul A";
        }
        else if (from == 2) {
            sourceTower = &towerB;
            mutari.turnul_1[moves] = "Turnul B";
        }
        else if (from == 3) {
            sourceTower = &towerC;
            mutari.turnul_1[moves] = "Turnul C";
        }
        else {
            cout << "Tija sursa invalida!\n";
            continue;
        }

        if (to == 1) {
            destTower = &towerA;
            mutari.turnul_2[moves] = "Turnul A";
        }
        else if (to == 2) {
            destTower = &towerB;
            mutari.turnul_2[moves] = "Turnul B";
        }
        else if (to == 3) {
            destTower = &towerC;
            mutari.turnul_2[moves] = "Turnul C";
        }
        else {
            cout << "Tija destinatie invalida!\n";
            continue;
        }

        // Verificare mutare legala
        if (sourceTower->length() == 0) {
            cout << "Tija sursa goala!\n";
            continue;
        }

        if (destTower->length() > 0 && sourceTower->top() > destTower->top()) {
            cout << "Nu poti pune o tija mai mare peste una mai mica!\n";
            continue;
        }

        // Efectuarea mutarii
        int disk = sourceTower->top();
        mutari.mutari.push(sourceTower->top());
        sourceTower->pop();
        destTower->push(disk);

        moves++;

        // Verificare daca jocul s-a terminat
        if (towerA.length() == 0 && towerB.length() == 0 && towerC.length() == numDisks)
        {
            cout << "-------------------------\n";
            cout << "Starea curenta a turnurilor:\n";
            cout << "Turnul A: ";
            towerA.print();
            cout << "\nTurnul B: ";
            towerB.print();
            cout << "\nTurnul C: ";
            towerC.print();
            cout << "\n-------------------------\n";
            cout << "Jocul s-a incheiat! Felicitari!\n";
            cout << "\n-------------------------\n";

            // Mutarile printate pe ecran in ordine:
            mutari.printMoves();

            break;
        }
    }
    return 0;
}