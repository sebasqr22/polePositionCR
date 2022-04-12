public class Colores {
    boolean ocupado = false;
    String color;


    public Colores(String color){
        this.color = color;
    }

    public void setOcupado(boolean ocupado) {
        this.ocupado = ocupado;
    }

    public String getColor() {
        return color;
    }

    public boolean getOcupado(){
        return this.ocupado;
    }
}
