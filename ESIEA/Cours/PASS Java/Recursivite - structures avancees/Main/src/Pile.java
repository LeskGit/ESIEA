
import java.util.ArrayList;

public class Pile {
    
    private ArrayList<String> pile;
    private String sommet;

    
    public Pile() {
        this.pile = new ArrayList<String>();
        this.sommet = "";
    }

    public String getSommet() {
        return this.sommet;
    }

    private void setSommet() {
        if (this.pile.isEmpty()) {
            this.sommet = "";
        } else {
            this.sommet = this.pile.get(this.pile.size() - 1);
        }
    }

    public void empiler(String value) {
        this.pile.add(value);
        this.setSommet();
    }

    public int getSize() {
        return this.pile.size();
    }

    public String depiler() {
        String rem = "";
        if (this.pile.isEmpty()) {
            System.out.println("Pile vide, impossible de dépiler.");
            return rem;
        }
        rem = this.pile.remove(this.pile.size() - 1);
        this.setSommet();
        return rem;
    }

    public String resolveWord() {
        String word = "";
        for (String w : this.pile) {
            word += w;
        }
        return word;
    }

    public void empilerMot(String word) {
        for (int i = 0; i < word.length(); i++) {
            char temp = word.charAt(i);
            this.empiler(String.valueOf(temp));
        }
    }

    public String resolveReverseWord() {
        String temp = this.resolveWord();
        StringBuilder word = new StringBuilder();
        int taille = this.getSize();

        for (int i = 0; i<taille; i++) {
            word.append(this.depiler());
        }

        this.empilerMot(temp);
        return word.toString();
    
    }



    @Override
    public String toString() {
        return "Pile" + this.pile + " | sommet = " + this.sommet;
    }
}

