#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>

#define capacityPlayer 10
#define capacityComputer 10

int counter_player;
int counter_computer;
//int Random_Number_Length  = 7;


//Funktionen

int menu();

int menuewahl();

void playerPlays(int player[], int computer[], int *iHaveZero, int *size_computer, int *size_player);

void computerPlays(int player[], int computer[], int *iHaveZero, int *size_player, int *size_computer);

void deletZero(int array[], int *size_array);

void change_zero(int array[], int position, int capacity_player, int null);

void wennNull(int player[], int size_player, int null, int who_plays);

int generateRandom(int arrpl[], int size, int value);


int spielablauf();


//Funktionen implementiert
void deletZero(int array[], int *size_array) {

    for (int i = 0; i < (*size_array); ++i) {

        if (array[i] == 0) {
            for (int j = i; j < (*size_array) - 1; ++j) {
                array[j] = array[j + 1];
            }
        }
    }
}

void shuffleArray(int arr[], int n) {

    srand(time(NULL));

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }


}

void change_zero(int array[], int position, int capacity_player, int null) {

    int i;
    for (i = 0; i < capacity_player; i++) {
        if (i + 1 == position) {
            int j;
            for (j = capacity_player; j > i; j--) {
                array[j] = array[j - 1];
            }
            array[i] = null;
            break;
        }
    }

}

void kartenAusgeben(int player[], int capacity, int iHaveZero) {
    printf("Hier sind Ihre Karten\n");

    if (iHaveZero == 1) {
        for (int i = 0; i < capacity; ++i) {
            printf(" %d ", player[i]);
        }
    } else {
        for (int i = 0; i < capacity - 1; ++i) {
            printf(" %d ", player[i]);
        }
    }

}


void wennNull(int player[], int size_player, int null, int who_plays) {
    //null= er zog diese Zahl
    int eingabe;

    if (who_plays == 1) {
        printf("Sie haben die Null gezogen! An welcher Stelle moechten sie sie haben?\n");

        scanf("%d", &eingabe);
    } else {
        int value = 0;
        eingabe = player[generateRandom(player, size_player, value)];
    }

    change_zero(player, eingabe, size_player, null);
}


int deletePair(int size_player, int karten_arr_player[], int size_computer, int karten_arr_computer[], int card) {

    //L??schen der Zahl aus Spieler Array
    for (int i = 0; i < size_player; i++) {
        if (karten_arr_player[i] == card) {
            for (int j = i; j < size_player - 1; ++j) {
                karten_arr_player[j] = karten_arr_player[j + 1];
            }
        }
    }

    //L??schen der Zahl aus Computer Array
    for (int i = 0; i < size_computer; i++) {
        if (karten_arr_computer[i] == card) {
            for (int j = i; j < size_computer - 1; ++j) {
                karten_arr_computer[j] = karten_arr_computer[j + 1];
            }
        }
    }

    return 0;
}

bool contains(int arrpl[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arrpl[i] == value) {
            return true;
        }
    }
    return false;
}

int generateRandom(int arrpl[], int size, int value) {
    srand(time(NULL));

    if (contains(arrpl, size, value)) {
        return rand() % (size - 1);
        // return rand() % Random_Number_Length-1; //0_9
    } else {
        return rand() % size + 1;
        // return (rand() % Random_Number_Length-1) -1; //1_9
    }

}


void computerPlays(int player[], int computer[], int *iHaveZero, int *size_player, int *size_computer) {

    if (*size_player != 1) {


        int value = 0;
        int eingabe;

        eingabe = player[generateRandom(player, *size_player, value)];

        if (eingabe == 0) {

            int who_plays = 0;
            wennNull(computer, *size_computer, eingabe, who_plays);

            printf("\n Der Computer zog diese Zahl: %d", eingabe);

            *iHaveZero = 0;

            deletZero(player, size_player);

            *size_player = (*size_player) - 1;


        } else {

            int card_computer = eingabe;

            printf("\n Der Computer zog diese Zahl: %d\n\n", eingabe);

            deletePair(*size_player, player, *size_computer, computer, card_computer);

            *size_player = (*size_player) - 1;

            *size_computer = (*size_computer) - 1;


        }
    }
}


