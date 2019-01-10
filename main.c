
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <windows.h>

struct ALLEGRO_OBJECT
{
    ALLEGRO_DISPLAY* display;

};
struct MONSTER
{
    ALLEGRO_BITMAP *monster;
};

#define FPS  120
#define SCREEN_W  640
#define SCREEN_H  480

ALLEGRO_EVENT_QUEUE* event_queue = NULL; /* create event queue */
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT events;

void printf_display(struct ALLEGRO_OBJECT *picture);
int random(int *ptr,int max,int min);
void load_monster(struct MONSTER *monster);

int main()
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    struct ALLEGRO_OBJECT picture[0]={NULL};;
    struct MONSTER monster[0]={NULL};

    printf_display(&picture);

    printf("13");
}

void printf_display(struct ALLEGRO_OBJECT *picture)
{
    (picture+0)->display = al_create_display(SCREEN_W, SCREEN_H);
}

int random(int *ptr,int max,int min)
//Random number with upper and lower bounds
//input Upper and lower bound and pointer
//output Random number;
{
    int i,random;
    i=max-min;
    random=(rand()%(i+1))+1;
    *ptr=random+min-1;

    return *ptr;
}
void load_monster(struct MONSTER *monster)
{
    (monster+0)->monster = al_load_bitmap("./back.jpg");
}
