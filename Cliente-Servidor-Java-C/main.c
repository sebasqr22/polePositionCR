#include <stdio.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main()
{
    // Inicialización del juego
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    // Se crea una ventana nueva
    ALLEGRO_DISPLAY *ventana = 0;
    ventana = al_create_display(1000, 600);

    // Si no se puede inicializar, se lanza error y se cierra la aplicación
    if (!al_init()){
        fprintf(stderr, "Fallo al inicializar Allegro 5.\n");
        return -1;
    }
    
    // Si no se puede crear la ventana, se lanza error y se cierra la aplicación
    if (!ventana){
        fprintf(stderr, "Fallo al crear la ventana.\n");
        return -1;
    }

    // Inicializar variables
    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *horizonte = al_load_bitmap("horizonte.jpg");
    ALLEGRO_BITMAP *CarFront = al_load_bitmap("CarFrente.jpg");
    ALLEGRO_BITMAP *CarIzq = al_load_bitmap("CarIzq.jpg");
    ALLEGRO_BITMAP *CarDer = al_load_bitmap("CarDer.jpg");

    bool done = false;
    queue = al_create_event_queue();
    timer = al_create_timer(1.0/60);
    al_start_timer(timer);
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(ventana));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    // curvatura, distancia de la curvatura
    float road[11][2] = {{0.0f,10.0f},{0.0f,200.0f},{1.0f,200.0f},{0.0f,400.0f},{-1.0f,100.0f},
                            {0.0f,200.0f},{-1.0f,200.0f},{1.0f,200.0f},{0.0f,200.0f},{0.2f,500.0f},{0.0f,200.0f}};
    // Variables para el control del juego
    float carSpeed = 0.0f;
    float curvatura = 0.0f;
    float x = 0;
    float distancia = 0.0f;
    float dist = 0.0f;
    float ellapsed = 0.0f;
    

    // loop del juego // crear conexión con servidor antes de esto
    while(!done){
        // Variables para el control de los eventos del juego
        ALLEGRO_KEYBOARD_STATE keyState;
        ALLEGRO_EVENT evt;
        al_get_keyboard_state(&keyState);
        al_wait_for_event(queue, &evt);

        int roadSection = 0;
        float offset = 0;

        // Si se cierra la ventana creada, finaliza el juego
        if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE) || evt.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        // Se encuentra la posicion del jugador en la pista
        while (roadSection < sizeof(road) && offset <= distancia){
            offset += road[roadSection][1];
            roadSection++;
        }

        if (roadSection==2 || roadSection==7 || roadSection==9)
            ellapsed+=0.02f;

        if (roadSection==4 || roadSection==6)
            ellapsed+=-0.02f;
        else
            ellapsed=0.3f;

        float targetCurvature = road[roadSection-1][0];
        float roadCurveDiff = (targetCurvature - curvatura)*ellapsed; // elapsed
        curvatura = roadCurveDiff;

        al_flip_display();
        al_clear_to_color(al_map_rgb(79, 79, 79));
        al_draw_bitmap(horizonte,0,0,0); // img, X, Y, flags
        al_draw_bitmap(CarFront, x + 462,500,0);
        //al_draw_filled_rectangle(0, 200, 10, 210,al_map_rgb(0,255,0));

        int screenWidth = 1000;
        int screenHeight = 600;
        for (int ypos = 0; ypos < (screenHeight - 200); ypos++)
        {
            for (int xpos = 0; xpos < screenWidth; xpos++)
            {
                float perspectiva = (float)ypos / 400;
                float fPuntoMedio = 0.5f + curvatura * pow((1.0f - perspectiva), 3);
                float fAnchoPista = 0.1f + perspectiva * 0.8f;
                float fAnchoClip = fAnchoPista * 0.15f;

                fAnchoPista *= 0.5f;

                int nLeftField = (fPuntoMedio-fAnchoPista-fAnchoClip)*screenWidth; 
                int nLeftClip = (fPuntoMedio-fAnchoPista)*screenWidth; 
                int nRightClip = (fPuntoMedio+fAnchoPista)*screenWidth;
                int nRightField = (fPuntoMedio+fAnchoPista+fAnchoClip)*screenWidth;
                int nRow = 200 + ypos;
                int verde;
                int r,g,b;
                // Se evalua la funcion seno para crear la perspectiva.
                if(sinf(20.0f *powf(1.0f - perspectiva, 3) + distancia*0.1f) > 0){
                    verde = 255;
                }
                if(sinf(20.0f *powf(1.0f - perspectiva, 3) + distancia*0.1f) < 0){
                    verde = 130;
                }
                // para la orilla de la carretera
                if(sinf(40.0f *powf(1.0f - perspectiva, 2) + dist*0.1f) > 0){
                    r = 255;
                    g = 255;
                    b = 255;
                }
                if(sinf(40.0f *powf(1.0f - perspectiva, 2) + dist*0.1f) < 0){
                    r = 255;
                    g = 0;
                    b = 0;
                }


                // Se dibuja la perspectiva del juego
                if (xpos >= 0 && xpos < nLeftField)
                    al_draw_filled_rectangle(xpos, 200 + ypos, 10+xpos, 210 + ypos,al_map_rgb(0,verde,0));
                if (xpos >= nLeftField && xpos < nLeftClip)
                    al_draw_filled_rectangle(xpos, 200 + ypos, 10+xpos, 210 + ypos,al_map_rgb(r,g,b));
                if(xpos >= nRightClip && xpos < nRightField)
                    al_draw_filled_rectangle(xpos, 200 + ypos, 10+xpos, 210 + ypos,al_map_rgb(r,g,b));
                if(xpos >= nRightField && xpos < screenWidth)
                    al_draw_filled_rectangle(xpos, 200 + ypos, 10+xpos, 210 + ypos,al_map_rgb(0,verde,0));
                xpos += 5;
            }
            //ypos += 1;
        }

        // Si se presiona la tecla direccional DERECHA, el carro se mueve a la derecha con una pequeña animación
        if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
        {
            al_draw_bitmap(CarDer, x + 462,500,0);
            x += 20;
        }
        // Si se presiona la tecla ARRIBA, 
        if (al_key_down(&keyState, ALLEGRO_KEY_UP))
        {
            distancia += 5.0f * 0.6f;
            dist += 30.0f * 0.6f;
        }
        // Si se presiona la tecla direccional IZQUIERDA, el carro se mueve a la izquierda con una pequeña animación
        if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
        {
            al_draw_bitmap(CarIzq, x + 462,500,0);
            x -= 20;
        }
        
        
        
        /*
        if (x > width)
        {
            x = -al_get_bitmap_width(horizonte);
        }
        */
        
    }
    

    //al_rest(5.0); // tiempo que esta abierta la ventana en segundos

    al_destroy_bitmap(horizonte);
    al_destroy_bitmap(CarFront);
    al_destroy_bitmap(CarDer);
    al_destroy_bitmap(CarIzq);
    al_destroy_display(ventana);
    al_destroy_timer(timer);
    al_uninstall_keyboard();

    return 0;
}