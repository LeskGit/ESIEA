# TP1 - Modèle Entités-Associations

## Ex1 Q1 Livre

```plantuml
@startuml
title Exercice 1 - Question 1 : LIVRE
hide circle
hide methods
skinparam classAttributeIconSize 0

class LIVRE {
  __idLivre__
  titre
  nbPages
  editeur
  anneeEdition
  isbn
  dateAchat
}
note right of LIVRE
  idLivre : numéro interne (identifiant)
  isbn : unique mais non retenu comme identifiant
end note
@enduml
```

## Ex1 Q2 Professeur

```plantuml
@startuml
title Exercice 1 - Question 2 : PROFESSEUR
hide circle
hide methods
skinparam classAttributeIconSize 0

class PROFESSEUR {
  __idProfesseur__
  nom
  prenom
  dateNaissance
  dateEntree
  dateSortie
  email
  specialite
  gradeChercheur
  rue
  ville
  codePostal
}
@enduml
```


## Ex1 Q3 Etudiant

```plantuml
@startuml
title Exercice 1 - Question 3 : ETUDIANT
hide circle
hide methods
skinparam classAttributeIconSize 0

class ETUDIANT {
  __idEtudiant__
  nom
  prenom
  dateNaissance
  dateEntree
  diplomeEntree
  email
  rue
  ville
  codePostal
}
@enduml
```

## Ex1 Q4 Promotion

```plantuml
@startuml
title Exercice 1 - Question 4 : PROMOTION
hide circle
hide methods
skinparam classAttributeIconSize 0

class PROMOTION {
  __idPromotion__
  libelle
  cycle
}
@enduml
```

## Ex1 Q5 Matiere

```plantuml
@startuml
title Exercice 1 - Question 5 : MATIERE
hide circle
hide methods
skinparam classAttributeIconSize 0

class MATIERE {
  __idMatiere__
  libelle
  duree
  syllabus
}
@enduml
```

## Ex2 Q1 Matiere Promotion

```plantuml
@startuml
title Exercice 2 - Question 1 : une matière est enseignée dans une promotion
hide circle
hide methods
skinparam classAttributeIconSize 0
left to right direction

class MATIERE {
  __idMatiere__
  libelle
  duree
  syllabus
}
class PROMOTION {
  __idPromotion__
  libelle
  cycle
}
MATIERE "0,n" -- "0,n" PROMOTION : ETRE ENSEIGNEE
@enduml
```

## Ex2 Q2 Professeur Matiere

```plantuml
@startuml
title Exercice 2 - Question 2 : un professeur enseigne des matières
hide circle
hide methods
skinparam classAttributeIconSize 0
left to right direction

class PROFESSEUR {
  __idProfesseur__
  nom
  prenom
  ...
}
class MATIERE {
  __idMatiere__
  libelle
  duree
  syllabus
}
PROFESSEUR "0,n" -- "0,n" MATIERE : ENSEIGNER >
@enduml
```

## Ex2 Q3 Livre Matiere

```plantuml
@startuml
title Exercice 2 - Question 3 : un livre concerne des matières
hide circle
hide methods
skinparam classAttributeIconSize 0
left to right direction

class LIVRE {
  __idLivre__
  titre
  ...
}
class MATIERE {
  __idMatiere__
  libelle
  ...
}
LIVRE "0,n" -- "0,n" MATIERE : CONCERNER >
@enduml
```

## Ex2 Q4 Livre MotCle

```plantuml
@startuml
title Exercice 2 - Question 4 : un livre est associé à 1 ou plusieurs mots-clés
hide circle
hide methods
skinparam classAttributeIconSize 0
left to right direction

class LIVRE {
  __idLivre__
  titre
  ...
}
class MOT_CLE {
  __idMotCle__
  mot
}
LIVRE "1,n" -- "0,n" MOT_CLE : ETRE ASSOCIE A >
@enduml
```

## Ex3 Q1 Prerequis

