## Intro 

**Mutexe** (abgeleitet von "Mutual Exclusion") sind essenziell, um den gleichzeitigen Zugriff auf gemeinsame Ressourcen durch mehrere Threads zu steuern und so Race Conditions zu vermeiden. 

Das **Signal-Wait-Konzept** ermöglicht eine effektive Kommunikation und Synchronisation zwischen Threads, indem es Signale nutzt, um Ereignisse zu kennzeichnen und auf sie zu warten.

Da diese Themen recht komplex sind, empfehle ich, die Dateien in der vorgegebenen Reihenfolge durchzuarbeiten. 

*Hinweis: Zu jeder Aufgabe gibt es eine C-Implementierung, die die gleiche Funktionalität wie der Psuedocode hat. Es bietet sich an, nach jeder Pseudo-Code Lösung die entsprechende C-Implementierung zu studieren. Wer mag kann natürlich auch erst alle Pseudo-Code Lösungen durcharbeiten und sich dann die C-Implementierungen ansehen.*


## Übersicht
1. Einstieg in Mutexe
   1. [Wozu Mutexe?](./intro/without_mutex.c)
   2. [Das erste Mutex](./intro/with_mutex.c)
   3. [Das erste Mutex - aber besser](./intro/with_mutex_better.c)

2. Mutexe
   1. [Mutexe - am Beispiel von Dönerbuden](./3.1/musterloesung/A.c)  [[C-Version](./3.1/c-version/A.c)] (Aufgabe 3.1.a)

3. Einstieg in Signal & Wait
   1. [Wozu Signal & Wait?](./3.1/musterloesung/why_signal_wait.c) [[C-Version](./3.1/c-version/why_signal_wait.c)]

4. Signal & Wait
   1. [Signal & Wait - am Beispiel von Dönerbuden](./3.1/musterloesung/B.c) [[C-Version](./3.1/c-version/B.c)] (Aufgabe 3.1.b)  
   2. [Cross-Thread Signal & Wait - am Beispiel von Dönerbuden](./3.1/musterloesung/C.c) [[C-Version](./3.1/c-version/C.c)] (Aufgabe 3.1.c) 
   3. [Signal & Wait - am Beispiel von Buffern](./3.2/musterloesung/C.c) [[C-Version](./3.2/c-version/C.c)] (Aufgabe 3.2.c)
   
5. Spurious Wakeups 
   1. [Was sind Spurious Wakeups?](./3.2/c-version/spurious_wakeup.c) (Aufgabe 3.2.b)



