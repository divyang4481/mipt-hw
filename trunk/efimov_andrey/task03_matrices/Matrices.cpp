#include <iostream>
#include <vector>

using namespace std;

class A{
	int val;
public:
	static int Created;
	static int Deleted;
	A(){
		++Created;
		val=0;
	}
	A(int v){
		++Created;
		val=v;
	}
	A(A& other){
		++Created;
		val=other.val;
	}
	~A(){
		++Deleted;
	}
};
void InputError(char i){
	switch (i){
	case '+':
		cout << "Addition";
		break;
	case '-':
		cout << "Subtraction";
		break;
	case '*':
		cout << "Multiplication";
		break;
	default:
		cout << "This method";
	}
	cout << " doesn't work on your input." << endl;
}

int A::Created=0;
int A::Deleted=0;

template <typename T>
class TMatrix{
private:
	int rows;
	int cols;
	vector<vector<T>> arry;
	void ArrayBuild(){
		arry.resize(rows);
		for (int i=0; i<rows; ++i){
			arry[i].resize(cols);
		}
	}
public:
	TMatrix(size_t rowCount, size_t colCount){
		cols=colCount;
		rows=rowCount;
		ArrayBuild();
		for (int i=0; i<rows; ++i)
			for (int j=0; j<cols; ++j)
				arry[i][j]=0;
	}
	TMatrix(){
		rows=1;
		cols=1;
		ArrayBuild();
	}
	TMatrix(const TMatrix &source){
		cols=source.cols;
		rows=source.rows;
		ArrayBuild();
		for (int i=0; i<rows; ++i)
			for (int j=0; j<cols; ++j)
				arry[i][j]=source.arry[i][j];
	}
	void Resize(size_t rowCount, size_t colCount){
		rows=rowCount;
		cols=colCount;
		ArrayBuild();
	}
	bool operator= (TMatrix &source){
		Resize(source.rows, source.cols);
		for (int i=0; i<rows; ++i)
			for (int j=0; j<cols; ++j)
				arry[i][j]=source.arry[i][j];
		return 1;
	}
	TMatrix operator+ (TMatrix &other){
		TMatrix result(rows, cols);
		if ((rows!=other.rows)||(cols!=other.cols)){
			InputError('+');
			return result;
		}
		for (int i=0; i<rows; ++i)
				for (int j=0; j<cols; ++j)
					result.arry[i][j]=arry[i][j]+other.arry[i][j];
		return result;
	}
	TMatrix operator- (TMatrix &other){
		TMatrix result(rows, cols);
		if ((rows!=other.rows)||(cols!=other.cols)){
			InputError('-');
			return result;
		}
		for (int i=0; i<rows; ++i)
				for (int j=0; j<cols; ++j)
					result.arry[i][j]=arry[i][j]-other.arry[i][j];
		return result;
	}
	TMatrix operator* (TMatrix &other){
		TMatrix result(rows, other.cols);
		if (cols!=other.rows){
			InputError('*');
			return result;
		}
		for (int i=0; i<rows; ++i){
			for (int j=0; j<other.cols; ++j){
				result.arry[i][j]=0;
				for (int k=0; k<cols; ++k){
					result.arry[i][j]+=(arry[i][k])*(other.arry[k][j]);
				}
			}
		}
		return result;
	}
	TMatrix operator* (T mult){
		TMatrix result(rows, cols);
		for (int i=0; i<rows; ++i){
			for (int j=0; j<cols; ++j){
				result.arry[i][j]=arry[i][j]*mult;
			}
		}
		return result;
	}
	TMatrix operator+= (TMatrix &other){
		*this=*this+other;
		return *this;
	}
	TMatrix operator-= (TMatrix &other){
		*this=*this-other;
		return *this;
	}
	TMatrix operator*= (TMatrix &other){
		*this=*this*other;
		return *this;
	}
	TMatrix Transpose() {
		TMatrix result(cols, rows);
		for (int i=0; i<rows; ++i)
				for (int j=0; j<cols; ++j)
					result.arry[j][i]=arry[i][j];
		return result;
	}
	T& At(size_t row, size_t col){
		return arry[row][col];
	}
	T At(size_t row, size_t col) const{
		return arry[row][col];
	}
	int Cols() const{
		return cols;
	}
	int Rows() const{
		return rows;
	}
};

template <typename T>
ostream& operator<< (ostream &out, const TMatrix<T> &source){
	for (int i=0; i<source.Rows(); i++){
		for (int j=0; j<source.Cols(); j++) 
			out << source.At(i,j) << " ";
		out << endl;
	}
    return out;
};
template <typename T>
istream& operator>> (istream &in, TMatrix<T> &dest){
	int r, c;
	in >> r >> c;
	dest.Resize(r, c);
	for (int i=0; i<r; i++){
		for (int j=0; j<c; j++) 
			in >> dest.At(i,j);
	}
    return in;
};
void NumberMultTest(int size, int maxmult){
	TMatrix<int> a(size, size);
	for (int i=0; i<size; ++i)
		for (int j=0; j<size; ++j)
			a.At(i,j)=i+j;
	for (int i=1; i<=maxmult; ++i)
		cout << a*i << endl;
	//supposed to return addition tables for 1 to size, multiplied by 1 to maxmult
}
void MultiplicationTest(int max){
	TMatrix<int> a(max,1);
	TMatrix<int> b;
	for (int i=0; i<max; ++i)
		a.At(i,0)=i+1;
	b=a.Transpose();
	TMatrix<int> res;
	res=a*b;
	cout << res;
	//supposed to result in a multiplication table 1 to max (5 in example)
	//also test for transposition
}
void MultiplicationFailTest(){
	TMatrix<int> a(3,3);
	TMatrix<int> b(4,4);
	a*=b;
	//supposed to result in an error message
}
void AdditionTest(int max){
	TMatrix<int> a(1, max);
	TMatrix<int> b(1, max);
	for (int i=0; i<max; ++i){
		a.At(0,i)=i+max;
		b.At(0,i)=max-i;
	}
	cout << a;
	cout << b;
	cout << a+b;
	cout << a-b;
	a-=b;
	cout << a-b;
	/*supposed to result in following progressions:
		max to 2max-1; (example: 8~15)
		max to 1; (8~1)
		all 2*max; (16)
		0 to max-2 with step=2; (0~14)
		-max to 2*max-3 with step=3. (-8~13)
	*/
}
void InOutTest(){
	TMatrix<int> a;
	cin >> a;
	cout << endl;
	cout << a;
	//supposed to give out an identical matrix
}
void MemoryLeakTestFunction(){
	TMatrix<A> q(8,8);
	q.Resize(6,3);
	TMatrix<A> r(5,2);
	q=r;
}
void MemoryLeakTest(){
	MemoryLeakTestFunction();
	cout << A::Created-A::Deleted;
	//supposed to return 0
}


int main(){
	//NumberMultTest(3, 5);
	//MultiplicationTest(5);
	//AdditionTest(8);
	MemoryLeakTest();
	system("pause");
}