

public class App {

    
    public static int checkVoyelle(char lettre) {
        String voyelles = "AEIUOY";
        for (int i = 0; i < 5; i++) {
            if (Character.toUpperCase(lettre) ==  voyelles.charAt(i)) {
                return 1;
            }
        }
        return 0;
    }

    public static int cptVoyelleSeq(String word) {
        int cpt = 0;
        for (int i = 0; i < word.length() - 1; i++) {
            char lettre =  word.charAt(i);
            cpt += checkVoyelle(lettre);
        }
        return cpt;
    }

    public static int rechercheDico(int[] tab, int valeur) {
        int[] curTab = tab.clone();
        while (curTab.length > 1) {
            curTab = 
        }
        
    }

    public static void main(String[] args) throws Exception {
        
        String word1 = "TestTestTest";
        System.out.println(cptVoyelleSeq(word1));
    }
}
