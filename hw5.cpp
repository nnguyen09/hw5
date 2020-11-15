/***********************************************
Author: <Ngan Nguyen>
Date: <10/06/2020>
Purpose: <Rational>
Sources of Help: <c++ library, lecture note>
***********************************************/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 10/06/2020
Name: Ngan Nguyen
*/

#include <iostream>
#include <cstdlib>
using namespace std;

class Rational {
public:
	//constructor
	//a default constructor that initializes an object to 0 (that is, to 0/1);
	Rational():numerator(0),denominator(1){}
	//a constructor that has only a single parameter of type int; call this single parameter wholeNumber and the object will be initialized to the rational number wholeNumber/1; 
	Rational(int wholeNumber):numerator(wholeNumber), denominator(1){}
	//a constructor with two arguments that can be used to set the member variables of an object to anylegitimate values.
	Rational(int numer, int denom){
		numerator= numer;
		if(denom == 0){
			cout<<"Cannot devided by 0!"<<endl;
			exit(1);
		}else{
			denominator	= denom;	
		}
		
	}
	void setNumer(int numer){
		numerator = numer;
	}
	void setDenom(int denom){
		denominator = denom;
	}
	int getNumer (void)const{
		return numerator;
	}
	int getDenom(void)const{
		return denominator;
	}
	
	//friendfunction
	//+ - * /
	friend const Rational operator+(const Rational& leftNum, const Rational& rightNum); 
	friend const Rational operator-(const Rational& leftNum, const Rational& rightNum);
	friend const Rational operator*(const Rational& leftNum, const Rational& rightNum);
	friend const Rational operator/(const Rational& leftNum, const Rational& rightNum);
	//== ,>= , <=, > , < operator
	friend const bool operator == (const Rational& leftNum, const Rational& rightNum);
	friend const bool operator >= (const Rational& leftNum, const Rational& rightNum);
	friend const bool operator <= (const Rational& leftNum, const Rational& rightNum);
	friend const bool operator > (const Rational& leftNum, const Rational& rightNum);
	friend const bool operator < (const Rational& leftNum, const Rational& rightNum);
	
private:
	int numerator;
	int denominator;
	void normalize(Rational& num);
	int gcd (int x, int y);
};

const Rational operator+(const Rational& leftNum, const Rational& rightNum); 
const Rational operator-(const Rational& leftNum, const Rational& rightNum);
const Rational operator*(const Rational& leftNum, const Rational& rightNum);
const Rational operator/(const Rational& leftNum, const Rational& rightNum);
	//== ,>= , <= operator
const bool operator == (const Rational& leftNum, const Rational& rightNum);
const bool operator >= (const Rational& leftNum, const Rational& rightNum);
const bool operator <= (const Rational& leftNum, const Rational& rightNum);	
const bool operator > (const Rational& leftNum, const Rational& rightNum);
const bool operator < (const Rational& leftNum, const Rational& rightNum);
//cout
ostream& operator<<(ostream &out, const Rational &num);
//cin
istream& operator>>(istream &in, Rational &num);

int main(int argc, char**argv){
	Rational n1(-1,2),n2(-2,-4), n3,n4;
	n3 = n1+n2;

	cout<<"n1: "<<n1<<endl;
	cout<<"n2: "<<n2<<endl;
	cout<<"n3(sum of n1 and n2): "<<n3<<endl;
	cout<<"change n3 to 2/3 \n";
	cin>> n3;
	cout<<"n3 now is "<<n3<<endl;
	cout<<"n1 * n2 = "<<n1*n2<<endl;
	cout<<"n1 / n2 = "<<n1/n2<<endl;
	cout<<"n1 - n2 = "<<n1-n2<<endl;
	if(n1/n2==n1-n2)
		cout<<"n1 / n2 is equal to n1 - n2 \n";
	else 
		cout<<"n1 / n2 is NOT equal to n1 - n2 \n";
	if(n3>n1)
		cout<<n3<<" > " <<n1<<endl;
	else
		cout<<n3<<" < " <<n1<<endl;
	if(n2<n3)
		cout<<n2<<" < " <<n3<<endl;
	else 
		cout<<n2<<" > " <<n3<<endl;
	if(n1<=n2)
		cout<<n1 <<" <= "<<n2<<endl;
	else 
		cout<<n1 <<" > "<<n2<<endl;
	cout<<"enter n4: ";
	cin>>n4;

	if(n3>=n4)
		cout<<"n3 >= n4"<<endl;
	else 
		cout<<"n3 < n4"<<endl;
	return 0;
}

const Rational operator+( const Rational& leftNum, const Rational& rightNum){

	int numer,denom;
	Rational left = leftNum;
	Rational right = rightNum;
	left.normalize(left);
	right.normalize(right);

	if(left.denominator == right.denominator){
		denom = left.denominator;
		numer = left.numerator + right.numerator;
	}else{
		left.numerator *= right.denominator; 
		right.numerator*= left.denominator;
		right.denominator *=left.denominator;
		numer = left.numerator+right.numerator;
		denom= right.denominator;
	}


	return Rational(numer, denom);
}

