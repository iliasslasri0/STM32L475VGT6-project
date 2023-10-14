extern int _bstart, _bend;

int *i = &_bstart;

void init_bss(){
	for(; i<&_bend; i++){
		*i=0;
	}
}
