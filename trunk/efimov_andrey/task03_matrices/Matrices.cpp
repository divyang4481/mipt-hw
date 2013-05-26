#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
using namespace std;

void ERRORLY (char index){
	switch (index){
	case '+':
		cout << "Addition ";
		break;
	case '-':
		cout << "Subtraction ";
		break;
	case '*':
		cout << "Multiplication ";
		break;
	default:
		cout << "Something ";
	}
	cout << "went wrong. Check matrix sizes." << endl;
}

size_t poweroftwo (size_t e){
	size_t i = 1;
	for (size_t j=0; j<e; ++j){
		i*=2;
	}
	return i;
}

long long GetClock() {
	return clock() * 1000 / CLOCKS_PER_SEC;
}

template<typename T>
class TMatrix{
private:
	vector<vector<T>> val;
	friend TMatrix<T> StrassenMultiply();
public:
	TMatrix(){
	}
	TMatrix(const TMatrix &other){
		*this=other;
	}
	TMatrix(size_t rowCount, size_t colCount){
		vector<T> vec(colCount);
		for (unsigned int j=0; j<rowCount; ++j)
			val.push_back(vec);
	}
	size_t get_cols() const{
		return val[0].size();
	}
	size_t get_rows() const{
		return val.size();
	}
	TMatrix& operator= (const TMatrix &other){
		val=other.val;
		return *this;
	}
	TMatrix<T> operator+(const TMatrix& other){
		if (other.get_cols()!=get_cols() || other.get_rows()!=get_rows()){
			ERRORLY('+');
			return *this;
		}
		TMatrix<T> result(get_rows(), get_cols());
		for (size_t i=0; i<get_rows(); ++i)
			for (size_t j=0; j<get_cols(); ++j)
				result.val[i][j]=val[i][j]+other.val[i][j];
		return result;
	}
	TMatrix<T> operator-(const TMatrix& other){
		if (other.get_cols()!=get_cols() || other.get_rows()!=get_rows()){
			ERRORLY('-');
			return *this;
		}
		TMatrix result(get_rows(), get_cols());
		for (size_t i=0; i<get_rows(); ++i)
			for (size_t j=0; j<get_cols(); ++j)
				result.val[i][j]=val[i][j]-other.val[i][j];
		return result;
	}
	TMatrix<T> operator*(T mult) {
		TMatrix temp(*this);
		for (unsigned int i=0; i<get_rows(); ++i)
			for (unsigned int j=0; j<get_cols(); ++j)
				temp.val[i][j]*=mult;
		return temp;
	}
	TMatrix<T> operator*(const TMatrix& other){
		if (val[0].size()!=other.val.size()){
			ERRORLY('*');
			return *this;
		}
		TMatrix<T> result(val.size(), other.val[0].size());
		for (unsigned int i=0; i<val.size(); ++i)
			for (unsigned int j=0; j<other.val[0].size(); ++j)
				for (unsigned int k=0; k<val[0].size(); ++k)
					result.val[i][j]+=(val[i][k]*other.val[k][j]);
		return result;
	}
	TMatrix<T> operator+=(const TMatrix& other){
		*this=*this+other;
		return *this;
	}
	TMatrix<T> operator-=(const TMatrix& other){
		*this=*this-other;
		return *this;
	}
	TMatrix<T> operator*=(const TMatrix& other){
		*this=*this*other;
		return *this;
	}
	TMatrix<T> operator*=(T mult){
		*this=*this*mult;
		return *this;
	}
	bool  operator== (TMatrix<T> other){
		if (get_cols()!=other.get_cols() || get_rows()!=other.get_rows())
			return false;
		for (unsigned int i = 0; i < other.get_rows(); ++i)

			for (unsigned int j = 0; j < other.get_cols(); ++j)
				if (val[i][j] != other.val[i][j] )
					return false;
		return true;
	}
	TMatrix<T> Resize(size_t rowCount, size_t colCount){
		if(rowCount>get_rows()){
			vector<T> temp(colCount,0);
			for(unsigned int i=get_rows(); i<rowCount; i++)
				val.push_back(temp);
		}
		else if (rowCount<get_rows()){
			val.resize(rowCount);
		}
		if(colCount!=get_cols()){
			for(unsigned int i=0; i<get_rows(); ++i)
				val[i].resize(colCount);
		}
		return *this;
	}
	TMatrix<T> Resize(size_t size){
		this->Resize(size, size);
		return *this;
	}
	const T& At(size_t row, size_t col) const{
		return val[row][col];
	}
	T& At(size_t row, size_t col){
		return val[row][col];
	}
	TMatrix<T> Transpose(){
		T temp;
		for (unsigned int i=0; i<get_rows(); ++i)
			for (unsigned int j=0; j<i; ++j){
					temp=val[i][j];
					val[i][j]=val[j][i];
					val[j][i]=temp;
				}

		return *this;
	}
	TMatrix<T> quarter(int v, int h){
		size_t size=val.size()/2;
		TMatrix<T> result(size, size);
		size_t ver=v*size;
		size_t hor=h*size;
		for (size_t i=0; i<size; ++i)
				for (size_t j=0; j<size; ++j)
					result.At(i, j)=val[i+ver][j+hor];
		return result;
	}
};

