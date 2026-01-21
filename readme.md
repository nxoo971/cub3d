# Cub3D

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![MiniLibX](https://img.shields.io/badge/MiniLibX-Graphics-blue?style=flat-square)
![Raycasting](https://img.shields.io/badge/Raycasting-3D-red?style=flat-square)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)

> Moteur 3D inspiré de Wolfenstein 3D - Projet graphique 42

## 📋 Description

**Cub3D** est un projet graphique inspiré du légendaire **Wolfenstein 3D**, considéré comme le premier vrai FPS de l'histoire. Le projet consiste à créer une vue 3D "réaliste" d'un labyrinthe depuis une perspective à la première personne, en utilisant la technique du **raycasting**.

Ce projet permet de découvrir les mathématiques du rendu 3D, la MiniLibX, et les bases de la programmation graphique temps réel.

## 🎯 Objectifs pédagogiques

- Comprendre et implémenter le **raycasting**
- Maîtriser les mathématiques du rendu 3D (vecteurs, angles, projections)
- Gérer les événements en temps réel (clavier, souris)
- Parser et valider des fichiers de configuration complexes
- Optimiser le rendu graphique pour maintenir de bonnes performances
- Travailler en équipe sur un projet technique

## 🚀 Installation et utilisation

### Compilation

```bash
# Cloner le repository
git clone https://github.com/nxoo971/cub3d.git
cd cub3d

# Compiler le projet
make

# Nettoyer
make clean
make fclean
make re
```

### Exécution

```bash
./cub3D maps/simple.cub
```

**Exemple de carte minimale** (`maps/simple.cub`) :

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

## 🎮 Contrôles

### Déplacements

- **W** : Avancer
- **S** : Reculer
- **A** : Déplacement latéral gauche (strafe)
- **D** : Déplacement latéral droit (strafe)

### Caméra

- **←** : Rotation caméra vers la gauche
- **→** : Rotation caméra vers la droite
- **Souris** : Rotation de la caméra (bonus)

### Autres

- **ESC** : Quitter le jeu
- **Croix rouge** : Fermer la fenêtre

## 🗺️ Format du fichier .cub

### Structure générale

Le fichier de configuration se divise en deux parties :

1. **Configuration des textures et couleurs**
2. **Carte du niveau**

### 1. Textures (4 obligatoires)

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
```

- `NO` : Texture du mur nord
- `SO` : Texture du mur sud
- `WE` : Texture du mur ouest
- `EA` : Texture du mur est

### 2. Couleurs (sol et plafond)

```
F 220,100,0    (Floor - Sol en RGB)
C 225,30,0     (Ceiling - Plafond en RGB)
```

Format : `R,G,B` avec valeurs entre 0 et 255

### 3. Carte du niveau

| Caractère | Signification |
|-----------|---------------|
| `0` | Espace vide (où le joueur peut marcher) |
| `1` | Mur |
| `N` | Position de départ du joueur (orientation Nord) |
| `S` | Position de départ du joueur (orientation Sud) |
| `E` | Position de départ du joueur (orientation Est) |
| `W` | Position de départ du joueur (orientation Ouest) |
| ` ` (espace) | Zone vide/extérieure |

### Exemple complet

```
NO ./textures/stone_north.xpm
SO ./textures/stone_south.xpm
WE ./textures/wood_west.xpm
EA ./textures/wood_east.xpm

F 100,50,25
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## ✅ Validation du parsing (ma partie)

### Vérifications obligatoires

#### Textures

- ✅ 4 textures présentes (NO, SO, WE, EA)
- ✅ Chemins valides et fichiers existants
- ✅ Format .xpm valide
- ✅ Pas de doublons
- ✅ Textures chargeables par MiniLibX

#### Couleurs

- ✅ Couleurs F (floor) et C (ceiling) présentes
- ✅ Format RGB correct (R,G,B)
- ✅ Valeurs entre 0 et 255
- ✅ Pas de doublons

#### Carte

- ✅ Un seul joueur (N, S, E, ou W)
- ✅ Carte fermée (entourée de murs)
- ✅ Caractères valides uniquement (0, 1, N, S, E, W, espace)
- ✅ Pas de "trous" dans les murs
- ✅ Forme rectangulaire ou valide
- ✅ Au moins une case praticable (0)

### Erreurs à détecter

```bash
# Fichier inexistant
./cub3D maps/nonexistent.cub
Error: Cannot open file

# Extension invalide
./cub3D maps/map.txt
Error: Invalid file extension

# Texture manquante
Error: Missing texture NO

# Couleur invalide
Error: Invalid RGB value (must be 0-255)

# Plusieurs joueurs
Error: Multiple player positions

# Carte ouverte
Error: Map is not closed by walls

# Caractère invalide
Error: Invalid character in map
```

### Projection 3D

Formule clé pour la hauteur du mur à l'écran :

```
hauteur_mur = (hauteur_écran / distance_au_mur) × facteur_échelle
```

## 🔧 Fonctionnalités

### Partie obligatoire

- ✅ Affichage 3D d'un labyrinthe en vue FPS
- ✅ Textures différentes selon l'orientation (N/S/E/W)
- ✅ Couleurs différentes pour sol et plafond
- ✅ Déplacements fluides (WASD)
- ✅ Rotation de la caméra (flèches)
- ✅ Gestion propre de la fermeture (ESC, croix)
- ✅ Parsing complet et validation stricte
- ✅ Aucune fuite mémoire

### Tests de rendu

```bash
./cub3D maps/mapfoot.cub

# Vérifier les fuites mémoire
valgrind --leak-check=full ./cub3D maps/mapfoot.cub
```

### Checklist de validation

**Parsing :**
- [ ] Extension .cub vérifiée
- [ ] Fichier existe et est lisible
- [ ] 4 textures (NO, SO, WE, EA) présentes
- [ ] Textures chargeables (.xpm valides)
- [ ] Couleurs F et C au bon format
- [ ] RGB entre 0-255
- [ ] Un seul joueur sur la carte
- [ ] Carte fermée
- [ ] Pas de caractères invalides
- [ ] Gestion de tous les cas d'erreur

**Rendu :**
- [ ] Textures correctement appliquées
- [ ] Déplacements WASD fonctionnels
- [ ] Rotation caméra fluide
- [ ] Sol et plafond aux bonnes couleurs
- [ ] Fermeture propre (ESC, croix)

## 👥 Équipe

Ce projet a été réalisé à deux.

**Membres de l'équipe :**
- Membre - `Rayan: @rferradi`

## 🎓 Compétences développées

### Parsing (ma partie)

- Parsing de fichiers complexes
- Validation de données
- Gestion d'erreurs robuste
- Algorithmes de recherche (flood fill)
- Structure de données (grilles 2D)

### Raycasting (partie globale)

- Mathématiques 3D (vecteurs, trigonométrie)
- Algorithmes de rendu graphique
- Optimisation de performances
- Programmation graphique temps réel
- Gestion d'événements
- Travail en équipe

## 📄 Licence

Ce projet est réalisé à des fins pédagogiques dans le cadre du cursus 42.