```plantuml
@startuml
title Exercice 3 - Question 1 : pré-requis entre matières (association réflexive)
hide circle
hide methods
skinparam classAttributeIconSize 0

class MATIERE {
  __idMatiere__
  libelle
  duree
  syllabus
}
MATIERE "0,n\nrôle : matière dépendante" -- "0,n\nrôle : pré-requis" MATIERE : PRE-REQUIS
note bottom of MATIERE
  Association réflexive N-N :
  une matière a 0..n pré-requis
  et peut être pré-requis de 0..n matières.
end note
@enduml
```

## Ex3 Q2 Statut Annee

```plantuml
@startuml
title Exercice 3 - Question 2 : étudiant / promotion / année scolaire / statut
hide circle
hide methods
skinparam classAttributeIconSize 0
skinparam class {
  BackgroundColor<<Association>> #FFF3CD
  BorderColor<<Association>> #B8860B
}

class ETUDIANT {
  __idEtudiant__
  nom
  prenom
  ...
}
class PROMOTION {
  __idPromotion__
  libelle
  cycle
}
class ANNEE_SCOLAIRE {
  __anneeScolaire__
}
class ETRE_INSCRIT <<Association>> {
  statut
}

ETUDIANT "0,n" -- ETRE_INSCRIT
PROMOTION "0,n" -- ETRE_INSCRIT
ANNEE_SCOLAIRE "0,n" -- ETRE_INSCRIT

note bottom of ETRE_INSCRIT
  statut ∈ {redoublant, admis en année supérieure, exclu, diplômé}
  CIF : (étudiant, année scolaire) -> promotion
  (un étudiant n'est que dans une promotion par année)
  Variante : statut = entité STATUT (idStatut, libellé) reliée en (0,n)-(0,1).
end note
@enduml
```

## Ex3 Q3 Cycle

```plantuml
@startuml
title Exercice 3 - Question 3 : gestion des cycles à part entière
hide circle
hide methods
skinparam classAttributeIconSize 0
left to right direction

class CYCLE {
  __idCycle__
  libelleCycle
}
class PROMOTION {
  __idPromotion__
  libelle
  ordre
}
CYCLE "0,n" -- "1,1" PROMOTION : CONTENIR >
note bottom of PROMOTION
  L'attribut "cycle" disparaît de PROMOTION
  (remplacé par l'association).
  "ordre" = rang de la promotion dans son cycle
  (ex. cpi1 = 1, cpi2 = 2, ing1 = 1, ...).
end note
@enduml
```

## Ex3 Q4 Evaluation

```plantuml
@startuml
title Exercice 3 - Question 4 : évaluation et pondération (associations ternaires)
hide circle
hide methods
skinparam classAttributeIconSize 0
skinparam class {
  BackgroundColor<<Association>> #FFF3CD
  BorderColor<<Association>> #B8860B
}

class MATIERE {
  __idMatiere__
  libelle
  duree
  syllabus
}
class PROMOTION {
  __idPromotion__
  libelle
  ordre
}
class ETUDIANT {
  __idEtudiant__
  nom
  prenom
  ...
}
class ANNEE_SCOLAIRE {
  __anneeScolaire__
}
class ENSEIGNER <<Association>> {
  coefficient
}
class EVALUER <<Association>> {
  note
}

' Pondération : fixée par matière, promotion et année, commune à tous les étudiants
MATIERE "0,n" -- ENSEIGNER
PROMOTION "0,n" -- ENSEIGNER
ANNEE_SCOLAIRE "0,n" -- ENSEIGNER

' Note : une par étudiant, matière et année
ETUDIANT "0,n" -- EVALUER
MATIERE "0,n" -- EVALUER
ANNEE_SCOLAIRE "0,n" -- EVALUER

note bottom of EVALUER
  Moyenne générale = Σ(note × coefficient) / Σ(coefficient)
  -> donnée calculée, non stockée.
  Les coefficients sont lus dans ENSEIGNER pour la promotion
  de l'étudiant cette année-là (cf. ETRE_INSCRIT).
end note
@enduml
```

## MCD global

