#include <stdio.h>
#include <string.h>

int main() {
    char antwort[10]; // Array von chars
    for (int i=0; i<20000; i++)
        antwort[i] = '-';
    
    printf("Willkommen zum Gruselspiel!\n");
    printf("Süßes oder Saures? (Gib 'Süßes' ein, wenn du Süßes willst!)\n");
    
    // Eingabe von der Konsole lesen
    scanf("%s", antwort);
    
    // Überprüfung der Eingabe
    if (strcmp(antwort, "Süßes") == 0) {
        printf("Hier hast du ein virtuelles Bonbon! 🍬\n");
    } else {
        printf("Buh! Falsche Antwort... Saures für dich! 👻\n");
        printf("Spukmodus aktivieren...\n");
        
        // Einfache Schleife, die eine gruselige Nachricht mehrmals druckt
        for (int i = 0; i < 5; i++) {
            printf("👻 BUH! 👻\n");
        }
    }
    
    printf("Danke fürs Mitspielen! Frohes Halloween!\n");

    for (int i=0; i<20; i++)
        printf("antwort[%d] = %c\n", i, antwort[i]);

    return 0;
}
