#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;


class Expr {
private: Expr* e;
public:
	virtual int eval() = 0;
	virtual string outputExpr() const = 0;
	friend ostream& operator <<(ostream &os, const Expr &a) {
		return os << a.outputExpr();
	}

};

class Const :public Expr {
private: int a;
public: Const(int a) :a(a) {}
		int eval() { return a; }
		string outputExpr()const {
			return to_string(a);
		}
		int getConst() { return this->a; }
};

class Var :public Expr {
private: string s; int a;
public:  Var(string s, int a = 0) :s(s), a(a) { Var::Globalmap->push_back(this); }
		 static vector<Var*> *Globalmap;
		 static void set(string n, int v) {
			 for (auto it = Globalmap->begin(); it != Globalmap->end(); it++)
			 {
				 if ((*it)->s == n)
				 {
					 (*it)->a = v;
				 }
			 }
		 }
		 int eval() { return this->a; }
		 string outputExpr()const {
			 return this->s;
		 }
		 int getVar() { return this->a; }
};

class Add :public Expr
{
private:
	Expr  *leftOp, *rightOp;
public:
	Add(Expr *lhs, Expr *rhs)
	{
		leftOp = lhs;
		rightOp = rhs;
	}
	string outputExpr() const
	{
		return leftOp->outputExpr() + " + " + rightOp->outputExpr();
	}
	int eval()
	{
		return leftOp->eval() + rightOp->eval();
	}
};
//class Add :public Expr{
//private: int a; int b; string x;
//		 bool f;
//public:
//	   Add(Const a, Const b) :a(a.getConst()), b(b.getConst()) { f = false; }
//	  
//	   Add(Var x, Const b) :x(x.getVar()), b(b.getConst()) { f = true; }
//	   
//	   int eval() { return a + b; }
//	   string outputExpr() const
//	   {   if(!f)
//		   return to_string(a) + " + " + to_string(b);
//	   return x + " + " + to_string(b);
//	   }
//	   
//	   
//};
