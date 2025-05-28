# Game of Life

Acesta este un program ce simuleaza in C regulile Game of Life in functie de unele taskuri prezentate pe site ul: https://site-pa.netlify.app/proiecte/game_of_life/

## Caracteristici

* Se foloseste de matrice pentru a simula celule din Game of Life, unde "X" reprezinta starea vie si "+" starea moarta
* Taskul 1 realizeaza transformarile specifice regulilor Game of Life, schimbarile fiind tinute minte intr o lista iar apoi sunt aplicate in fiecare generatie asupra unei matrice
* Taskul 2 aplica aceleasi reguli dar in loc sa se foloseasca de o matrice, acesta retine toate listele de schimbari intr-o stiva pe care apoi o foloseste sa afiseze toate generatiile
* Taskul 3 creeaza un arbore in care pe ramura stanga se aplica o noua regula, orice celula cu exact doi vecini vii devine celulă vie, iar pe ramura dreapta aplica aceeasi regula ca la Taskul 1.
* Taskul 4 se foloseste de arborele creat la Taskul 3 pentru a transforma fiecare nod intr-un graf si apoi afla cel mai lung lant hamiltonian din acel graf, cu conditia ca daca sunt mai multe lanturi cu aceeasi lungime se va alege cel cu nodurile cu indicii mai mici

# Cum se utilizeaza

Trebuie rulat programul GameofLifeB.c alaturi de JoculVietii2.c, iar biblioteca asociata programului se afla in JoculVietii.h. Verificarea corectitudinii taskurilor se poate realiza cu ajutorul unui checker ce poate fi instalat de aici: https://gitlab.cs.pub.ro/paaa/checker/-/releases

# Structura si functii importante

In fisierul GameofLifeB.c se afla toate functiile, iar in JoculVietii2.c se afla functia main.
* Functiile pushL respectiv popL sunt folosite pentru Taskul2 pentru a introduce si pentru a scoate un element din stiva
* Functia DFS_scan este folosita la Task4 si rolul sau este de a parcurge graful in adancime si de a memora intr-o matrice componentele conexe
* Functia buildInCompVector este folosita in Task4 si se foloseste de o variabile booleana pentru a stoca nodurile prezente in componenta conexa curenta
* Functia DFS este folosita in Task4 si realizeaza o parcurgere in adancime pentru o componenta conexa pentru a afla cel mai lung lant Hamiltonian, folosind si o metoda de optimizare ce verifica daca cumva cel mai lung lant Hamiltonian gasit pana acum nu este cel mai lung lant posibil din acea componenta
* Functia verificareVec este folosita pentru Taskurile 1 si 3 si numara cati vecini vii are o celula
* Functia verificareVec2 este folosita la Taskul2 si numara cati vecini vii are o celula dar fara a se folosi de o matrice
* Functia reguli este folosita atat la Task 1 cat si 3 si aceasta aplica fie regula standard din GameofLife fie cea specifica taskului 3 si introduce intr o lista modificarile
* Functia taskuri aplica modificarile din lista matricei si o si afiseaza in cazul Taskului 1
* Functia bonus preia o matrice la o anumita generatie si stiva de liste de schimbari corespunzatoare acelei generatii si restaureaza matricea la starea sa initiala
* Functia CreateA contine atat Taskul 3 cat si Taskul 4, acesta realizeaza arborele dupa regulile corespunzatoare folosindu-se de o pracurgere in preordine pentru a genera nodurile, unde r reprezinta numarul de intrari pe partea stanga si r1 numarul de intrari pe partea dreapta, iar pentru task 4, mai intai creeaza graful si matricea de adiacenta corespunzatoare lui, avand in vedere ca o muchie intre doua noduri se formeaza atunci cand douca celule vii sunt vecini.
Apoi imparte graful in componente conexe in matricea comp_conex, unde primul element de pe fiecare linie este numarul de noduri din acea componenta.
Apoi foloseste inca o metoda de optimizare, aceea sa ordoneze componente conexe in ordine descrescatoare in functie de numarul de noduri pentru a putea determina daca mai are rost sa cautam si in acelea cel mai lung lant hamiltonian.
Apoi ordoneaza crescator ndoruile componentelor conexe pentru a putea respecta regula ca daca sunt doua lanturi de aceeasi lungime sa se ia cea cu nodurile cu indicii cei mai mici.
Apoi dupa ce s a gasit cel mai lung lant se face transformarea din noduri in coordonate ale matricei cu o lista nodes in care au fost notate aceste date mai devreme.
