#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// gra ma 3 zakonczenia, mozesz umrzec w walce, pokonac wszystkie smoki, zostac oszukanym przez ostatniego smoka

// ilosci itemkow
int potkaOdwagi = 0;
int potkaZdrowia = 0;

int zdrowieGracza = 10;
int atakGracza = 2;

// tablica w ktorej trzymam wartosci 0 i 1, sluzy do tego zeby nie dalo sie wrocic do obronionej lokacji
int pokonaneLokacje[3] = {0,0,0};

// Funkcja do wyczyszczenia bufora wejsciowego
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funkcja ktora wywoluje w kazdej dzielnicy zeby walczyc ze smokiem
void walkaZeSmokiem(int zdrowieSmoka, int idDzielnicy) {
    atakGracza = 2;
    char input;
    int valid = 0;
    int smoczeZdrowie = zdrowieSmoka;

    int atakSmoka = 0;
    while (smoczeZdrowie > 0 && zdrowieGracza > 0) {
        printf("\nTwoj atak: %d\nTwoje zdrowie: %d\nZdrowie smoka: %d", atakGracza, zdrowieGracza, smoczeZdrowie);
        printf("\nItemy:");
        // Sprawdzam i wyswietlam jakie itemy ma uzytkownik
        if (potkaOdwagi == 0 && potkaZdrowia == 0) {
            printf("Nie masz zadnych itemow");
        }
        if (potkaOdwagi) {
            printf("\nPosiadasz Miksture Odwagi");
        }
        if (potkaZdrowia) {
            printf("\nPosiadasz Miksture Zdrowia");
        }
        printf("\nCo robisz?\n\t1 - atak\n\t2 - itemy\n");
        input = getchar();
        clear_input_buffer(); // czyszczenie buffera przy blednych wejsciach uzytkownika
        // zmniejszam smocze zdrowie o punkty ataku gracza
        if (input == '1') {
            smoczeZdrowie -= atakGracza;
            printf("\n\nZadajesz %d obrazen! Zdrowie Smoka: %d\n", atakGracza, smoczeZdrowie);
            // sprawdzam czy smok moze atakowac czy zginal
            if (smoczeZdrowie > 0) {
                printf("Smok kontratakuje!\n");
                if (smoczeZdrowie > 0) {
                    // smok losowo bije za 1 albo 2 puntky ataku
                    atakSmoka = rand() % 2 + 1;
                    zdrowieGracza -= atakSmoka;
                    printf("Smok kontratakuje i zadaje %d obrazen! Twoje zdrowie: %d\n", atakSmoka, zdrowieGracza);
                }
            }
            else {
                printf("Smok zostal pokonany!\n");
                pokonaneLokacje[idDzielnicy] = 1;
                return;
            }
        }
        // wybor itemkow, potki zdrowia i potki odwagi
        else if (input == '2') {
            if (potkaOdwagi > 0 || potkaZdrowia > 0) { // jesli gracz ma jakiekolwiek itemy
                printf("\nUzywanie mikstur...\n");
                char itemInput;
                int itemValid = 0;

                while (!itemValid) {
                    printf("\nWybierz miksture do uzycia:\n\t1 - Mikstura Odwagi (posiadasz %d)\n\t2 - Mikstura Zdrowia (posiadasz %d)\nPodaj wartosc (1, 2): ", potkaOdwagi, potkaZdrowia);
                    itemInput = getchar();
                    clear_input_buffer();

                    switch (itemInput) {
                    case '1':
                        // potka odwagi dodaje +2 do ataku w tym starciu
                        if (potkaOdwagi > 0) {
                            potkaOdwagi--;
                            atakGracza += 2;
                            printf("Uzywasz Mikstury Odwagi! Twoj atak wzrosl do %d.\n", atakGracza);
                            itemValid = 1;
                        }
                        else {
                            printf("Nie masz Mikstury Odwagi. Wybierz inna opcje.\n");
                        }
                        break;
                    case '2':
                        // potka zdrowia dodaje leczy gracza o +5
                        if (potkaZdrowia > 0) {
                            potkaZdrowia--;
                            zdrowieGracza += 5;
                            printf("Uzywasz Mikstury Zdrowia! Twoje zdrowie wzroslo do %d.\n", zdrowieGracza);
                            itemValid = 1;
                        }
                        else {
                            printf("Nie masz Mikstury Zdrowia. Wybierz inna opcje.\n");
                        }
                        break;
                    default:
                        printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
                    }
                }
            }
            else {
                printf("\nNie masz zadnych mikstur...\n");
            }
        }
        else if (input == '2' && (potkaOdwagi == 0 && potkaZdrowia == 0)) {
            printf("\nNie masz zadnych itemow...\n");
        }
        else {
            printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
        }
    }
    // sprawdzam kto umarl
    if (smoczeZdrowie <= 0) {
        printf("\nPokonales Smoka! Gratulacje!\n");
        pokonaneLokacje[idDzielnicy] = 1;
    }
    else if (zdrowieGracza <= 0) {
        printf("\nSmok cie pokonal, spoczywaj w kawalkach\n");
    }

}

