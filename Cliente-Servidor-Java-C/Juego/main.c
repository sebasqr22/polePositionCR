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
int posicionH = 0, posicionT = 0, posicionV = 0, posicionD = 0, posicionM;
int tTurbo =0;
float carPos = 0;
float dist = 0.0f;
bool T = false, disparando = false, final = false;
long time1;
long time2, eTime;
double ellapsed_time;
char player[10];
char pColor[10];

// Estructuras de los jugadores
struct jugador
{
    float carSpeed;
    float distancia;
    int puntos;
    int vidas;
    char color[10];
}jugador = {0.0f, 0.0f, 0, 3, ' '};

struct enemigo1
{
    float carSpeed;
    float distancia;
    int puntos;
    char color[10];
    bool enJuego;
}enemigo1 = {0.0f, 0.0f, 0, 3,' ',false};

struct enemigo2
{
    float carSpeed;
    float distancia;
    int puntos;
    int vidas;
    char color[10];
    bool enJuego;
}enemigo2 = {0.0f, 0.0f, 0, 3,' ',false};

struct enemigo3
{
    float carSpeed;
    float distancia;
    int puntos;
    int vidas;
    char color[10];
    bool enJuego;
}enemigo3 = {0.0f, 0.0f, 0, 3, ' ',false};

// Estructura para la calle
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
// Estructura para los proyectiles
struct disparo
{
    int direccion;
}disparo={0};




// Se inicia la comunicacion con el servidor
void *comenzarComunicacion(void *valor){
    printf("Se inicia el segundo hilo comunicacion.........\n");
    iniciarServidor();
    return NULL;
}
// Cronometro para el tiempo de juego
void tiempoJuego(){
    if (milesimas>20){
        segundos ++;
        milesimas = 0;
    }
}
// Cronometro para la duracion del turbo
void tiempoTurbo(){
    if (milesimasT>20){
        segundosT ++;
        milesimasT = 0;
    }
}
// Funcion determina si hay una colision entre dos objetos utilizando la funcion para la distancia entre do puntos
bool hayColision(float xCar, float yCar, float xObject, float yObject, float rCar, float rObject){
    if(sqrtf(powf(xCar-xObject,2)+powf(yCar-yObject,2)) <= rCar + rObject) // sqrt( (x2 - x1)^2 + (y2 - y1)^2 )
        return true;
    else 
        return false;
}

