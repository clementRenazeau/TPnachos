# Rapport TP1 Nachos: Entrées/Sorties

Clément Renazeau & Thomas Loubiou


## Bilan

Dans cette première partie il nous a été demandé de découvrir le fonctionnement de Nachos par une étude préalable, en surface du code, pour ensuite nous lancer dans l'implémentation de la des entrées/sorties en mode synchrone.
Pour ce faire il a fallu ajouter un certain nombre de fichiers comme demandé dans le fascicule de TD, à savoir:

* `userprog/synchConsole`, une classe qui gère les entrées/sorties consoles en mode synchrone, en encapsulant la classe Console qui fonctionne de manière asynchrone.
    * Il faut noter que l'implémentation de la fonction SynchGetString de cette classe diffère de celle proposée par l'énoncer du TP:
    elle retourne le nombre de caractères copiés dans le buffer de sortie, afin de faciliter son utilisation.
* `threads/sysutils`, qui regroupe des fonctions utilitaires systèmes facilitant la communication noyau/programme utilisateur depuis le noyau.
    Nous avons décidé de les mettre dans un fichier séparé du reste du système pour une réutilisation simplifiée,
    et éventuellement pouvoir ajouter de manière visible de nouvelles fonctions dans la suite du projet si le besoin s'en fait sentir.
    C'est dans ce fichier que sont implémentés:

    * copyStringFromMachine, la fonction permettant de copier une chaîne de caractères depuis l'espace utilisateur MIPS vers l'espace noyau.
    * copyStringToMachine, la fonction permettant de copier une chaîne de caractères depuis l'espace noyau vers l'espace utilisateur MIPS.

D'autres fichiers ont dus être modifiés pour répondre aux questions du TP:

 * `test/Start.S` qui contient le code assembleur chargé d'effectuer les appels systèmes, mais également de définir la fonction `\_start` qui est le réel point d'entré d'un programme C.
   C'est également ce point d'entré qui retourne la valeur retournée par la fonction `main` du programme vers le noyau.
   Dans l'implémentation originale, cette valeur était perdue, dans notre version elle a été sauvegardée dans le registre 4.
   De plus la gestion de l'exception `SC_Exit` correspondante n'avait pas été implémentée. Cela a été corrigé.
 * `userprog/exception` qui implémente toutes les interruptions possibles, notamment les interruptions logicielles envoyées par les programmes utilisateurs afin de communiquer avec le noyau.

    * Dans le cadre de l'utilisation de `Get_Char` il est a noté que nous retournons la valeur de la macro `EOF`.

## Points délicats

Le début de l'implémentation étant assez simple, c’est finalement les dernières méthodes qui se sont révélés les plus ardus à implémenter. 
Notamment les appels système `SC_GetString` et `SC_PutString`. Ce sont ces appels qui nous ont demandés le plus de reflexion : 

- pour l'appel `SC_GetString` l'utilisateur doit pouvoir demander à récuperer une très longue chaîne de caractères et nous devons être en mesure de restituer cette chaîne en se servant d'un buffer de taille réduite. La chaîne entrée par l'utilisateur est découpée en plusieurs morceaux qui sont copiés un à un dans l'espace mémoire du programme utilisateur,
- l'appel système `SC_PutString` nous a posé le même problème, si l'utilisateur passe une chaîne de 1Mo il ne faut pas que le noyau alloue un buffer de la même taille. 
On doit également procéder par morceaux,
- Nous avons buté un moment sur les indices et le bon positionnement du caractère `NULL` à la fin des chaînes de caractères.

Il est également à noter que l'implémentation de l'appel système `SC_GetInt` a nécessité une attention particulière, car contrairement à `GetChar`,
la valeur de retour passe ici par un pointeur. Il a donc fallu allouer une variable temporaire de type `int` dans le noyau, remplir ce buffer et au final le recopier dans la mémoire
du programme utilisateur à l'adresse spécifiée. Cette opération de recopie a entrainée la création d'une méthode utilitaire `copyIntToMachine(int val, int addr)`.

## Limitations

Pour le moment la méthode optionnelle `printf` de la première partie n'a pas encore été implémentée par manque de temps.

Nous n'avons pas encore étudié les accès concurrents sur le `GetString`, en conséquence il n'est pas encore envisageable d'utiliser les `threads` utilisateur: 
en effet des appels concurrents à la routine noyau `SC_GetString` produiraient un résultat indéterminé pour les 2 appelants, chacun ayant une partie de la chaine de caractères.

Par exemple, si 2 threads essaient en même temps de récupérer une chaine de caractères depuis l'entrée utilisateur,
et que l'utilisateur entre `abcd\ne\n`, le thread 1 pourra récupérer `ad\n` alors que le thread 2 récupérera `bce\n`.

Les paramètres introduits (tel que `MAX_STRING_SIZE`) ne sont pas externalisés et il pourrait être intéressant de le faire pour permettre une utilisation plus agréable et flexible du système. 

## Tests

Pour le moment les tests réalisés sont relativement simplistes et sont là pour s’assurer qu'une utilisation classique du système ne crée pas de problèmes.
Ils consistent principalement à la création de fichiers similaire à `putchar.c` mais avec des appels à des fonctions différentes,
pour pouvoir tester les méthodes dans des conditions normales d'utilisations.
Par exemple, tester l'écriture via `putString` de chaînes de caractères plus ou moins longue que la définition de la taille maximum des chaines de caractère (`MAX_STRING_SIZE`).

Le test suivant permet de mettre en évidence le fait que notre implémentation s'arrête bien quand `GetString` rencontre la fin du fichier.

```bash
$ echo  "c" | ./userprog/nachos -d s -x ./test/getstring
GetString
PutString
c
Shutdown, initiated by user program.
```
