#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur für Operationen
typedef struct {
    char *name;
    int (*operation)(int, int);
} Operation;

// Beispieloperationen
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int mult(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return a / b;
}

// Funktion zum Ausführen einer Operation
void execute_operation(Operation *ops, int count, const char *name, int a, int b) {
    for (int i = 0; i < count; i++) {
        if (ops[i].name && strcmp(ops[i].name, name) == 0) {
            printf("Result of %s: %d\n", name, ops[i].operation(a, b));
            return;
        }
    }
    printf("Operation '%s' not found!\n", name);
}

int main() {
    // Erweiterbare Liste von Operationen
    Operation operations[] = {
        {"add", add},
        {"subtract", subtract},
        {"multiply", mult},
        {"divide", divide},
        {NULL, NULL}
    };

    // Beispielverwendung
    int nr_operations = sizeof(operations) / sizeof(operations[0]);
    printf("nr_operations=%d\n", nr_operations);
    execute_operation(operations, nr_operations, "add", 5, 3);
    execute_operation(operations, nr_operations, "subtract", 10, 4);
    execute_operation(operations, nr_operations, "multiply", 3, 100);
    execute_operation(operations, nr_operations, "divide", 100, 3);

    // Neue Operationen können einfach hinzugefügt werden
    return 0;
}
