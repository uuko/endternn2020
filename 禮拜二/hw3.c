void fun1();
void fun2();

void main(){

	fun1();
	fun2();
	
	

}
void fun2(){
	unsigned int i;
	unsigned int num=0;
	for(i=0;i<100;i++){
		if(i%2==1){
			if( (i==39)||(i==59)||(i==79)){
			
			}
			else{ 
				num+=i;
			}
		}
	}
}

void fun1(){
	unsigned int j;
	unsigned int TableConv[10]={0};
	unsigned int Table[10]={34,65,12,34,67,89,7,6,83,89};
	
	for(j=0;j<10;j++){
		if(Table[j]<20){
		  Table[j]=0;
			TableConv[j]=Table[j];
		}
		if(20<=Table[j]<40){
			TableConv[j]=Table[j];
		}
		if(40<=Table[j]){
			TableConv[j]=Table[j]%40;
		}
}	}