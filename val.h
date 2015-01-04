#ifndef VAL_H
#define VAL_H

#include <stdexcept>

/**
 * @brief Cette classe permet de gérer un système de calcule de valeur dynamique.
 * La valeur n'est calculé qu'en cas de besoin.
 */
template <typename T> class val {
public:
	/**
	 * @brief Constructeur par défaut : met `isCalc` à `false`
	 */
	val() {
		calc = false;
	}

	/**
	 * @brief Retourne si la valeur est calculé
	 * @return `true` si on a déja calculé la valeur
	 */
	bool isCalc() {
		return calc;
	}


	/**
	 * @brief Renvoi la valeur calculée
	 * @exception std::logic_error La valeur n'a pas été calculée.
	 * @return La valeur calculée.
	 */
	T getVal() {
		if(!calc)
			throw std::logic_error("La valeur n'a pas été calculé");
		else
			return _val;
	}

	/**
	 * @brief Définie la nouvelle valeur, isCalc renvoi maintenant `true`
	 * @param newVal La nouvelle valeur a définir.
	 */
	void setVal(const T newVal) {
		calc = true;
		_val = newVal;
	}

private:
	bool calc; /**< Si la valeur a été calculé vaut `true`, sinon vaut `false` (privée) */
	T _val; /**< Stockage de la valeur (privée) @see getVal */
};

#endif // VAL_H