// Se calcula el radio de de la elipse
float radio(float a, float b,float cb, float h){
    float r = b/sqrtf(1-(1-((powf(b,2)) / (powf(a,2)))) * powf(cosf(asinf(cb/h)), 2));
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
    ALLEGRO_BITMAP *meta = al_load_bitmap("meta.png");

    ALLEGRO_BITMAP *CarFrontA = al_load_bitmap("CarFrenteA.png");
    ALLEGRO_BITMAP *CarFrontB = al_load_bitmap("CarFrenteB.png");
    ALLEGRO_BITMAP *CarFrontM = al_load_bitmap("CarFrenteM.png");

    ALLEGRO_BITMAP *CarIzqA = al_load_bitmap("CarIzqA.png");
    ALLEGRO_BITMAP *CarIzqB = al_load_bitmap("CarIzqB.png");
    ALLEGRO_BITMAP *CarIzqM = al_load_bitmap("CarIzqM.png");

    ALLEGRO_BITMAP *CarDerA = al_load_bitmap("CarDerA.png");
    ALLEGRO_BITMAP *CarDerB = al_load_bitmap("CarDerB.png");
    ALLEGRO_BITMAP *CarDerM = al_load_bitmap("CarDerM.png");

    ALLEGRO_BITMAP *newTurbo = al_load_bitmap("turbo.png");
    ALLEGRO_BITMAP *newHueco = al_load_bitmap("hueco.png");
    ALLEGRO_BITMAP *newVida = al_load_bitmap("vida.png");
    ALLEGRO_BITMAP *proyectil = al_load_bitmap("proyectil.png");
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
    pthread_join(hilo, NULL); 

    // Enviar nombre y color elegido por eljugador al servidor
    char message[25] = "1-";
    strcat(message,player);// se concatena player al final de la cadena message
    strcat(message,"-");
    strcat(message,pColor);
    enviarMensaje(message); // Enviar mensaje

    /**
     * @brief Loop del juego
     */
    while(!done){
        // Enviar posicion de jugador---------------------------------------------------------------------
        char message[25] = "5-";
        strcat(message,player);// se concatena player al final de la cadena message
        strcat(message,"-");
        /*
        char charValue[10]={0};
        int number = jugador.distancia;
        char buffer[10]={0};
        itoa(number, buffer, 10);
        strcat(message,charValue);
        enviarMensaje(message); // Enviar mensaje
        */
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
        
        // Si la distancia de jugador es mayor que 10 000, ha llegado a la meta
        if(jugador.distancia >= 10000){
            final = true;
        }
        // Si el jugador llego a la meta
        if(final){
            // notificar al servidor que se llego al final de la pista
        }

        //Se asigna un punto cada 10 segundos jugados
        if (segundos == 10*multiploSeg){
            jugador.puntos ++;
            multiploSeg ++;
        }

        // Si se cierra la conexion con el servidor
        if (getConexion()){
            break;
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
        // Se dibuja la meta
        if(jugador.distancia + 300 >= 10000){
            al_draw_bitmap(meta, 314,250-posicionM,0);
            posicionM += 20;
        }

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

        // Si se presiona la tecla ESPACIADORA, se dispara un proyectil
        if (al_key_down(&keyState, ALLEGRO_KEY_SPACE)){
            disparo.direccion = carPos + 495;
            disparando = true;
        }

        if(500-(posicionD)>200 && disparando == true){
            al_draw_bitmap(proyectil, disparo.direccion,480-posicionD,0);
            posicionD += 20;
        }
            
        else{
            disparando = false;
            posicionD = 0;
        }
            
        // Si se presiona la tecla ARRIBA, se acelera 
        if (al_key_down(&keyState, ALLEGRO_KEY_UP)){
            char buffer[20];
            gcvt(jugador.distancia,9,buffer); // Se convierte el numero a una cadena de caracteres
            //enviarMensaje(buffer); // se envia al servidor la distancia recorrida por el jugador 

            // Si se va por una curva, se crea inercia en el carro arrastrandolo a la orilla
            jugador.carSpeed += 2.0f * (ellapsed_time + 0.001);
            if(targetCurvature > 0){
                carPos -= 10;
                if (disparando)
                    disparo.direccion -= 10;
            }
            if(targetCurvature < 0){
                carPos += 10;
                if (disparando)
                    disparo.direccion += 10;
            }
        }
        else
            jugador.carSpeed -= 1.0f * ellapsed_time;

        // Se limita la velocidad del carro //////////////////////////////////////////////////////////////////////
        if(jugador.carSpeed<0.0f) jugador.carSpeed = 0.0f;
        if(jugador.carSpeed>1.0f) {
            if(T == true && segundosT < 5){
                printf("segundos: %d\n", segundosT);
                jugador.carSpeed = 1.8f; 
                tiempoTurbo();
                milesimasT ++;
            }
            else{
                jugador.carSpeed = 1.0f; 
                T = false;
                segundosT =0;
                milesimasT =0;
            }
                
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
        // Si el jugador se va en un hueco, su velocidad disminuye a cero
        float radCarH = radio(38, 16, (308+posicionH)-516, sqrtf(powf(650 - (carPos+500), 2)+powf((308+posicionH)-516,2))); 
        float radHCar = radio(150, 58, 516-(308+posicionH), sqrtf(powf((carPos + 500)-650, 2)+powf(516-(308+posicionH),2)));

        if(hayColision(carPos + 500, 516, 650, 308+posicionH, radCarH, radHCar)) { 
            jugador.carSpeed -= 5.0f *ellapsed_time;
        }

        // Si el jugador obtiene un turbo se aumenta su velocidad
        float radCarT = radio(38, 16, (308+posicionT)-516,sqrtf(powf(558-(carPos+500), 2)+powf((308+posicionT)-516,2)));
        float radTCar = radio(58, 58, 516-(308+posicionT),sqrtf(powf((carPos+500)-558, 2)+powf(516-(308+posicionT),2)));
        
        if(hayColision(carPos + 500, 516, 558, 308+posicionT, radCarT, radTCar)) {
            T = true;
            jugador.puntos += 2;
        }

        // Si el jugador obtiene una vida, se suma a las actuales   
        float radCarV = radio(38, 16, (296+posicionV)-516,sqrtf(powf(550-(carPos+500), 2)+powf((296+posicionV)-516,2)));
        float radVCar = radio(50, 46, 516-(296+posicionV), sqrtf(powf((carPos+500)-550, 2)+powf(516-(296+posicionV),2)));
        
        if(hayColision(carPos + 500, 516, 550, 296+posicionV, radCarV, radVCar)) {
            if(jugador.vidas < 3)
                jugador.vidas += 1;
            jugador.puntos += 3;
        }
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
    al_destroy_bitmap(proyectil);
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

int main(){
    // Se pide un nombre de usuario.
    printf("Escribe tu nombre:\n");
    scanf("%s", player); 

    // Se pide un color de carro
    printf("Escribe uno de los sigueintes colores:\n -rojo\n -azul\n -blanco\n -morado\n");
    scanf("%s", pColor); 

    // Al iniciar el juego, se inicia la conexion con el servidor, si la conexion falla, el juego no inicia.
    jugar();   

    return 0;
}
