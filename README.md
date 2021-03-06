# Projet programmation avancée

## Présentation du jeu
Vous incarnez un personnage célèbre personnage du nom de Sacha. Grâce à de la magie rudimentaire car extrêmement ancienne, vous pouvez capturer des petits Pokémons !
  
  
## Organisation du projet
  
### Avancement
Ce qui est possible :
 - Création de la carte et affichage
 - Création du personnage, affichage et déplacement
 - Création, affichage et gestion des Pokémons
 - Création du menu principal
 - Gestion des scores et des meilleurs joueurs !  

### Module Engine
Le module Engine apporte plusieurs fonctions facilitant la gestion d'erreurs, l'utilisation de la SDL, ... Un ensemble de fonctions bien pratique !
  
  - *struct* **Coord** {  int x, int y }  
    Structure pour contenir une coordonnée représentée par un point X et un point Y.
  
  - *struct* **Size** { int w, int h }  
    Strucutre pour contenir une taille représentée par sa longueur et sa hauteur.
  
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
    Permet de retourner la valeur de la distance entre a et b.
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
    
### Module List
Le module permet la manipulation directe d'une liste : Primitives (Verifier si elle est vide, créer une liste, ... ), libération...

  - *struct* **TListElem** struct TListElem { *ptr, *next}  
    Permet de définir un élèment de la liste qui contient un pointeur sur l'élèment et un pointeur sur le prochain élèment de la liste.
    
  - *bool*  **IsEmpty** ( TList list )  
    Permet de vérifier si la liste est vide.
  
  - *void** **Head** ( TList list )  
    Permet de retourner le pointeur du premier élèment de la liste.
  
  - *TList* **Rest** ( TList list )  
    Retourne le reste des élèments de la liste sans le premier.
  
  - *TList* **CreateEmpty** ()  
    Permet de créer une liste vide.
  
  - *TList* **Create** ( void *ptr, TList list )  
    Permet de Créer une liste.
  
  - *void* **ModifyHead** ( void *ptr, TList list )  
    Permet de modifier la première valeur de la liste.
  
  - *void*  **ModifyRest** ( TList a, TList b )  
    Permet de modifier le reste de la liste.
  
  - *TList* **DeleteItem** ( TList item, TList list )  
    Permet de supprimer un élément de la liste.
  
  - *void*  **FreeList** ( TList list )  
    Permet de libérer la mémoire une liste.
  
### Module Tile
Le module Tile permet la manipulation directe d'un bloc composant la carte : création et identification du bloc ( traversable ou non )

  - *enum* **Passability** { NO_PASSABLE , PASSABLE }  
    Permet de définir une structure *Tile* qui contient une *surface* ( image du bloc ), et un *entier* ( permet de définir si le bloc est franchissable ).

  - *struct* **Tile** { SDL_Surface*, int }  
    Permet de définir une structure *Tile* qui contient une *surface* ( image du bloc ), et un *entier* ( permet de définir si le bloc est franchissable ).
  
  - *Tile** **TileCreate** ( SDL_Surface* surface, const Passability passability )  
    Retourne un bloc ayant pour surface *surface* où *passability* représente sa franchissabilité sur la carte.
  
  - *void* **TileFree** ( Tile *tile )  
    Permet de libérer un bloc.
  
### Module Player
Le module Player permet la sauvegarde des scores des joueurs et d'ainsi connaître le meilleur score.

  - *struct* **Player** { char* pseudo, int score }  
    Structure qui permet de stocker le résultat d'un joueur.
    
  - *Tlist* **findAndDeleteMin** ( TList *input )  
    Permet de chercher et de supprimer le minimum de la liste, il doit y avoir au moins un élément dans la liste.
    
  - *Tlist* **invert** ( Tlist input )  
    Permet de retourner la liste inversé.
    
  - *Tlist* **sort** ( Tlist input )  
    Permet de trier la liste de manière décroissante.
    
  - *void* **saveScore** ( int score )  
    Permet de sauvegarder les scores dans la variable score.
  
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
N'oubliez pas de créer un dossier bin et obj à la racine du projet ( même niveau que ce Makefile ) sinon la compilation provoquera une erreur !
Compilez le projet avec la commande make puis lancez le jeu avec la commande : *bin/game*  
Dans le cas où vous n'avez pas configuré le chemin des librairies, lancez le jeu avec : *LD_LIBRARY_PATH=/usr/local/lib bin/game*  

## Crédits
Porjet développé par Théo Barragué <theo.barrague2@etu.univ-lorraine.fr> et Vincent Bir <vincent.bir1@etu.univ-lorraine.fr>
