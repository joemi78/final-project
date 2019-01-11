#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <windows.h>

struct ALLEGRO_OBJECT
{
    ALLEGRO_BITMAP* background;

};
struct MONSTER
{
    ALLEGRO_BITMAP* monster1;
};

void load_monster(struct MONSTER *monster);
void monster_fall_straight(struct MONSTER *monster,int count);
int random(int *ptr,int max,int min);
void monster_fall_parallel(struct MONSTER *monster,int y,int *count);
void determine_appear_count(int *count);


// Definition of display size
#define DISPLAY_WIDTH   480
#define DISPLAY_HEIGHT  640
#define TRACK 6

ALLEGRO_EVENT alEvent;
ALLEGRO_EVENT_QUEUE* alEventQueue = NULL;

int main()
{
    srand(time(NULL));

    ALLEGRO_BITMAP* bitmap = NULL;
    ALLEGRO_DISPLAY* display = NULL;

    struct ALLEGRO_OBJECT picture[0]={NULL};
    struct MONSTER monster[0]={NULL};


    // Initialize Allegro
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    alEventQueue = al_create_event_queue();


    // Create allegro display
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    load_monster(monster);
    monster_fall_straight(monster,1);


    // Wait for keyboard event
    al_wait_for_event(alEventQueue, &alEvent);
    al_destroy_event_queue(alEventQueue);


    return 0;
}

void load_monster(struct MONSTER *monster)
{
    (monster+0)->monster1=al_load_bitmap("./blue.jpg");
}

void monster_fall_straight(struct MONSTER *monster,int count)
{
    int i,j,x,y;
    int count_vary[TRACK];

    y=0;

    determine_appear_count(count_vary);

    for(i = 0; y < DISPLAY_HEIGHT; i++)
    {
        monster_fall_parallel(monster,y,count_vary);

        al_rest(0.01);
        al_flip_display();

        y = y + 1;

        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

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

void monster_fall_parallel(struct MONSTER *monster,int y,int *count)
 {
     int i;
     for(i=0;i<TRACK;i=i+1)
     {
         if((*(count+i)==1) || (*(count+i)==2) || (*(count+i)==3))
         {
            al_draw_scaled_bitmap((monster+0)->monster1, 0, 0,al_get_bitmap_width ((monster+0)->monster1), al_get_bitmap_height((monster+0)->monster1), i*(DISPLAY_WIDTH / TRACK) , y,70, 70,0);
         }
    }
 }

void determine_appear_count(int *count)
{
    int i,j;
    for(i=0;i<TRACK;i=i+1)
    {
        j=random(&j,4,0);
        *(count+i)=j;
    }
}

