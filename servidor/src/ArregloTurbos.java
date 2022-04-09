class ArregloTurbos {
    private Turbos lista[];
    private int cuenta;

    public ArregloTurbos(int largo) { lista = new Turbos[largo]; }

    public void imprimir()
    {
        for (int i = 0; i < cuenta; i++) {
            System.out.print(lista[i] + " ");
        }
    }
    public void insertar(Turbos elemento)
    {

        if (lista.length == cuenta) {
            Turbos nueva[] = new Turbos[2 * cuenta];
            for (int i = 0; i < cuenta; i++) {
                nueva[i] = lista[i];
            }
            lista = nueva;
        }
        lista[cuenta++] = elemento;
    }
}
