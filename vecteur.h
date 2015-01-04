#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>

/**
 * @brief Stocke un vecteur 2d
 */
class vecteur {
public:
	double x; /**< Coordonné sur l'axe X (accéssible en lecture + écriture) */
	double y; /**< Coordonné sur l'axe Y (accéssible en lecture + écriture) */

	/**
	 * @brief Constructeur par défaut
	 */
	vecteur();

	/**
	 * @brief Constructeur prenant deux paramètres
	 * @param x La coordonné X du vecteur
	 * @param y La coordonné Y du vecteur
	 */
	vecteur(const double &x, const double &y);

	/**
	 * @brief Constructeur de copie
	 * @param old Objet a copier
	 */
	vecteur(const vecteur &old);

	/**
	 * @brief Calcule la norme
	 * @return La norme du vecteur
	 */
	double norme();

	/**
	 * @brief Normalise le vecteur : sa orme devient 1
	 */
	void normalize();

	/**
	 * @brief Permet d'afficher un vecteur.
	 * Forme : (x;y)
	 * @param c Objet de type vecteur a afficher
	 */
	friend std::ostream& operator<<(std::ostream& os, const vecteur& c);

	/**
	 * @brief Operateur d'addition
	 * @param Valeur a ajouter
	 * @return L'objet lui même
	 */
	vecteur& operator+=(vecteur const& a);
};

/**
 * @brief Operateur d'addition
 * @param a Première valeur a ajouter
 * @param b Deuxième valeur a ajouter
 * @return La somme de `a` et`b`
 */
vecteur operator+(vecteur const& a, vecteur const& b);

/**
 * @brief Opérateur d'égalité
 * @param lhs Left-hand side
 * @param rhs Right-hand side
 * @return `true` si les deux paramètre sont égaux
 */
bool operator==(const vecteur& lhs, const vecteur& rhs);


#endif // VECTEUR_H
