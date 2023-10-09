int _exit = 0;
int fibo(int);
int main(){
	int x = fibo(8);
	int y = 0;
	while(!_exit);
	return 0;
}

int fibo(int n){
	if (n==0){return 0;}
	else if (n==1){return 1;}
	else {return (fibo(n-1)+fibo(n-2));}
}
