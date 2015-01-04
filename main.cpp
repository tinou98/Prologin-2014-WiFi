#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <limits>

#include "coord.h"
#include "tri.h"

using namespace std;

bool testAngle(tri t) {
	cerr << "a : " << t.a << endl;
	cerr << "b : " << t.b << endl;
	cerr << "c : " << t.c << endl;

	cerr << "AB : " << t.ab() << endl;
	cerr << "BC : " << t.bc() << endl;
	cerr << "CA : " << t.ac() << endl;

	double ABC = acos((t.ab()*t.ab() + t.bc()*t.bc() - t.ac()*t.ac())/(2*t.ab()*t.bc()));
cerr << "ABC : " << ABC << " => " << round(ABC*2 * 100) / 100 << " = " << ABC*180/M_PI << "\n";
	if(round(ABC*2 * 100) / 100 >= round(M_PI * 100) / 100)	return false;

	double BCA = acos((t.bc()*t.bc() + t.ac()*t.ac() - t.ab()*t.ab())/(2*t.ac()*t.bc()));
cerr << "BCA : " << BCA << " => " << round(BCA*2 * 100) / 100 << " = " << BCA*180/M_PI << "\n";
	if(round(BCA*2 * 100) / 100 >= round(M_PI * 100) / 100)	return false;

	double BAC = acos((t.ab()*t.ab() + t.ac()*t.ac() - t.bc()*t.bc())/(2*t.ab()*t.ac()));
	//double BAC = M_PI - ABC - BCA;
cerr << "BAC : " << BAC << " => " << round(BAC*2 * 100) / 100 << " = " << BAC*180/M_PI << "\n";
	if(round(BAC*2 * 100) / 100 >= round(M_PI * 100) / 100)	return false;

cerr << "## END ##\n";
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
							cerr << t.getRayonCercleCirconscrit();
							list.insert(make_pair<double, tri>(t.getRayonCercleCirconscrit(), t));
						}
					}
				}
			}
		}
	}

	cerr << "Nombre de triangle retenue (Pratique) : " << list.size() << endl;
	cerr << "Nombre de triangle retenue (Théorie ) : " << (n*(n-1)*(n-2)) / (6) << endl;

	for (std::multimap<double, tri>::reverse_iterator it=list.rbegin(); it!=list.rend(); ++it) {
		bool ok = true;
		double r = it->first,
				r2 = r * r;
		coord cCC =  it->second.getCentreCercleCirconscrit();
		for(int l = 0; l < n; l++) {
			double dist = cCC.dist(*tab->at(l));
			cerr << "R² = " << r2 << "<?>" << dist << endl;
			if(r2 < dist) {
				cerr << "## FATAL ERROR : STOP :) ##" << endl;
				ok = false;
				break;
			}
		}
		if(ok) {// Trouvé !
			show(r);
			return;
		}
	}
	// Rien ...
	cout << "0" << endl;

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

		cerr << c->x << ";" << c->y << endl;
	}

	wifi(n, coords);

	return 0;
}