```plantuml
@startuml
title MCD global (Exercices 1 à 3)
hide circle
hide methods
skinparam classAttributeIconSize 0
skinparam class {
  BackgroundColor<<Association>> #FFF3CD
  BorderColor<<Association>> #B8860B
}

class LIVRE {
  __idLivre__
  titre
  nbPages
  editeur
  anneeEdition
  isbn
  dateAchat
}
class MOT_CLE {
  __idMotCle__
  mot
}
class MATIERE {
  __idMatiere__
  libelle
  duree
  syllabus
}
class PROFESSEUR {
  __idProfesseur__
  nom
  prenom
  dateNaissance
  dateEntree
  dateSortie
  email
  specialite
  gradeChercheur
  rue
  ville
  codePostal
}
class ETUDIANT {
  __idEtudiant__
  nom
  prenom
  dateNaissance
  dateEntree
  diplomeEntree
  email
  rue
  ville
  codePostal
}
class PROMOTION {
  __idPromotion__
  libelle
  ordre
}
class CYCLE {
  __idCycle__
  libelleCycle
}
class ANNEE_SCOLAIRE {
  __anneeScolaire__
}
class ENSEIGNER <<Association>> {
  coefficient
}
class ETRE_INSCRIT <<Association>> {
  statut
}
class EVALUER <<Association>> {
  note
}

LIVRE "1,n" -- "0,n" MOT_CLE : ETRE ASSOCIE A >
LIVRE "0,n" -- "0,n" MATIERE : CONCERNER >
PROFESSEUR "0,n" -- "0,n" MATIERE : PROFESSER >
MATIERE "0,n" -- "0,n" MATIERE : PRE-REQUIS
CYCLE "0,n" -- "1,1" PROMOTION : CONTENIR >

MATIERE "0,n" -- ENSEIGNER
PROMOTION "0,n" -- ENSEIGNER
ANNEE_SCOLAIRE "0,n" -- ENSEIGNER

ETUDIANT "0,n" -- ETRE_INSCRIT
PROMOTION "0,n" -- ETRE_INSCRIT
ANNEE_SCOLAIRE "0,n" -- ETRE_INSCRIT

ETUDIANT "0,n" -- EVALUER
MATIERE "0,n" -- EVALUER
ANNEE_SCOLAIRE "0,n" -- EVALUER
@enduml
```

## Ex3 Q5 Relationnel

```plantuml
@startuml
title Exercice 3 - Question 5 : modèle relationnel
hide circle
skinparam linetype ortho

entity LIVRE {
  * idLivre : PK
  --
  titre
  nbPages
  editeur
  anneeEdition
  isbn
  dateAchat
}
entity MOT_CLE {
  * idMotCle : PK
  --
  mot
}
entity MATIERE {
  * idMatiere : PK
  --
  libelle
  duree
  syllabus
}
entity PROFESSEUR {
  * idProfesseur : PK
  --
  nom, prenom, dateNaissance
  dateEntree, dateSortie
  email, specialite, gradeChercheur
  rue, ville, codePostal
}
entity ETUDIANT {
  * idEtudiant : PK
  --
  nom, prenom, dateNaissance
  dateEntree, diplomeEntree
  email
  rue, ville, codePostal
}
entity CYCLE {
  * idCycle : PK
  --
  libelleCycle
}
entity PROMOTION {
  * idPromotion : PK
  --
  libelle
  ordre
  # idCycle : FK NOT NULL
}
entity ANNEE_SCOLAIRE {
  * anneeScolaire : PK
}
entity LIVRE_MOT_CLE {
  * # idLivre : PK, FK
  * # idMotCle : PK, FK
}
entity LIVRE_MATIERE {
  * # idLivre : PK, FK
  * # idMatiere : PK, FK
}
entity PROFESSEUR_MATIERE {
  * # idProfesseur : PK, FK
  * # idMatiere : PK, FK
}
entity PRE_REQUIS {
  * # idMatiere : PK, FK
  * # idMatierePrerequis : PK, FK
}
entity ENSEIGNER {
  * # idMatiere : PK, FK
  * # idPromotion : PK, FK
  * # anneeScolaire : PK, FK
  --
  coefficient
}
entity ETRE_INSCRIT {
  * # idEtudiant : PK, FK
  * # anneeScolaire : PK, FK
  --
  # idPromotion : FK
  statut
}
entity EVALUER {
  * # idEtudiant : PK, FK
  * # idMatiere : PK, FK
  * # anneeScolaire : PK, FK
  --
  note
}

CYCLE ||--o{ PROMOTION
LIVRE ||--o{ LIVRE_MOT_CLE
MOT_CLE ||--o{ LIVRE_MOT_CLE
LIVRE ||--o{ LIVRE_MATIERE
MATIERE ||--o{ LIVRE_MATIERE
PROFESSEUR ||--o{ PROFESSEUR_MATIERE
MATIERE ||--o{ PROFESSEUR_MATIERE
MATIERE ||--o{ PRE_REQUIS
MATIERE ||--o{ PRE_REQUIS
MATIERE ||--o{ ENSEIGNER
PROMOTION ||--o{ ENSEIGNER
ANNEE_SCOLAIRE ||--o{ ENSEIGNER
ETUDIANT ||--o{ ETRE_INSCRIT
PROMOTION ||--o{ ETRE_INSCRIT
ANNEE_SCOLAIRE ||--o{ ETRE_INSCRIT
ETUDIANT ||--o{ EVALUER
MATIERE ||--o{ EVALUER
ANNEE_SCOLAIRE ||--o{ EVALUER
@enduml
```

