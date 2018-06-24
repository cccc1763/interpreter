//
// 52121729 최주헌
// Project 2. interpreter
// 

#include <iostream>
#include <string.h>
using namespace std;

void tokenize();
void analyze();
void copy(char*, char*);

// 토큰 하나의 최대길이 32 bytes
// 최대 64개 저장.
char tok[64][32];

// 변수저장 strVal은 변수명 intVal은 변수 값. valIdx는 현재 까지 생성된 변수 갯수
int intVal[32];
char strVal[32][32];
int valIdx = 0;

int k = 0;
// 입력값
char* input = new char[128];
char ch;
int idx;

int main() {
	while (1) {
		// cin을 통해 입력 받음
		cin.getline(input, 128);

		// input의 첫문자 ch 설정.
		ch = input[0];

		// 토크나이징 함수. 문장을 토큰화 하여 배열에 넣음.
		tokenize();

		// 의미 분석 함수.
		analyze();
	}
	return 0;
}

// 문자, 숫자 구분 후 토큰을 tok 배열에 넣음.
void tokenize() {
	char buff[128];
	int i = 0;
	for (idx = 0;; idx++) {
		ch = input[idx];
		// 문자열 중 null 값을 만나면.(문자열이 끝나면)
		if (ch == '\0') {
			if (input[idx - 1] == ')')
				break;
			else {
				buff[idx] = '\0';
				copy(tok[k++], buff);
				break;
			}
		}
		// 공백이 나오면
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
			// (와 )와 ,와 ?를 만나면 buff 배열 초기화 후 tok 배열에 넣음.
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

// 의미분석 
// put을 만나면 배열의 valIdx+1의 요소를 변수명, valIdx+2 요소를 변수 값으로 지정.
// sum, min, mul, div를 만나면 valIdx+2의 요소를 변수 a1, valIdx+4의 요소를 변수 a2에 대입 후 연산.
void analyze() {
	for (int i = 0; i<k; i++) {

		// 토큰 배열의 i번째 요소가 put일 경우.
		if (!strcmp(tok[i], "put")) {
			copy(strVal[valIdx], tok[i + 1]);
			intVal[valIdx++] = atoi(tok[i + 2]);
		}

		// 토큰 배열의 i번째 요소가 sum일 경우.
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

		// 토큰 배열의 i번째 요소가 min일 경우.
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

		// 토큰 배열의 i번째 요소가 mul일 경우.
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

		// 토큰 배열의 i번째 요소가 div일 경우.
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

	// tok 배열 초기화.
	k = 0;
	memset(tok, '\0', 2048);
}