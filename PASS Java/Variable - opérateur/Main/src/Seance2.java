
import java.util.ArrayList;
import java.util.List;

public class Seance2 {
    public static void main(String[] args) throws Exception {

        double note1 = 10.0;
        double note2 = 15.5;
        double note3 = 13.4;

        int avg = (int) ((note1 + note2 + note3) / 3);
        System.out.println(avg);

        String response;

        if (avg > 15) {
            response = "Awesome !";
        }
        else if (avg > 10) {
            response = "Nice !";
        }
        else {
            response = "Bad !";
        }

        System.out.println(response);

        List<Integer> liste = new ArrayList<>();
        
        for (int i = 0; i < 9; i++) {
            liste.add(i);
        }
        int somme = 0; 
        for (Integer number : liste) {
            System.out.println(number);
            somme += number;
        }
        System.out.println(somme);
    }
}
