## Orga
- **Anmeldung:** 
    - über Moses bis **17.05.24**
    - wählt vorerst einen der zwei Termine; Umentscheidung bis **15.07.24** möglich

- **Benotung:**
    - **50PP** Klausur
    - **50PP** Hausaufgabe
        - *2x* **5P** Theorie
        - *1x* **10P** Praxis
        - *1x* **30P** Praxis

## Einrichtung Entwicklungsumgebung
- **Dringende Empfehlung:** 
    - Richtet euch eure Entwicklungsumgebung ein!
    - Nicht nur für diesen Kurs von Relevanz, sondern fürs gesamte Studium und spätere Laufbahn...
    - Haltet die Barriere für das schnelle Entwicklen von Software möglichst klein!

- **Meine (persönliche) Empfehlung:**   
    - Entwickelt auf *Linux* oder *Mac* basierten Systemen - die meiste (nützliche) Software ist auf diesen Betriebssystemen erhätlich... 
    - Falls ihr einen Windowsrechner habt, schaut euch WSL an um Linux auf eurem Rechner "genießen" zu können

- **Inspiration**:
    - Googlet nach *'mac/windows/linux developer setup'* - so findet ihr meist gute Guides

- **Must-Do's**:
    - **Windows:**
        - Installiert euch Linux über **WSL**. Siehe [hier](https://learn.microsoft.com/en-us/windows/wsl/install#install-wsl-command:~:text=install%20page.-,Install%20WSL%20command,your%20machine.%20All%20future%20launches%20should%20take%20less%20than%20a%20second.,-Note) für mehr Information.
        - Zu *Hinweisen und Best Practices* bei der Einrichtung von WSL siehe [hier](https://learn.microsoft.com/en-us/windows/wsl/setup/environment#set-up-your-linux-username-and-password).
        - Für weitere Hinweise siehe *Kapitel Linux* weiter unten
        - **Wichtig:** Falls ihr nicht dauerhaft im Terminal arbeiten wollt, richtet euch eine *externe Verbindung zu einem **grafischen** Editor* ein (bspw. [VSCode der nativen Support für WSL anbietet](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-vscode))
    - **Mac**
        - Installiert euch **XCode** ("*suite of software development tools developed by Apple for developing software"*)
        - Installiert euch **Homebrew** ("*The missing package manager for macOS*")
        - anstelle des Debuggers **gdb** könnt ihr auf Max auch **lldb** verwenden
        - anstelle von **valgrind** könnt ihr **leaks** verwenden
        - (Eine Menge wichtiger) Software kann nun über ```brew install package-xyz``` installiert werden.
        - für mehr Tipps zur Einrichtung siehe [hier]( https://sourabhbajaj.com/mac-setup/).
    - **Linux**
        - Lucky you!
        - (Quasi) jeglich Software wird über den Befehl ```sudo apt-get install package-xyz``` bzw. ```sudo apt install package-xyz``` installiert

- **Code-Editoren**
    - Euch überlassen!
    - **Persönlich:** Ich bevorzuge grafische Editoren und benutze selbst VSCode. In meiner Erfahrung empfiehlt es sich bekannte Editoren zu wählen, da sie den besten Support/Packages/Extensions anbieten.

- **Terminal**
    - Learn how to use your shell!
    - Für Shell 101 siehe [hier](https://www.youtube.com/watch?v=IYZDIhfAUM0).
    - Installiert euch shell packages für syntax-highlighting, auto-complete, history etc.


## C-Material
- [C-Kurs für Einsteiger](https://www.youtube.com/playlist?list=PL5FRnzOULdYfzyeoaKFJmfeHJvwIwqK0a)
- [Common C Erros](https://pacman128.github.io/internal/common_c_errors/)
- [Data structure alignment](https://en.wikipedia.org/wiki/Data_structure_alignment)
- [Call-by-value vs. Call-by-reference](https://www.geeksforgeeks.org/difference-between-call-by-value-and-call-by-reference/)
- [Pointers explained](https://www.youtube.com/watch?v=2ybLD6_2gKM) & [Pointer arithmetic](https://www.youtube.com/watch?v=q24-QTbKQS8)
