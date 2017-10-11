# Projet programmation avancée

## Présentation du jeu
Vous incarnez un personnage célèbre personnage du nom de Sacha. Grâce à de la magie rudimentaire car extrêmement ancienne, vous pouvez capturer des petits Pokémons !
  
  
## Organisation du projet
  
### Avancement
Ce qui est possible :
 - Création de la carte et affichage ( basique )
 - Création du personnage, affichage et déplacement ( basique )
 - Création d'une map en fonction d'un fichier 

Ce qui sera bientôt possible :
 - Gestion des animations du personnage ( effet de marche )
 - Création, affichage et gestion des Pokémons
 - Création du menu principal
  

### Module Engine
Le module Engine apporte plusieurs fonctions facilitant la gestion d'erreurs, l'utilisation de la SDL, ... Un ensemble de fonctions bien pratique !
  
  - bool **InitSDL**()  
    Permet d'initialiser la SDL en mode vidéo. Retourne vrai en cas de réussite.
    
  - bool **CreateWindow**( SDL_Window** window, const int width, const int height, const char* title )  
    Permet de créer une fenêtre *window* de largeur *width*, de hauteur *height* et de titre *title*. Retourne vrai en cas de réussite.
        
  - bool **CreateWindowSurface**( SDL_Surface** surface, SDL_Window* window )  
    Permet de récupérer la *surface* surface d'une fenêtre *window* créée.
    
  
  
### Module Character
Le module Character permet la manipulation directe d'un personnage : création, déplacement, ... 
  
  
### Module Map
Le module Map permet la manipulation directe d'une carte : création, affichage, ...
  
  
### Module Tile
Le module Tile permet la manipulation directe d'un bloc composant la carte : création et identification du bloc ( traversable ou non )
  
  
### Les petites structures
Pour mener à bien ce projet, nous avons intégré quelques structures de base comme Coord et Size par exemple.
