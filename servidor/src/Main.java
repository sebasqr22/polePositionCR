public class Main {
    private static GUI pantalla = new GUI();
    private static SocketCliente servidor;


    public static void main(String args[]){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {pantalla.setVisible(true);
            }
        });
        servidor = new SocketCliente();
        pantalla.setServer(servidor);
        pantalla.iniciarColores();
        servidor.enlazarObjetos(pantalla);
    }
}
