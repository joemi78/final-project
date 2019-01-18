#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_native_dialog.h>
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
    ALLEGRO_BITMAP* background;

};
struct PLANE
{
    ALLEGRO_BITMAP* plane;
    ALLEGRO_BITMAP* black;
    int position_x;
    int position_y;
};
struct MONSTER
{
    ALLEGRO_BITMAP* monster1;
    ALLEGRO_BITMAP* black;
    int blood;
    int position_x;
    int position_y;
};

void load_monster(struct MONSTER *monster);
void load_plane(struct PLANE *plane);
void monster_fall_straight(struct MONSTER *monster_1,struct MONSTER *monster_2, struct PLANE *plane);
int random(int *ptr,int max,int min);
void monster_fall_parallel(struct MONSTER *monster,int y,int *count);
void determine_appear_count(int *count);
int monster_fall_wave(int count,int *count_vary,int y,struct MONSTER *monster);
void Move_Plane( struct PLANE *plane );
void delete_monster_picture(struct MONSTER *monster);
void object_position(int *position_x,int *position_y,int x,int y);
void collition(int determine,int *object1_position_x,int *object1_position_y,int object1_size,int *object2_position_x,int *object2_position_y,int object2_size);
void monster_plane_collition(struct MONSTER *monster,struct PLANE *plane);

float FPS=1;


// Definition of display size
#define DISPLAY_WIDTH   480
#define DISPLAY_HEIGHT  640
#define TRACK 6
#define PLANE_MOVE 3
#define plane_W 50
#define plane_H 50
#define MONSTER_SIZE 70
#define PLANE_SIZE 50
#define BULLET_SIZE 30


int plane_x ;

ALLEGRO_EVENT_QUEUE* event_queue = NULL; /* create event queue */
ALLEGRO_TIMER *timer1 = NULL;
ALLEGRO_EVENT events;
ALLEGRO_BITMAP *plane = NULL; /* pointer to the bar's image bitmap */
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_KEYBOARD_STATE KBstate;


int main()
{
    srand(time(NULL));

    ALLEGRO_DISPLAY* display = NULL;

    struct ALLEGRO_OBJECT picture[1]= {NULL};
    struct MONSTER monster_1[TRACK]= {NULL};
    struct MONSTER monster_2[TRACK]= {NULL};
    struct PLANE plane[1]= {NULL};

    // Initialize Allegro

    al_init(); /* initialize Allegro */
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_audio();  // install sound driver
    al_init_acodec_addon();
    al_reserve_samples(9);
    al_init_font_addon();    // install font addons
    al_init_ttf_addon();
    al_install_keyboard(); /* install the keyboard for Allegro to use */



    event_queue = al_create_event_queue();

    // Create allegro display
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);


    monster_fall_straight(monster_1 , monster_2 , plane);

    // Wait for keyboard event

    al_wait_for_event(event_queue, &events);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap( plane); /* destroy the ball bitmap */
    al_destroy_display( display);


    return 0;
}

void load_monster(struct MONSTER *monster)
{
    int i;

    for(i=0; i<TRACK; i=i+1)
    {
        (monster+i)->monster1=al_load_bitmap("./blue.jpg");
        (monster+i)->black=al_load_bitmap("./black.jpg");
    }
}

void load_plane(struct PLANE *plane)
{
    (plane+0)->plane=al_load_bitmap("./plane.jpg");
    (plane+0)->black=al_load_bitmap("./black.jpg");
}


