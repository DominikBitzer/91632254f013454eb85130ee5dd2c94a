SysPrak Gruppe23
====================================

Link for socket explanation: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html

Milestone 1: tbd
----------------
### Obligatory Features
* Input GameID: done
  * as part of config: added readConfig in config.c/config.h in anticipation of to be added functionality
* Constants: done
  * added in header file config.h for portability and modularity
* Connection to Server: done
* performConnection() Prolog: partially done
  * Problem: Last receive in prolog are two lines ==> find logic behind it and adjust recvFromGameserver
  * Add error-handling if numbytes == -1, because message was only partially send. Repeat Transmission?
  * Integrate latency-handling in recvFromGameserver ==> do recvGromGameser while answer == none
* Gameserver output formatting: tbd
* Error handling: done
  * die() routine implemented in utils.c
* Makefile: done
  * `make` compiles project
  * `make clean` cleans up project files
  * `make X.o` compiles X.c
  * please add additional files to OBJECTS variable in Makefile

### Additional Features
* Added .gitignore file so objects and executables don't clutter the src dir
* valgrind shows no leaky memory

Milestone 2: tbd
----------------
* Parametrisierbare Konfiguration über eine Konfigurationsdatei
  * client.conf auslesen, falls keine config Datei angegeben wurde	DONE
  * struct config aktualisieren und Einstellungen einlesen:
    - Hostname des Gameservers (nicht als char[] sondern wie htons())
    - Portnummer des Gameservers
    - Art des Spieles (hier: NMMorris)
* Aufspaltung des Programmablaufs in zwei Prozesse – den Thinker und den Connector
  * Achtung: Es ist darauf zu achten, dass der Kindprozess nicht zu einem Waisen- oder Zombieprozess wird.
  * Problem: Wie können wir verhindern, dass printf() mit dem Server aus parallelem Prozess kommuniziert?
* Implementierung eines Shared-Memory-Bereichs für die Kommunikation der beiden Prozesse

Milestone 3: tbd
----------------

Milestone 4: tbd
----------------
