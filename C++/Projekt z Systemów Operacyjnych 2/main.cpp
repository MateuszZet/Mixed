/*
 * SO2 Projekt
 * Saunarium
 *
 * Mateusz Ząbczyk
 * 210040
 */

#include <iostream>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>

#define TIMETODIE 1000000

using namespace std;
//inicjowanie mutexów
pthread_mutex_t drawMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t kasjer1Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t saunaMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t prysznicMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t czasCond = PTHREAD_COND_INITIALIZER;
//Struktury obiektów

//Sauna
struct sauna{
    int miejsce = 30;
};

int prysznice = 30;


//kluczyki
int klucze = 50;

//reczniki
int reczniki = 30;


struct kasjer{
    int recznikowi = 0;
    int nierecznikowi = 0;
};

int neverEnd = 0;
int klientz ; //klient z recznikiem
int klientbez ; // klient bez ręcznika
int weszli ;
int umyci ;
int nieumyci2 ;
int umyci2 ;
int nieumyci3;
int umyci3 ;
int posaunie;
int posaunie2;

//zmienne struktualne
sauna sauna1, sauna2 ;
kasjer kasjer1, kasjer2;

//dodawanie ludzi do kolejki
void * kasaThread(void *var){
 do{
     if (klientz+klientbez < 30){
        if ((rand() % 100) <= 40){
            klientbez += 5 ;
            kasjer1.nierecznikowi += 3;
            kasjer2.nierecznikowi += 2;
        }
        else {
            klientz += 5;
            kasjer1.recznikowi += 2;
            kasjer2.recznikowi += 3;
        }

    }
    //Rysowanie ncurses
    pthread_mutex_lock(&drawMutex);
    mvprintw(1, 6, "Liczba osob z recznikiem: %d", klientz);
    mvprintw(2, 6, "Liczba osob bez recznika: %d", klientbez);
     pthread_mutex_unlock(&drawMutex);
     usleep(3000000);
 }while(neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

//watek kasjera1
void *kasjer1Thread(void *var) {
    do {
        pthread_mutex_lock(&kasjer1Mutex);
        if (klucze > 0) {
            if (kasjer1.recznikowi > 0) {
                kasjer1.recznikowi--;
                klucze--;
                klientz--;
                weszli++;
            };

            if (kasjer1.nierecznikowi > 0 && reczniki > 0) {
                kasjer1.nierecznikowi--;
                klucze--;
                klientbez--;
                reczniki--;
                weszli++;
            };



        }
        pthread_mutex_unlock(&kasjer1Mutex);
        pthread_mutex_lock(&drawMutex);
        mvprintw(4, 6, "Liczba recznikow w recepcji: %d ", reczniki);
        mvprintw(3, 6, "Liczba kluczykow w recepcji: %d ", klucze);
        mvprintw(9,6, "Na terenie obiektu: %d ", weszli);
        mvprintw(1, 6, "Liczba osob z recznikiem: %d ", klientz);
        mvprintw(5, 40, "---KASJER1---");
        mvprintw(6, 40, "|           |");
        mvprintw(5, 15, "Z recznikami: %d ", kasjer1.recznikowi);
        mvprintw(6, 15, "Bez recznikow: %d ", kasjer1.nierecznikowi);
        mvprintw(2, 6, "Liczba osob bez recznika: %d ", klientbez);
        pthread_mutex_unlock(&drawMutex);
        usleep(1000000);
    } while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

//watek kasjera2
void *kasjer2Thread(void *var) {
    do {
        pthread_mutex_lock(&kasjer1Mutex);
        if (klucze > 0) {
            if (kasjer2.recznikowi > 0 ) {
                kasjer2.recznikowi--;
                klucze--;
                klientz--;
                weszli++;

            };

            if (kasjer2.nierecznikowi > 0 && reczniki > 0 ) {
                kasjer2.nierecznikowi--;
                klucze--;
                klientbez--;
                reczniki--;
                weszli++;
            };

        };
        pthread_mutex_unlock(&kasjer1Mutex);
        pthread_mutex_lock(&drawMutex);
        mvprintw(4, 6, "Liczba recznikow w recepcji: %d ", reczniki);
        mvprintw(3, 6, "Liczba kluczykow w recepcji: %d ", klucze);
        mvprintw(9,6, "Na terenie obiektu: %d ", weszli);
        mvprintw(1, 6, "Liczba osob z recznikiem: %d ", klientz);
        if (reczniki !=0){mvprintw(4, 40, "                                ");}
        mvprintw(7, 40, "---KASJER2---");
        mvprintw(8, 40, "|           |");
        mvprintw(7, 15, "Z recznikami: %d ", kasjer2.recznikowi);
        mvprintw(8, 15, "Bez recznikow: %d ", kasjer2.nierecznikowi);
        mvprintw(2, 6, "Liczba osob bez recznika: %d ", klientbez);
        pthread_mutex_unlock(&drawMutex);
        usleep(1000000);
    } while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

//watek wejscia pod prysznic
void *prysznicThread(void *var) {
    do {

        pthread_mutex_lock(&prysznicMutex);
        while (prysznice > 0 && weszli > 0) {
            prysznice--;
            weszli--;
            umyci++;
        }
        pthread_mutex_unlock(&prysznicMutex);
        pthread_mutex_lock(&drawMutex);
        mvprintw(10, 6, "Wolne prysznice: %d / 30 ", prysznice);
        mvprintw(9,6, "Na terenie obiektu: %d ", weszli);
        pthread_mutex_unlock(&drawMutex);
        usleep(5000000);
    } while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

void *wyjscieThread(void *var) {
    do {

        pthread_mutex_lock(&prysznicMutex);
        while( posaunie2 > 0) {

            klucze++;
            posaunie2--;
        }
        pthread_mutex_unlock(&prysznicMutex);

        pthread_mutex_lock(&drawMutex);
        mvprintw(3, 6, "Liczba kluczykow w recepcji: %d ", klucze);
        mvprintw(12,45, "Gotowi do wyjscia: %d  ", posaunie2);
        pthread_mutex_unlock(&drawMutex);
        usleep(6000000);
    } while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

void *recznikiThread(void *var) {
    do {
        pthread_mutex_lock(&kasjer1Mutex);
        if(reczniki == 0){
            pthread_mutex_unlock(&kasjer1Mutex);
            usleep(5000000);
            pthread_mutex_lock(&kasjer1Mutex);
            reczniki = 30;
        }
        pthread_mutex_unlock(&kasjer1Mutex);

        pthread_mutex_lock(&drawMutex);
        mvprintw(4, 6, "Liczba recznikow w recepcji: %d ", reczniki);
        if (reczniki==0){
        mvprintw(4, 40, "DOSTAWA NOWYCH RECZNIKOW");}

        pthread_mutex_unlock(&drawMutex);

    } while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

//watek wejscia do sauny1
void *sauna1Thread(void *var) {
    do {
        pthread_mutex_lock(&saunaMutex);
        while(sauna1.miejsce>0 && umyci>0){
            umyci--;
            prysznice++;
            nieumyci2++;
            sauna1.miejsce --;
        }
        pthread_mutex_unlock(&saunaMutex);

        pthread_mutex_lock(&drawMutex);
        mvprintw(11,6, "Miejsce w saunie finskiej: %d / 30 ", sauna1.miejsce);
        mvprintw(10, 6, "Wolne prysznice: %d / 30 ", prysznice);
        pthread_mutex_unlock(&drawMutex);
        usleep(7000000);

    }while (neverEnd != TIMETODIE);
    pthread_exit(NULL);

}

void *posauna1(void *var){
    do {
        pthread_mutex_lock(&saunaMutex);
        while(nieumyci2>0){
            nieumyci2--;
            sauna1.miejsce ++;
            posaunie++;
        }
        pthread_mutex_unlock(&saunaMutex);

        pthread_mutex_lock(&drawMutex);
        mvprintw(11,6, "Miejsce w saunie finskiej: %d / 30 ", sauna1.miejsce);
        mvprintw(11,45, "Po saunie finskiej: %d  ", posaunie);
        pthread_mutex_unlock(&drawMutex);
        usleep(8000000);

    }while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

//watek wejscia do sauny2
void *sauna2Thread(void *var) {
    do {
        pthread_mutex_lock(&saunaMutex);
        while(sauna2.miejsce>0 && posaunie>0){
            sauna2.miejsce --;
            posaunie --;
            nieumyci3++;
        }
        pthread_mutex_unlock(&saunaMutex);
        pthread_mutex_lock(&drawMutex);
        mvprintw(12,6, "Miejsce w saunie parowej: %d / 30 ", sauna2.miejsce);
        mvprintw(11,45, "Po saunie finskiej: %d  ", posaunie);
        pthread_mutex_unlock(&drawMutex);
        usleep(7000000);
    }while (neverEnd != TIMETODIE);
    pthread_exit(NULL);


}

void *posauna2(void *var){
    do {
        pthread_mutex_lock(&saunaMutex);
        while(nieumyci3>0){
            nieumyci3--;
            sauna2.miejsce ++;
            posaunie2++;
        }

        pthread_mutex_lock(&drawMutex);
        mvprintw(12,6, "Miejsce w saunie parowej: %d / 30 ", sauna1.miejsce);
        mvprintw(12,45, "Gotowi do wyjscia: %d  ", posaunie2);
        pthread_mutex_unlock(&drawMutex);
        pthread_mutex_unlock(&saunaMutex);
        usleep(8000000);

    }while (neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

//wątek odliczający czas symulacji
void *timeToEndFunc(void *arg){
    do{
        neverEnd++;
        usleep(1600);
    }while( neverEnd != TIMETODIE);
    pthread_exit(NULL);
}

int main() {

    pthread_t timeToEnd, kasa_t, kasjer_t, kasjer_t2, sauna_t, sauna_t2, prysznice_t, posauna_t, posauna_t2, wyjscie_t, reczniki_t;
    //Inicjowanie ncurses
    initscr();
    curs_set(FALSE);

    if(pthread_create(&timeToEnd, NULL, timeToEndFunc, NULL)){
        printf("blad, watek timeToEnd");
        abort();
    }
       if(pthread_create(&kasa_t, NULL, kasaThread, NULL)){
        printf("Błąd przy tworzeniu watku kasa_t");
        abort();
    }

        if(pthread_create(&kasjer_t, NULL, kasjer1Thread, NULL)){
        printf("Błąd przy tworzeniu watku kasjer_t");
        abort();
    }

        if(pthread_create(&kasjer_t2, NULL, kasjer2Thread, NULL)){
        printf("Błąd przy tworzeniu watku kasjer_t2");
        abort();
    }

    if(pthread_create(&prysznice_t, NULL, prysznicThread, NULL)){
        printf("blad, watek prysznicThread");
        abort();
    }

    if(pthread_create(&sauna_t, NULL, sauna1Thread, NULL)){
        printf("Błąd przy tworzeniu watku sauna_t");
        abort();
    }

    if(pthread_create(&posauna_t, NULL, posauna1, NULL)){
        printf("Błąd przy tworzeniu watku posauna_t");
        abort();
    }


    if(pthread_create(&sauna_t2, NULL, sauna2Thread, NULL)){
        printf("Błąd przy tworzeniu watku sauna_t");
        abort();
    }

    if(pthread_create(&posauna_t2, NULL, posauna2, NULL)){
        printf("Błąd przy tworzeniu watku posauna_t");
        abort();
    }


    if(pthread_create(&wyjscie_t, NULL, wyjscieThread, NULL)){
        printf("blad, watek wyjscieThread");
        abort();
    }

    if(pthread_create(&reczniki_t, NULL, recznikiThread, NULL)){
        printf("blad, watek recznikiThread");
        abort();
    }

    while(neverEnd != TIMETODIE) {
        refresh();}
    endwin();
    return 0;
}