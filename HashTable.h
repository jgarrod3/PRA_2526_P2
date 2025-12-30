#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../../prac_1/PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;

		int h(std::string key) const {
			int suma = 0;
			for (char c : key) {
				suma += static_cast<int>(c);
			}
			return suma % max;
		}

	public:
		HashTable(int size) : n(0), max(size) {
			table = new ListLinked<TableEntry<V>>[max];
		}

		~HashTable() {
			delete[] table;
		}

		int capacity() const {
			return max;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
			out << "HashTable [Entradas: " << th.entries() 
			    << ", Capacidad: " << th.capacity() << "]\n"; 
			out << "====================================\n\n";  
			
			for (int i = 0; i < th.max; i++) {
				out << "== Cubeta " << i << "==\n\n";
				if (th.table[i].size() == 0) {
					out << "List => []\n\n";
				} else {
				out << "List => [\n";
				for (int j = th.table[i].size() - 1; j >= 0; j--) {
					TableEntry<V> e = th.table[i].get(j);
					out << "  ('" << e.key << "' => " << e.value << ")\n";
					}
				out << "]\n\n";
				}
			}
			out << "==============================\n";
			
			
			return out;
			
		}

		V operator[](std::string key) {
			return search(key);
		}

		void insert(std::string key, V value) override {
			int index = h(key);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index].get(i).key == key) {
					throw std::runtime_error("La clave ya existe");
				}
			}
			TableEntry<V> entry(key, value);
			table[index].append(entry);
			n++;
		}

		V search(std::string key) const override {
			int index = h(key);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index].get(i).key == key) {
					return table[index].get(i).value;
				}
			} 
			throw std::runtime_error("No se ha encontrado la clave");
		}

		V remove(std::string key) override {
			int index = h(key);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index].get(i).key == key) {
					V value = table[index].get(i).value;
					table[index].remove(i);
					n--;
					return value;
				}
			}
			throw std::runtime_error("No se ha encontrado la clave");
		}
		
		int entries() const override {
			return n;
		}
};

#endif
