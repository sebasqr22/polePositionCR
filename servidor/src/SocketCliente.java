import java.net.*;
import java.io.*;
import java.util.ArrayList;

/**
 * Clase que crea un socket cliente, establece la conexión y lee los datos
 * del servidor, escribiéndolos en pantalla.
 */
public class SocketCliente implements SujetoObservable {
    private String llegada = "";
    private String envio;
    private ArrayList<Observador> observadores;
    private int port;
    public void enlazarObjetos(Observador o1){observadores.add(o1);};



    private ServerSocket server, server1;
    private reader lector = new reader();

    void encontrarPuerto(){
        for(int i=1000; i<=65000; i++){
            try{
                server = new ServerSocket(i);
                System.out.printf("PUERTO LIBRE: " + String.valueOf(i) + "\n");
                port = i;
                break;

            } catch (IOException e) {
                e.getMessage();
                System.out.printf("Puerto: " + String.valueOf(i) + " ---OCUPADO---\n");
            }
        }
    }


    ;
    private Socket servidor;



    /** Programa principal, crea el socket cliente
    public static void main (String [] args)
    {
        new SocketCliente();
    }*/

    /**
     * Crea el socket cliente y lee los datos
     */

    @Override
    public void notificar() {
        for(Observador o:observadores){
            System.out.println("NOtificando a los observadores...\n");
            o.update();
        }

    }
    public SocketCliente()
    {
        observadores = new ArrayList<Observador>();
        encontrarPuerto();

        /*
        try {
            server = new ServerSocket(1025);
        } catch (IOException e) {
            e.printStackTrace();
        }*/


    }
    private void escuchar(ServerSocket server, Socket socket, int puerto){
        try {
            System.out.println("Esperando cliente en el puerto " + String.valueOf(puerto) + "...\n");
            socket = server.accept();
            System.out.printf("Conectado a: " + socket.getRemoteSocketAddress() + "\n");
            socket.setSoLinger (true, 10);
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }



    public void iniciar() {
        try {
            /*
            llegada = lector.leer();
            lector.reset();
            notificar(); */
            System.out.println("Esperando cliente en el puerto " + String.valueOf(port) + "...\n");
            servidor = server.accept();
            System.out.printf("Conectado a: " + servidor.getRemoteSocketAddress() + "\n");
            servidor.setSoLinger (true, 10);

            while (true){
                // Se espera por el mensaje del cliente
                System.out.println("Esperando mensaje del cliente....");
                // Se preparan los datos para ser leidos
                DataInputStream bufferEntrada = new DataInputStream (servidor.getInputStream());
                System.out.println("Se ha recibido un mensaje...");
                DatoSocket aux = new DatoSocket("");
                aux.readObject (bufferEntrada); // se espera el mensaje
                System.out.println("Se leyo mensaje...");

                // Se obtiene el contenido importante del mensaje y se guarda en la variable mensaje.
                String texto = aux.toString();
                String mensaje = "";
                int cont = 0;
                for (int i=0; i < texto.length(); i++){
                    if (cont >= 4){
                        mensaje = mensaje + texto.charAt(i);
                    }
                    cont ++;
                }
                System.out.println ("Mensaje Recibido: " + mensaje);
                llegada = lector.leer();
                lector.reset();
                notificar();
            }
        }
        catch (IOException e) {
            System.out.printf("No se pudo establecer la conexion con el cliente!");
            e.printStackTrace();
        }
    }
    public void enviar(String salida) throws IOException {
        /*
        enviador = server.accept();
        PrintWriter sal = new PrintWriter(servidor.getOutputStream(), true);
        //System.out.println("Enviando: ");
        sal.println("Enviado............");
        enviador.close();*/

        DataOutputStream bufferSalida = new DataOutputStream (servidor.getOutputStream());

        /* Se crea el dato y se escribe en el flujo de salida */
        DatoSocket aux = new DatoSocket (salida);
        aux.writeObject (bufferSalida);

        System.out.println ("Cliente Java: Enviado " + aux.toString());
    }

    public String getInfo() {
        return this.llegada;
    }
    public void setEnvio(String envio){
        this.envio = envio;
    }
    public String getEnvio(){
        return this.envio;
    }

}