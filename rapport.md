% Rapport TP1 Nachos: Entrées/Sorties
% Clément Renazeau & Thomas Loubiou
% 5 Octobre 2016

# Rapport TP Nachos n°1


## Bilan

Dans cette première partie il nous a été demandé de découvrir le fonctionnement de Nachos par une étude préalable, en surface du code, pour ensuite nous lancer dans l’implémentation de la des entrées/sorties en mode synchrone.
Pour ce faire il a fallu ajouter un certain nombre de fichiers comme demandé dans le fascicule de TD, à savoir:

* `userprog/synchConsole`, une classe qui gère les entrées/sorties consoles en mode synchrone, en encapsulant la classe Console qui fonctionne de manière asynchrone.
    * Il faut noter que l'implémentation de la fonction SynchGetString de cette classe diffère de celle proposée par l'énoncer du TP:
    elle retourne le nombre de caractères copiés dans le buffer de sortie, afin de faciliter son utilisation.
* `threads/sysutils`, qui regroupe des fonctions utilitaires systèmes facilitant la communication noyau/programme utilisateur depuis le noyau. C'est dans ce fichier que sont implémentés:
    * copyStringFromMachine, la fonction permettant de copier une chaîne de caractères depuis l'espace utilisateur MIPS vers l'espace noyau.
    * copyStringToMachine, la fonction permettant de copier une chaîne de caractères depuis l'espace noyau vers l'espace utilisateur MIPS.

D'autres fichiers ont dus être modifiés pour répondre aux questions du TP:

 * `test/Start.S` qui contient le code assembleur chargé d'effectuer les appels systèmes, mais également de définir la fonction `\_start` qui est le réel point d'entré d'un programme C.
   C'est également ce point d'entré qui retourne la valeur retournée par la fonction `main` du programme vers le noyau.
   Dans l'implémentation originale, cette valeur était perdue, dans notre version elle a été sauvegardée dans le registre 4.
   De plus la gestion de l'exception SC_Exit correspondante n'avait pas été implémentée. Cela a été corrigé.

## Points délicats

Le début de l’implémentation étant assez simple, c’est finalement les dernières méthodes qui se sont révélés les plus ardus à implémenter. Notamment les méthodes « SynchGetString » et « SynchPutString ».
Nous avons buté un moment sur les indices et le positionnement du caractère 'EOF' à la fin des chaînes de caractères.

## Limitations

Pour le moment les méthodes optionnelles de la première partie n'ont pas encore été implémentées par manque de temps. Nous n'avons pas encore étudié les accès concurrents sur le « GetString », en conséquence il n'est pas encore envisageable d'utiliser les "threads" utilisateur, pour l'instant. Les paramètres introduits (tel que "MAX_STRING_SIZE") ne sont pas externalisés et il pourrait être intéressant de le faire pour permettre une utilisation plus agréable et fléxible du système. 

## Tests

Pour le moment les tests réalisés sont relativement simplistes et sont là pour s’assurer qu’une utilisation classique du système ne crée pas de problèmes. Ils consistent principalement à la création de fichiers similaire à "putchar.c" mais avec des appels à des fonctions différentes pour pouvoir tester les méthodes dans des conditions normales d'utilisations. Par exemple, tester l'écriture via "putString" de chaînes de caractères plus ou moins longue que la définition de la taille maximum des chaines de caractère ("MAX_STRING_SIZE").

Le test suivant permet de mettre en évidence le fait que 

```bash
$ echo  "c" | ./userprog/nachos -d s -x ./test/getstring
GetString
PutString
c
Shutdown, initiated by user program.
```
