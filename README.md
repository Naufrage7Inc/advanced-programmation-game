# Projet programmation avancée

## Présentation du jeu
Vous incarnez un personnage célèbre personnage du nom de Sacha. Grâce à de la magie rudimentaire car extrêmement ancienne, vous pouvez capturer des petits Pokémons !
  
  
## Organisation du projet
  
### Avancement
Ce qui est possible :
 - Création de la carte, chargement depuis un fichier et affichage
 - Création du personnage, affichage et déplacement ( basique )
 - Gestion des menus
 - Gestion des joueurs ( meilleurs scores )
 - Déplacement des ennemis
  

### Module Engine
Le module Engine apporte plusieurs fonctions facilitant la gestion d'erreurs, l'utilisation de la SDL, ... Un ensemble de fonctions bien pratique !
  
  - *bool* **InitSDL** ( )  
    Permet d'initialiser la SDL en mode vidéo. Retourne vrai en cas de réussite.
    
  - *bool* **CreateWindow** ( SDL_Window** window, const int width, const int height, const char* title )  
    Permet de créer une fenêtre *window* de largeur *width*, de hauteur *height* et de titre *title*. Retourne vrai en cas de réussite.
        
  - *bool* **CreateWindowSurface** ( SDL_Surface** surface, SDL_Window* window )  
    Permet de récupérer la *surface* surface d'une fenêtre *window* créée. Retourne vrai en cas de réussite.
    
  - *void* **CleanupSDL** ( SDL_Window* window )  
    Permet de détruire la fenêtre *window* et décharger la SDL.
    
  - *SDL_Surface** **LoadBMP** ( const char* imagePath )  
    Retourne une image *imagePath* ( format .bmp ).
    
  - *Coord* **CoordCreate** ( const int x, const int y )  
    Retourne une coordonnée ( *x*, *y* ).
    
  - *Size* **SizeCreate** ( const int w, const int h )  
    Retourne une taille de longueur *w* et de hauteur *h*.
    
  - *SDL_Surface** **SurfaceGetResource** ( SDL_Surface* surface, const int nTilesX, const int id )  
    Retourne l'image de la ressource *id* depuis une surface *surface* ayant *nTilesX* tiles sur la longueur.
    
  - *SDL_Surface** **SurfaceCreate** ( const int w, const int h )  
    Retourne une surface vierge de longueur *w* et de hauteur *h*.
    
  - *int* **GetDistance** ( const Coord a, const Coord b )
    Retourne la distance entre la position a et b ( en nombre de bloc )
  
### Module Character
Le module Character permet la manipulation directe d'un personnage : création, déplacement, ... 

  - *enum* **Direction** { UP , DOWN , LEFT , RIGHT }  
    Permet de définir un ensemble de direction: *Haut*, *Bas*, *Gauche* et *Droite*.
  
  - *struct* **Character** { SDL_Surface*, SDL_Rect, Coord, Direction }  
    Permet de définir une structure *Character* qui contient une *surface* ( image du personnage ), un *Rect* ( rectangle qui découpe une partie de l'image du personnage ), une *Coord* ( coordonnée qui détermine la position du personnage sur la carte ) et une *Direction* ( direction du personnage ).

  - *Character** **CharacterCreate** ( const char* imagePath, const Coord position )  
    Retourne un personnage en utilisant l'image *imagePath* à la position *position*.
        
  - *void* **CharacterDraw** ( const Character* character, SDL_Surface* surface )  
    Permet de dessiner le personnage *character* sur une surface *surface*.
        
  - *void* **CharacterMove** ( Character* character, Direction direction )  
    Permet de déplacer un personnage *character* vers la direction *direction*.
    
  - *void* **CharacterFree** ( Character* character )  
    Permet de libérer la mémoire utilisée par le personnage *character*.
  
### Module Map
Le module Map permet la manipulation directe d'une carte : création, affichage, ...

  - *struct* **Map** { SDL_Surface*, Tile* }  
    Permet de définir une structure *Map* qui contient une *surface* ( image du terrain de la carte ), et plusieurs *Tile** ( tableau de blocs de la carte ).
    
  - *Map** **MapCreate** ( const char* imagePath, const char* filePath )  
    Retourne une carte en utilisant l'image *imagePath* dans la carte *filePath*.
    
  - *void* **MapDraw** ( const Map* map, SDL_Surface* surface )  
    Permet de dessiner la carte *map* sur la surface *surface*.

  - *void* **MapFree** ( Map* map )  
    Permet de libérer la mémoire utilisée par la carte *map*.
  
### Module Tile
Le module Tile permet la manipulation directe d'un bloc composant la carte : création et identification du bloc

  - *enum* **Passability** { NO_PASSABLE , PASSABLE }  
    Permet de définir une structure *Tile* qui contient une *surface* ( image du bloc ), et un *entier* ( permet de définir si le bloc est franchissable ).

  - *struct* **Tile** { SDL_Surface*, int }  
    Permet de définir une structure *Tile* qui contient une *surface* ( image du bloc ), et un *entier* ( permet de définir si le bloc est franchissable ).
  
  - *Tile** **TileCreate** ( SDL_Surface* surface, const Passability passability )  
    Retourne un bloc ayant pour surface *surface* où *passability* représente sa franchissabilité sur la carte.
    
### Module Player
Le module Player permet la manipulation des joueurs ( sauvegarde et lecture des meilleurs scores )

  - *enum* **Player** { char*, int }
    Permet de définir une structure *Player* pour contenir le pseudo du joueur et son score.
    
  - *void* **saveScore** ( int score )
     Enregistre le score du joueur et affiche les meilleurs scores dans la console.
     
   - findAndDeleteMin, invert et sort
     Utilisées uniquement pour faciliter la lecture de la fonction de sauvegarde **saveScore**.
  
### Les petites structures
Pour mener à bien ce projet, nous avons intégré quelques structures de base comme Coord ( structure définie par un couple (*x*, *y*) ) et Size ( structure définie par une *longueur* et une *hauteur* ) par exemple.

# Compilation sous Linux
## Compilation de la SDL2
Télécharger le code source disponible à cette adresse : https://www.libsdl.org/download-2.0.php  
Une fois le dossier extrait, configurez le projet avec la commande : *./configure*  
Ensuite, compilez avec : *make*  
Installez le tout avec la commande : *sudo make install*  

## Compilation de SDL2_ttf
Télécharger le code source disponible à cette adresse : https://www.libsdl.org/projects/SDL_ttf/  
Une fois le dossier extrait, configurez le projet avec la commande : *./configure*  
Ensuite, compilez avec : *make*  
Installez le tout avec la commande : *sudo make install*  

## Compilation de SDL2_mixer
Télécharger le code source disponible à cette adresse : https://www.libsdl.org/projects/SDL_mixer/  
Une fois le dossier extrait, configurez le projet avec la commande : *./configure*  
Ensuite, compilez avec : *make*  
Installez le tout avec la commande : *sudo make install*  

## Compilation du projet
Compilez le projet avec la commande make puis lancez le jeu avec la commande : *bin/game*  
Dans le cas où vous n'avez pas configuré le chemin des bibliothèques, lancez le jeu avec : *LD_LIBRARY_PATH=/usr/local/lib bin/game*  
