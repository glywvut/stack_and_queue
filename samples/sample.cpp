#include "stack_and_queue.h"
#include <string>
using namespace std;

int Check(string s) {
	Stack<char> stack;
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] == '(') || (s[i] == '[') || (s[i] == '{'))
			stack.push(s[i]);
		if (s[i] == ')') {
			if (stack.top() != '(')
				return 0;
			stack.pop();
		}
		if (s[i] == ']') {
			if (stack.top() != '[')
				return 0;
			stack.pop();
		}
		if (s[i] == '}') {
			if (stack.top() != '{')
				return 0;
			stack.pop();
		}
	}
	if (stack.size()) return 0;
	return 1;
}
int main() {
	setlocale(LC_ALL, "rus");
	string tmp;
	cout << "Введите выражение: ";
	cin >> tmp;
	if (Check(tmp))
		cout << "Скобки расставлены верно" << endl;
	else
		cout << "Есть несоответствие" << endl;
}