void zawodzie() {
    atakGracza = 2;
    char input;
    int valid = 0;
    printf("\n - - - - - - - -\nZ A W O D Z I E\n - - - - - - - -");
    printf("\nPrzybywasz na zawodzie, w oddali widac jak Smok Gyeksiarski zionie ogniem na pobliskie familoki.");
    printf("\nNa twojej drodze staje grupka dzentelmenow ubranych w dresy\nDecydujesz sie ich ominac czy wdac w dyskusje?");

    while (!valid) {
        printf("Podaj wartosc (1 - omijam, 2 - dyskutuje): ");
        input = getchar();
        clear_input_buffer();

        switch (input) {
        case '1':
            printf("\n\nDecydujesz sie ich ominac\n");
            valid = 1;
            break;
        case '2':
            potkaOdwagi = 1;
            printf("\nPo pokojowej dyskusji i wyjasnieniu dzentelmenom twojej misji, przekazuja ci Miksture Odwagi (zwieksza atak dla walki w ktorej bedzie uzyta)\n");
            valid = 1;
            break;
        default:
            printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
        }
    }

    printf("\nNajwyzsza pora zmierzyc sie ze Smokiem Gyeksiarskim\n");
    valid = 0;
    // Walka ze Smokiem Gyeksiarskim
    int smoczeZdrowie = 10;
    printf("\nWalczysz ze Smokiem Gyeksiarskim! Smok ma %d zdrowia.\n", smoczeZdrowie);

    walkaZeSmokiem(10, 0);
}

void szopienice() {
    atakGracza = 2;
    char input;
    int valid = 0;
    printf("\n - - - - - - - -\nS Z O P I E N I C E\n - - - - - - - -");
    printf("\nPrzybywasz do Szopienic, gdzie Smok Cegielniarski dewastuje domek kultury.");
    printf("\nSpotykasz grupke skautow, ktorzy oferuja ci Miksture Zdrowia.\nDecydujesz sie przyjac ich pomoc?");

    while (!valid) {
        printf("Podaj wartosc (1 - tak, 2 - nie): ");
        input = getchar();
        clear_input_buffer();

        switch (input) {
        case '1':
            potkaZdrowia = 1;
            printf("\nSkautow przekonaly twoje dzielne plany i ofiaruja ci Miksture Zdrowia!\n");
            valid = 1;
            break;
        case '2':
            printf("\nDecydujesz sie odrzucic ich pomoc i ruszasz dalej.\n");
            valid = 1;
            break;
        default:
            printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
        }
    }

    printf("\nCzas stanac twarza w twarz ze Smokiem Cegielniarskim!\n");
    valid = 0;
    // Walka ze Smokiem Cegielniarskim
    walkaZeSmokiem(12, 1);
}

