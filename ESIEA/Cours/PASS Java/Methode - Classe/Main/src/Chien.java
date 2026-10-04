public class Chien {
    
    private String nom;
    private int age;
    private char sexe;

    public Chien(String nom, int age, char sexe) {
        this.nom = nom;
        this.age = age;
        this.sexe = sexe;
    }

    public String getNom() {
        return this.nom;
    } 

    public int getAge() {
        return this.age;
    } 

    public char getSexe() {
        return this.sexe;
    } 

    public String resolveSexe() {
        String resolveSexe;
        if (this.sexe == 'M') {resolveSexe = "Male";}
        else {resolveSexe = "Femelle";}
        return resolveSexe;
    }

    public void  abboie() {
        System.out.println("Ouaf !!!");
    }

    @Override
    public String toString() {
        return this.getNom() + " a " + this.getAge() + " et, est de sexe " + this.resolveSexe();
    }
}
