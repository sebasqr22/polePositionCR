public class Jugador {
    private String name;
    private int cantidadVidas;
    private String puerto;
    private int distanciaRecorrida;
    private boolean inicializado = false;

    public boolean getInicializado() {
        return inicializado;
    }

    public void setInicializado(boolean inicializado) {
        this.inicializado = inicializado;
    }

    public Jugador(){}

    public void setInfoBasica(String name, String vidas){
        this.name = name;
        this.cantidadVidas = Integer.parseInt(vidas);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCantidadVidas() {
        return cantidadVidas;
    }

    public void setCantidadVidas(int cantidadVidas) {
        this.cantidadVidas = cantidadVidas;
    }

    public String getPuerto() {
        return puerto;
    }

    public void setPuerto(String ip) {
        this.puerto = ip;
    }

    public int getDistanciaRecorrida() {
        return distanciaRecorrida;
    }

    public void setDistanciaRecorrida(int distanciaRecorrida) {
        this.distanciaRecorrida = distanciaRecorrida;
    }
}
