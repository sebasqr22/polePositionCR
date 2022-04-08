public class Jugador {
    private String name;
    private int cantidadVidas;
    private String ip;
    private int distanciaRecorrida;

    public Jugador(String name, String ip) { /* contrstuctor de la clase*/
        this.name = name;
        this.ip = ip;
        this.cantidadVidas = 3;
        this.distanciaRecorrida = 0;
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

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public int getDistanciaRecorrida() {
        return distanciaRecorrida;
    }

    public void setDistanciaRecorrida(int distanciaRecorrida) {
        this.distanciaRecorrida = distanciaRecorrida;
    }
}