const Rational operator-(const Rational& leftNum, const Rational& rightNum){
	int numer,denom;
	Rational left = leftNum;
	Rational right = rightNum;

	if(leftNum.denominator == rightNum.denominator){
		denom = leftNum.denominator;
		numer = leftNum.numerator - rightNum.numerator;
	}else if(left.denominator%right.denominator==0){
		right.numerator *= left.denominator/right.denominator;
		right.denominator*= left.denominator/right.denominator;
		numer= left.numerator-right.numerator;
		denom= left.denominator;
	}else if(right.denominator%left.denominator==0){
		left.numerator *= right.denominator/left.denominator;
		left.denominator*= right.denominator/left.denominator;
		numer= left.numerator-right.numerator;
		denom= left.denominator;
	}else{
		left.numerator *= right.denominator; 
		right.numerator*= left.denominator;
		right.denominator *=left.denominator;
		numer = left.numerator-right.numerator;
		denom= right.denominator;
	}
	return Rational(numer, denom);
}

const bool operator == (const Rational& leftNum, const Rational& rightNum){
	bool boolVal;
	Rational left = leftNum;
	Rational right = rightNum;
	left.normalize(left);
	right.normalize(right);
	if(left.numerator==right.numerator&&left.denominator==right.denominator)
		boolVal=true;
	else 
		boolVal=false;
	return boolVal;

}

const Rational operator*(const Rational& leftNum, const Rational& rightNum){
	int numer, denom;
	numer= leftNum.numerator * rightNum.numerator;
	denom = leftNum.denominator * rightNum.denominator;
	return Rational(numer, denom); 
}

const Rational operator/(const Rational& leftNum, const Rational& rightNum){
	int numer, denom;
	Rational left = leftNum;
	Rational right ;
	right.numerator = rightNum.denominator;
	right.denominator = rightNum. numerator;
	numer = left.numerator*right.numerator;
	denom= left.denominator*right.denominator;
	return Rational(numer, denom); 
}

void Rational::normalize(Rational& num){
	
	if((num.denominator<0&&num.numerator>0)||(num.denominator<0&&num.numerator<0)){
		num.numerator*=(-1);
		num.denominator*=(-1);
	}
	int a= gcd(num.numerator, num.denominator); //reduce leftNum ration
	num.denominator/=a;
	num.numerator/=a;
}

const bool operator >= (const Rational& leftNum, const Rational& rightNum){
	
	Rational left = leftNum;
	Rational right = rightNum;
	left.normalize(left);
	right.normalize(right);
	double numLeft = static_cast <double> (left.numerator)/left.denominator;
	double numRight = static_cast <double> (right.numerator)/right.denominator;
	return (numLeft>numRight||numLeft==numRight);

}
const bool operator <= (const Rational& leftNum, const Rational& rightNum){
	
	Rational left = leftNum;
	Rational right = rightNum;
	left.normalize(left);
	right.normalize(right);
	double numLeft = static_cast <double> (left.numerator)/left.denominator;
	double numRight = static_cast <double> (right.numerator)/right.denominator;
	return (numLeft < numRight||numLeft==numRight);
}

const bool operator > (const Rational& leftNum, const Rational& rightNum){
	
	Rational left = leftNum;
	Rational right = rightNum;
	left.normalize(left);
	right.normalize(right);
	double numLeft = static_cast <double> (left.numerator)/left.denominator;
	double numRight = static_cast <double> (right.numerator)/right.denominator;
	return (numLeft > numRight);

}
const bool operator < (const Rational& leftNum, const Rational& rightNum){
	Rational left = leftNum;
	Rational right = rightNum;
	left.normalize(left);
	right.normalize(right);
	double numLeft = static_cast <double> (left.numerator)/left.denominator;
	double numRight = static_cast <double> (right.numerator)/right.denominator;
	return (numLeft < numRight);
}

//format: x/y
ostream& operator<<(ostream &out, const Rational &num){

	int numerator=num.getNumer();
	int denominator=num.getDenom();

	if((denominator<0&&numerator>0)||(denominator<0&&numerator<0)){
		numerator*=(-1);
		denominator*=(-1);
	}

	out<<numerator<<"/"<<denominator;

	return out;

}

istream& operator>>(istream &in, Rational &num){
	int numer;
	int denom;
	char divided ;
	in>>numer;
	in>> divided;
	if(divided!='/'){
		cout<<"Wrong form of rational number!"<<endl;
		exit(1);
	}	
	in>>denom;
	if(denom==0){
		cout<<"Cannot devided by 0!"<<endl;
		exit(1);
	}
	num.setNumer(numer);
	num.setDenom(denom);

	return in;
}
int Rational::gcd (int x, int y){
	int z=x-(y*(x/y));;
   	while(z!=0){
        x=y;
        y=z;
        z=x-(y*(x/y));
    }
    return y;
}




