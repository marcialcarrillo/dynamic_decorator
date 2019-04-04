#include "Nodo.h"

class Arista{
	protected:
		Nodo* first;
		Nodo* second;
	public:
		Arista() {}
		Arista(Nodo* first, Nodo* second){
			this->first = first;
			this->second = second;
		}
		virtual ~Arista() {}
		virtual string toString() const = 0;
};