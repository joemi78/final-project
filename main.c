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
    int position_x;
    int position_y;
};
struct MONSTER
{
    ALLEGRO_BITMAP* monster1;
    int blood;
    int position_x;
    int position_y;
};
struct BULLET
{
    ALLEGRO_BITMAP* bullet;
    int position_x;
    int position_y;
    int count;
};
struct BOSS
{
    ALLEGRO_BITMAP* boss;
    ALLEGRO_BITMAP* black;
    int blood;
    int position_x;
    int position_y;
    int direction;
};

void load_monster(struct MONSTER *monster);
void load_plane(struct PLANE *plane);
void monster_fall_straight(struct MONSTER *monster_1,struct MONSTER *monster_2, struct PLANE *plane, struct BULLET *bullet,struct BOSS *boss1,struct BOSS *boss2,struct BOSS *boss3 );
int random(int *ptr,int max,int min);
void monster_fall_parallel(struct MONSTER *monster,int y,int *count);
void determine_appear_count(int *count);
int monster_fall_wave(int count,int *count_vary,int y,struct MONSTER *monster);
void Move_Plane( struct PLANE *plane ,struct BULLET *bullet,int count3);
void delete_monster_picture(struct MONSTER *monster);
void object_position(int *position_x,int *position_y,int x,int y);
void collition(int num,int *object1_position_x,int *object1_position_y,int object1_size,int *object2_position_x,int *object2_position_y,int object2_size,int *count_vary);
void monster_plane_collition(struct MONSTER *monster,struct PLANE *plane,int *count_vary);
void determine_monster_wave_bumb(int *count_vary,int num);
void load_bullet(struct BULLET *bullet);
void bullet_shoot(int *position_y);
void bullet_shoot_straight_single(struct BULLET *bullet,int count3,int num);
void bullet_shoot_series(struct BULLET *bullet,int count3);
int determine_series(struct BULLET *bullet,int count3);

void reverseVerticalDirection(struct BOSS *boss);
void reverseHorizontalDirection(struct BOSS *boss);
void Move_Boss(struct BOSS *boss );
void boss_transform(struct BOSS *boss);
void load_boss(struct BOSS *boss);

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
#define BULLET_SIZE 20
#define BULLET_NUM 16
#define BULLET_SPEED 2
#define BOSS_SIZE 100

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

ALLEGRO_BITMAP *boss = NULL;
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
    struct BULLET bullet[BULLET_NUM]= {NULL};
    struct BOSS boss1[1]={NULL};
    struct BOSS boss2[1]={NULL};
    struct BOSS boss3[1]={NULL};

    (boss1)->position_x=DISPLAY_WIDTH/2;
    (boss1)->position_y=

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


    monster_fall_straight(monster_1, monster_2, plane,bullet,boss1,boss2,boss3);

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
    }
}

void load_bullet(struct BULLET *bullet)
{
    int i,temp;
    for(i=0; i<BULLET_NUM; i=i+1)
    {
        (bullet+i)->bullet=al_load_bitmap("./blue.jpg");
        (bullet+i)->position_y=DISPLAY_HEIGHT;
        temp=40*i;
        (bullet+i)->count=temp;
    }
}

void load_plane(struct PLANE *plane)
{
    (plane+0)->plane=al_load_bitmap("./plane.jpg");
}


