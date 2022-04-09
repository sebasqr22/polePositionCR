import java.util.Random;

public class Identificador {
    private String lista[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    private static int randomNumber(){

        Random random = new Random();// create random class
        int number = random.nextInt(26);
        return number;
    }

    public String generar(){
        String total = "";
        for(int i=0; i <= 10; i++){
            total += lista[randomNumber()];
        }
        return total;
    }
}