## Ex4 MCD enonce

```plantuml
@startuml
title Exercice 4 - MCD de l'énoncé (hôpital)
hide circle
hide methods
skinparam classAttributeIconSize 0
skinparam class {
  BackgroundColor<<Association>> #FFF3CD
  BorderColor<<Association>> #B8860B
}

class PERSONNE {
  __idPersonne__
  nom
  prenom
}
class PATIENT {
  __numeroSecu__
  adresse
}
class MEDECIN {
  __idMedecin__
  specialite
}
class MUTUELLE {
  __idMutuelle__
  nomMutuelle
}
class AFFECTATION {
  __idAffectation__
  nomAffectation
}
class DATE {
  __date__
}
class HOSPITALISER <<Association>> {
  dureeHospitalisation
  chambre
}

PERSONNE <|-- PATIENT
PERSONNE <|-- MEDECIN

PATIENT "1,1" -- "0,n" MUTUELLE : COTISER >

PATIENT "0,n" -- HOSPITALISER
MEDECIN "0,n" -- HOSPITALISER
AFFECTATION "0,n" -- HOSPITALISER
DATE "0,n" -- HOSPITALISER
@enduml
```

## Ex4 Relationnel

```plantuml
@startuml
title Exercice 4 - Modèle relationnel
hide circle
skinparam linetype ortho

entity PERSONNE {
  * idPersonne : PK
  --
  nom
  prenom
}
entity PATIENT {
  * # idPersonne : PK, FK
  --
  numeroSecu : UNIQUE NOT NULL
  adresse
  # idMutuelle : FK NOT NULL
}
entity MEDECIN {
  * # idPersonne : PK, FK
  --
  idMedecin : UNIQUE NOT NULL
  specialite
}
entity MUTUELLE {
  * idMutuelle : PK
  --
  nomMutuelle
}
entity AFFECTATION {
  * idAffectation : PK
  --
  nomAffectation
}
entity DATE {
  * date : PK
}
entity HOSPITALISER {
  * # idPatient : PK, FK -> PATIENT(idPersonne)
  * # idMedecin : PK, FK -> MEDECIN(idPersonne)
  * # idAffectation : PK, FK
  * # date : PK, FK
  --
  dureeHospitalisation
  chambre
}

PERSONNE ||--o| PATIENT
PERSONNE ||--o| MEDECIN
MUTUELLE ||--o{ PATIENT
PATIENT ||--o{ HOSPITALISER
MEDECIN ||--o{ HOSPITALISER
AFFECTATION ||--o{ HOSPITALISER
DATE ||--o{ HOSPITALISER

note bottom of HOSPITALISER
  Association quaternaire (0,n partout) :
  clé primaire = concaténation des 4 identifiants.
  Cotiser (1,1)-(0,n) : pas de table, clé étrangère idMutuelle dans PATIENT.
  Héritage : une table par entité, la clé de PATIENT/MEDECIN est celle de PERSONNE
  (numeroSecu et idMedecin restent uniques).
end note
@enduml
```
