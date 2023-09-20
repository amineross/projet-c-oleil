
# Libraries
SDL2

# IDE
VS Code 
Clion

# Réflection individuelle
## Objectifs
1. Rédiger une documentation technique simplifiée (sections suivantes).
2. Discussion et partage d'idées entre les membres dugroupe.
3. Lire les docs de la section *Lien utiles* notamment: SDL2, SDL\_GFX avec Visual Studio et les différents liens de calcul physique.
4. Se familiariser avec les concepts physiques de gravité et de mouvement.
5. Essayer de recréer la structure de fichiers demandée et d'avoir une fenetre graphique vierge.
6. Répartition des taches selon les compétences de chaque membre du groupe.

## Mon expérience en C 
Environ 4 ans de développement en C.
*Github https://github.com/amineross*


# Structures
Game
-> Score
-> Controls
-> Portals = {StartPortal; EndPortal}

Portal
-> Color = #FFFFFF | rgb(255,255,255) (WHITE)
-> Height; Width = 5px
-> PosX; PosY

Solar system
-> Sun
-> Planets
-> Spaceship

Planet
-> PosX, PosY
-> Radius
-> Orbit
-> Mass
-> Orbit duration
*Radius = Mass = OrbitDuration*

Spaceship
-> Color = #FF0000 | rgb(255,0,0)  (RED)
-> Height = 10px
-> Width = 10px
-> Mass = 2
-> Speed {2; 8}
-> Velocity {1/2 initial speed ; 2x initial speed}

# Game logic
*Planets PosX;PosY are constant*
*Planets are unaffected by other planets gravities*
*Planets movement is exclusively circular*

*Spaceship is the only object affected by gravity*
*G = 1000* 

*Game ends when Distance(Spaceship, EndPortal) < 5px*

# GUI
WIN\_SIZE (Window Size)
WIN\_TITLE (Not constant): ProjetC_oleil | FPS : XX.X | Score : X 
FPS\_CAP = 60 FPS
FRAME\_COLOR = WHITE
FRAME\_MARGIN = 10px

# Controls
ESCAPE     : Closes window
SPACE      : Starts gameplay
V          : Toggle Vectors (init = OFF)
ARR\_RIGHT : Turn Right
ARR\_LEFT  : Turn Left

# Config files
File type : .txt
Attributes: (See docs)
*Rejectable if not valid*



