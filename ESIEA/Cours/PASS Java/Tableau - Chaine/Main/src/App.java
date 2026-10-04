public class App {


    public static int findMax(int[] tab) {
        int max = tab[0];
        for (int i = 1; i < tab.length-1; i++) {
            if (tab[i] > max) {max = tab[i];}
        }
        return max;
    }

    public static void showNameInfo(String prenom) {
        System.out.println(prenom.charAt(0));
        System.out.println(prenom.length());
        System.out.println(prenom.charAt(prenom.length()-1));
    }

    public static int cptOccurence(String chaine, char lettre) {
        int cpt = 0;
        for (int i = 0; i < chaine.length()-1; i++) {if (lettre == chaine.charAt(i)) {cpt += 1;}}
        return cpt;
    }

    public static void main(String[] args) throws Exception {


        int[] test1 = {1, -12, 50, 32, 9};
        System.out.println(findMax(test1));

        String name1 = "Nedia";
        showNameInfo(name1);    

        String chaine1 = "TestTestTestjfeomjfopejopf";
        System.out.println(cptOccurence(chaine1, 'e'));
    }
}
