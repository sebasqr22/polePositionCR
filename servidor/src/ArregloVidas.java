class ArregloVidas {

    private Vidas lista[];
    private int cuenta;

    public ArregloVidas(int largo) {
        lista = new Vidas[largo];
    }

    public void imprimir()
    {
        for (int i = 0; i < cuenta; i++) {
            System.out.print(lista[i] + " ");
        }
    }

    public void insertar(Vidas elemento)
    {

        if (lista.length == cuenta) {

            Vidas nueva[] = new Vidas[2 * cuenta];


            for (int i = 0; i < cuenta; i++) {
                nueva[i] = lista[i];
            }

            lista = nueva;
        }

        lista[cuenta++] = elemento;
    }
}
