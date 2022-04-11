import java.io.IOException;
import java.net.ServerSocket;

public class Servidor {
    int puerto;
    ServerSocket server;

    boolean encontrarElemento(int lista[], int elemento){
        int largo = lista.length;
        boolean encontrado = false;
        for(int i=0; i< largo; i++){
            if(lista[i] == elemento){
                encontrado = true;
                break;
            }
        }
        return encontrado;
    }

    public Servidor(int lista[]){
        for(int i=1000; i<=65000; i++){ //se crea el puerto
            try{
                if(encontrarElemento(lista, i) == false){
                    server = new ServerSocket(i);
                    System.out.printf("PUERTO LIBRE: " + String.valueOf(i) + "\n");
                    puerto = i;
                    break;
                }
                else{
                    System.out.printf("Puerto: " + String.valueOf(i) + " ---OCUPADO---\n");
                }

            } catch (IOException e) {
                e.getMessage();
                System.out.printf("Puerto: " + String.valueOf(i) + " ---OCUPADO---\n");
            }
        }
    }
}
