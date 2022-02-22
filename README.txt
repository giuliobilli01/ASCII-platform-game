ASCII PLATFORM GAME

Gioco scritto in c++ organizzato in stanze, in ogni stanza sono presenti due porte, una per andare al livello successivo e una per andare al livello precedente. Ogni stanza ha una struttura particolare, composta da piattaforme, ostacoli, bonus e nemici sparsi casualmente all'interno di essa.
Il giocatore può raccogliere i bonus per guadagnare punti e aumentare la sua vita. Andando avanti con i livelli
i nemici acquisiscono più vita diventando così più forti.
Il gioco finisce quando la vita del giocatore arriva a zero.
Lo scopo del gioco è andare avanti nei livelli cercando di fare il maggior numero di punti

______________________________________________________________________________________________

COME ESEGUIRE IL GIOCO

Generare il file .exe
	g++ -o main main.o Game.o Constant.o Level.o Levels.o WindowsFunction.o Player.o menuMessage.o
	Shot.o Shots.o Character.o Generator.o BasicEnemiesList.o BasicEnemy.o MediumEnemy.o MediumEnemiesList.o 
	HardEnemy.o HardEnemiesList.o 

Eseguire il comando ./main da cmd

______________________________________________________________________________________________

ELEMENTI DEL GIOCO

Ambiente di gioco:
    - Diviso in stanze e livelli, a ogni stanza corrisponde un nuovo livello
    - Il giocatore si muove all'interno delle stanze 
    - Nelle stanze ci sono bonus e diversi tipi di nemici generati casualmente
    - Le stanze hanno una struttura prefissata, in totale ci sono sei modelli di stanze.
    - Ogni stanza ha due porte, una per andare al livello successivo e una per andare al livello precedente
    - I modelli delle stanze si alternano andando avanti nel gioco

Giocatore:
    - Viene controllato da tastiere attraverso i comandi "W", "A", "S", "D"
    - Può esplorare la stanza salendo sulle piattaforme
    - Può sparare senza limitazioni

Bonus:
    - I bonus vengono generati casualmente in ogni stanza
    - Ci sono due tipi di bonus:
        - Il tipo $ aumenta i punti del giocatore
        - Il tipo L aumenta la vita del giocatore

Nemici:
    - I nemici si generano sulle piattaforme in modo casuale
    - Andando avanti con i livelli aumenta la quantità di nemici e la loro vita
    - Ci sono tre tipi di nemici:
        - BasicEnemy: sta fermo e fa da ostacolo togliendo vita al giocatore se ci va sopra
        - MediumEnemy: si muove e cerca di raggiungere il player che perde vita se viene raggiunto
        - HardEnemy: sta fermo e inizia a sparare al giocatore quando entra nel suo campo visivo

______________________________________________________________________________________________

DATI ELEMENTI DEL GIOCO

Giocatore:
    - Vita: 100
    - Punti: partono da 0 e aumentano prendeno bonus
    - Colpi: infiniti
    - I dati del giocatore vengono stampati nella parte destra della schermata di gioco
    - Attacco:
        - 10 BasicEnemy
        - 20 MediumEnemy
        - 20 HardEnemy

Nemici:
    - BasicEnemy:
        - Vita: 50 (aumenta di un parametro lifeIncreaser pari a lifeIncreaser * numero del livello ad ogni livello)
        - Attacco: 30 se il player ci va sopra 
        - Probabilità:
            - Fino al livello 6 aumentano di 1 ogni livello con un minimo di 6
            - Dal livello 6 in poi aumentano di 1 ogni livello con un minimo di 9
    
    - MediumEnemy:
        - Vita: 40 (aumenta di un parametro lifeIncreaser pari a lifeIncreaser * numero del livello * 0.5 ad ogni livello)
        - Attacco: 20 quando raggiungono il player
        - Probabilità:
            - Fino al livello 2 non ci sono
            - Dal livello 3 in poi compaiono in quantità pari al numero del livello + un valore casuale tra 0 e 3
            - Al livello 6 smettono di aumentare
    
    - HardEnemy:
        - Vita: 50 (aumenta di un parametro lifeIncreaser pari a lifeIncreaser * numero del livello * 0.25 ad ogni livello)
        - Attacco:
            - 10 sparando
            - 50 se il player ci va sopra
        - Rateo di fuoco: casuale
        - Probabilità:
            - Fino al livello 8 compaiono in quantità pari al numero del livello
            - Dal livello 8 in poi sono 7 + un numero casuale tra 0 e 3

Bonus:
    - LifeBonus:
        - Vita: + 20
        - Probabilità:
            - Fino al livello 5 ne compaiono abbastanza per far tornare la vita del player a 100
            - Dal livello 5 in poi ne compaiono per far tornare la vita del player a 50
    - PointBonus:
        - Punti: + 20
        - Vita: + 50 ogni 200 punti
        - Probabilità:
            - Fino al livello 12 diminuiscono di 1 poi compaiono in quantità randomica in un range tra 25 e 1

