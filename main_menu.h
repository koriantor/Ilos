#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <iostream>


	
static int where_is_mouse(int mouse_x,int mouse_y)
	/*
	0=nothing
	1=new
	2=load
	3=options
	4=exit
	*/
	{
	int numberOfButtons=4+1;						//Number of menu buttons + 1
	int pix_places[5]={332,372,420,468,506};		//The Y values of the menu buttons used for hover detection
	if (!(mouse_x>324 && mouse_x<473))				//The buttons are definitely within these x coordinates
		{
		return 0;
		}
	for (int i=0;i<numberOfButtons;i++)				//Finds which button is hovering over, if any
		{
		if (mouse_y>pix_places[i] && mouse_y<pix_places[i+1])
			{
			return i+1;
			}
		}
	return 0;
	}
	
static int main_menu(ALLEGRO_DISPLAY *display,int screen_w,int screen_h,double FPS)
	{
	int buttonpositions[5]={0,332,372,420,468};		//Number of menu buttons + 1
	bool redraw1 = false;
	bool redraw2 = false;
	ALLEGRO_BITMAP *menu_background = NULL;
	ALLEGRO_BITMAP *button_new = NULL;
	ALLEGRO_BITMAP *button_load = NULL;
	ALLEGRO_BITMAP *button_options = NULL;
	ALLEGRO_BITMAP *button_exit = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT ev;
	bool doexit=false;
	int hovered_button=0;
	int return_value=0;
	
	al_install_mouse();
	
	menu_background=al_load_bitmap("images/menu_main.png");
	button_new=al_load_bitmap("images/menu_new.png");
	button_load=al_load_bitmap("images/menu_load.png");
	button_options=al_load_bitmap("images/menu_options.png");
	button_exit=al_load_bitmap("images/menu_exit.png");
	
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(menu_background,0,0,0);
	al_flip_display();
	if(!(menu_background && button_new && button_load && button_options && button_exit)) {return -1;}
	timer = al_create_timer(1 / FPS);
	if(!timer) {return -2;}
	event_queue = al_create_event_queue();
	if(!event_queue) {return -3;}
	
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	/*
	where_is_mouse return values (which menu button)
	0=nothing
	1=new
	2=load
	3=options
	4=exit
	*/
	al_start_timer(timer);
	while(!doexit)
		{
		al_wait_for_event(event_queue, &ev);						//Wait for something to happen
		if (ev.type == ALLEGRO_EVENT_TIMER)
			{
			redraw1=true;
			}
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
			return_value=0;
			break;
			}
			if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
				hovered_button=where_is_mouse(ev.mouse.x,ev.mouse.y);
				if(hovered_button)
					{
					return_value= hovered_button;
					break;
					}
				}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
				{
				hovered_button=where_is_mouse(ev.mouse.x,ev.mouse.y);
				redraw2=true;
				}
				
		if(redraw1 && redraw2 && al_is_event_queue_empty(event_queue))
			{
			redraw1=false;
			redraw2=false;
			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(menu_background,0,0,0);
			switch(hovered_button)
				{
				std::cout << ev.mouse.x << ev.mouse.y;
				case 1: al_draw_bitmap(button_new,324,buttonpositions[hovered_button],0);break;
				case 2: al_draw_bitmap(button_load,324,buttonpositions[hovered_button],0);break;
				case 3: al_draw_bitmap(button_options,324,buttonpositions[hovered_button],0);break;
				case 4: al_draw_bitmap(button_exit,324,buttonpositions[hovered_button],0);break;
				}
			al_flip_display();
			}
	
		}
		
   al_destroy_bitmap(menu_background);
   al_destroy_bitmap(button_new);
   al_destroy_bitmap(button_load);
   al_destroy_bitmap(button_options);
   al_destroy_bitmap(button_exit);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   return return_value;
	
	}