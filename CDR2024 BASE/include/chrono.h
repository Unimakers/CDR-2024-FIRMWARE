#pragma once

//struct a utiliser
typedef struct {
	clock_t start_time, stop_time;
	double total_time;
	bool running;
}chrono;

chrono c = { 0,0,0,0 };

//demarre un chronom�tre
chrono start_chrono() {
	c.running = true;
	c.start_time = clock();
	return c;
}

//enregistre le moment de l'arret
chrono stop_chrono() {
	c.running = false;
	c.stop_time = clock();
	c.total_time = c.total_time + difftime(c.stop_time, c.start_time) / CLOCKS_PER_SEC;
	return c;
}

// //fonction qui affiche le chrono
// void affiche_chrono(chrono c) {
// 	if (c.running == true) {
// 		c.stop_time = clock();
// 		c.total_time = c.total_time + difftime(c.stop_time, c.start_time) / CLOCKS_PER_SEC;
// 	}
// 	else {
// 		printf("Le chrono est arrete\n");

// 	}
// 	printf("le temps ecoule est de %f secondes\n", c.total_time);

// }



//fonction qui reinitialise le chrono
chrono reinitialise_chrono() {
	c.start_time = 0;
	c.stop_time = 0;
	c.total_time = 0;
	c.running = false;
	return c;
}

double check_chrono (){ // return the time since the start of the chrono
	c.stop_time = clock();
	c.total_time = c.total_time + difftime(c.stop_time, c.start_time) / CLOCKS_PER_SEC;
	return c.total_time;
}


//gestion du chrono
void gestion_chrono(unsigned short int rep) {
	do {
		switch (rep) {
			case 1:
				start_chrono();
				break;
			case 2:
				stop_chrono();
				break;
			case 5:
				reinitialise_chrono();
				break;
		}
	} while (rep != 6);
}