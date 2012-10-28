#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
// Вычислим коэффиценты, использую треугольник Паскаля. Соответственно, сначала строим сам треугольник, а потом выводим интересующую нам строку.
// Также можно было воспользоваться рекурсивным методом, но он, наверное, был бы дольше.
int main(){
	int n=0;
	cin >> n;
	int* *ptr;
	ptr=(int**)malloc((n+1)*sizeof(int));
	for (int i=0;i<=n;++i)
		ptr[i]=(int*)malloc((i+1)*sizeof(int));
	ptr[0][0]=ptr[1][0]=ptr[1][1]=1;
	for(int i=2;i<=n;++i){
		ptr[i][0]=ptr[i][i]=1;
		for(int j=1;j<i;++j)
			ptr[i][j]=ptr[i-1][j-1]+ptr[i-1][j];
	}
	for( int i=0;i<=n;++i)
		printf("%d\n", ptr[n][i]);
	return 0;
}
	
