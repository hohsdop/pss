#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

vector<char> symbols;
vector<char> digits;
vector<char> letters;

class User {
private:
	string login;
	int amount;
	int len;
	bool aredigits;
	bool aresymbols;
	vector<string> passwords;
public:
	void generate() {
		string res;
		int flag;
		for (int i = 0; i < amount; i++) {
			res = "";
			for (int i = 0; i < len; i++) {
				if (aredigits && aresymbols) {
					flag = rand() % 3;
				} else if (aredigits || aresymbols) {
					flag = rand() % 2;
				} else {
					flag = 0;
				}
				if (flag == 0) {
					res += letters[rand() % (letters.size())];
				} else if (flag == 1 && aredigits) {
					res += digits[rand() % (digits.size())];
				} else if (flag == 1 && aresymbols) {
					res += symbols[rand() % (symbols.size())];
				} else{
					res += symbols[rand() % (symbols.size())];
				}
			}
			passwords.push_back(res);
		}
	}

	void record(string name) {
		ofstream fout(name);
		fout << "Login: " << login << '\n';
		fout << "Passwords:\n";
		for (int i = 0; i < amount; i++) {
			fout << passwords[i] << '\n';
		}
		fout.close();
	}

	friend istream& operator>> (istream &in, User &v) {
		cout << "Your login: ";
		in >> v.login;
		cout << "Amount of passwords to generate: ";
		in >> v.amount;
		cout << "Length of passwords: ";
		in >> v.len;
		cout << "Are there will digits? 1-there are; 0-there are not: ";
		in >> v.aredigits;
		cout << "Are there will special symbols? 1-there are; 0-there are not: ";
		in >> v.aresymbols;
		return in;
	}
	friend ostream& operator<< (ostream &out, const User &v){
		out << "Login: " << v.login << '\n';
		out << "Generated passwords:\n";
		for (int i = 0; i < v.passwords.size(); i++) {
			out << v.passwords[i] << '\n';
		}
		out << "--------------------------------------";
		return out;
	}
	void print() {
		cout << login << ' ' << amount << ' ' << len << ' '<< aredigits << ' ' << aresymbols;
	}
};

int main() {
	srand(time(NULL));
	//------------------------------
	for (int i = 33; i < 48; i++) {
		symbols.push_back(i);
	}
	for (int i = 48; i < 58; i++) {
		digits.push_back(i);
	}
	for (int i = 65; i < 91; i++) {
		letters.push_back(i);
	}
	for (int i = 97; i < 123; i++) {
		letters.push_back(i);
	}
	//------------------------------
	User u;
	cin >> u;
	u.generate();
	u.record("tes.txt");
	cout << u << '\n';
	return 0;
}
