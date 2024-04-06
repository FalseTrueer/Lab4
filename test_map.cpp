#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include "sha256.h"

using namespace std;

template<class T, class K>
class hashMap {
	public:
		map<T, map<T, K>> buckets;
		int elemCount;
		int buckCount;
		float cof;

		hashMap(float cof = 2.0) {
			/*
				Конструктор
			*/
			for (int i = 0; i < 11; ++i) {
				buckets[i] = map<T, K>();
			}
			elemCount = 0;
			buckCount = buckets.size();
			this->cof = cof;
		}

		void clear() {
			/*
				Функция-очистки	
			*/
			for (int i = 0; i < 11; ++i) {
				buckets[i] = map<T, K>();
			}
			elemCount = 0;
			buckCount = buckets.size();
			cof = 2.0;
		}

		int hash_func(K key) {
			/*
				Хеш-функция.

				Вычисляет хеш-значение для ключа key с использованием алгоритма SHA256.

				Возвращает индекс ведра, в которое следует поместить элемент с данным ключом.
			*/
			// Преобразуем ключ в массив байтов
			string key_bytes = to_string(key);

			// Вычислим хеш-объект
			string hash_obj = sha256(key_bytes);

			// Преобразование к числовому значению
			unsigned long long hash_value;
			stringstream ss;
			ss << hash_obj;
			ss >> hex >>  hash_value;                            //ПРОБЛЕМА ТУТ, СЛИШКОМ БОЛЬШОЕ ЧИСЛО ВОЗВРАЩАЕТСЯ НА HASH_VALUE, из-за чего он просто берет макс long long(а возвращается там шестнацетиричное число)
			
			// return значение хеша % buckCount 
			return hash_value % buckCount;
		}

		void insert(T key, K value) {
			this->mp.insert(key, value);
		}

};

void printMap(const map<int, map<int, int>>& m) {
	for (const auto& pair : m) {
		cout << "Key out map: " << pair.first << endl;
		cout << "Inside map: " << endl;
		for (const auto& inner_pair : pair.second) {
			cout << "  Key inside map: " << inner_pair.first
				<< ", Value inside map: " << inner_pair.second << endl;
		}
		cout << endl;
	}
}

int main() {

	hashMap<int, int> hm;
	int encodedData = hm.hash_func(123);
	string a = sha256("123");
	cout << encodedData << endl;
	return 0;
}