// nave2.1.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include<stdio.h>
#include<Windows.h>
#include<conio.h>  //da facilidades para detectar la tecla que se presiona
#include<iostream>
#include<stdlib.h>   //el rand() funciona tbn sin este
#include<list>       //sera necesario para usar el metodo 'lista' tbn using namespace std pero ya lo tenia puesto


#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace System;
using namespace std;

void gotoxy(int x, int y){   //es una funcion de windows pero aqui lo hacemos
	// en su forma de funcion fuera del main()    
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);

}

void pintar_limites(){
	for (int i = 2; i < 78; i++){
		gotoxy(i, 3); printf("%c", 205);
		gotoxy(i, 33); printf("%c", 205);
	}
	for (int i = 4; i < 33; i++){
		gotoxy(2, i); printf("%c", 186);
		gotoxy(77, i); printf("%c", 186);
	}

	gotoxy(2, 3); printf("%c", 201);
	gotoxy(2, 33); printf("%c", 200);
	gotoxy(77,3); printf("%c", 187);
	gotoxy(77,33); printf("%c", 188);


}



class NAVE{  //definir una nave y pintarla, class permite definir objetos

	int x, y;                        //los atributos son los que nos permite definir objetos
	int corazones;                   //para definir la nave necesitamos coordenadas
	int vidas;
public:

	NAVE(int _x, int _y, int _corazones, int _vidas) :x(_x), y(_y), corazones(_corazones),vidas(_vidas){} //toda clase tiene un constructor que nos permite inicializar, se puede poner aqui o afuera como otra funcion
	int X(){ return x; }  //como las coordenadas son privadas creamos estos metodos para que podamos acceder a las coordenadas
	int Y(){ return y; }    //cuando llame a estas funciones me regresen el valor de la coordenada correspondiente
	void cor(){ corazones--; }
	void pintar();     //los metodos son las funciones que nos permite que los
	void borrar();     //objetos actuen 
	void mover();      // public es nuestra interfase
	void pintar_corazones();
	void morir();


};  //en la clase si va el:  ;
                       
void NAVE::pintar(){  //los :: nos permite acceder a los metodos de la clase
	gotoxy(x, y); printf("  %c",30);
	gotoxy(x, y+1); printf(" %c%c%c",40, 207, 41);
	gotoxy(x, y+2); printf("%c%c %c%c", 30, 190, 190, 30);

	
}

void NAVE::borrar (){
	gotoxy(x, y);     cout << "       ";
	gotoxy(x, y + 1); cout << "       ";
	gotoxy(x, y + 2); cout << "       ";

}

void NAVE::mover(){
	if (_kbhit()){   //kbhit detecta si se presiono una tecla
		char tecla = _getch();      //getch guarda la letra que se presiona y como
		borrar();                          //lo hacemos igual a var tecla entonces pasamos
		if (tecla == IZQUIERDA && x>3) x--;                              //el valor que se presiona a nuestra var tecla
		if (tecla == DERECHA &&x+5<77) x++;
		if (tecla == ARRIBA &&y>4) y--;
		if (tecla == ABAJO && y+3<33) y++;
		if (tecla == 'e') corazones--;
		pintar(); //reemplaze
		pintar_corazones();
	
		
	}
}

void NAVE::pintar_corazones(){

	gotoxy(50, 2); printf("VIDAS %d", vidas);
	gotoxy(64, 2); printf("Salud");
	gotoxy(70, 2); printf("     ");

		for (int i= 0; i < corazones; i++){
			gotoxy(70 + i, 2); printf("%c", 3);

		}


		
}

void NAVE::morir(){
	if (corazones == 0){
		borrar();
		gotoxy(x, y);   printf("   **   ");
		gotoxy(x, y+1); printf("  ****  ");
		gotoxy(x, y+2); printf("   **   ");
		Sleep(200);

		borrar();
		gotoxy(x, y);     printf(" * ** *");
		gotoxy(x, y + 1); printf("  **** ");
		gotoxy(x, y + 2); printf(" * ** *");
		Sleep(200);
		borrar();
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();
	}

}

class AST {

	int x, y;

public:
	AST(int _x, int _y) :x(_x), y(_y) {}
	int X(){ return x; }
	int Y(){ return y; }
	void pintar();
	void mover();
	void choque(class NAVE &N); //detecta el choque de nave y asteroido,podria estar en class NAVE tbn
	                            //solo N seria un solo valor pero con & es por referencia: los valores varian
	        //para poder usar las coordenadas (son privadas) de los asteroides en el for final(del main) donde chocan con balas
	
};

void AST::pintar(){

	gotoxy(x, y); printf("%c", 184);
	
}

void AST::mover(){
	gotoxy(x, y); printf(" ");  //primero borro siempre
	y++;
	if (y > 32){
		x = rand() % 71 + 4; //el rand()%71 selecciona al azar numero entre 0 y 71
		y = 4;

	}
	pintar();  //usara el de su misma clase osea AST
	//probe aqui con Sleep(40) hace mas lento a los asteroides
}

void AST::choque(class NAVE &N){
	if (x >= N.X() && x < N.X() + 5 && y >= N.Y() && y <= N.Y() + 2){

		N.cor(); // nos ayuda a restar corazones ( uno por uno)
		N.borrar(); //se puso porque se quedaban pintados algunos asteroides, luego de ponerlo ya no
		N.pintar(); //pinta la nave, para que si se nos borra una parte o todo
		N.pintar_corazones(); // pinta los corazones..se actualiza
		x = rand() % 71 + 4; // la coordenada x vuelva a tomar un valor al azar
		y = 4;               // y vuelva a ser 4


	}





}

