import java.net.*;
import java.io.*;
import java.util.ArrayList;

/**
 * Clase que crea un socket cliente, establece la conexión y lee los datos
 * del servidor, escribiéndolos en pantalla.
 */
public class SocketCliente implements SujetoObservable {
    private String llegada;
    private String envio;
    private ArrayList<Observador> observadores;
    public void enlazarObjetos(Observador o1){observadores.add(o1);};
    private boolean ejecutando = true;

    Socket cliente;


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


    }
    public void iniciar(){
        try
        {
            // Se crea un socket servidor atendiendo a un determinado puerto.
            // Por ejemplo, el 25557.
            ServerSocket socket = new ServerSocket (8080);

            // Se acepata una conexión con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            System.out.println ("Esperando cliente");
            cliente = socket.accept();
            System.out.println ("Conectado con cliente de " + cliente.getInetAddress());

            // se espera a que el cliente lea los datos, hasta un máximo de 10 segundos de espera antes de cerrar el socket.
            cliente.setSoLinger (true, 10);


            /* Inicio del loop *//////////////////////////////////////////////////////////////////////////////////
            while (true){

                /**
                 * Cambiar dato por los mensajes necesarios para la ejecucion del juego (se puede usar json)
                 */

                // Se preparan los datos para ser leidos
                DataInputStream bufferEntrada = new DataInputStream (cliente.getInputStream());
                DatoSocket aux = new DatoSocket("");
                aux.readObject (bufferEntrada);

                // Se obtiene el contenido importante del mensaje y se guarda en la variable mensaje.
                llegada = aux.toString();
                String mensaje = "";
                int cont = 0;
                for (int i=0; i < llegada.length(); i++){
                    if (cont >= 4){
                        mensaje = mensaje + llegada.charAt(i);
                    }
                    cont ++;
                }
                llegada = mensaje;
                System.out.println ("Mensaje Recibido: " + mensaje);

                if (mensaje.equals("salir")){
                    break;
                }
            }


            // Se cierra el socket con el cliente. // setSoLinger() espera a que el cliente retire los datos.
            cliente.close();

            // Se cierra el socket encargado de aceptar clientes.
            socket.close();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
    public void enviar(String salida) throws IOException {
        DataOutputStream bufferSalida = new DataOutputStream (cliente.getOutputStream());

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
            o.update();
        }

    }
}