void playerPlays(int player[], int computer[], int *iHaveZero, int *size_computer, int *size_player) {

    if (*size_computer != 0) {
        kartenAusgeben(player, *size_player, *iHaveZero);

        printf("\nWaehlen Sie eine Karte des Gegenspielers: (1 bis %d) \n", (*size_computer));
        int eingabe;
        scanf("%d", &eingabe);

        eingabe = computer[eingabe - 1];

        if (eingabe == 0) {

            int who_plays = 1;
            wennNull(player, *size_player, eingabe, who_plays);

            *iHaveZero = 1;

            deletZero(computer, size_computer);

            *size_computer = (*size_computer) - 1;

            kartenAusgeben(player, *size_player, *iHaveZero);

        } else {

            int card_player = eingabe;
            printf("\nSie haben die %d gezogen. Paar gefunden!\n", eingabe);

            //Karte wird mit der gezogenen Zahl wird aus beiden Arrays entfernt
            deletePair(*size_player, player, *size_computer, computer, card_player);

            //L??nge des Arrays von Player verk??rzen
            *size_player = (*size_player) - 1;

            //L??nge des Arrays von Computer verk??rzen
            *size_computer = (*size_computer) - 1;

            //Ausgabe der Kartenarrays f??r Test
            kartenAusgeben(player, *size_player, *iHaveZero);
        }

    }

}



//Spiel spielen

int main() {
    menu();
    menuewahl();
}


int menu() {
    int i;
    int k;
    for (i = 0; i <= 32; i++) {
        printf("*");
    }

    printf("\n* *\n* Schwarzer Peter mit Zahlen *\n");
    printf("*");
    printf(" * \n* 'a': Spielregeln *\n*");
    printf(" * \n* 'b': Spiel starten *\n*");
    printf(" * \n* 'c': High Score *\n*");
    printf(" * \n* 'd': Menue *\n* *");
    printf("\n");
    for (i = 0; i <= 32; i++) {
        printf("*");
    }
    printf("\n");
}


int menuewahl() {
    char taste;
    scanf("%c", &taste);
    switch (taste) {
        case 'a':
            printf("Regel 1: Wer die 0 zuletzt hat,\nhat verloren!\n\n");
            printf("Regel 2: Mit den Tasten 0,1,2,3,4,5,6,7,8 und 9 \nwaehlen sie jeweils die Position \neiner Karte des Gegenspielers");
            printf("\n");
            menuewahl();
            break;
        case 'b':
            spielablauf();
            break;
        case 'c':
            printf("Dein Score: %d", counter_player);
            printf("\nComputerscore:%d \n", counter_computer);
            menuewahl();
            break;
        case 'd':
            menu();
            menuewahl();
            break;
        default:
            menuewahl();
            break;
    }
    return 0;
}

int spielablauf() {

    int player[capacityPlayer] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int computer[capacityComputer] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    shuffleArray(player, 9);
    shuffleArray(computer, 10);

    int size_player = sizeof(player) / sizeof(player[0]);
    int size_computer = sizeof(computer) / sizeof(computer[0]);

    //Pointer um f??r die spielfunktionen die Variablen zu verwenden

    int *pointer_size_player = &size_player;
    int *pointer_size_computer = &size_computer;

    //Wenn der Spieler gleich zu beginn die 0 zieht, reicht die Kapazit??t nicht aus
    // deshalb machen wir f??r den Spieler die Kapazit??t auf 10 und passen alles an.
    //zieht der Spieler die Null wird der Wert iHaveZero auf 1 gesetzt und sorgt daf??r, dass die Karten anders ausgegeben werden
    int iHaveZero = 0;

    //Warum !=1? - Die Kapazit??t von Player ist statt 9 auf 10 gesetzt weil es die m??glichkeit gibt gleich am Anfang
    // die 0 zu ziehen. Dadurch hat das Arrays immer einen Wert zuviel. Der bleibt am Ende ??brig
    while (size_player != 1 || size_computer != 0) {

        //Pointer f??r iHaveZero
        int *pointer_iHaveZero = &iHaveZero;

        //Spieler f??ngt an

        if(size_player!=1&iHaveZero==0|| size_computer!=0&iHaveZero==1) {

            playerPlays(player, computer, pointer_iHaveZero, pointer_size_computer, pointer_size_player);


            //COMPUTER SPIELT
            //Funktion Computerplays einf??gen
            computerPlays(player, computer, pointer_iHaveZero, pointer_size_player, pointer_size_computer);
        }
        if (size_player == 1&iHaveZero==0) {
            printf("Sie haben gewonnen! Herzlichen Glueckwunsch!!!\n");
            counter_player++;
            break;
        }
        if (size_computer == 0&iHaveZero==1) {
            printf("Sie haben verloren. Schade!\n");
            counter_computer++;
            break;
        }

    }

    printf("Das Spiel ist zu Ende!");

    menu();
    menuewahl();

    return 0;
}