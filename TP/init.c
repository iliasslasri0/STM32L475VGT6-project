extern int _bstart, _bend;

void init_bss(){
	for(int *i=&_bstart; i<&_bend; i++){
		*i=0;
	}
}
