#ifndef RUN_EXPR_H
#define RUN_EXPR_H

#include <math.h>
#include <stdio.h>
#include <string.h>

int RUN_EXPR_LOG = 0;
int opPriority(char chr) {
	switch (chr) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;
	}
	return 0;
}
int isDigit(char chr) {
	return chr >= '0' && chr <= '9';
}
int isIdHead(char chr) {
	return chr=='_' || (chr|=32)>='a' && chr<='z';
}
int isIdBody(char chr) {
	return isDigit(chr) || isIdHead(chr);
}
double runExprRec(const char str[], int ini, int end, double x) {
	int i;
	while (str[ini] == ' ' || str[ini] == '+' && ini < end) ++ ini;
	while (str[end] == ' ' && end > ini) -- end;
	if (RUN_EXPR_LOG) {
		putchar('[');
		for (i=ini; i<=end; ++i) putchar(str[i]);
		putchar(']');
	}
	int n = end - ini + 1;
	const char* s = str + ini;
	if (s[0] == '-') {
		return - runExprRec(s, 1, n - 1, x);
	}
	int bracketLevel = 0;
	char opr = '\0';
	int lowerPriority = 4;
	int oprIndex = -1;
	for (i=0; i<n; ++i) {
		if (s[i] == '(') ++ bracketLevel;
		if (bracketLevel == 0) {
			int priority = opPriority(s[i]);
			if (priority && priority <= lowerPriority) {
				int cancel = 0;
				if (priority == 1) {
					int j;
					for (j=i-1; j>0 && s[j]==' '; --j);
					if (opPriority(s[j]) > 1) {
						cancel = 1;
						break;
					}
				}
				if (!cancel) {
					oprIndex = i;
					opr = s[i];
					lowerPriority = priority;
				}
			}
		}
		if (s[i] == ')') -- bracketLevel;
	}
	if (oprIndex >= 0) {
		double a = runExprRec(s, 0, oprIndex - 1, x);
		double b = runExprRec(s, oprIndex + 1, n - 1, x);
		switch (opr) {
			case '+': return a + b;
			case '-': return a - b;
			case '*': return a * b;
			case '/': return a / b;
			case '^': return pow(a, b);
		}
		return 0;
	}
	if (s[0] == '(') {
		return runExprRec(s, 1, n - 2, x);
	}
	if (isDigit(*s)) {
		double r;
		char temp[255];
		for (i=0; isDigit(s[i]) || s[i] == '.'; ++i) {
			temp[i] = s[i];
		}
		temp[i] = '\0';
		sscanf(temp, "%lf", &r);
		return r;
	}
	if (isIdHead(s[0])) {
		char temp[255];
		for (i=0; isIdBody(s[i]); ++i) {
			temp[i] = s[i];
		}
		temp[i] = '\0';
		if (!strcmp(temp, "log")) return log10(runExprRec(s, i, n - 1, x));
		if (!strcmp(temp, "ln")) return log(runExprRec(s, i, n - 1, x));
		if (!strcmp(temp, "exp")) return exp(runExprRec(s, i, n - 1, x));
		if (!strcmp(temp, "sin")) return sin(runExprRec(s, i, n - 1, x));
		if (!strcmp(temp, "cos")) return cos(runExprRec(s, i, n - 1, x));
		if (!strcmp(temp, "tan")) return tan(runExprRec(s, i, n - 1, x));
		//double x = 
		if (!strcmp(temp, "e")) return (double) 2.718281828459045235360287;
		if (!strcmp(temp, "x")) return x;
	}
}
double runExpr(const char str[], double x) {
	if (RUN_EXPR_LOG) {
		putchar('<');
	}
	double value = runExprRec(str, 0, strlen(str) - 1, x);
	if (RUN_EXPR_LOG) {
		puts(">");
	}
	return value;
}
double runExprRecDif(const char str[], int ini, int end, double x, double y) {
	int i;
	while (str[ini] == ' ' || str[ini] == '+' && ini < end) ++ ini;
	while (str[end] == ' ' && end > ini) -- end;
	if (RUN_EXPR_LOG) {
		putchar('[');
		for (i=ini; i<=end; ++i) putchar(str[i]);
		putchar(']');
	}
	int n = end - ini + 1;
	const char* s = str + ini;
	if (s[0] == '-') {
		return - runExprRecDif(s, 1, n - 1, x, y);
	}
	int bracketLevel = 0;
	char opr = '\0';
	int lowerPriority = 4;
	int oprIndex = -1;
	for (i=0; i<n; ++i) {
		if (s[i] == '(') ++ bracketLevel;
		if (bracketLevel == 0) {
			int priority = opPriority(s[i]);
			if (priority && priority <= lowerPriority) {
				int cancel = 0;
				if (priority == 1) {
					int j;
					for (j=i-1; j>0 && s[j]==' '; --j);
					if (opPriority(s[j]) > 1) {
						cancel = 1;
						break;
					}
				}
				if (!cancel) {
					oprIndex = i;
					opr = s[i];
					lowerPriority = priority;
				}
			}
		}
		if (s[i] == ')') -- bracketLevel;
	}
	if (oprIndex >= 0) {
		double a = runExprRecDif(s, 0, oprIndex - 1, x, y);
		double b = runExprRecDif(s, oprIndex + 1, n - 1, x, y);
		switch (opr) {
			case '+': return a + b;
			case '-': return a - b;
			case '*': return a * b;
			case '/': return a / b;
			case '^': return pow(a, b);
		}
		return 0;
	}
	if (s[0] == '(') {
		return runExprRecDif(s, 1, n - 2, x, y);
	}
	if (isDigit(*s)) {
		double r;
		char temp[255];
		for (i=0; isDigit(s[i]) || s[i] == '.'; ++i) {
			temp[i] = s[i];
		}
		temp[i] = '\0';
		sscanf(temp, "%lf", &r);
		return r;
	}
	if (isIdHead(s[0])) {
		char temp[255];
		for (i=0; isIdBody(s[i]); ++i) {
			temp[i] = s[i];
		}
		temp[i] = '\0';
		if (!strcmp(temp, "log")) return log10(runExprRecDif(s, i, n - 1, x, y));
		if (!strcmp(temp, "ln")) return log(runExprRecDif(s, i, n - 1, x, y));
		if (!strcmp(temp, "exp")) return exp(runExprRecDif(s, i, n - 1, x, y));
		if (!strcmp(temp, "sin")) return sin(runExprRecDif(s, i, n - 1, x, y));
		if (!strcmp(temp, "cos")) return cos(runExprRecDif(s, i, n - 1, x, y));
		if (!strcmp(temp, "tan")) return tan(runExprRecDif(s, i, n - 1, x, y));
		if (!strcmp(temp, "e")) return (double) 2.718281828459045235360287;
		if (!strcmp(temp, "x")) return x;
		if (!strcmp(temp, "y")) return y;
	}
}
double runExprDif(const char str[], double x, double y) {
	if (RUN_EXPR_LOG) {
		putchar('<');
	}
	double value = runExprRecDif(str, 0, strlen(str) - 1, x, y);
	if (RUN_EXPR_LOG) {
		puts(">");
	}
	return value;
}
#endif
