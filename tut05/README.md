**Mutexe** (abgeleitet von "Mutual Exclusion") sind essenziell, um den gleichzeitigen Zugriff auf gemeinsame Ressourcen durch mehrere Threads zu steuern und so Race Conditions zu vermeiden. 

Das **Signal-Wait-Konzept** ermöglicht eine effektive Kommunikation und Synchronisation zwischen Threads, indem es Signale nutzt, um Ereignisse zu kennzeichnen und auf sie zu warten.

Da diese Themen recht komplex sind, empfehle ich, die Dateien in der vorgegebenen Reihenfolge durchzuarbeiten.

1. Einstieg in Mutexe
   1. [Wozu Mutexe?](./intro/without_mutex.c)
   2. [Das erste Mutex](./intro/with_mutex.c)
   3. [Das erste Mutex - aber besser](./intro/with_mutex_better.c)
   4. [Mutexe - am Beispiel von Dönerbuden](./01/1_A_pthread.c)

2. Signal & Wait
   1. [Wozu Signal & Wait? - am Beispiel von Dönerbuden](./01/1_B_muster_naive.c)
   2. [pthread-Implementierung von 2.1](./01/1_B_pthread_naive.c)
   3. [Signal & Wait - am Beispiel von Dönerbuden](./01/1_B_muster.c)
   4. [pthread-Implementierung von 2.3](./01/1_B_pthread.c)
   5. [Cross-Thread Signal & Wait - am Beispiel von Dönerbuden](./01/1_C_muster.c)
   6. [pthread-Implementierung von 2.5](./01/1_C_pthread.c)
   7. [Wiederholung - am Beispiel von Buffern](./02/2_C_muster.c)
   8. [pthread-Implementierung von 2.7](./02/2_C_pthread.c)
   9. [Spurious Wakeups - was ist das?](./02/spurious_wakeup.c)



