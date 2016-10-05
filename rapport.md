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
Nous avons buté un moment sur les indices et le positionnement du caractère 'EOF' à la fin des chaînes de caractères.

## Limitations

Pour le moment les méthodes optionnelles de la première partie n'ont pas encore été implémentées par manque de temps. Nous n'avons pas encore étudié les accès concurrents sur le « GetString », en conséquence il n'est pas encore envisageable d'utiliser les "threads" utilisateur, pour l'instant. Les paramètres introduits (tel que "MAX_STRING_SIZE") ne sont pas externalisés et il pourrait être intéressant de le faire pour permettre une utilisation plus agréable et fléxible du système. 

## Tests

Pour le moment les tests réalisés sont relativement simplistes et sont là pour s’assurer qu’une utilisation classique du système ne crée pas de problèmes. Ils consistent principalement à la création de fichiers similaire à "putchar.c" mais avec des appels à des fonctions différentes pour pouvoir tester les méthodes dans des conditions normales d'utilisations. Par exemple, tester l'écriture via "putString" de chaînes de caractères plus ou moins longue que la définition de la taille maximum des chaines de caractère ("MAX_STRING_SIZE").

Le test suivant permet de mettre en évidence le fait que 

    echo  "c" | ./userprog/nachos -d s -x ./test/getstring
    GetString
    PutString
    c
    Shutdown, initiated by user program.
