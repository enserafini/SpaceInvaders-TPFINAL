#include <iostream>
#include <conio2.h>
#include <ctime>
using namespace std;

const int LIM_IZQ = 5;
const int LIM_DER = 115;
const int LIM_SUP = 2;
const int LIM_INF = 28;

void dibujarBordes() {
	for (int x = LIM_IZQ; x <= LIM_DER; x++) {
		putchxy(x, LIM_SUP, '-');
		putchxy(x, LIM_INF, '-');
	}
	for (int y = LIM_SUP; y <= LIM_INF; y++) {
		putchxy(LIM_IZQ, y, '|');
		putchxy(LIM_DER, y, '|');
	}
}

class Nave {
	int x;
	int y;
	int dir; 
	clock_t tempo;
	clock_t paso;
	bool vivo;
public:
	Nave() {
		x = 0;
		y = 0;
		dir = 0;
		paso = CLOCKS_PER_SEC / 30;  
		tempo = clock();
		vivo = true;
	}
	
	int getX() { return x; }
	int getY() { return y; }
	int getDir() {return dir; }
	int getState() {return vivo; }
	clock_t getTempo() {return tempo; }
	clock_t getPaso() {return paso; }

	void setX(int _x) {x = _x;}
	void setY(int _y) {y = _y;}
	void setDir(int _dir) {dir = _dir;}
	void setState(bool _vivo) {vivo = _vivo;}
	void setTempo(clock_t _tempo) {tempo = _tempo;}
	void setPaso(clock_t _paso) {paso = _paso;}
	
	virtual void dibujar() {
		textcolor(RED);
		gotoxy(x, y);
		cout << "[^]";
	}
	void borrar() {
		gotoxy(x, y);
		cout << "   ";
	}
	

};

class Jugador : public Nave{
	
public:
	Jugador(){
		setX((LIM_IZQ + LIM_DER) / 2);
		setY(LIM_INF - 1);
	}
	void procesarTecla(int tecla) {
		switch (tecla) {
		case 75: 
		case 'a':
		case 'A':
			setDir(-1); break; 
		case 77:
		case 'd':
		case 'D':
			setDir(1); break;  
		}
	}
	
	void actualizarMovimiento() {
		if (getTempo() + getPaso() < clock()) {  
			if (getDir() == -1 && getX() > LIM_IZQ + 1) {
				borrar();
				setX(getX()-1);
				dibujar();
			} else if (getDir() == 1 && getX() < LIM_DER - 3) {
				borrar();
				setX(getX()+1);
				dibujar();
			}
			setTempo(clock());  
		}
	}
};

class Enemigo : public Nave {
public:
	Enemigo(int _x, int _y){
		setX(_x);
		setY(_y);
	}
	void dibujar(){
		textcolor(GREEN);
		gotoxy(getX(), getY());
		cout << "{*}";
	}
};

class Bala {
	int x;
	int y;
	bool activa;
	clock_t tempo;
	clock_t paso;
public:
	Bala() {
		activa = false;
		paso = CLOCKS_PER_SEC / 40;  
		tempo = clock();
	}
	void disparar(int _x, int _y) {
		if (!activa) {
			x = _x;
			y = _y - 1;
			activa = true;
			putchxy(x, y, '|');
			tempo = clock();
		}
	}
	void mover() {
		if (activa) {
			if (tempo + paso < clock()) {
				putchxy(x, y, ' ');
				y--;
				if (y <= LIM_SUP + 1) {
					activa = false;
				} else {
					putchxy(x, y, '|');
				}
				tempo = clock();
			}
		}
	}
};



int main() {
	dibujarBordes();
	Jugador jugador;
	Enemigo enemigo((LIM_IZQ + LIM_DER) / 2, LIM_SUP + 10);
	Bala b1;
	jugador.dibujar();
	enemigo.dibujar();
	while (true) {
		
		
		if (kbhit()) {
			int t = getch();
			if (t == ' ') {
				b1.disparar(jugador.getX() + 1, jugador.getY());
			} else {
				jugador.procesarTecla(t);   
			}
		}
		
	
		jugador.actualizarMovimiento();
		
		b1.mover();
	}
	
	return 0;
}