//For equal-sized, square matrices
/*template<typename T>
TMatrix<T> StrassenMultiply(TMatrix<T>& a, TMatrix<T>& b){
	if(a.get_rows()<=128){
		return a*b;
	}
	TMatrix<T> result (a.get_cols(), a.get_rows());
	int n=a.get_cols()/2;
	TMatrix<T> temp1(n,n);
	TMatrix<T> temp2(n,n);
	// Matrix M1
		//A11+A22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j)+a.At(n+i, n+j);
		//B11+B22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j)+b.At(n+i, n+j);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			result.At (i, j) = result.At (i+n, j+n) = temp1.At(i, j);

	//M2
		//A21+A22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(i,j)=a.At(n+i,j)+a.At(n+i, n+j);
		//B11
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			result.At (i+n, j+n) -= (result.At (i+n, j) = temp1.At(i, j));
	//M3
		//A11
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j);
		//B12-B22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j+n)-b.At(n+i, n+j);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			result.At (i+n, j+n) += (result.At (i, j+n) = temp1.At(i, j));

	//M4
		//A22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(n+i,n+j)=a.At(n+i,n+j);
		//B21-B11
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i+n,j)-b.At(i, j);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j){
			result.At (i, j) += temp1.At(i, j);
			result.At (i+n, j) += temp1.At(i, j);
		}

	//M5
		//A11+A12
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j)+a.At(i, j+n);
		//B22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(n+i,n+j)=b.At(n+i,n+j);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j){
			result.At (i, j) -= temp1.At(i, j);
			result.At (i, j+n) += temp1.At(i, j);
		}

	//M6
		//A21-A11
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i+n,j)-a.At(i, j);
		//B11+B12
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j)+b.At(i, j+n);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j){
			result.At (i+n, j+n) += temp1.At(i, j);
		}
	
	//M7
		//A12-A22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j+n)-a.At(i+n, j+n);
		//B21+B22
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i+n,j)+b.At(i+n, j+n);
	temp1 = StrassenMultiply(temp1, temp2);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j){
			result.At (i, j) += temp1.At(i, j);
		}
	return result;
}*/

