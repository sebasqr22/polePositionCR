import java.net.*;
import java.io.*;

/**
 * Clase principal que instancia un socket servidor, acepta una conexión
 * de un cliente y le envía un entero y una cadena de caracteres.
 */
public class SocketServidor
{
    public static void main (String [] args)
    {
        // Se llama al metodo SocketSevidor para crear el socket y realizar la conexion
        new SocketServidor();
    }

    /**
     * Constructor.
     */
    public SocketServidor()
    {
        try
        {
            // Se crea un socket servidor atendiendo a un determinado puerto.
            // Por ejemplo, el 25557.
            ServerSocket socket = new ServerSocket (8080);

            // Se acepata una conexión con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            System.out.println ("Esperando cliente");
            Socket cliente = socket.accept();
            System.out.println ("Conectado con cliente de " + cliente.getInetAddress());

            // se espera a que el cliente lea los datos, hasta un máximo de 10 segundos de espera antes de cerrar el socket.
            cliente.setSoLinger (true, 10);


            /* Inicio del loop *//////////////////////////////////////////////////////////////////////////////////
            while (true){

                /**
                 * Cambiar dato por los mensajes necesarios para la ejecucion del juego (se puede usar json)
                 */
                // Se prepara un dato para enviar.
                DatoSocket dato = new DatoSocket("Hola");

                // Se preparan los datos para ser enviados
                DataOutputStream bufferSalida = new DataOutputStream (cliente.getOutputStream());

                // Se envía el dato.
                dato.writeObject (bufferSalida);
                System.out.println ("Mensaje enviado: " + dato.toString());

                // Se preparan los datos para ser leidos
                DataInputStream bufferEntrada = new DataInputStream (cliente.getInputStream());
                DatoSocket aux = new DatoSocket("");
                aux.readObject (bufferEntrada);

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
}