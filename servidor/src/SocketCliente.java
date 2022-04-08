import java.net.*;
import java.io.*;
import java.util.ArrayList;

/**
 * Clase que crea un socket cliente, establece la conexión y lee los datos
 * del servidor, escribiéndolos en pantalla.
 */
public class SocketCliente implements SujetoObservable
{
    private String info;
    private String envio;
    private ArrayList<Observador> observadores;
    public void enlazarObjetos(Observador o1){observadores.add(o1);};
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
        try
        {
            /* Se crea el socket cliente */
            Socket socket = new Socket ("localhost", 8080);
            System.out.println ("conectado");

            /* Se hace que el cierre espere a la recogida de todos los datos desde
             * el otro lado */
            socket.setSoLinger (true, 10);

            /* Se obtiene un stream de lectura para leer objetos */
            DataInputStream bufferEntrada =
                    new DataInputStream (socket.getInputStream());

            /* Se lee un Datosocket que nos envía el servidor y se muestra
             * en pantalla */
            DatoSocket dato = new DatoSocket("");
            dato.readObject(bufferEntrada);
            info = dato.toString();
            notificar(); //se notifica a los observadores

            System.out.println ("Cliente Java: Recibido " + info);

            /* Se obtiene un flujo de envio de datos para enviar un dato al servidor */
            DataOutputStream bufferSalida =
                    new DataOutputStream (socket.getOutputStream());

            /* Se crea el dato y se escribe en el flujo de salida */
            DatoSocket aux = new DatoSocket (envio);
            aux.writeObject (bufferSalida);

            System.out.println ("Cliente Java: Enviado " + aux.toString());

             /* La llamada a setSoLinger() hará que el cierre espere a que el otro
             lado retire los datos que hemos enviado */
            socket.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public String getInfo() {
        return this.info;
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
            o.update();
        }

    }
}