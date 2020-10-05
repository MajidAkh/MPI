#include <stdlib.h>
#include <cstdint>
#include <ctime>
#include <climits>
#include <iostream>
#include <thread>     
#include <chrono>  
#include <mpi.h>


// Fonction auxiliaire du  tri fusion sequentiel, a ne pas modifier
void fusion(int tableau[],int deb1,int fin1,int fin2)
        {
        int *table1;
        int deb2=fin1+1;
        int compt1=deb1;
        int compt2=deb2;
        int i;
        
	int tailleLocal = fin1-deb1+1;        
        
	table1 = new int[tailleLocal];

        //on recopie les éléments du début du tableau
        for(i=deb1;i<=fin1;i++)
            {
            table1[i-deb1]=tableau[i];
            }
	
        for(i=deb1;i<=fin2;i++)
            {        
            if (compt1==deb2) //c'est que tous les éléments du premier tableau ont été utilisés
                {
                break; //tous les éléments ont donc été classés
                }
            else if (compt2==(fin2+1)) //c'est que tous les éléments du second tableau ont été utilisés
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute les éléments restants du premier tableau
                compt1++;
                }
            else if (table1[compt1-deb1]<tableau[compt2])
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute un élément du premier tableau
                compt1++;
                }
            else
                {
                tableau[i]=tableau[compt2]; //on ajoute un élément du second tableau
                compt2++;
                }
            }
	delete [] table1;
        }
        
// Fonction auxiliaire du tri fusion sequentiel 
void tri_fusion_bis(int tableau[],int deb,int fin)
        {
        if (deb<fin)
            {
            int milieu=(fin+deb)/2;
            tri_fusion_bis(tableau,deb,milieu);
            tri_fusion_bis(tableau,milieu+1,fin);
            fusion(tableau,deb,milieu,fin);
            }
        }

// tri fusion implémenté en sequentiel, à utiliser pour phase -1
void tri_fusion(int tableau[],int longueur)
     {
     if (longueur>0)
            {
            tri_fusion_bis(tableau,0,longueur-1);
            }
     }

//à partir de deux tableaux déjà triés tableau1 et tableau2, on trie les éléments communs, tableau1 contiendra les plus petits éléments triés, tableau 2 les plus grands éléments triés
//TODO
void merge_sorted(int tableau1[],int longueur1,int tableau2[],int longueur2){
	int tab1[longueur1];
	int tab2[longueur2];
	int min1 = 0,min2 = 0, max1 = longueur1-1, max2 = longueur2-1;
	for(int i = 0; i<longueur1; i++){
		if(tableau1[min1]<tableau2[min2]){
			tab1[i] = tableau1[min1];
			min1++;
		}else{
			tab1[i] = tableau2[min2];
			min2++;
		}
		if(tableau1[max1]>tableau2[max2]){
			tab2[longueur1-i-1] = tableau1[max1];
			max1--;
		}else{
			tab2[longueur1-i-1] = tableau2[max2];
			max2--;
		}
	}
	for(int i = 0; i<longueur1; i++){
		tableau1[i] = tab1[i];
		tableau2[i] = tab2[i];
	}
}

//Pour imprimer le tableau dans l'ordre defini par les processus sans tout envoyer à un processus
// Difficulté, l'ordre de sortie à l'affichage écran ne se contrôle pas bien, des messages de sortie peuvent se chevaucher
// Solution aprtielle: prevoir des temsp d'attente supplémentaire, outre els attentes bloquantes de send/receive
void print_tab_distrib(int tableau[],int longueur)
     {

	std::this_thread::sleep_for (std::chrono::seconds(1));

	int finished = 0;
	int id, p,j;
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Status status;

	if (id==0)  std::cout  << std::endl;

	if (id==0) finished = 1;

	if (id>0) MPI_Recv(&finished, 1, MPI_INT, id-1, 0, MPI_COMM_WORLD,&status);

	std::this_thread::sleep_for (std::chrono::seconds(1));

	std::cout  << "Proc" << id;

	for(j=0;j<longueur;j++)
		std::cout  << " " << tableau[j]; 
	std::cout  << std::endl;   
	
	if (id<p-1) MPI_Send(&finished, 1, MPI_INT, id+1, 0, MPI_COMM_WORLD);


	if (id == p-1) std::cout  << std::endl;
}


// Pour imprimer le tableau dans l'ordre defini par les processus en envoyant tout à un processus
// Une telle fonction n'est pas utilisable si tailleGlobal est de très grande taille excède la capacité mémoire
// Une telle fonction sert avant tout à debugger, sur des petites tailles
// Les difficultés mentionnées pour print_tab_distrib incitent à une telle fonction 
void print_tab_distrib_gather(int tabLocal[],int tailleLocal)
     {

	int id, p,j;
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Status status;

	int* tabGlobal;
	int tailleGlobal = tailleLocal * p;

	tabGlobal = new int[tailleGlobal];

	MPI_Gather(tabLocal, tailleLocal, MPI_INT, tabGlobal, tailleLocal, MPI_INT, 0, MPI_COMM_WORLD);

	if (id==0)  
		{
		for(j=0;j<tailleGlobal;j++)
			std::cout  << " " << tabGlobal[j]; 
		std::cout  << std::endl;   
		}
	delete [] tabGlobal;

}

