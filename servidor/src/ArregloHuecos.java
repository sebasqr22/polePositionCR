class ArregloHuecos {
    private Huecos lista[];
    private int cuenta;

    public ArregloHuecos(int largo) { lista = new Huecos[largo]; }
    public void imprimir()
    {
        for (int i = 0; i < cuenta; i++) {
            System.out.print(lista[i] + " ");
        }
    }
    public void insertar(Huecos elemento)
    {
        if (lista.length == cuenta) {
            Huecos nueva[] = new Huecos[2 * cuenta];
            for (int i = 0; i < cuenta; i++) {
                nueva[i] = lista[i];
            }

            lista = nueva;
        }
        lista[cuenta++] = elemento;
    }
}
