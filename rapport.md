% Rapport TP1 Nachos: Entrées/Sorties
% Clément Renazeau & Thomas Loubiou
% 5 Octobre 2016

# Rapport TP Nachos n°1


## Bilan

Dans cette première partie il nous a été demandé de découvrir le fonctionnement de Nachos par une étude préalable, en surface du code, pour ensuite nous lancer dans l’implémentation de la synchronisation des entrées et des sorties. Pour ce faire il a fallu ajouter un certain nombre de fichiers comme demandé dans le fascicule de TD. 

- sysutils
- synchgetstring renvoie int au lieu de void
- halt → exit
- copyStringFromMachine

## Points délicats

Le début de l’implémentation étant assez simple, c’est finalement les dernières méthodes qui se sont révélés les plus ardus à implémenter. Notamment les méthodes « SynchGetString » et « SynchPutString ».
Nous avons buté un moment sur les indices et le positionnement du caractère EOF 

## Limitations


Pas les bonus, pas d’accès concurrent sur le « GetString », les paramètres introduits ne sont pas externalisés. 

## Tests

Pour le moment les tests réalisés sont relativement simplistes et sont là pour s’assurer qu’une utilisation classique du système ne crée pas de problèmes.

    echo  "c" | ./userprog/nachos -d s -x ./test/getstring
    GetString
    PutString
    c
    GetString
    PutString
    Shutdown, initiated by user program.
