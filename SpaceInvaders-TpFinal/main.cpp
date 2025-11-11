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
public:
	Nave() {
		x = (LIM_IZQ + LIM_DER) / 2;
		y = LIM_INF - 1;
		dir = 0;
		paso = CLOCKS_PER_SEC / 30;  
		tempo = clock();
	}
	
	int getX() { return x; }
	int getY() { return y; }
	
	void dibujar() {
		textcolor(RED);
		gotoxy(x, y);
		cout << "[^]";
	}
	void borrar() {
		gotoxy(x, y);
		cout << "   ";
	}
	
	void procesarTecla(int tecla) {
		switch (tecla) {
		case 75: dir = -1; break; 
		case 77: dir = 1; break;  
		}
	}
	
	void actualizarMovimiento() {
		if (tempo + paso < clock()) {  
			if (dir == -1 && x > LIM_IZQ + 1) {
				borrar();
				x--;
				dibujar();
			} else if (dir == 1 && x < LIM_DER - 3) {
				borrar();
				x++;
				dibujar();
			}
			tempo = clock();  
		}
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
	Nave n1;
	Bala b1;
	n1.dibujar();
	
	while (true) {
		
		
		if (kbhit()) {
			int t = getch();
			if (t == ' ') {
				b1.disparar(n1.getX() + 1, n1.getY());
			} else {
				n1.procesarTecla(t);   
			}
		}
		
	
		n1.actualizarMovimiento();
		
		b1.mover();
	}
	
	return 0;
}

