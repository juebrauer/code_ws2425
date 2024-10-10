#include <stdio.h>

int main() {
    double kapital = 1000.0;  // Startkapital in Euro
    double zinssatz = 3.6;    // Zinssatz in Prozent
    int jahre;
    
    
    double zahl = 1.467;
    printf("zahl=%.1f\n", zahl);

    printf("Gib die Anzahl der Jahre ein, ueber die das Kapital verzinst werden soll: ");
    scanf("%d", &jahre);

    printf("\nJahr | Kapital\n");
    printf("--------------------\n");

    for (int i = 1; i <= jahre; i++) {
        kapital = kapital + kapital * (zinssatz / 100);
    }
    
    printf("%04d | %.1f Euro\n", jahre, kapital);

    return 0;
}
