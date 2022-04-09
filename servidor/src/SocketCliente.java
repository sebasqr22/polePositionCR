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
    private ServerSocket server;

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
    private Socket servidor, enviador;



    /** Programa principal, crea el socket cliente
    public static void main (String [] args)
    {
        new SocketCliente();
    }*/

    /**
     * Crea el socket cliente y lee los datos
     */
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
    public void iniciar() {
        while(true){
            try {
                System.out.println("Esperando cliente en el puerto " + String.valueOf(port) + "...\n");
                servidor = server.accept();
                System.out.printf("Conectado a: " + servidor.getRemoteSocketAddress());
                BufferedReader entrada = new BufferedReader( new InputStreamReader(servidor.getInputStream()));
                llegada = entrada.readLine();


            } catch (IOException e) {
                System.out.printf("MAmeluco el tuco!");
                e.printStackTrace();
            }
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

    @Override
    public void notificar() {
        for(Observador o:observadores){
            System.out.println("NOtificando a los observadores...\n");
            o.update();
        }

    }
}