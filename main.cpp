// Projet disponible en fichier séparé : https://github.com/tinou98/Prologin-2014-WiFi //
// Les commentaires sont compatibles Doxygen //

/**
 * \file main.cpp
 * \brief Programme de resolution du problème WiFi pour Prologin 2015
 * \author Quentin M
 * \version 1.2
 * \date 4 Janvier 2015
 */

#include <vector>
#include <math.h>
#include <algorithm>
#include <map>

#include "tri.h"
#include "coord.h"

/** On définit PI pour qu'il ait la même précision sur tout les compilateurs */
#define M_PI 3.14159265358979323846

using namespace std;

vector<coord> blocked; /**< Tout point qui est passé qu'une fois : bloqué*/
vector<coord> released; /**< Tout point qui est passé deux fois : débloqué*/

/**
 * @brief Teste les angles du triangle.
 * Si un des angles est supérieur a 90°, il n'y aura pas de point enfermé
 * @param t Un triangle
 * @return `false` si un des angles est >90. `true` sinon
 */
bool testAngle(tri t) {
	bool b = false;

	//cerr << "a : " << t.a << endl;
	//cerr << "b : " << t.b << endl;
	//cerr << "c : " << t.c << endl;

	//cerr << "AB : " << t.ab() << endl;
	//cerr << "BC : " << t.bc() << endl;
	//cerr << "CA : " << t.ac() << endl;

	double ABC = acos((t.ab()*t.ab() + t.bc()*t.bc() - t.ac()*t.ac())/(2*t.ab()*t.bc()));
//cerr << "ABC : " << ABC << " => " << round(ABC*2 * 100) / 100 << " = " << ABC*180/M_PI << "\n";
	if(round(ABC*2 * 100) / 100 > round(M_PI * 100) / 100)	return false;
double a1 = round(ABC*2 * 100) / 100;
double a2 = round(M_PI * 100) / 100;
	if(a1 == a2)	b = true;

	double BCA = acos((t.bc()*t.bc() + t.ac()*t.ac() - t.ab()*t.ab())/(2*t.ac()*t.bc()));
//cerr << "BCA : " << BCA << " => " << round(BCA*2 * 100) / 100 << " = " << BCA*180/M_PI << "\n";
	if(round(BCA*2 * 100) / 100 > round(M_PI * 100) / 100)	return false;
a1 = round(BCA*2 * 100) / 100;
	if(a1 == a2)	b = true;

	double BAC = acos((t.ab()*t.ab() + t.ac()*t.ac() - t.bc()*t.bc())/(2*t.ab()*t.ac()));
	//double BAC = M_PI - ABC - BCA;
//cerr << "BAC : " << BAC << " => " << round(BAC*2 * 100) / 100 << " = " << BAC*180/M_PI << "\n";
	if(round(BAC*2 * 100) / 100 > round(M_PI * 100) / 100)	return false;
a1 = round(BAC*2 * 100) / 100;
	if(a1 == a2)	b = true;

	if(b == true) {
		coord c(t.getCentreCercleCirconscrit());
		if(std::find(blocked.begin(), blocked.end(), c)!=blocked.end()) {
			//cerr << c << " found. He is now released !!" << endl;
			if(std::find(released.begin(), released.end(), c) == released.end()) {
				released.push_back(c);
			} else {//cerr << "Mais il est déjà dans la base ...\n";
			}
		} else {
			//cerr << "Adding " << c << " too block !!" << endl;
			blocked.push_back(c);
		}
	}

	//cerr << "## END ##\n";
	return true;
}

/**
 * @brief Mise en forme du nombre, avec le bon nombre de chiffre après la virgule
 * @param i Le double a afficher
 */
void show(double i) {
	std::cout.precision(3);
	cout << std::fixed << round(i*1000)/1000 << endl;
}

void wifi(int n, std::vector<coord *> * tab) {
	// Compter nombre de triangle
	//unsigned int nbTriangle = (n*(n-1)*(n-2)) / (6);

	std::multimap<double, tri> list;

	coord a, b, c;
	for(int i = 0; i < n; i++) {
		a = *tab->at(i);
		for(int j = 0; j < n; j++) {
			b = *tab->at(j);
			for(int k = 0; k < n; k++) {
				c = *tab->at(k);

				if(i != j && i != k && j != k) {
					tri t = tri(a, b, c);

					bool found = false;
					for (std::map<double, tri>::iterator it=list.begin(); it!=list.end(); ++it) {
						if(it->second == t) {
							found = true;
							break;
						}
					}

					if(!found) {
						if(testAngle(t)) {
							list.insert(make_pair(t.getRayonCercleCirconscrit(), t)); // Auto template ...
						}
					}
				}
			}
		}
	}

	//cerr << "Nombre de triangle retenue (Pratique) : " << list.size() << endl;
	//cerr << "Nombre de triangle retenue (Théorie ) : " << (n*(n-1)*(n-2)) / (6) << endl;

	for (std::multimap<double, tri>::reverse_iterator it=list.rbegin(); it!=list.rend(); ++it) {
		bool calc = true;
		if(std::find(blocked.begin(), blocked.end(), it->second.getCentreCercleCirconscrit()) != blocked.end()) {
			calc = false;
			//cerr << "Item bloqué ..." << endl;
			if(std::find(released.begin(), released.end(), it->second.getCentreCercleCirconscrit()) != released.end()) {
				calc = true;
				//cerr << "Item débloqué ..." << endl;
			}
		}

		if (calc) {
			//cerr << "Item libre ..." << endl;
			bool ok = true;
			double r = it->first;
			coord cCC =  it->second.getCentreCercleCirconscrit();
			for(int l = 0; l < n; l++) {
				double dist = cCC.dist(*tab->at(l));
				//cerr << "R = " << r << "<?>" << dist << " = dist" << endl;
				if(r > dist) {
					//cerr << "## Un routeur couvre déjà la zone piégé ... ##" << endl;
					ok = false;
					break;
				}
			}
			if(ok) {// Trouvé !
				show(r);
				return;
			}
		}
	}

	// Rien ...
	cout << "0" << endl;
	return;
}

int main(){
	int n;
	std::cin >> n >> std::skipws;
	std::vector<coord * > *coords = new std::vector<coord *>( n );

	for(int i = 0 ; i < n; i++) {
		coord * c = new coord();
		c->x=0;	c->y=0;
		std::cin >> c->x >> std::skipws >> c->y;
		coords->at(i) = c;

		//cerr << c->x << ";" << c->y << endl;
	}

	wifi(n, coords);

	return 0;
}

