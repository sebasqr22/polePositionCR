import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class reader {
    private String route = "readme.txt";
    private String datos = "";

    public String leer(){
        try{
            File archivo = new File(route);
            Scanner lectura = new Scanner(archivo);

            while(lectura.hasNextLine()){
                datos = lectura.nextLine();
                System.out.println("Se lee: " + datos + "\n");
            }
            lectura.close();
        }
        catch (FileNotFoundException e){
            System.out.println("NO se ha podido leer el archivo...\n");
            e.printStackTrace();
        }
        return datos;

}

public void reset(){
    this.datos = "";
    }
}
