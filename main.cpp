//main.cpp
//Starts the game

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "main_menu.h"

//Screen sizes
ALLEGRO_DISPLAY *display = NULL;
int screen_w=800;
int screen_h=600;
const double FPS=80;



int main (int argc, char **argv)
	{
	//Object declarations

		if(!al_init()){return -1;}
		
	display = al_create_display(screen_w, screen_h);
	
		if(!display){return -2;}
		if(!al_init_image_addon()) {return -3;}
		
	return main_menu(display,screen_w,screen_h,FPS);
	/*
	main_menu return values for buttons clicked on
	<0=error
	0=exit
	1=new
	2=load
	3=options
	4=exit
	*/
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	}