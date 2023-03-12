---
title: Perfectionnement à la programmation C
subtitle: TP5 - Snake
date: 6 mars 2023
colorlinks: true
author:
    - Nicolas SEBAN
    - Amir POUYANFAR
lang: fr # texlive-lang-french / texlive-babel-french
geometry: margin=2.5cm
header-includes:
    - \usepackage{graphicx}
    - \usepackage{fancyhdr}
    # <https://ctex.org/documents/packages/layout/fancyhdr.pdf>
    - \pagestyle{fancy}
    - \rhead{}
    - \lhead{}
    - \renewcommand{\headrulewidth}{0pt}
    - \renewcommand{\footrulewidth}{0.2pt}
    - \lfoot{\includegraphics[height=0.8cm]{logos/namedlogoUGE.png}}
    - \rfoot{\includegraphics[height=1cm]{logos/logoLIGM.png}}
...

\pagebreak

# Introduction

Le sujet de cette semaine consiste à programmer un jeu mythique : le Snake.

Le but du jeu est de faire grandir le serpent en mangeant des pommes, et sans se mordre la queue.
Le serpent peut se déplacer dans les quatre directions mais pas en diagonale, et ne peut faire demi-tour. Le jeu se termine quand le serpent se mord la queue ou atteint le bord du jeu.

# Compilation

Afin de compiler ce projet, nous avons créé un Makefile, vous pouvez alors utiliser la commande suivante :

```shell
make
```

Les fichiers objets et l'exécutable seront créés dans le dossier `build`.
Vous pouvez utiliser la commande suivante pour supprimer les fichiers objets :

```shell
make clean
```

# Utilisation

Pour lancer le jeu, veuillez vous situer dans le dossier `build` avec ``cd build`` et utiliser la commande suivante :

```shell
./main
```

Le jeu est paramétrable à l'aide du fichier `serpent.ini` situé dans le dossier `build`.
Les options disponibles sont les suivantes :

- `largeur` : largeur du monde (en nombre de cases)
- `hauteur` : hauteur du monde (en nombre de cases)
- `nombre_pommes` : nombre de pommes dans le monde
- `taille_serpent` : taille du serpent au début de la partie
- `duree_tour` : durée d'un tour (en millisecondes)
- `pourcentage_pommes_empoisonnees` : pourcentage de pommes empoisonnées dans le monde
- `son` : activer/désactiver le son (Utilise le caractère `BEL`)

L'interface est très simple, elle se compose du monde et du score.

\pagebreak

# Réponses

## Exercice 1

1. Le projet est divisé en plusieurs modules :

    - `main` : contient la fonction `main` et la boucle de jeu principale.
    - `interface` : contient les fonctions d'interface avec l'utilisateur.
    - `list` : contient les fonctions de manipulation de la liste chaînée.
        - Les listes sont implémentées avec des macros, à la manière de ``<sys/queue.h>``, afin de pouvoir utiliser des listes de types différents, et par conséquent d'éviter de la redondance.
        Contrairement à cette bibliothèque il est également possible de libérer les listes, et il est assumé que les types définis implémentent un pointeur vers la cellule suivante nommée ``next``.
    - `monde` : Manipulation du monde (évolution du serpent).
    - `random` : Génération de nombres aléatoires.
    - `serpent` : Manipulation du serpent (avancement, prochaine case visée).
    - `pomme` : Manipulation des pommes (génération et ajout/suppression de la liste).
    - `temps` : Le type PeriodicChrono, et des fonctions permettant d'attendre un point dans le temps.
    - `ini_parser` : Parseur du fichier de configuration

2. Certains prototypes ont été modifiés par rapport à l'énoncé :

    - ``void interface_piloter(Monde *mon)``{.c} a été modifié afin de renvoyer une valeur représentant un appui signifiant la fin du jeu.
    - Celles-ci ont été modifiées afin de renvoyer un entier pour permettre de remonter les erreurs d'allocation de mémoire :
        - ``void monde_evoluer_serpent(Monde* mon)``{.c}
        - ``void monde_ajouter_pomme(Monde* mon, PommeType type)``{.c}

# Améliorations

Parmi les améliorations proposées nous avons choisi d'apporter celles-ci au projet :

- ($\star$) La possibilité de mettre le jeu en pause avec la touche ``p``.
- ($\star$) La création de pommes empoisonnées, qui font perdre le jeu si mangées. (Le pourcentage de pommes empoisonnées est paramétrable)
- ($\star$) La création aléatoire de pommes particulières qui ajoutent deux points aux score.
- ($\star\star$) Des sons à chaque déplacement du serpent, quand il mange ou quand il perd, à l'aide du caractère ``BEL``. (les trois cas ne peuvent pas se distinguer car il n'existe pas de différents caractères ``BEL``).
- ($\star\star\star$) La possibilité de modifier les paramètres du jeu à l'aide d'un fichier de configuration.

# Difficultés rencontrées

Pour le chargement du fichier de configuration, nous devons allouer la mémoire nécessaire pour le nom du paramètre et sa valeur.\
En examinant le manuel C de la fonction ``scanf`` (``man 3 scanf``), nous avons découvert que celle-ci est capable de gérer l'allocation dynamique de la mémoire à l'aide du spécificateur ``m``. Nous l'avons donc utilisée.\
Cependant, ceci est une fonctionnalité POSIX, non conforme à la norme ISO C, ce qui peut générer des warnings lors de la compilation avec l'option ``-pedantic``.
