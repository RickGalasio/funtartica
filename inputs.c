#include "inputs.h"
#include "config.h"
#include "globals.h"
#include "playsound.h"
#include "debug.h"
#include "console.h"

int inputs(){
	SDL_Event e;
	e.type = 0;
	SDL_PollEvent(&e);
	state = SDL_GetKeyboardState(NULL);

    // Other SDL events--------vvv
	if (e.type == SDL_QUIT){
		// SDL_free(state);
		DBG("CLOSE [X] EXITING......NOW");
		return (1); //Scape
	}
	// Other SDL events--------^^^

	//----INPUTs-------------------------------------------------v

	// F12 open/close terminal
	if (state[SDL_SCANCODE_F12] && e.type == SDL_KEYDOWN){
		toggleconsole();
		inputmode = consoleon() ? terminal : play;
	}

	if (inputmode == play){
		// ['] or [.] open terminal
		if ((state[SDL_SCANCODE_GRAVE] || state[SDL_SCANCODE_PERIOD] )&& e.type == SDL_KEYDOWN){
			setconsole(true);
			inputmode = terminal;
		}
		if ((state[SDL_SCANCODE_GRAVE] || state[SDL_SCANCODE_SLASH] )&& e.type == SDL_KEYDOWN){
			setconsole(true);
			inputmode = terminal;
		}

		// [ESC] close play (TODO: Change inputmode to menu.)
		if (state[SDL_SCANCODE_ESCAPE] && e.type == SDL_KEYDOWN) return(1);        

		// TODO: SCRIPT DE INPUT----vv
		if (e.type == SDL_KEYUP && !state[SDL_SCANCODE_SPACE] && pressed_fire) 
			pressed_fire = false;
			
		if (!pressed_fire && e.type == SDL_KEYDOWN && state[SDL_SCANCODE_SPACE]){
			
			if (pressed_fire == false){
				for (int ibullet = 0; ibullet < DBULLETS; ibullet++){
					if (bullets[ibullet].hide == true){
						pressed_fire = true;

						// DBG("FIRE bullet:%d", ibullet);
						bullets[ibullet].hide = false;

						//Mix_PlayChannel(0, sound[1], 0);
						playSound(0, 1, 0);

						bullets[ibullet].pos.x = GE_sprite[SPT_SHIP].pos.x;
						bullets[ibullet].pos.y = GE_sprite[SPT_SHIP].pos.y - 11;
						break;
					}
				}
			}
		}
		if (state[SDL_SCANCODE_LEFT]){
			GE_sprite[SPT_SHIP].pos.x -= 1;
			if(GE_sprite[SPT_SHIP].pos.x < 0)
				GE_sprite[SPT_SHIP].pos.x = 0;
		}
		if (state[SDL_SCANCODE_RIGHT]){
			GE_sprite[SPT_SHIP].pos.x += 1;
			if(GE_sprite[SPT_SHIP].pos.x > width - GE_sprite[SPT_SHIP].pos.w)
				GE_sprite[SPT_SHIP].pos.x = width - GE_sprite[SPT_SHIP].pos.w;
		}
		// TODO: SCRIPT DE INPUT----^^

        // TOUCH -------------------VVV
		if(e.type == SDL_FINGERDOWN){
			autoshot = SDL_GetTicks() + 100;
			GE_sprite[SPT_SHIP].pos.x = e.tfinger.x * width;
		}
		//Touch motion
		else if(e.type == SDL_FINGERMOTION){
			GE_sprite[SPT_SHIP].pos.x = e.tfinger.x * width;
		}
		//Touch release
		else if (e.type == SDL_FINGERUP){
			GE_sprite[SPT_SHIP].pos.x = e.tfinger.x * width;
		}
		// TOUCH -------------------^^^

	}else if(inputmode == terminal){

		// [ESC] to close terminal
		if(state[SDL_SCANCODE_ESCAPE] && e.type == SDL_KEYDOWN){
			toggleconsole();
			inputmode = play;

		// [CTRL]+[BACKSPACE] to delete a word to the left of the cursor.
		}else if( SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_BACKSPACE]  &&
		 		   e.type == SDL_KEYDOWN && strlen(consoletxt)
				){
			int i=strlen(consoletxt);
			do{
              i--;
			}while(consoletxt[i]!=' ' && i>0);
			consoletxt[i]='\0';

		// [BACKSPACE] to delete a character to the left of the cursor.
		}else if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(consoletxt) > 0 &&
				 e.type == SDL_KEYDOWN
				){
			consoletxt[strlen(consoletxt) - 1] = '\0';

		// [DELETE] to delete a character to the right of the cursor.
		}else if(e.key.keysym.sym == SDLK_DELETE && strlen(consoletxt_) > 0 &&
				  e.type == SDL_KEYDOWN
				){
			LETSF(tmp,"%s",consoletxt_+1);
			LETS(consoletxt_,tmp);
		
		// [CTRL]+v Paste clipboard content in text.
		}else if( SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_V] && e.type == SDL_KEYDOWN ){
			// LETS(tmp, consoletxt);
			// LETSF(consoletxt,"%s%s",tmp , SDL_GetClipboardText() );

			LETS(tmp_, SDL_GetClipboardText() );
			int j=0,l=strlen(tmp_);
			for(int i=0;i<l;i++){
				if(tmp_[i]=='\n'){
					tmp_[i]='\0';
	           		LETS(tmp,tmp_+j);
					LETS(term[history].txt,tmp);
					LETS(term[history].txt_,"");
				    
					DBG("Executa: %s",tmp);
					if(execconsole(tmp)){			
						// bzero(consoletxt, sizeof(consoletxt));
						// bzero(consoletxt_, sizeof(consoletxt_));
					}
					history++;
					if(history>termlinesview) history=0;
					
					j=i+1;
				}
			}

		// [CTRL]+c copy line content to clipboard.
		}else if( SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_C] &&e.type == SDL_KEYDOWN ){
			LETSF(tmp,"%s%s",consoletxt, consoletxt_ );
			SDL_SetClipboardText(tmp);

		// Type the characters and diacritcs, latin accents (in UTF-8 encodding).
		}else if (e.type == SDL_TEXTINPUT){
			LETS(tmp,consoletxt);
			LETSF(consoletxt, "%s%s", tmp, e.text.text);

		// [RETURN] or [ENTER] for execute edited line.
		}else if((e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2) &&
				    e.type == SDL_KEYDOWN
				){
			LETSF(tmp, "%s%s",consoletxt,consoletxt_);
			DBG("Executa: %s",tmp);
			LETS(term[history].txt,consoletxt);
			LETS(term[history].txt_,consoletxt_);
			if(execconsole(tmp)){			
				// bzero(consoletxt, sizeof(consoletxt));
				// bzero(consoletxt_, sizeof(consoletxt_));
			}
			
			history++;
			if(history>termlinesview) history=0;

			LETS(consoletxt,term[history].txt);
			LETS(consoletxt_,term[history].txt_);

		// Acess the backwards register of history.
		}else if(state[SDL_SCANCODE_UP]  && e.type == SDL_KEYDOWN && history){
			LETS(term[history].txt,consoletxt);
			LETS(term[history].txt_,consoletxt_);
			history--;
			TVARD(history);
			LETS(consoletxt,term[history].txt);
			LETS(consoletxt_,term[history].txt_);
			if(history<termlineini) termlineini--;
		
		// Acess the next register of history.
		}else if(state[SDL_SCANCODE_DOWN]  && e.type == SDL_KEYDOWN){
			LETS(term[history].txt,consoletxt);
			LETS(term[history].txt_,consoletxt_);			
			history++;
			TVARD(history);
			LETS(consoletxt,term[history].txt);
			LETS(consoletxt_,term[history].txt_);
			if(history>=termlinesview+termlineini) termlineini++;
			//AQUI 

		// Moves the cursor to the previous word.
		}else if( SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_LEFT]  &&
				  e.type == SDL_KEYDOWN && strlen(consoletxt)
				){
			int i=strlen(consoletxt);
			do{
              i--;
			}while(consoletxt[i]!=' ' && i>0);
			LETSF(tmp,"%s%s",consoletxt+i,consoletxt_);
			LETS(consoletxt_,tmp);
			consoletxt[i]='\0';
		
		// Moves the cursor to the next word.
		}else if( SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_RIGHT]  &&
				   e.type == SDL_KEYDOWN && strlen(consoletxt_)
				){
			int i=0;
			do {
              i++;
			}while(consoletxt_[i]!=' ' && i<strlen(consoletxt_));
			LETS(tmp,consoletxt);
			LETS(tmp_,consoletxt_);			
			consoletxt_[i]='\0';
			LETSF(consoletxt,"%s%s",tmp,consoletxt_);
			LETS(consoletxt_,tmp_+i);

		// Moves the cursor to the previous character.
		}else if(state[SDL_SCANCODE_LEFT]  && e.type == SDL_KEYDOWN && strlen(consoletxt)){
			LETS(tmp,consoletxt_);
			LETSF(consoletxt_,"%c%s",consoletxt[strlen(consoletxt) - 1],tmp);
			consoletxt[strlen(consoletxt) - 1] = '\0';

		// Moves the cursor to the next character.
		}else if(state[SDL_SCANCODE_RIGHT]  && e.type == SDL_KEYDOWN && strlen(consoletxt_)){
			LETS(tmp,consoletxt);
			LETSF(consoletxt,"%s%c",tmp,consoletxt_[0]);
			LETS(tmp,consoletxt_);
			LETS(consoletxt_,tmp+1);

		// [CTRL]+[END]- Delete all characters after the cursor.
		}else if(SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_END]  && e.type == SDL_KEYDOWN ){
			bzero(consoletxt_, sizeof(consoletxt_));

		// Moves the cursor to the end of line.
		}else if(state[SDL_SCANCODE_END]  && e.type == SDL_KEYDOWN ){
			LETSF(tmp,"%s%s",consoletxt,consoletxt_);
			bzero(consoletxt_, sizeof(consoletxt_));
			LETS(consoletxt,tmp);

		// [CTRL]+[HOME] - Delete all characters before the cursor.
		}else if(SDL_GetModState() & KMOD_CTRL && state[SDL_SCANCODE_HOME]  && e.type == SDL_KEYDOWN ){
			bzero(consoletxt, sizeof(consoletxt));

		// Moves the cursor to the begin of line.
		}else if(state[SDL_SCANCODE_HOME]  && e.type == SDL_KEYDOWN ){
			LETSF(tmp,"%s%s",consoletxt,consoletxt_);
			bzero(consoletxt, sizeof(consoletxt));
			LETS(consoletxt_,tmp);
		}

	}else if (inputmode == menu){
		//TODO: Menu controls
	}
	//----INPUTs-------------------------------------------------^

	return (0);
}

// - EOF
