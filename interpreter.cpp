//
// 52121729 ������
// Project 2. interpreter
// 

#include <iostream>
#include <string.h>
using namespace std;

void tokenize();
void analyze();
void copy(char*, char*);

// ��ū �ϳ��� �ִ���� 32 bytes
// �ִ� 64�� ����.
char tok[64][32];

// �������� strVal�� ������ intVal�� ���� ��. valIdx�� ���� ���� ������ ���� ����
int intVal[32];
char strVal[32][32];
int valIdx = 0;

int k = 0;
// �Է°�
char* input = new char[128];
char ch;
int idx;

int main() {
	while (1) {
		// cin�� ���� �Է� ����
		cin.getline(input, 128);

		// input�� ù���� ch ����.
		ch = input[0];

		// ��ũ����¡ �Լ�. ������ ��ūȭ �Ͽ� �迭�� ����.
		tokenize();

		// �ǹ� �м� �Լ�.
		analyze();
	}
	return 0;
}

// ����, ���� ���� �� ��ū�� tok �迭�� ����.
void tokenize() {
	char buff[128];
	int i = 0;
	for (idx = 0;; idx++) {
		ch = input[idx];
		// ���ڿ� �� null ���� ������.(���ڿ��� ������)
		if (ch == '\0') {
			if (input[idx - 1] == ')')
				break;
			else {
				buff[idx] = '\0';
				copy(tok[k++], buff);
				break;
			}
		}
		// ������ ������
		else if (isspace(ch)) {
			buff[i] = '\0';
			copy(tok[k++], buff);
			memset(buff, '\0', 128);
			i = 0;
		}
		else if (isalpha(ch))
			buff[i++] = ch;
		else if (isdigit(ch))
			buff[i++] = ch;
		else {
			// (�� )�� ,�� ?�� ������ buff �迭 �ʱ�ȭ �� tok �迭�� ����.
			if (ch == '(' || ch == ')' || ch == ',' || ch == '?') {
				buff[i] = '\0';
				copy(tok[k++], buff);
				i = 0;
				tok[k++][0] = ch;
				memset(buff, '\0', 128);
			}
			else {
				cout << "error" << endl;
				exit(1);
			}
		}
	}
}

void copy(char* dest, char* src) {
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
}

// �ǹ̺м� 
// put�� ������ �迭�� valIdx+1�� ��Ҹ� ������, valIdx+2 ��Ҹ� ���� ������ ����.
// sum, min, mul, div�� ������ valIdx+2�� ��Ҹ� ���� a1, valIdx+4�� ��Ҹ� ���� a2�� ���� �� ����.
void analyze() {
	for (int i = 0; i<k; i++) {

		// ��ū �迭�� i��° ��Ұ� put�� ���.
		if (!strcmp(tok[i], "put")) {
			copy(strVal[valIdx], tok[i + 1]);
			intVal[valIdx++] = atoi(tok[i + 2]);
		}

		// ��ū �迭�� i��° ��Ұ� sum�� ���.
		if (!strcmp(tok[i], "sum")) {
			double a1 = 0; double a2 = 0;
			for (int j = 0; j<valIdx; j++) {
				if (!strcmp(tok[i + 2], strVal[j]))
					a1 = intVal[j];
				if (!strcmp(tok[i + 4], strVal[j]))
					a2 = intVal[j];
			}
			cout << a1 + a2 << endl;
		}

		// ��ū �迭�� i��° ��Ұ� min�� ���.
		if (!strcmp(tok[i], "min")) {
			double a1 = 0; double a2 = 0;
			for (int j = 0; j<valIdx; j++) {
				if (!strcmp(tok[i + 2], strVal[j]))
					a1 = intVal[j];
				if (!strcmp(tok[i + 4], strVal[j]))
					a2 = intVal[j];
			}
			cout << a1 - a2 << endl;
		}

		// ��ū �迭�� i��° ��Ұ� mul�� ���.
		if (!strcmp(tok[i], "mul")) {
			double a1 = 0; double a2 = 0;
			for (int j = 0; j<valIdx; j++) {
				if (!strcmp(tok[i + 2], strVal[j]))
					a1 = intVal[j];
				if (!strcmp(tok[i + 4], strVal[j]))
					a2 = intVal[j];
			}
			cout << a1*a2 << endl;
		}

		// ��ū �迭�� i��° ��Ұ� div�� ���.
		if (!strcmp(tok[i], "div")) {
			double a1 = 0; double a2 = 0;
			for (int j = 0; j<valIdx; j++) {
				if (!strcmp(tok[i + 2], strVal[j]))
					a1 = intVal[j];
				if (!strcmp(tok[i + 4], strVal[j]))
					a2 = intVal[j];
			}
			cout << a1 / a2 << endl;
		}
	}

	// tok �迭 �ʱ�ȭ.
	k = 0;
	memset(tok, '\0', 2048);
}