void monster_fall_straight(struct MONSTER *monster_1, struct MONSTER *monster_2, struct PLANE *plane, struct BULLET *bullet,struct BOSS *boss1,struct BOSS *boss2,struct BOSS *boss3)
{
    int y1,y2;
    int count_vary1[TRACK];
    int count_vary2[TRACK];
    int count1,count2,count3;
    int i;

    load_plane(plane);
    load_bullet(bullet);
     load_boss(boss1);

    y1=0;
    y2=0;
    count1=0;
    count2=(DISPLAY_HEIGHT/2);
    count3=0;
    plane_x = DISPLAY_HEIGHT / 2;
    (boss1)->direction=rand()%2;
    (boss2)->direction=RIGHT;
    (boss3)->direction=UP;

    while(1)
    {
        al_get_keyboard_state(&KBstate);
        if (al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
            break;
        if(count1<1280){

        y1=monster_fall_wave(count1,count_vary1,y1,monster_1);
        monster_fall_parallel(monster_1,y1,count_vary1);
        monster_plane_collition(monster_1,plane,count_vary1);
        monster_plane_collition(monster_2,plane,count_vary2);
        }
        if(count2<1280){
        y2=monster_fall_wave(count2,count_vary2,y2,monster_2);
        monster_fall_parallel(monster_2,y2,count_vary2);
        }


         if(count1>1280&&count1<6400)
        {
            Move_Boss(boss1);
            al_draw_scaled_bitmap((boss1)->boss, 0, 0,al_get_bitmap_width ((boss1)->boss), al_get_bitmap_height((boss1)->boss),(boss1)->position_x, (boss1)->position_y, BOSS_SIZE , BOSS_SIZE ,0);
            (boss2)->position_x=(boss1)->position_x;
            (boss2)->position_y=(boss1)->position_y;
            (boss3)->position_y=(boss1)->position_y;
            (boss3)->position_x=(boss1)->position_x;
        }

        if(count1%1500==0){
           (boss1)-> direction=DOWN;

           (boss3)-> direction=DOWN;

        }
        if(count1%1800==0)
        {
           (boss2)-> direction=DOWN;
        }


        if(count1>6400)
        {

            Move_Boss(boss3);
            al_draw_scaled_bitmap((boss1)->boss, 0, 0,al_get_bitmap_width ((boss1)->boss), al_get_bitmap_height((boss1)->boss),(boss3)->position_x, (boss3)->position_y, BOSS_SIZE /2, BOSS_SIZE/2 ,0);

            Move_Boss(boss2);
            al_draw_scaled_bitmap((boss1)->boss, 0, 0,al_get_bitmap_width ((boss1)->boss), al_get_bitmap_height((boss1)->boss),(boss2)->position_x, (boss2)->position_y, BOSS_SIZE /2, BOSS_SIZE/2 ,0);
        }
////
        Move_Plane(plane,bullet,count3);

        al_rest(0.005);
        al_flip_display();

        y1 = y1 + 1;
        y2 = y2 + 1;

        count1=count1+1;
        count2=count2+1;
        count3=count3+BULLET_SPEED;

        al_clear_to_color(al_map_rgb(0, 0, 0));

    }
}
int determine_series(struct BULLET *bullet,int count3)
{
    int i;
    if(count3<DISPLAY_HEIGHT)
    {
        for(i=0;i<BULLET_NUM;i=i+1)
        {
            if(count3>=(bullet+BULLET_NUM-1)->count)
            {
                return BULLET_NUM;
            }
            if( (count3 >=(bullet+i)->count) && (count3<(bullet+i+1)->count) )
            {
                return i+1;
            }
        }
    }
    else
    {
        return BULLET_NUM;
    }
}
void bullet_shoot_series(struct BULLET *bullet,int count3)
{
    int j,start;
    start=determine_series(bullet,count3);

    for(j=0; j<start; j=j+1)
    {
        bullet_shoot_straight_single(bullet,count3,j);
    }
}

void bullet_shoot_straight_single(struct BULLET *bullet,int count3,int num)
{
    int x;
    bullet_shoot(&(bullet+num)->position_y);
    if((bullet+num)->position_y==DISPLAY_HEIGHT)
    {
        (bullet+num)->position_x=plane_x+PLANE_SIZE/4;
    }
    al_draw_scaled_bitmap((bullet+num)->bullet, 0, 0,al_get_bitmap_width ((bullet+num)->bullet), al_get_bitmap_height((bullet+num)->bullet), (bullet+num)->position_x, (bullet+num)->position_y,BULLET_SIZE, BULLET_SIZE,0);
    (bullet+num)->position_y=(bullet+num)->position_y-BULLET_SPEED;
}

void bullet_shoot(int *position_y)
{
    if((*position_y %DISPLAY_HEIGHT)==0)
    {
        *position_y=DISPLAY_HEIGHT;
    }
}


void determine_monster_wave_bumb(int *count_vary,int num)
{
    *(count_vary + num)=0;
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
    for(i=0; i<TRACK; i=i+1)
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
        object_position(&(monster+i)->position_x,&(monster+i)->position_y,i*(DISPLAY_WIDTH / TRACK),DISPLAY_HEIGHT);
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

void Move_Plane(struct PLANE *plane,struct BULLET *bullet,int count3)
{

    if (al_key_down(&KBstate, ALLEGRO_KEY_LEFT))
        plane_x -= PLANE_MOVE;
    if (al_key_down(&KBstate, ALLEGRO_KEY_RIGHT))
        plane_x += PLANE_MOVE;


    /* make sure the plane do not go out off screen */
    if (plane_x  < 0  )
        plane_x  = 0;
    if (plane_x  > DISPLAY_WIDTH -plane_W )
        plane_x  = DISPLAY_WIDTH -plane_W;

    bullet_shoot_series(bullet,count3);
    al_draw_scaled_bitmap((plane)->plane, 0, 0,al_get_bitmap_width ((plane)->plane), al_get_bitmap_height((plane)->plane), plane_x, DISPLAY_HEIGHT-PLANE_SIZE, PLANE_SIZE, PLANE_SIZE,0);
    object_position(&(plane)->position_x,&(plane)->position_y,plane_x,DISPLAY_HEIGHT-PLANE_SIZE);

}

void collition(int num,int *object1_position_x,int *object1_position_y,int object1_size,int *object2_position_x,int *object2_position_y,int object2_size,int *count_vary)
{
    int count;
    count=-1;

    if(*object1_position_y<DISPLAY_HEIGHT)
    {
        if( (*object1_position_y+object1_size)+(DISPLAY_HEIGHT-*object2_position_y) > DISPLAY_HEIGHT)
        {
            if( (*object1_position_x <= *object2_position_x + object2_size) && (*object1_position_x+object1_size>= *object2_position_x) )
            {
                count=num;
                determine_monster_wave_bumb(count_vary,num);
            }
        }
    }
}

void monster_plane_collition(struct MONSTER *monster,struct PLANE *plane,int *count_vary)
{
    int i;
    i=1;

    for(i=0; i<TRACK; i=i+1)
    {
        collition(i,&(monster+i)->position_x,&(monster+i)->position_y,MONSTER_SIZE,&(plane)->position_x,&(plane)->position_y,PLANE_SIZE,count_vary);
    }

}


void load_boss(struct BOSS *boss)
{
    (boss+0)->boss=al_load_bitmap("./boss.jpg");
    (boss+0)->black=al_load_bitmap("./black.jpg");
}
void Move_Boss(struct BOSS *boss )
{
    switch ( (boss)->direction ) {
      case RIGHT:
         (boss)->position_x= (boss)->position_x+1;

         break;
      case LEFT:
         (boss)->position_x=(boss)->position_x-1;
         break;
      case UP:
         (boss)->position_y=(boss)->position_y-1;
         break;
      case DOWN:
         (boss)->position_y=(boss)->position_y+1;
         break;
   }
   if ( (boss)->position_y <= 0 || (boss)->position_y >= DISPLAY_HEIGHT-BOSS_SIZE )
      reverseVerticalDirection(boss); /* make it go the other way */


   if ( (boss)->position_x <= 0 || (boss)->position_x >= (DISPLAY_WIDTH - BOSS_SIZE) )
    reverseHorizontalDirection(boss);
    //al_draw_scaled_bitmap((boss)->boss, 0, 0,al_get_bitmap_width ((boss)->boss), al_get_bitmap_height((boss)->boss), boss_x, boss_y, BOSS_SIZE , BOSS_SIZE ,0);

}
void reverseVerticalDirection(struct BOSS *boss)
{
   if ( (boss)->direction == UP  ) (boss)->direction = LEFT;
    else if ( (boss)->direction == DOWN ) (boss)->direction = UP;


} /* end function reverseVerticalDirection */

void reverseHorizontalDirection(struct BOSS *boss) /* reverses the horizontal direction */
{
   switch ( (boss)->direction ){
      case RIGHT:
          (boss)->direction = LEFT;
         break;
      case LEFT:
         (boss)->direction = RIGHT;
         break;

   } /* end switch */
} /* end function reverseHorizontalDirection */
