

public class App {

    public static double factorielleRec(double n) {
        if (n == 0) {return 1;}
        return n * factorielleRec(n - 1);
    }

    public static double puissance(double n, int exposant) {
        if (exposant == 0) {return 1;}
        return n * puissance(n, exposant - 1);
    }

    public static double sommetab(int[] tab, int indice) {
        if (indice >= tab.length) {return 0;}
        return tab[indice] + sommetab(tab, indice + 1);
    }

    


    public static void main(String[] args) throws Exception {
        
        Pile pile = new Pile();
        String word = "";
        pile.empiler("s");
        pile.empiler("k");
        pile.empiler("i");
        pile.empiler("b");
        pile.empiler("i");
        pile.empiler("d");
        pile.empiler("i");

        System.out.println(pile.resolveReverseWord());
        System.out.println(pile.resolveWord());
    }
}