//Initialisation  des morceaux du grand tableau
// un modeInit !=0 crée aléatoirement des tableaux pour chacun des processus, le mode 0 diffuse a partir du proc 0 pour s'exercer avec Scatter
void init_tab_random(int tabLocal[],int tailleLocal, int modeInit)
     {
	
	int id, p,j;
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Status status;

	int* tabGlobal;
	int tailleGlobal = tailleLocal * p;

	srand(id+1); // N.B: pour avoir des suites aléatoires diffeerentes, sinon, tous les tableaux locaux seront identiques !!!

	if (modeInit == 0){
		if (id==0){
			tabGlobal = new int[tailleGlobal];
			for(j=0;j<tailleGlobal;j++)
				tabGlobal[j] = rand()%1000+1;
		}
		MPI_Scatter(tabGlobal, tailleLocal, MPI_INT,tabLocal , tailleLocal, MPI_INT, 0, MPI_COMM_WORLD);



		// Libère la mémoire du grand tableau
		if (id==0){
			delete [] tabGlobal;
		}
	}
	else{
		srand(id+1);
		for(j=0;j<tailleLocal;j++)
			tabLocal[j] = rand()%1000+1;
	}

	if (id==0) std::cout  << "Impression tableau initial" << std::endl;
	print_tab_distrib_gather(tabLocal,tailleLocal);
	//print_tab_distrib(tabLocal,tailleLocal);

	//if (id==p-1) std::cout  <<  std::endl <<  std::endl;

}

//main prend en entrée k, le nombre d'elements de tableaux pour chaque processus et modeInit, le mode d'initialisation
int main (int argc, char *argv[]) {

	// taille des tableaux locaux par processus
	int k =  atoi(argv[1]);
 	// un modeInit !=0 crée aléatoirement des tableaux pour chacun des processus, le mode 0 diffuse a partir du proc 0 pour s'exercer avec Scatter
	int modeInit = atoi(argv[2]);

	int id, p,j;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	
	MPI_Status status;

	int tailleGlobal = k * p;
	int tailleLocal = k;        
        int* tabGlobal;

        int* tabLocal;
        int* tabRecv;

	tabLocal = new int[tailleLocal];
	tabRecv = new int[tailleLocal];

	// Creation du tableau aleatoire
	init_tab_random(tabLocal,tailleLocal,modeInit);
	// TODO: algo tri distribué

	tri_fusion(tabLocal,tailleLocal);

	for(int i = 0; i<p;i++){
		if(i%2 == 0){
			if(id%2 == 0 && id+1 != p){
				MPI_Send(tabLocal,tailleLocal,MPI_INT,id+1,0,MPI_COMM_WORLD);
				MPI_Recv(tabLocal,tailleLocal,MPI_INT,id+1,0,MPI_COMM_WORLD,&status);
			}
			if(id%2 == 1){
				MPI_Recv(tabRecv,tailleLocal,MPI_INT,id-1,0,MPI_COMM_WORLD,&status);
				merge_sorted(tabRecv,tailleLocal,tabLocal,tailleLocal);
				MPI_Send(tabRecv,tailleLocal,MPI_INT,id-1,0,MPI_COMM_WORLD);
			}
		}else{
			if(id%2 == 1 && id+1 != p){
				MPI_Send(tabLocal,tailleLocal,MPI_INT,id+1,0,MPI_COMM_WORLD);
				MPI_Recv(tabLocal,tailleLocal,MPI_INT,id+1,0,MPI_COMM_WORLD,&status);
			} 
			if(id != 0 && id%2 == 0){
				MPI_Recv(tabRecv,tailleLocal,MPI_INT,id-1,0,MPI_COMM_WORLD,&status);
				merge_sorted(tabRecv,tailleLocal,tabLocal,tailleLocal);
				MPI_Send(tabRecv,tailleLocal,MPI_INT,id-1,0,MPI_COMM_WORLD);
			}
		}
		print_tab_distrib_gather(tabLocal, tailleLocal);
	}

	//Sortie du resultat

	if (id==0) std::cout  << "\nImpression tableau final" << std::endl;
	print_tab_distrib(tabLocal, tailleLocal);
	//print_tab_distrib_gather(tabLocal, tailleLocal);
	// on libere l'espace memoire avant de sortir
	delete [] tabLocal;
	MPI_Finalize();
    return 0;
}
