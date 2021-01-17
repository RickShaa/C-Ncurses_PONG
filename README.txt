1.) Programmdokumentation

2.) Vorname, Nachname: Rick Shaffer
3.) Matrikelnummer: 3527436
4.) Entwicklungssystem: macOS Catalina 10.15.4
5.) Titel: Pong
6.) Zwei Spieler treten in einem Match gegeneinander an.
Jeder Spieler hat einen Schläger mit dem er den Ball abprallen lassen kann.
Der Spieler muss außerdem verhindern das der Ball eine Kollision mit dem
Screen hinter dem Schläger hat. Ist dies der Fall bekommt der Gegenspieler
einen Punkt. Das Spiel hat zwei Schwierigkeitsgrade mit denen die Größe 
Des Schlägers verringert wird. Bei dem erreichen von 5 Punkten hört das Spiel auf und einer hat gewonnen.

7.)
	7.1) Menü 
	-> (Level-Menü um Schwierigkeitsgrad einzustellen)

	7.2) Interaktive Tastatureingabe 
	-> (bewegen des Pedals, Steuerung des Menü.

	7.3) ASCII-ART
	-> (Animiertes Pong im Start-Screen, sowie Gewinner Screen.

	7.4) Einfache grafische Animation 
	->(PONG Logo bewegt sich und ändert seine Farbe im Start-Screen, Ball bewegt sich
	sowie die Pedals)

	7.5) Grafisch animierte und bewegte Objekte mit Kollisionserkennung 
	->(Ball erkennt Kollision mit Pedal, sowie screen oben, unten und seitlich, 
	PONG-Logo erkennt Kollision mit screen, wechselt die Farbe und bewegt sich)

8.) 	START_SCREEN: "SPACE" = Spielstart
	LEVEL_SCREEN: "E" = Easy Mode, "M" = Medium Mode
	GAME_LOOP:

			P1: "W" = Up, "S" = DOWN
			P2: "O" = Up, "L" = DOWN
			
			"P" = Pause

	PAUSE_SCREEN: "Q" = Quit, "C" = continue
	WINNER_SCREEN: "SPACE" = new Game, "Q" = Quit
	END_SCREEN: "Q" = QUIT

9.) 	Benutzte Literatur:

		Internet-Literatur:

			C Vorlesung - Prof. Dr. Röttger

			-> http://schorsch.efi.fh-nuernberg.de/roettger/				index.php/Lectures/PROG1

			NCURSES Vorlesung - Prof. Dr. Röttger

			-> http://schorsch.efi.fh-nuernberg.de/roettger/				index.php/NCurses/NCurses-Tutorial
			Video 1-7

		ASCII-ART Generator:
			https://www.ascii-art-generator.org/

		Buch-Literatur:

			Variationen zum Thema Java - Prof Dr. Ralph Lano
			