void giszowiec() {
    atakGracza = 2;
    char input;
    int valid = 0;
    printf("\n - - - - - - - -\nG I S Z O W I E C\n - - - - - - - -");
    printf("\nDocierasz do Giszowca, gdzie Smok Ogrodowy niszczy piekne ogrody.");
    printf("\nSpotykasz ogrodnika, ktory proponuje ci Miksture Odwagi w zamian za pomoc w ugaszeniu pozaru na jego dzialce.\nDecydujesz sie mu pomoc?");

    while (!valid) {
        printf("Podaj wartosc (1 - tak, 2 - nie): ");
        input = getchar();
        clear_input_buffer();

        switch (input) {
        case '1':
            potkaOdwagi = 1;
            printf("\nPomagajac ogrodnikowi, otrzymujesz Miksture Odwagi, ale gaszenie pozaru bylo bardzo ciezkie\nTracisz 1 punkt zdrowia");
            zdrowieGracza -= 1;
            valid = 1;
            break;
        case '2':
            printf("\nOdrzucasz jego propozycje i idziesz dalej.\n");
            valid = 1;
            break;
        default:
            printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
        }
    }

    printf("\nCzas na walke ze Smokiem Ogrodowym!\n");
    valid = 0;
    // Walka ze Smokiem Ogrodowym
    walkaZeSmokiem(15,2);
}

