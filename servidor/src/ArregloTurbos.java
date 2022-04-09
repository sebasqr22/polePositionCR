class ArregloTurbos {

    // Member variables of this class
    // Private access modifier
    private Turbos lista[];
    private int cuenta;

    // Note they can only be called through function

    // Method 1
    // Inside helper class
    // to compute length of an array
    public ArregloTurbos(int largo) { lista = new Turbos[largo]; }

    // Method 2
    // Inside helper class
    // To print array
    public void imprimir()
    {

        // Iterating over array using for loop
        for (int i = 0; i < cuenta; i++) {

            // Print the elements of an array
            System.out.print(lista[i] + " ");
        }
    }

    // Method 3
    // Inside Helper class
    public void insertar(Turbos elemento)
    {

        if (lista.length == cuenta) {

            // Creating a new array double the size
            // of array declared above
            Turbos nueva[] = new Turbos[2 * cuenta];

            // Iterating over new array using for loop
            for (int i = 0; i < cuenta; i++) {
                nueva[i] = lista[i];
            }

            // Assigning new array to original array
            // created above
            lista = nueva;
        }

        lista[cuenta++] = elemento;
    }
}