void monster_fall_straight(struct MONSTER *monster_1 , struct MONSTER *monster_2 , struct PLANE *plane )
{
    int y1,y2;
    int count_vary1[TRACK];
    int count_vary2[TRACK];
    int count1,count2;


    load_plane(plane);

    y1=0;
    y2=0;
    count1=0;
    count2=(DISPLAY_HEIGHT/2);
    //load_plane(plane);
    plane_x = DISPLAY_HEIGHT / 2;

    while(1)
    {
       al_get_keyboard_state(&KBstate);
       if (al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
          break;

        Move_Plane(plane);

        y1=monster_fall_wave(count1,count_vary1,y1,monster_1);
        monster_fall_parallel(monster_1,y1,count_vary1);

        y2=monster_fall_wave(count2,count_vary2,y2,monster_2);
        monster_fall_parallel(monster_2,y2,count_vary2);

        monster_plane_collition(monster_1,plane);
        monster_plane_collition(monster_2,plane);

        al_rest(0.005);
        al_flip_display();

        y1 = y1 + 1;
        y2 = y2 + 1;

        count1=count1+1;
        count2=count2+1;


        al_clear_to_color(al_map_rgb(0, 0, 0));

    }

}

int monster_fall_wave(int count,int *count_vary,int y,struct MONSTER *monster)
{
    if( (count % DISPLAY_HEIGHT) == 0)
    {

        if(count != 0)
        {
           delete_monster_picture(monster);
        }
        determine_appear_count(count_vary);
        load_monster(monster);
        return 0;
    }
    else
    {
        return y;
    }
}
void delete_monster_picture(struct MONSTER *monster)
{
    int i;
    for(i=0;i<TRACK;i=i+1)
    {
        al_destroy_bitmap((monster+i)->monster1);
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
    for(i=0; i<TRACK; i=i+1)
    {
        object_position(&(monster+i)->position_x,&(monster+i)->position_y,i*(DISPLAY_WIDTH / TRACK),0);
        if((*(count+i)==1) || (*(count+i)==2) || (*(count+i)==3) || (*(count+i)==4))
        {
            al_draw_scaled_bitmap((monster+i)->monster1, 0, 0,al_get_bitmap_width ((monster+i)->monster1), al_get_bitmap_height((monster+i)->monster1), i*(DISPLAY_WIDTH / TRACK), y,MONSTER_SIZE, MONSTER_SIZE,0);
            object_position(&(monster+i)->position_x,&(monster+i)->position_y,i*(DISPLAY_WIDTH / TRACK),y);
        }
    }
}
void object_position(int *position_x,int *position_y,int x,int y)
{
    *position_x=x;
    *position_y=y;
}

void determine_appear_count(int *count)
{
    int i,j;
    for(i=0; i<TRACK; i=i+1)
    {
        j=random(&j,4,0);
        *(count+i)=j;
    }
}

void Move_Plane(struct PLANE *plane)
{

    if (al_key_down(&KBstate, ALLEGRO_KEY_LEFT)) plane_x -= PLANE_MOVE;
    if (al_key_down(&KBstate, ALLEGRO_KEY_RIGHT)) plane_x += PLANE_MOVE;


    /* make sure the plane do not go out off screen */
    if (plane_x  < 0  )             plane_x  = 0;
    if (plane_x  > DISPLAY_WIDTH -plane_W )       plane_x  = DISPLAY_WIDTH -plane_W;

 //  al_draw_bitmap( (plane)->plane , plane_x, 560, 0);
    al_draw_scaled_bitmap((plane)->plane, 0, 0,al_get_bitmap_width ((plane)->plane), al_get_bitmap_height((plane)->plane), plane_x, DISPLAY_HEIGHT-PLANE_SIZE, PLANE_SIZE , PLANE_SIZE ,0);
    object_position(&(plane)->position_x,&(plane)->position_y,plane_x,DISPLAY_HEIGHT-PLANE_SIZE);

}

void collition(int determine,int *object1_position_x,int *object1_position_y,int object1_size,int *object2_position_x,int *object2_position_y,int object2_size)
{
       if( (*object1_position_y+object1_size)+(DISPLAY_HEIGHT-*object2_position_y) > DISPLAY_HEIGHT)
       {
           if( (*object1_position_x <= *object2_position_x + object2_size) && (*object1_position_x+object1_size>= *object2_position_x) )
           {
               printf("num = %d \n",determine);
           }
       }


}

void monster_plane_collition(struct MONSTER *monster,struct PLANE *plane)
{
    int i;
    i=0;
    for(i=0;i<TRACK;i=i+1)
    {
        collition(i,&(monster+i)->position_x,&(monster+i)->position_y,MONSTER_SIZE,&(plane)->position_x,&(plane)->position_y,PLANE_SIZE);
    }
}

