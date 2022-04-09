public class Vidas {
    Identificador iden = new Identificador();

    public Vidas(String xCor, String yCor){
        this.corX = Integer.parseInt(xCor);
        this.corY = Integer.parseInt(yCor);
    }

    public int getCorX() {
        return corX;
    }

    public void setCorX(int corX) {
        this.corX = corX;
    }

    public int getCorY() {
        return corY;
    }

    public void setCorY(int corY) {
        this.corY = corY;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    int corX, corY;
    String token = iden.generar();
}