class BALA {
	int x, y;

public:
	BALA(int _x, int _y) :x(_x), y(_y) {}
	int X(){ return x; }  //para poder usar el valor de x e y en el if dentro del for del main
	int Y(){ return y; }
	void mover();
	bool fuera();
};

void BALA::mover(){

	gotoxy(x, y); printf(" "); //nos situamos en sus coordenadas,primero borramos
	y--;                           //se borro el if (y > 4) se mantuvo el y--; //no hay que dejar que la bala sobrepase el limite ( borre xq se creo la funcion en bool
	gotoxy(x, y); printf("*"); //se ubique en su nueva coordenada y pinte la bala


}

bool BALA::fuera(){

	if (y == 4) return true;
	return false;
}

int main(array<System::String ^> ^args)
{
	pintar_limites();
	NAVE N(37, 30, 3, 4); //(se creo elementos de la clase a mano de esta forma)(pero ahora queremos que cada vez que se precione una tecla se cree los elementos, con una lista)
	N.pintar();
	N.pintar_corazones();
	
	list<AST*>A; //se creo para hacer una lista de asteroides y ya no de la forma anterior,uno por uno. sera mas facil hacer el impacto bala-asteroide
	list<AST*>::iterator itA;
	for (int  i=0; i < 5;i++){ //se ejecutara 5 veces
		A.push_back(new AST(rand() % 75 + 3, rand() % 5 + 4)); // se creara asteroides, al azar su ubicacion dentro de los limites

	}

	list<BALA*>B; //creamos una lista que tendra como elementos objetos de la clase BALA.Pero no vamos a poner elementos sino vamos a pasarle punteros(entones tendremos una lista de punteros)(lista se llama B)
	list<BALA*>::iterator it; //se crea un indice especial para la lista( para usarlo en el for)
	bool game_over = false; //ejecutate siempre y cuando la varible sea falsa
	while (!game_over) {

		if (_kbhit()){

			char tecla = _getch();
			if (tecla == 'a') //si se presiona a
				B.push_back(new BALA(N.X() + 2, N.Y() - 1)); //creamos un nuevo elemento y lo llamamos con new, lo llamamos desde bala, lo acomodamos para se vea que sale del avion
		}


		for (it = B.begin(); it != B.end();){  //desde que it empieza(B.begin) hasta que termina

			(*it)->mover();  //it sin nada es un puntero, la dirrecion donde esta la informacion pero necesito la informacion de adentro (con *); para acceder se pone ->
			if ((*it)->fuera()){  //si esto sucede entonces... eliminamos la bala
				gotoxy((*it)->X(), (*it)->Y());  //coordenadas de la bala para eliminar
				printf("  ");
				delete(*it);//eliminar al elemento de la lista ( el it correspondiente, xq va tomando varios valores)
				it = B.erase(it); //adicionamos para que tome el siguiente valor de la lista, usamos erase
			}
				
			else it++;   //con el codigo del video 10 falla, sigo solucion de comentario borre el i++ de for y adicione el else
		}

		for (itA = A.begin(); itA != A.end(); itA++)  //vamos usar el iterador para usar la lista de asteroides
		{
			(*itA)->mover();      //antes era ast1.mover();ast1.choque(N) de los tres asteroides
			(*itA)->choque(N);
		}

		//ya tenemos un iterador que recorre las balas y otro los asterides,lineas arriba
		//it controla la bala, itA controla el asteroide
		for (itA = A.begin(); itA != A.end();itA++) //vamos a recorrer a los asteroides,con su iterador desde el inicio hasta el final..y tbn compararlas con la lista de balas
		{
			for (it = B.begin(); it != B.end();it++)  //el for que nos recorre las balas,para usar las coordenadas de asteroides creamos una funcion para obtener su coordenada, como lo hize con bala antes
			{
				if ((*itA)->X() == (*it)->X() && ((*itA)->Y() + 1 == (*it)->Y()) || (*itA)->X() == (*it)->X() &&(*itA)->Y()==(*it)->Y())   //para los dos casos cuando hay una colision
				{
					gotoxy((*it)->X(), (*it)->Y()); printf(" "); //nos situamos en sus coordenadas,luego a borrar a la bala
					delete(*it); //hay que borrar el iterador, choco entonces lo borramos este elemento de la lista
					it = B.erase(it); // se borro entonces hay que pasar al siguiente elemento de la lista con el erase
				
					//los asteroides: borrar el que choco y crear otro nuevo que aparesca desde arriba al azar
					A.push_back(new AST(rand() % 74 + 3, 4)); //  creamos un asteroides, al azar
					gotoxy((*itA)->X(), (*itA)->Y()); printf(" "); //borramos al asteroides que choco xq puede que se quede pegado como otros casos anteriores
					delete(*itA); //borrar al asteroides que choco con la abala (borrar al objeto de la lista que se identifica con este interador)
					itA = A.erase(itA); //al borrar se pierde la secuencia entonces usamos erase
	
				}

			}

		}
		
		N.morir();
		N.mover();
		Sleep(30); //las pulsasiones sean menores y el programa no trabaje de mas

	}


	_getch();

	
    return 0;
}
