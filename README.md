# funtartica
2D Game Engine with LUA scripts.

# Compile

The fastest compile:  
```bash
./configure  
make
```  
The advanced ./configure parameters:  
```bash
./configure <parameters>
```
Parameters:  
> -h,-help,--help  - This help message.  
> -c,--compiler [gcc|clang]  - Select compiler.  
> -d,--debug  - Enable debug mode.  
> --no-debug - Disable debug mode.  
> -l,--lua [luajit|lua51|lua53]  - Select LUA version.  
> -m,--mem  - Debug memory leak (sanitizer).  
> --no-mem  - Disable sanitizer memory leak debug.  

# Run  
```bash
./ge
```

### TODO LIST

Sistem:
* [X] Command line parameters.  
* [X] Set path (and name) of the config file (aka ge.ini).  
* [ ] Refac. animacaoN variables.  
* [ ] Refac. speed of game based in FPS.  
* [ ] Refac. filenames .c and .h .  
* [ ] Add LUA script call trigger in ge.ini.  
* [ ] Add quick profiles for creating games.  

Input:
* [ ] Read key definitions in ge.ini.  
* [ ] Read joystick definitions in ge.ini.  
* [ ] Read touch command definitions in ge.ini.  

Sound systm:
* [ ] Change the playsound so that it refers to names and numbers of sound effects.  

Debug and terminal system:
* [X] Add terminal Quake like, \<F12\> to open.  
* [X] Add open and close animation.  
* [X] Add command /show[ variable],/ls[ variable] - List variables.  
* [X] Add command /set \<variable name\> \<int\>  -Create variable or change variable and set the content.
* [X] Add command /pause|/stop - Pause animations and scripts.  
* [X] Add command /unpause|/cont|/continue - Unpause animations and scripts.  
* [ ] Add command /debugon|/debug on - Show debug log on terminal.  
* [ ] Add command /debugoff|/debug off - Hide debug log on terminal.  
* [ ] Add /cls|/clear|/home - Clear terminal and go to first line in top. * Fix a Bug  
* [ ] Fix CTRL+V in terminal.  
* [ ] Fix CTRL+C in terminL.  
* [ ] Add autocomplete in terminal.  
* [X] Show and blink terminal cursor.  
* [X] Add horizontal movement in text cursor on the terminal.
* [X] Add horizontal movement between words in the terminal cursor, CTRL+-\> and CTRL+\<- 
* [X] Add delete word, CTRL+BACKSPACE and CTRL+DELETE.  
* [ ] Fix the paging of the terminal.  
* [ ] Add instant command for create and show sprites.  
* [ ] Add save sprite command: /savesprt \<name\> \<name file\>  
* [ ] Add edit .ini file command: /edit \<ini file\>  

LOG:
* [X] Functions DBG()/ERR()/MSG(), prints line text in the terminal and saves to the log file.

Screen:
  Trabalhar proporção de frame image x spritex x,y do .ini x screen real: /
* [X] Fix colision boxes.  
* [ ] Fix the draw of colision an sprite boxes.  

Zoom, camera:
* [X] Print mirrored images: (h)flip=[0/1]  
* [ ] Print upside down images: vflip=[0/1]  
* [ ] Print the image at a given angle: angle=[0..360]  
  -Integação a tilemap, ver abaixo.

Animation:
* [ ] Refactor of animation definition on sprites, increase animations.
* [ ] Change the animation indice on events.
* [ ] Exec. Lua ini animation.
* [ ] Exec. Lua update animation.
* [ ] Exec. Lua end animation.

Tileset:
* [X] Function to assemble tileset.  
* [ ] Camera control and zoom in the tile scenario.  
* [ ] Add solidity, hole and trigger characteristics of tiles.  
  
TTF fonts:
* [X] Load multiples fonts via config gile (ge.ini).  
* [ ] Add LUA function to display text on game screen.  
   
Menu:
* [ ] Add menu system on config file.
* [ ] Add dialog/popup system.
* [ ] Add LUA triger in choices.

Scripts:
* [X] Exec. LUA initialize scripts.  
* [X] Exec. LUA update scripts.  
* [ ] Exec. Lua end scripts.  
* [X] ADD LUA inline on the config file (ge.ini).  
* [ ] Examples and profile script.  
* [ ] Exec LUA into loop sprites and animation.  
* [ ] Add inline LUA scripting into config file (ge.ini).  

IA/Events/Heuristics  
* [ ] Add the target parameter to the sprite, so that it can chase it.  
* [ ] Add flag to sprite chase hidden sprites.  
* [ ] Add parameters to sprite chase x,y coordenate.  
* [ ] Add script when it hits a target.  
* [ ] Add multiple targets.  
* [ ] Add sprite types: type=<character,pattern,mosaic,tile,bar,gauge>   
>>    -caracter, character sprite, sprite with N animations.  
>>    -pattern, background, title and menu images.  
>>    -mosaic, a scenario background assembled by tiles.  
>>    -tile, a scenario building unit.  
>>    -bar,Uma barra de status que é impressa cortada dependendo do valor 0%-100%).  
>>    -gauge, Indexed images that are displayed depending on the percentage of a variable (0%-100%).  
    

