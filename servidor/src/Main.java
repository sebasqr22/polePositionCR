public class Main {
    private static GUI pantalla = new GUI();
    private static SocketCliente servidor = new SocketCliente();


    public static void main(String args[]){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {pantalla.setVisible(true);
            }
        });
        servidor.enlazarObjetos(pantalla);
    }
}
