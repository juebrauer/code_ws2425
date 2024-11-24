#include "unity.h"

// Funktion, die getestet werden soll
int addiere(int a, int b) {
    return a + b + 1;
}

// Setup- und Teardown-Funktionen (optional)
void setUp(void) {
    // Hier kann man Code schreiben, der vor jedem Test ausgeführt wird
}

void tearDown(void) {
    // Hier kann man Code schreiben, der nach jedem Test ausgeführt wird
}

// Testfunktionen
void test_addiere_sollte_zwei_und_drei_addieren(void) {
    TEST_ASSERT_EQUAL(5, addiere(2, 3));
}

void test_addiere_sollte_null_liefern_bei_nullwerten(void) {
    TEST_ASSERT_EQUAL(0, addiere(0, 0));
}

void test_addiere_sollte_negativen_wert_liefern(void) {
    TEST_ASSERT_EQUAL(-1, addiere(-2, 1));
}

int main(void) {
    UNITY_BEGIN(); // Initialisiert Unity Test Framework
    RUN_TEST(test_addiere_sollte_zwei_und_drei_addieren);
    RUN_TEST(test_addiere_sollte_null_liefern_bei_nullwerten);
    RUN_TEST(test_addiere_sollte_negativen_wert_liefern);
    return UNITY_END(); // Beendet das Testframework und gibt das Ergebnis zurück
}
