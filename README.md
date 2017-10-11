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
  
  - *bool* **InitSDL**( )  
    Permet d'initialiser la SDL en mode vidéo. Retourne vrai en cas de réussite.
    
  - *bool* **CreateWindow**( SDL_Window** window, const int width, const int height, const char* title )  
    Permet de créer une fenêtre *window* de largeur *width*, de hauteur *height* et de titre *title*. Retourne vrai en cas de réussite.
        
  - *bool* **CreateWindowSurface**( SDL_Surface** surface, SDL_Window* window )  
    Permet de récupérer la *surface* surface d'une fenêtre *window* créée. Retourne vrai en cas de réussite.
    
  - *void* **CleanupSDL**( SDL_Window* window )  
    Permet de détruire la fenêtre *window* et décharger la SDL.
    
  - *SDL_Surface** **LoadBMP**( const char* imagePath )  
    Retourne une image *imagePath* ( format .bmp ).
    
  - *Coord* **CoordCreate**( const int x, const int y )  
    Retourne une coordonnée ( *x*, *y* ).
    
  - *Size* **SizeCreate**( const int w, const int h )  
    Retourne une taille de longueur *w* et de hauteur *h*.
    
  - *SDL_Surface** **SurfaceGetResource**( SDL_Surface* surface, const int nTilesX, const int id )
    Retourne une image depuis une surface *surface* ayant *nTilesX* tiles sur la longueur
  
### Module Character
Le module Character permet la manipulation directe d'un personnage : création, déplacement, ... 

  - *enum* **Direction** { UP , DOWN , LEFT , RIGHT }  
    Permet de définir un ensemble de direction: *Haut*, *Bas*, *Gauche* et *Droite*.
  
  - *struct* **Character** { SDL_Surface* , SDL_Rect , Coord , Direction }  
    Permet de définir une structure *Character* qui contient une *surface* (image du personnage), un *Rect* (rectangle qui découpe une partie de l'image du personnage), une *Coord* (coordonnée qui détermine la position du personnage sur la carte) et une *Direction* (direction du personnage).

  - *Character** **CharacterCreate**( const char* imagePath, const Coord position )  
    Retourne un personnage en utilisant l'image *imagePath* à la position *position*.
        
  - *void* **CharacterDraw**( const Character* character, SDL_Surface* surface )  
    Permet de dessiner le personnage *character* sur une surface *surface*.
        
  - *void* **CharacterMove**( Character* character, Direction direction )  
    Permet de déplacer un personnage *character* vers la direction *direction*.
    
  - *void* **CharacterFree**( Character* character )  
    Permet de libérer la mémoire utilisée par le personnage *character*.
  
### Module Map
Le module Map permet la manipulation directe d'une carte : création, affichage, ...
  
  
### Module Tile
Le module Tile permet la manipulation directe d'un bloc composant la carte : création et identification du bloc ( traversable ou non )
  
  
### Les petites structures
Pour mener à bien ce projet, nous avons intégré quelques structures de base comme Coord et Size par exemple.