// for square matrixes (power of 2)
template<typename T>
TMatrix<T> StrassenMultiply_for_2(TMatrix<T>& a, TMatrix<T>& b){
	if(a.get_rows() <= 128){
		return a*b;
	}
	TMatrix <T> result (a.get_cols(), a.get_rows());
	size_t n=a.get_cols()/2;
	TMatrix <T> temp1 (n,n);
	TMatrix <T> temp2 (n,n);
	size_t i, j;
	// Matrix M1
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j)+a.At(n+i, n+j);
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j)+b.At(n+i, n+j);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
			result.At (i, j) = result.At (i+n, j+n) = temp1.At(i, j);

	//M2
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(n+i,j)+a.At(n+i, n+j);
		for (i=0; i<n; ++i)
				for (j=0; j<n; ++j)
					temp2.At(i,j)=b.At(i,j);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
			result.At (i+n, j+n) -= (result.At (i+n, j) = temp1.At(i, j));
	//M3
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j);
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j+n)-b.At(n+i, n+j);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
			result.At (i+n, j+n) += (result.At (i, j+n) = temp1.At(i, j));

	//M4
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i+n, j+n);
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i+n,j)-b.At(i, j);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j){
			result.At (i, j) += temp1.At(i, j);
			result.At (i+n, j) += temp1.At(i, j);
		}

	//M5
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j)+a.At(i, j+n);
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i+n,j+n);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j){
			result.At (i, j) -= temp1.At(i, j);
			result.At (i, j+n) += temp1.At(i, j);
		}

	//M6
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i+n,j)-a.At(i, j);
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i,j)+b.At(i, j+n);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j){
			result.At (i+n, j+n) += temp1.At(i, j);
		}
	
	//M7
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp1.At(i,j)=a.At(i,j+n)-a.At(i+n, j+n);
		for (i=0; i<n; ++i)
			for (j=0; j<n; ++j)
				temp2.At(i,j)=b.At(i+n,j)+b.At(i+n, j+n);
	temp1 = StrassenMultiply_for_2(temp1, temp2);
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j){
			result.At (i, j) += temp1.At(i, j);
		}
	return result;
}

template<typename T>
ostream& operator<< (ostream& out, const TMatrix<T>& matrix){
	size_t col=matrix.get_cols();
	size_t row=matrix.get_rows();
	out << endl << endl;
	for (size_t i=0; i<row; ++i){
		for (size_t j=0; j<col; ++j)
			out << matrix.At(i,j) << '\t';
		out << endl;
	}
	return out;
}

template<typename T>
istream& operator>> (istream& in, TMatrix<T>& matrix){
	int row, col;
	in >> row >> col;
	T tp;
	TMatrix<T> result (row, col);
	for(int i=0; i<row; ++i){
		for(int j=0; j<col; ++j){
			in >> tp;
			result.At(i,j)=tp;
		}
	}
	matrix=result;
	return in;
}

void commontests(){
	size_t size = 3;
	TMatrix <int> test1(size, size);
	for (size_t i=0; i<size; ++i)
		for (size_t j=0; j<size; ++j)
			test1.At(i,j) = rand()%10;
	cout << "Matrix A:" << endl << test1 ;
	TMatrix <int> test2 (size, size);
	for (size_t i=0; i<size; ++i)
		for (size_t j=0; j<size; ++j)
			test2.At(i,j) = rand()%10;
	cout << "Matrix B:" << endl << test2 ;
	cout << "A+B" << endl << test1+test2;
	cout << "A-B" << endl << test1-test2;
	cout << "A*B with the common method" << endl << test1*test2;
	int number  = 5;
	cout << "A*n, n=" << number << endl << (test1 *= number);
	TMatrix <int> test3;
	test3=test1;
	cout << "Checking operator =, must be same" << endl << test1 << endl << test3;
}

TMatrix<int> FillRandom(size_t n){
	TMatrix<int> res(n,n);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			res.At(i,j)=rand()%100;
	return res;
}

void strassentest(){
	size_t i=4;
	long long ck, ck2;
	TMatrix<int> src1;
	TMatrix<int> src2;
	TMatrix<int> res1;
	TMatrix<int> res2;
	for (i; i<12; ++i){
		src1=FillRandom(poweroftwo(i));
		src2=FillRandom(poweroftwo(i));
		cout << "Matrix size of " << poweroftwo(i) << endl;
		ck=GetClock();
		res1=src1*src2;
		ck2=GetClock()-ck;
		cout << "Common method time spent: " << ck2 << endl;
		ck=GetClock();
		res2=StrassenMultiply_for_2(src1,src2);
		ck2=GetClock()-ck;
		cout << "Strassen method time spent: " << ck2 << endl;
		if (res1==res2) cout << "K." << endl;
		else{
			cout << "Failures" << endl;
			break;
		}
	}
	system("pause");
}

int main(){
	//commontests();
	strassentest();
	
	return 0;
}