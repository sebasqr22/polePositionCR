#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "comunicacion.c"
#include <pthread.h>

// Variables globales
int milesimas = 0, milesimasT = 0,segundos = 0,segundosT = 0, multiploSeg = 1;
float carPos = 0;
int T=0;
int tTurbo =0;
int posicionH = 0, posicionT = 0, posicionV = 0;
float dist = 0.0f;
long time1;
long time2, eTime;
double ellapsed_time;

// Estructuras del juego
struct jugador
{
    float carSpeed;
    float distancia;
    int puntos;
    int vidas;
}jugador = {0.0f, 0.0f, 0, 3};

struct calle
{
    float curvatura ;
    float road[11][2];
}calle = {0.0f,{{0.0f ,10.0f},
                {0.0f ,200.0f},
                {1.0f ,600.0f},
                {0.0f ,400.0f},
                {-1.0f,600.0f},
                {0.0f ,200.0f},
                {-1.0f,600.0f},
                {1.0f ,600.0f},
                {0.0f ,200.0f},
                {0.2f ,500.0f},
                {0.0f ,200.0f}}};
// Estructura para huecos
struct Huecos
{
    int distH;
}Huecos = {0};
// Estructura para turbos
struct Turbos
{
    int distT;
}Turbos = {0};
// Estructura para vidas
struct Vidas
{
    int distV;
}Vidas = {0};



// Se inicia la comunicacion con el servidor
void *comenzarComunicacion(void *valor){
    printf("Se inicia el segundo hilo comunicacion.........\n");
    iniciarServidor();
    return NULL;
}

void tiempoJuego(){
    if (milesimas>20){
        segundos ++;
        milesimas = 0;
    }
}

void tiempoTurbo(){
    if (milesimasT>20){
        segundosT ++;
        milesimasT = 0;
    }
}
// Funcion determina si hay una colision entre dos objetos utilizando la funcion para la distancia entre do puntos
bool hayColision(float xCar, float yCar, float xObject, float yObject, float rCar, float rObject){
    if(sqrtf(powf(xCar-xObject,2)+powf(yCar-yObject,2)) <= rCar + rObject)
        return true;
    else 
        return false;
}

// Se calcula el radio de de la elipse
float radio(float a, float b,float cb, float h){
    float r = b/(sqrtf(1-(a-(powf(b,2)/a)) * (powf(cosf(asinf(cb/h)), 2))));
    return r;
}


/**
 * @brief Metodo del juego
 * 
 * @return int 
 */
