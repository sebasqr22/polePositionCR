/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JFrame.java to edit this template
 */

import java.awt.event.ActionEvent;

/**
 *
 * @author sebas
 */
public class GUI extends javax.swing.JFrame implements Observador {

    /**
     * Creates new form GUI
     */
    public GUI() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")

    /** variables globales */
    private int puerto = 25557;
    private String llegada;
    private Jugador jugador1 = new Jugador();
    private Jugador jugador2 = new Jugador();
    private Jugador jugador3 = new Jugador();
    private Jugador jugador4 = new Jugador();
    private ArregloTurbos listaTurbos = new ArregloTurbos(1);
    private ArregloVidas listaVidas = new ArregloVidas(1);


    public static SocketCliente server;

    public static void setServer(SocketCliente server) {
        GUI.server = server;
    }

    private String[] quitarPartes(String total){
        total.charAt(0);
        String[] lista = total.split("-");
        return lista;
    }

    private void enviar(String mensaje){
        try{
            server.enviar(mensaje);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    private void asignarJugador(String nombre, String vidas){
        if(jugador1.getInicializado()){
            jugador1.setInfoBasica(nombre, vidas);
            jugador1.setInicializado(true);
            jugadoresArea.append(nombre + "---" + vidas);
        }
        else if(jugador2.getInicializado()){
            jugador2.setInfoBasica(nombre, vidas);
            jugador2.setInicializado(true);
            jugadoresArea.append(nombre + "---" + vidas);
        }
        else if(jugador3.getInicializado()){
            jugador3.setInfoBasica(nombre, vidas);
            jugador3.setInicializado(true);
            jugadoresArea.append(nombre + "---" + vidas);
        }
        else if(jugador4.getInicializado()){
            jugador4.setInfoBasica(nombre, vidas);
            jugador4.setInicializado(true);
            jugadoresArea.append(nombre + "---" + vidas);
        }
        else{
            enviar("NO");
            System.out.printf("NO hay espacios para jugadores disponibles...");
        }
    }

    @Override
    public void update() {
        System.out.println("Se hace un update.....");
        llegada = server.getInfo();

        if(llegada.contains("1")){ //1-Sebas-3
            String[] lista = quitarPartes(llegada);
            asignarJugador(lista[0], lista[1]);
        }

    }


    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        jugadoresArea = new javax.swing.JTextArea();
        jugadoresText = new javax.swing.JLabel();
        puertoLabel = new javax.swing.JTextField();
        puertoText = new javax.swing.JLabel();
        tipoCombo = new javax.swing.JComboBox<>();
        xLabel = new javax.swing.JTextField();
        yLabel = new javax.swing.JTextField();
        tipoText = new javax.swing.JLabel();
        xText = new javax.swing.JLabel();
        yText = new javax.swing.JLabel();
        enviarButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        jugadoresArea.setEditable(false);
        jugadoresArea.setColumns(20);
        jugadoresArea.setRows(5);
        jScrollPane1.setViewportView(jugadoresArea);

        jugadoresText.setText("Lista de Jugadores");

        puertoLabel.setEditable(false);

        puertoText.setText("Puerto");

        tipoCombo.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "Hueco", "Vida", "Turbo" }));
        tipoCombo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tipoComboActionPerformed(evt);
            }
        });

        xLabel.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                xLabelActionPerformed(evt);
            }
        });

        tipoText.setText("Seleccionar Tipo");

        xText.setText("Inserte Coordenada X");

        yText.setText("Inserte Coordenada Y");

        enviarButton.setText("Enviar");
        enviarButton.addMouseListener(new java.awt.event.MouseAdapter() {

        });
        enviarButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                enviarButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(puertoLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(puertoText, javax.swing.GroupLayout.PREFERRED_SIZE, 57, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(14, 14, 14))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(enviarButton, javax.swing.GroupLayout.PREFERRED_SIZE, 118, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(312, 312, 312))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(77, 77, 77)
                        .addComponent(jugadoresText))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(150, 150, 150)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(tipoCombo, javax.swing.GroupLayout.PREFERRED_SIZE, 104, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(103, 103, 103)
                                .addComponent(xLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(42, 42, 42))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(tipoText)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(xText, javax.swing.GroupLayout.PREFERRED_SIZE, 138, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(6, 6, 6)))
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGap(70, 70, 70)
                                .addComponent(yLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGap(31, 31, 31)
                                .addComponent(yText)))))
                .addGap(26, 183, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addComponent(puertoLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(puertoText))
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 169, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jugadoresText)
                .addGap(91, 91, 91)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(tipoCombo, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(xLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(yLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(tipoText)
                    .addComponent(xText)
                    .addComponent(yText))
                .addGap(63, 63, 63)
                .addComponent(enviarButton, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 75, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void tipoComboActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tipoComboActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_tipoComboActionPerformed

    private void xLabelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_xLabelActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_xLabelActionPerformed

    // ACCION AL TOCAR BOTON DE ENVIAR
    private void enviarButtonActionPerformed(ActionEvent evt) {//GEN-FIRST:event_enviarButtonActionPerformed
        // TODO add your handling code here:
        int tipoNum = tipoCombo.getSelectedIndex() + 1;
        String corX = xLabel.getText();
        String corY = yLabel.getText();

        xLabel.setText("");
        yLabel.setText("");

        String mensaje = "";
        if(tipoNum != 4){
            //mensaje = String.valueOf(tipoNum) + "-" + corX + "-" + corY;
            if(tipoNum == 2){
                mensaje = String.valueOf(tipoNum) + "-" + corX + "-" + corY;
            }
            else{
                Turbos turbo = new Turbos(corX, corY);
                listaTurbos.insertar(turbo);
            }
        }
        else{
            Vidas vida = new Vidas(corX, corY);
            listaVidas.insertar(vida);
            mensaje = String.valueOf(tipoNum) + "-0-0";
        }
        enviar(mensaje);
    }//GEN-LAST:event_enviarButtonActionPerformed

    /**
     * @param args the command line arguments
     */

    //public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
       /* try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>     */

        /* Create and display the form */
        //java.awt.EventQueue.invokeLater(new Runnable() {
          //  public void run() {
            //    new GUI().setVisible(true);
            //}
        //});

        //server = new SocketCliente();
        //server.enlazarObjetos(GUI);

    //}
    /** definicion de funciones propias */
    private static void agregarJugador(String nombre, int vidas){
        String completo = nombre + " --- " + String.valueOf(vidas) + "\n";
        jugadoresArea.append(completo);
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton enviarButton;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane1;
    private static javax.swing.JTextArea jugadoresArea;
    private javax.swing.JLabel jugadoresText;
    private javax.swing.JTextField puertoLabel;
    private javax.swing.JLabel puertoText;
    private javax.swing.JComboBox<String> tipoCombo;
    private javax.swing.JLabel tipoText;
    private javax.swing.JTextField xLabel;
    private javax.swing.JLabel xText;
    private javax.swing.JTextField yLabel;
    private javax.swing.JLabel yText;

    // End of variables declaration//GEN-END:variables
}
