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
				�����������
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
				�������-�������	
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
				���-�������.

				��������� ���-�������� ��� ����� key � �������������� ��������� SHA256.

				���������� ������ �����, � ������� ������� ��������� ������� � ������ ������.
			*/
			// ����������� ���� � ������ ������
			string key_bytes = to_string(key);

			// �������� ���-������
			string hash_obj = sha256(key_bytes);

			// �������������� � ��������� ��������
			unsigned long long hash_value;
			stringstream ss;
			ss << hash_obj;
			ss >> hex >>  hash_value;                            //�������� ���, ������� ������� ����� ������������ �� HASH_VALUE, ��-�� ���� �� ������ ����� ���� long long(� ������������ ��� ���������������� �����)
			
			// return �������� ���� % buckCount 
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