int jugar(){
    // Inicialización del juego
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font = al_load_font("hoffmann.TTF",20,0);
    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *horizonte = al_load_bitmap("horizonte.jpg");
    ALLEGRO_BITMAP *CarFront = al_load_bitmap("CarFrente.png");
    ALLEGRO_BITMAP *CarIzq = al_load_bitmap("CarIzq.png");
    ALLEGRO_BITMAP *CarDer = al_load_bitmap("CarDer.png");

    ALLEGRO_BITMAP *newTurbo = al_load_bitmap("turbo.png");
    ALLEGRO_BITMAP *newHueco = al_load_bitmap("hueco.png");
    ALLEGRO_BITMAP *newVida = al_load_bitmap("vida.png");
    ALLEGRO_DISPLAY *ventana = 0; 
    ventana = al_create_display(1000, 600); // Se crea una ventana nueva

    // Variables para el control del juego
    time1 = clock();
    bool done = false;
    queue = al_create_event_queue();
    timer = al_create_timer(1.0/60);
    al_start_timer(timer);
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(ventana));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Si no se puede inicializar el juego, se lanza error y se cierra la aplicación
    if (!al_init()){
        fprintf(stderr, "Fallo al inicializar Allegro 5.\n");
        return -1;
    }
    // Si no se puede crear la ventana, se lanza error y se cierra la aplicación
    if (!ventana){
        fprintf(stderr, "Fallo al crear la ventana.\n");
        return -1;
    }
    pthread_t hilo;
    pthread_create(&hilo, NULL, comenzarComunicacion, NULL);

    pthread_join(hilo, NULL); /////////////////////////////////////// habilitar para conexion

    /**
     * @brief Loop del juego
     * 
     */
    while(!done){
        // Variables para el control de los eventos en la ventana del juego
        ALLEGRO_KEYBOARD_STATE keyState;
        ALLEGRO_EVENT evt;
        al_get_keyboard_state(&keyState);
        al_wait_for_event(queue, &evt);

        // Variables para la ejecucion del juego
        time2 = clock();
        eTime = time2- time1;
        time1 = time2;
        ellapsed_time = (double)eTime/CLOCKS_PER_SEC;
        int screenWidth = 1000;
        int screenHeight = 600;
        Huecos.distH = getNumeroH();
        Turbos.distT = getNumeroT();
        Vidas.distV = getNumeroV();
        

        //Se asigna un punto cada 10 segundos jugados
        if (segundos == 10*multiploSeg){
            jugador.puntos ++;
            multiploSeg ++;
        }

        // Si se cierra la ventana creada, finaliza el juego
        if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE) || jugador.vidas <= 0)
        {
            done = true;
        }

        int roadSection = 0;
        float offset = 0;
        while (roadSection < sizeof(calle.road) && offset <= jugador.distancia){
            offset += calle.road[roadSection][1]; 
            roadSection++; 
        }

        float targetCurvature = calle.road[roadSection-1][0];
        float roadCurveDiff = (targetCurvature - calle.curvatura)*(ellapsed_time + 0.05) * jugador.carSpeed; // elapsed
        calle.curvatura = roadCurveDiff; 

         // Se dibujan los huecos segun los mensajes del servidor ///////////////////////////////////////////////////
        if (Huecos.distH > jugador.distancia && (Huecos.distH - jugador.distancia)<200){
            al_draw_bitmap(newHueco, 500,250+posicionH,0);
            posicionH+= 10;
        }
        int jd = jugador.distancia;
        int d = jd - Huecos.distH;
        if (d > 50){
            posicionH = 0;
            Huecos.distH =0;
        }
        // Se dibujan los turbos segun los mensajes del servidor
        if (Turbos.distT > jugador.distancia && (Turbos.distT - jugador.distancia)<200){
            al_draw_bitmap(newTurbo, 500,250+posicionT,0);
            posicionT+= 10;
        }
        if ((jugador.distancia - Turbos.distT) > 50){
            posicionT = 0;
            Turbos.distT = 0;
        }
        // Se dibujan las vidas segun los mensajes del servidor
        if (Vidas.distV > jugador.distancia && (Vidas.distV - jugador.distancia)<200){
            al_draw_bitmap(newVida, 500,250+posicionV,0);
            posicionV+= 10;
        }
        if ((jugador.distancia - Vidas.distV) > 50){
            posicionV = 0;
            Vidas.distV =0;
        }

        // Se actualiza la pantalla 
        al_flip_display();
        al_clear_to_color(al_map_rgb(79, 79, 79));
        al_draw_bitmap(horizonte,0,0,0); // img, X, Y, flags
        
        // Bucles para dibujar la perspectiva del juego
        for (int ypos = 0; ypos < (screenHeight - 200); ypos++)
        {
            for (int xpos = 0; xpos < screenWidth; xpos++)
            {
                float perspectiva = (float)ypos / 400;
                float fPuntoMedio = 0.5f + calle.curvatura * pow((1.0f - perspectiva),3);
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

                // Se evalua la funcion seno para crear la zona verde de la perspectiva.
                if(sinf(20.0f *powf(1.0f - perspectiva, 3) + jugador.distancia*0.1f) > 0){
                    verde = 255;
                }
                if(sinf(20.0f *powf(1.0f - perspectiva, 3) + jugador.distancia*0.1f) < 0){
                    verde = 130;
                }
                // Se evalua la funcion seno para crear la orilla de la carretera
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
        }
        // Se dibuja el carro del jugador
        al_draw_bitmap(CarFront, carPos + 462,500,0);

        // Si se presiona la tecla direccional DERECHA, el carro se mueve a la derecha con una pequeña animación
        if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
        {
            al_draw_bitmap(CarDer, carPos + 462,500,0);
            jugador.carSpeed += 2.0f * (ellapsed_time + 0.001);
            carPos += 20;
        }

        // Si se presiona la tecla direccional IZQUIERDA, el carro se mueve a la izquierda con una pequeña animación
        if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
        {
            al_draw_bitmap(CarIzq, carPos + 462,500,0);
            jugador.carSpeed += 2.0f * (ellapsed_time + 0.001);
            carPos -= 20;
        }

        printf("CarPos: %f\n", carPos + 462);
        // Si se presiona la tecla ARRIBA, se acelera 
        if (al_key_down(&keyState, ALLEGRO_KEY_UP)){
            char buffer[20];
            gcvt(jugador.distancia,9,buffer); // Se convierte el numero a una cadena de caracteres
            //enviarMensaje(buffer); // se envia al servidor la distancia recorrida por el jugador 

            // Si se va por una curva, se crea inercia en el carro arrastrandolo a la orilla
            jugador.carSpeed += 2.0f * (ellapsed_time + 0.001);
            if(targetCurvature > 0)
                carPos -= 10;
            if(targetCurvature < 0)
                carPos += 10;

        }
        else
            jugador.carSpeed -= 1.0f * ellapsed_time;

        // Se limita la velocidad del carro //////////////////////////////////////////////////////////////////////
        if(jugador.carSpeed<0.0f) jugador.carSpeed = 0.0f;
        if(jugador.carSpeed>1.0f) {
            
            //printf("T: %d\n", T);
            if(T==1 && segundosT < 5){
                //printf("segundos: %d\n", segundosT);
                jugador.carSpeed = 1.8f; 
                Turbos.distT = jugador.distancia+100;
                tiempoTurbo();
            }
            else
                jugador.carSpeed = 1.0f; 
                T = 0;
                segundosT =0;
                milesimasT =0;
        }
        // Se mueve el carro hacia los lados de acuerdo con su velocidad
        jugador.distancia += (70.0f * jugador.carSpeed) * ellapsed_time;
        dist += (70.0f * jugador.carSpeed)*(ellapsed_time + 0.09);

        // Si el jugador se sale de la calle, su velocidad es cero
        if(carPos <= -380.0f || carPos >= 380.0f) 
           jugador.carSpeed -= 5.0f *ellapsed_time;
        
        ///--------------------------------------------------------------------------------------------------------
        /// Se verifican colisiones 
        ///--------------------------------------------------------------------------------------------------------
        float radCarH = radio(38, 16, 750+posicionH, sqrtf(powf(carPos-38, 2)+powf(250-posicionH,2))); 
        printf("radCar: %f\n", radCarH);
        float radHCar = radio(150, 58, 250-posicionH, sqrtf(powf(carPos-38, 2)+powf(250-posicionH,2)));
        printf("radHueco: %f\n", radHCar);
        if(hayColision(carPos + 462, 500, 500, 250+posicionH, radCarH, radHCar)) {
            printf("Entra a la condicion\n");
            jugador.carSpeed -= 5.0f *ellapsed_time;
        }
         /*  
        // Si el jugador obtiene un turbo se aumenta su velocidad
        if(((carPos + 537)>500) && ((carPos + 537)<615) && (Huecos.distH - jugador.distancia)<0 && (Huecos.distH - jugador.distancia)>-100) {
            T = 1;
        }
           
        // Si el jugador obtiene una vida, se suma a las actuales
        if((carPos + 537)>500 && (carPos + 537)<600 && Vidas.distV == jugador.distancia) {
            jugador.vidas += 1;
        }*/

        ///--------------------------------------------------------------------------------------------------------
        /// bool hayColision(float xCar, float yCar, float xObject, float yObject, float rCar, float rObject){
        /// float radio(float a, float b,float cb, float h){
        /// sqrtf(powf(xCar-xObject,2)+powf(yCar-yObject,2))
        ///--------------------------------------------------------------------------------------------------------
           
        
        // Se imprimen en la pantalla cada una de las variables importantes del jugador
        char buffer[5]; // se guarda el numero en formato char
        char res[100];
        // Para imprimir las vidas en tiempo real
        char vida[10] = "VIDAS: ";
        gcvt(jugador.vidas,6,buffer); // Se convierte el numero de vidas a una cadena de caracteres
        strcpy(res,vida);
        strcat(res, buffer);
        al_draw_text(font,al_map_rgb(0,0,0),5,5,ALLEGRO_ALIGN_LEFT,res);

        // Para imprimir distancia en tiempo real
        char distance[20] = "DISTANCIA (m): ";
        gcvt(jugador.distancia,9,buffer); 
        strcpy(res,distance);
        strcat(res, buffer);
        al_draw_text(font,al_map_rgb(0,0,0),5,25,ALLEGRO_ALIGN_LEFT,res);

        // Para imprimir distancia en tiempo real
        char points[10] = "PUNTOS: ";
        gcvt(jugador.puntos,9,buffer); 
        strcpy(res,points);
        strcat(res, buffer);
        al_draw_text(font,al_map_rgb(0,0,0),5,45,ALLEGRO_ALIGN_LEFT,res);

        // Para imprimir distancia en tiempo real
        char vel[20] = "VELOCIDAD (km/h): ";
        gcvt(jugador.carSpeed*100,9,buffer);
        strcpy(res,vel);
        strcat(res, buffer);
        al_draw_text(font,al_map_rgb(0,0,0),5,65,ALLEGRO_ALIGN_LEFT,res);
        
        // Se actualiza y se imprime el tiempo de juego
        milesimas ++;
        tiempoJuego();
        char timeS[15] = "TIEMPO (s): ";
        gcvt(segundos,9,buffer);
        strcpy(res,timeS);
        strcat(res, buffer);
        al_draw_text(font,al_map_rgb(0,0,0),5,85,ALLEGRO_ALIGN_LEFT,res);
    }

    // Si el juego finaliza, se destruyen los objetos creados por allegro 
    // para liberar la memoria utilizada
    al_destroy_bitmap(newHueco);
    al_destroy_bitmap(newTurbo);
    al_destroy_bitmap(newVida);
    al_destroy_bitmap(horizonte);
    al_destroy_bitmap(CarFront);
    al_destroy_bitmap(CarDer);
    al_destroy_bitmap(CarIzq);
    al_destroy_font(font);
    al_destroy_display(ventana);
    al_destroy_timer(timer);
    al_uninstall_keyboard();
}

int main()
{
    // Al iniciar el juego, se inicia la conexion con el servidor, si la conexion falla, el juego no inicia.
    jugar();   

    return 0;
}