int main() {
    printf("\n\nHistoria zaczyna sie w tetniacym zyciem miescie Pyroklas, znanym z czestych obserwacji smokow i wynikajacych z tego pozarow.\n\n");
    printf("Ostatnio ataki smokow staly sie czestsze i intensywniejsze, co sugeruje zlowieszcze motywy stojace za ich dzialaniami.\n\n");
    printf("Brygada Skrzydla Ognia zrekrutowala Ciebie, nowego, ale obiecujacego strazaka, abys pomogl stawic czola temu zagrozeniu.\n\n");
    printf("Twoje nadludzkie umiejetnosci wladania wezem strazackim bardzo przydadza sie w tej misji\n\n");
    printf("Wpisz swoje imie:\n");

    char nazwaGracza[15];
    int valid = 0;

    while (!valid) {
        printf("Podaj imi gracza (max 10 znakow): ");
        fgets(nazwaGracza, sizeof(nazwaGracza), stdin);

        // Usun znak nowej linii, jesli jest obecny w buforze
        nazwaGracza[strcspn(nazwaGracza, "\n")] = '\0';

        if (strlen(nazwaGracza) > 10) {
            printf("Imie ma wiecej niz 10 znakow. Sprobuj ponownie.\n\n");
        }
        else {
            valid = 1;
        }
    }

    printf("%s\n\n", nazwaGracza);


    char input;
    valid = 0;
    // glowny game loop obrony 3 dzielnic
    // warunek w while sprawdza czy ktoras lokacja zostala jeszcze do obronienia, jesli wszystkie juz sa obronione to sie konczy
    while (!pokonaneLokacje[0] || !pokonaneLokacje[1] || !pokonaneLokacje[2]) {
        printf("\n\nAktualnie w miescie Pyroklas smoki atakuja trzy dzielnice:\n\n\t* Zawodzie\n\n\t* Szopienice\n\n\t* Giszowiec\n\n");
        printf("\n\nGdzie chcesz sie udac %s? Wpisz 1, 2 lub 3 aby przejsc do wyboru dzielnicy\n", nazwaGracza);
        while (!valid) {
            printf("Podaj wartosc (1, 2, 3): ");
            input = getchar();
            clear_input_buffer(); // wyczysc bufor po kazdym odczycie

            switch (input) {
            // sprawdzam czy lokacja jest obroniona, do obronionej lokacji nie mozna ponownie wejsc
            case '1':
                if (!pokonaneLokacje[0]) {
                    zawodzie();
                    valid = 1;
                }
                else {
                    printf("Ta lokacja zostala juz obroniona!\n");
                }
                break;
            case '2':
                if (!pokonaneLokacje[1]) {
                    szopienice();
                    valid = 1;
                }
                else {
                    printf("Ta lokacja zostala juz obroniona!\n");
                }
                break;
            case '3':
                if (!pokonaneLokacje[2]) {
                    giszowiec();
                    valid = 1;
                }
                else {
                    printf("Ta lokacja zostala juz obroniona!\n");
                }
                break;
            default:
                printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
            }
        }
        valid = 0;
    }
    // jesli wszystkie trzy dzielnice zostaly juz obronione to wykonuje sie ponizszy kod
    valid = 0;
    printf("Ostatni smok, chwile przed tym jak skonal, wydusil z siebie ze wszyscy byly kontrolowani przez... Wladce Zaru!\n\nPora na finalne starcie...\n\n");
    printf("Przed walka masz chwile zeby isc do kaplicy i poprosic strazackie bostwo o regeneracje ran poniesionych w walkach\n\n");
    printf("Czy decydujesz sie to zrobic? 1 - tak, 2 - nie\n");
    int bonusZdrowia;
    while (!valid) {
        printf("Podaj wartosc (1, 2): ");
        input = getchar();
        clear_input_buffer(); // wyczysc bufor po kazdym odczycie

        switch (input) {
        case '1':
            bonusZdrowia = rand() % 10 + 9; // losowy wzrost zdrowia od 9 do 18
            zdrowieGracza += bonusZdrowia;
            printf("Twoje zdrowie wzroslo o %d i wynosi %d\n\n", bonusZdrowia, zdrowieGracza);
            valid = 1;
            break;
        case '2':
            printf("Czujesz sie na silach zeby stanac oko w oko z Wladca Zaru bez chwili oddechu\n\n");
            valid = 1;
            break;
        default:
            printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
        }
    }
    valid = 0;
    printf("Przed walka Wladca Zaru oferuje zakopac topor wojenny i zamienic cie w poteznego smoka, o sile takiej jak on\n\n");
    printf("Przyjmujesz oferte? 1 - tak 2 - nie\n");
    while (!valid) {
        printf("Podaj wartosc (1, 2): ");
        input = getchar();
        clear_input_buffer(); // wyczysc bufor po kazdym odczycie

        switch (input) {
        case '1':
            // ZLE ZAKONCZENIE
            printf("\n - - - - - - - - - -\nPORAZKA\n- - - - - - - - - - \nIdziesz na uklad ze smokiem, jednak jego obietnica okazala sie okropnym klamstwem\n\nWladca Zaru wyciaga do ciebie lape, ale zanim zdazysz sie zorientowac lezysz zmiazdzony pod jej ciezarem\n\n");
            printf("Dales sie oszukac %s...", nazwaGracza);
            return 0;
        case '2':
            printf("Ten uklad nie moze byc prawdziwy... Stajesz do walki!\n\n");
            valid = 1;
            break;
        default:
            printf("Nieprawidlowe wejscie. Sprobuj ponownie.\n");
        }
    }
    printf("Walczysz z Wladca Zaru!");
    walkaZeSmokiem(15, 0);
    // DOBRE ZAKONCZENIE
    if (zdrowieGracza>0) {
        printf(" **GRATULACJE!** \n");
        printf(" Udalo ci sie obronic miasto Pyroklas przed wszystkimi smokami, w tym przed Wladca Zaru!\n");
        printf(" Dzieki tobie, mieszkancy miasta moga znowu zyc w spokoju i bezpieczenstwie. Twoje imie, %s, zostanie zapamietane jako bohater Pyroklas!\n\n", nazwaGracza);
        printf(" Twoje finalne statystyki:\n");
        printf(" Zdrowie: %d\n", zdrowieGracza);
        printf(" Pokonane smoki: 4\n");
        printf(" Dobra robota! \n");
    }
    return 0;
}