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
    ALLEGRO_DISPLAY* display;

};
struct MONSTER
{
    ALLEGRO_BITMAP* monster1;
};


// Definition of display size
#define DISPLAY_WIDTH   640
#define DISPLAY_HEIGHT  480

ALLEGRO_EVENT alEvent;
ALLEGRO_EVENT_QUEUE* alEventQueue = NULL;

int main()
{
    int i;
    int x, y;

    ALLEGRO_BITMAP* bitmap = NULL;
        ALLEGRO_DISPLAY* display = NULL;

//    struct ALLEGRO_OBJECT picture[0]={NULL};
//    struct MONSTER monster[0]={NULL};


    // Initialize Allegro
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    // Create allegro display
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);


    // Create Event Queue
    alEventQueue = al_create_event_queue();


    // Load bitmap
//    monster[0].monster1 = al_load_bitmap("./blue.jpg");
//    al_draw_bitmap(monster[0].monster1, 100, 100, 0);

    bitmap = al_load_bitmap("./blue.jpg");

    al_draw_bitmap(bitmap, 200, 200, 0);



//    // Register keyboard and mouse to event queue
//    al_register_event_source(alEventQueue, al_get_keyboard_event_source());
//
//    // Move bitmap
//    x = 500;
//    y = 0;
//    for(i = 0; y < 480; i++)
//    {
//        // Draw bitmap
//        al_draw_scaled_bitmap(bitmap, 0, 0,
//                              al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
//                              x, y,
//                              100, 100,
//                              0
//                              );
//
//        // Flip display to show the drawing result
//        al_flip_display();
//printf("123");
//        // Delay
//        al_rest(0.01);
//
//
//        y = y + 1;
//
//        // Clear display
//        al_clear_to_color(al_map_rgb(0, 0, 0));
//    }
//
//
//
//    // Register keyboard and mouse to event queue
//    al_register_event_source(alEventQueue, al_get_keyboard_event_source());
//
//    // Move bitmap
//    x = 0;
//    y = 0;
//    for(i = 0; y < 480; i++)
//    {
//        // Draw bitmap
//        al_draw_scaled_bitmap(bitmap, 0, 0,
//                              al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
//                              x, y,
//                              100, 100,
//                              0
//                              );
//
//        // Flip display to show the drawing result
//        al_flip_display();
//printf("123");
//        // Delay
//        al_rest(0.01);
//
//
//        y = y + 1;
//
//        // Clear display
//        al_clear_to_color(al_map_rgb(0, 0, 0));
//    }

    // Wait for keyboard event
    al_wait_for_event(alEventQueue, &alEvent);

    // Cleanup
    al_destroy_event_queue(alEventQueue);


    return 0;
}


