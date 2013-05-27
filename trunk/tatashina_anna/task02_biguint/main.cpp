#include "TBigUInt.h"#include <iostream>#include <vector>TBigUInt::TBigUInt () {	   //figure.push_back(0);	   negative = false;}TBigUInt::TBigUInt (int value) {  if (value < 0) { 	  negative = true;	  value = -value;  } else negative = false;  if (value == 0) figure.push_back(0);  for (int i = 0; value > 0; i++) {	  figure.push_back(value % BASE);	  value /= BASE;  }}	void TBigUInt::reverse () {   unsigned char t;   for (unsigned i = 0; i < figure.size() / 2; i++) {	  t = figure[i];	  figure[i] = figure[figure.size()-i-1];	  figure[figure.size()-i-1] = t;   }      }TBigUInt TBigUInt::operator - () const {  TBigUInt opposite;  if (figure.size() > 1 || figure[0])	opposite.negative = !negative;  opposite.figure = figure;  return opposite; }TBigUInt TBigUInt::abs(const TBigUInt& value) const {	TBigUInt newvalue = value;	newvalue.negative = false;	return newvalue;}bool TBigUInt::operator == (const TBigUInt& operand) const {  return (negative == operand.negative && figure == operand.figure);}bool TBigUInt::operator < (const TBigUInt& operand) const {	if (negative > operand.negative) return true;	else if (negative < operand.negative) return false;	else {		if (figure.size() < operand.figure.size()) return !negative;		else if (figure.size() > operand.figure.size()) return negative;		else {			int i;			for (i = figure.size() - 1; i > 0 && figure[i] == operand.figure[i]; i--);			if (figure[i] < operand.figure[i]) return !negative;			else if (figure[i] > operand.figure[i]) return negative;			else return false;		}	}}bool TBigUInt::operator <= (const TBigUInt& operand) const {	return (*this == operand || *this < operand);}bool TBigUInt::operator > (const TBigUInt& operand) const {	return !(*this <= operand);}bool TBigUInt::operator >= (const TBigUInt& operand) const {	return !(*this < operand);}  bool TBigUInt::operator != (const TBigUInt& operand) const {	return !(*this == operand);}TBigUInt TBigUInt::operator + (const TBigUInt& summand) const {  if (negative == summand.negative) {	TBigUInt summ;	summ.negative = negative;	summ.figure.push_back(figure[0] + summand.figure[0]);	unsigned i = 0;	while (i < figure.size() - 1 || i < summand.figure.size() - 1 || summ.figure[i] > BASE - 1 ) {	   summ.figure.push_back((summ.figure[i] - summ.figure[i] % BASE) / BASE);	   summ.figure[i] %= BASE;	   i++;	   if (i < figure.size()) summ.figure[i] += figure[i];	   if (i < summand.figure.size()) summ.figure[i] += summand.figure[i];      	}     	return summ;       } else {	TBigUInt difference;	const TBigUInt* subtrahend;	if (abs(*this) < abs(summand)) {		difference = summand;		subtrahend = this;	} else {		difference = *this;		subtrahend = &summand;	}	for (unsigned i = 0; i < (*subtrahend).figure.size(); i++) {		if (difference.figure[i] < (*subtrahend).figure[i]) {			difference.figure[i] += BASE;			unsigned j;			for (j = i + 1; difference.figure[j] == 0; j++)				difference.figure[j] = BASE - 1;			difference.figure[j] -= 1;		}		difference.figure[i] -= (*subtrahend).figure[i];	}	for (unsigned i = difference.figure.size() - 1; i > 0 && difference.figure[i] == 0; i--)		difference.figure.resize(i);	if (difference == 0) difference.negative = false;   	return difference;  }}TBigUInt& TBigUInt::operator += (const TBigUInt& summand) {  *this = *this + summand;  return *this;}TBigUInt TBigUInt::operator - (const TBigUInt& subtrahend) const {  TBigUInt difference = (*this) + (-subtrahend);  return difference;     }TBigUInt& TBigUInt::operator -= (const TBigUInt& subtrahend) {  *this = *this - subtrahend;  return *this;}TBigUInt& TBigUInt::operator ++ () {	return *this += 1;}TBigUInt TBigUInt::operator ++ (int) {	TBigUInt number = *this;	*this += 1;	return number;}TBigUInt& TBigUInt::operator -- () {	return *this -= 1;}TBigUInt TBigUInt::operator -- (int) {	TBigUInt number = *this;	*this -= 1;	return number;}TBigUInt TBigUInt::operator * (const TBigUInt& multiplier) const {	TBigUInt product;	product.figure.resize((*this).figure.size() + multiplier.figure.size());	for (unsigned i = 0; i < multiplier.figure.size(); i++) {		for (unsigned j = 0; j < (*this).figure.size(); j++) {			product.figure[i + j] += (*this).figure[j] * multiplier.figure[i];			product.figure[i + j + 1] += product.figure[i + j] / BASE;			product.figure[i + j] %= BASE;		}	}	unsigned i;	for (i = product.figure.size() - 1; i > 0 && product.figure[i] == 0; i--);	product.figure.resize(i + 1);	product.negative = i || product.figure[0] ? (*this).negative != multiplier.negative : false;	return product;}TBigUInt& TBigUInt::operator *= (const TBigUInt& multiplier) {  *this = *this * multiplier;  return *this;}void TBigUInt::DeleteLeadingZeros() {	unsigned int i;	for (i = 0; i < (*this).figure.size() && (*this).figure[i] == 0; i++);	if (i == (*this).figure.size())		*this = 0;	else {		TBigUInt temp;		for (; i < (*this).figure.size(); i++)			temp.figure.push_back((*this).figure[i]);		(*this).figure.resize(temp.figure.size()); //�� ������, ����� �� ��� �������		*this = temp;	}}            bool TBigUInt::LessThan(const TBigUInt& rev_number) {  	TBigUInt number = *this;	number.DeleteLeadingZeros();	TBigUInt operand = rev_number;	operand.DeleteLeadingZeros();	unsigned len = operand.figure.size();	if (number.figure.size() < len) return true;	unsigned int ind = 0;	if (number.figure.size() == len) {		while (ind < len && number.figure[ind] == operand.figure[ind]) ++ind;		if (ind < len && number.figure[ind] < operand.figure[ind]) return true;	}	return false;}void TBigUInt::add(const TBigUInt& summand) {	unsigned len1 = (*this).figure.size();	unsigned len2 = summand.figure.size();	unsigned len = (len1 > len2 ? len1 : len2) +1;	TBigUInt summ;	summ.figure.resize(len);	for (unsigned i = 1; i <= len; i++) {		if (i <= len1) summ.figure[len-i] += (*this).figure[len1-i];		if (i<=len2) summ.figure[len-i] += summand.figure[len2-i];		if (summ.figure[len-i] >= BASE) {			summ.figure[len-i-1] += 1;			summ.figure[len-i] %= BASE;		}	}	summ.DeleteLeadingZeros();	(*this).figure.resize(summ.figure.size()); 	*this = summ;				}TBigUInt TBigUInt::operator / (const TBigUInt& divisor) const {	//if (divisor == 0) throw	if (*this == 0) return 0;		TBigUInt number = *this;	for (int i = number.figure.size() - 1; i > 0 && number.figure[i] == 0; i--) number.figure.pop_back();	number.reverse();	TBigUInt rest = number;	TBigUInt divider = divisor;	for (int i = divider.figure.size() - 1; i > 0 && divider.figure[i] == 0; i--) divider.figure.pop_back();	divider.reverse();		TBigUInt quotient;	unsigned ind = 0;	TBigUInt minuend;	while (ind < number.figure.size()) {		//������ ��������� �����		minuend.figure.push_back(number.figure[ind++]);		//������, �� ��� ���� ��������� ��������, � ���������� ����������		unsigned short multiplier;		TBigUInt subtrahend = 0;		for (multiplier = 0; ; multiplier++) {			TBigUInt temp = subtrahend;			temp.add(divider);			if (minuend.LessThan(temp)) break;			else subtrahend = temp;		}		//��������� ��������� ����� ��������		quotient.figure.push_back(multiplier);		//������� � ���������� ������� �����, ����� ��� ���� ������ �� ����� �������		for (unsigned int i = subtrahend.figure.size(); i < rest.figure.size(); i++)			subtrahend.figure.push_back(0);		//�� ��� ���� ���������, ����� �� ����� ��� ��������� �� ������ ���		if (rest.LessThan(subtrahend)) {			for (int i = subtrahend.figure.size() - 1; i > 0; i--)				subtrahend.figure[i] = subtrahend.figure[i-1];			subtrahend.figure[0] = 0;			}		//�������� ������� �� �������� �����������		for (int i = rest.figure.size() - 1; i >= 0; i--) {			if (rest.figure[i] < subtrahend.figure[i]) {				rest.figure[i] += BASE;				int j;				for (j = i-1; rest.figure[j] == 0; j--)					rest.figure[j] = BASE-1;				rest.figure[j] -= 1;			}			rest.figure[i] -= subtrahend.figure[i];		}		//��� ����� ������������ ������� ���������������� ������� �������		for (unsigned int i = 0; i < minuend.figure.size(); i++)			minuend.figure[i] = rest.figure[i];		//������ ���������� ���� �� �������		rest.DeleteLeadingZeros();		//� �� ������������		minuend.DeleteLeadingZeros();				//����� ��	}		quotient.DeleteLeadingZeros();	quotient.reverse();		if ((*this).negative != divisor.negative) {		quotient.negative = true;		if (rest != 0) quotient -= 1;	}		return quotient;	  }TBigUInt& TBigUInt::operator /= (const TBigUInt& divisor) {	*this = *this / divisor;	return *this;}TBigUInt TBigUInt::operator % (const TBigUInt& divisor) const {	return *this - (*this / divisor) * divisor;}TBigUInt& TBigUInt::operator %= (const TBigUInt& divisor) {	*this = *this % divisor;	return *this;}	  ostream& operator << (ostream& out,const TBigUInt& number) {     if (number.negative && number != 0)        out << '-';     for (int i = number.figure.size()-1; i >= 0; i--)         out << (char)(number.figure[i] + '0');     return out;    }         istream& operator >> (istream& in, TBigUInt& number) {     number.negative = false;     number.figure.resize(0);     char c;     in.get(c);     while (isspace(c)) in.get(c);     if (c == '-') {         number.negative = true;         in.get(c);     } else number.negative = false;     while (c >= '0' && c <= '9' && in.good() ) {         if (!number.figure.empty() || c != '0')             number.figure.push_back(c - '0');         in.get(c);          }     if (!number.figure.empty())         number.reverse();     else {         number.figure.push_back(0);         number.negative = false;     }     return in;}     TBigUInt operator * (int value, TBigUInt& number) {    TBigUInt factor = value;    return factor*number;}TBigUInt operator * (TBigUInt& number, int value) {    return value*number;}TBigUInt fact(unsigned const n) {    TBigUInt product;    product = 1;    for (unsigned i=1; i<=n; i++)        product = product*i;    return product;     }TBigUInt power(unsigned const number, unsigned const degree) {    TBigUInt product;    product = 1;    for (unsigned i=1; i<=degree; i++)        product = product*number;    return product;}   TBigUInt KaratsubaMultiply(const TBigUInt& a, const TBigUInt& b){        size_t maxDigits = max(a.figure.size(), b.figure.size());        if (maxDigits <= 50)                 return a*b;        size_t n = maxDigits / 2;        TBigUInt a1(a, 0, n);        TBigUInt a2(a, n, maxDigits);         TBigUInt b1(b, 0, n);        TBigUInt b2(b, n, maxDigits);        TBigUInt z2 = KaratsubaMultiply(a2, b2);        TBigUInt z0 = KaratsubaMultiply(a1, b1);        TBigUInt z1 = KaratsubaMultiply(a1 + a2, b1 + b2) - z2 - z0;        z2.figure.insert(z2.figure.begin(), 2 * n, 0);        z1.figure.insert(z1.figure.begin(), n, 0);        return z2 + z1 + z0;}int main() {    TBigUInt number1,number2;    ifstream input("input.txt");    ofstream output("output.txt");        input >> number1>>number2;    output<<number1*number2;        input >> number1>>number2;    output<<KaratsubaMultiply(number1, number2);    return 0;}