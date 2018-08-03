/*
	calculator_buggy.cpp
*/

#include "std_lib_facilities.h"


struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void putback(Token t) { buffer=t; full=true; }

	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

const char sinfunction = 's';//declar const sin
const char cosfunction = 'c';//declar const cos
const char tanfunction = 't';//declar const tan
const char sqrtfunction = 'S';//declar const sqrt




Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case '!'://case if it is a factorial
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
		cin.unget();
		double val;
		cin >> val;
		return Token(number,val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == "let") return Token(let);	
			if (s == "quit") return Token(quit);
			if (s == "sin") return Token(sinfunction);//case if it is sin 
			if (s == "cos") return Token(cosfunction);//case if it is cos
			if (s == "tan") return Token(tanfunction);//case if it is tan 
			if (s == "sqrt") return Token(sqrtfunction);//case if it is sqrt 
			return Token(name,s);
		}
		error("Bad token");
	}
}




void Token_stream::ignore(char c)
{
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin>>ch)
		if (ch==c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;	




double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

void set_value(string s, double d)
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();



int factorial(int t)//Calculating a factorial
{
	int result = 1;//if it is a 0! result is 1;
	for (int i = 1; i <= t; i++)
		{
			result *= i;
		}
	return result;
}


double mathsin(string s) //Calculating a sin function
{
	Token t = ts.get();// get (
	Token t2 = ts.get();// get number
	Token t3 = ts.get();// get )
	return sin(t2.value);
}

double mathcos(string s) //Calculating a cos function
{
	Token t = ts.get();// get (
	Token t2 = ts.get();// get number
	Token t3 = ts.get();// get )
	return cos(t2.value);
}

double mathtan(string s) //Calculating a tan function
{
	Token t = ts.get();// get (
	Token t2 = ts.get();// get number
	Token t3 = ts.get();// get )
	return tan(t2.value);
}

double mathsqrt(string s) //Calculating a sqrt function
{
	Token t = ts.get();// get (
	Token t2 = ts.get();// get number
	Token t3 = ts.get();// get )
	return sqrt(t2.value);
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':{	
		double d = expression();
	t = ts.get();
	if (t.kind != ')') error("'(' expected");
	return d; //print d
	}
	case '-':
		return -primary();
	case '+': //case if it is a +number
		return +primary();//return +number
	case number:
	{
		Token t2 = ts.get();//check if it is a factorial after the number
		if (t2.kind == '!')
			return factorial(t.value);//Calculating a factorial
		else {//if it is not a factorial
			ts.putback(t2);
			return t.value;
		}
	}
	case name:
			return get_value(t.name);
	case sinfunction://case if it is a sin function
			return mathsin(t.name);//calculate sin
	case cosfunction://case if it is a cos function
		return mathcos(t.name);//calculate cos
	case tanfunction://case if it is a tan function
		return mathtan(t.name);//calculate tan
	case sqrtfunction://case if it is a sqrt function
		return mathsqrt(t.name);//calculate sqrt
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}





double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	else if(name == "pi") error(name, " declared twice");
	else if (name == "e") error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	names.push_back(Variable(name,d));
	return d;

}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void declaration_number()//declaer 'pi' and 'e'
{
	names.push_back(Variable("pi", 3.14159));
	names.push_back(Variable("e", 2.71828));
}




void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	declaration_number();//get 'pi' and 'e'
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "exception\n";
	return 2;
}
