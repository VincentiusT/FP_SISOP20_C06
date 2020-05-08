#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int kabisat(int x){
	int kab = 0;
	if(x%400==0) kab = 1;
	else if(x%100==0) kab = 0;
	else if(x%4==0) kab = 1;
	else kab = 0;
	return(kab);
}

void dayName(int d, int m, int y){
  int t[] ={0,3,2,5,0,3,5,1,4,6,2,4};
  y-=m<3;
  int day = (y+y/4-y/100+y/400+t[m-1]+d)%7;
  if(day==0) printf(1,"Sun");
  else if(day==1) printf(1,"Mon");
  else if(day==2) printf(1,"Tue");
  else if(day==3) printf(1,"Wed");
  else if(day==4) printf(1,"Thu");
  else if(day==5) printf(1,"Fri");
  else if(day==6) printf(1,"Sat");
}

void monthName(int monthIndex){
  if(monthIndex==1) printf(1," Jan");
  else if(monthIndex==2) printf(1," Feb ");
  else if(monthIndex==3) printf(1," Mar ");
  else if(monthIndex==4) printf(1," Apr ");
  else if(monthIndex==5) printf(1," May ");
  else if(monthIndex==6) printf(1," June ");
  else if(monthIndex==7) printf(1," July ");
  else if(monthIndex==8) printf(1," Aug ");
  else if(monthIndex==9) printf(1," Sep ");
  else if(monthIndex==10) printf(1," Oct ");
  else if(monthIndex==11) printf(1," Nov ");
  else if(monthIndex==12) printf(1," Dec ");
}

void time(){
  struct rtcdate r;
  if(date(&r)){
    printf(2,"failed\n");
    exit();
  }
  int h = r.hour;
  int m = r.minute;
  int s = r.second;
  h+=7;
  if(h>24) h-=24;
  printf(1," %d:%d:%d",h,m,s);
}

void currentDate(){
  struct rtcdate r;
  if(date(&r)){
    printf(1,"failed\n");
    exit();
  }
  dayName(r.day,r.month,r.year);
  monthName(r.month);
  printf(1,"%d", r.day);
  time();;
  printf(1," WIB %d\n",r.year);
}

void printFormat(char c){
  struct rtcdate r;
  if(date(&r)){
    printf(2,"failed\n");
    exit();
  }
  switch(c){
    case 'd':printf(1,"%d",r.day); break;
    case 'm':printf(1,"%d",r.month); break;
    case 'y':printf(1,"%d",r.year); break;
    case 'a':dayName(r.day,r.month,r.year); break;
    case 'b':monthName(r.month); break;
    case 'D':printf(1,"%d/%d/%d",r.month,r.day,r.year); break;
    case 'T':time();break;
    case 'M':printf(1,"%d",r.minute); break;
    case 'H':printf(1,"%d",r.hour);break;
    case 'S':printf(1,"%d",r.second);break;
  }
}

//date +
void getDateByFormat(const char *format ,int length){
  for(int i=0;i<length;i++){
    if(format[i]=='%'){
      char charFormat = format[i+1];
      printFormat(charFormat);
      i++;
    }
    else if(format[i]=='"' || format[i]=='+'){
      continue;
    }
    else{
      printf(1,"%c",format[i]);
    }
  }
}

//date -s
void getDateByString(const char *format, int length){
	struct rtcdate r;
  	if(date(&r)){
    	printf(2,"failed\n");
    	exit();
  	}
	for(int i=0;i<length;i++){
		if(format[i]=='m' && format[i+1]=='o' && format[i+2]=='n' && format[i+3]=='t' && format[i+4]=='h' ){
			monthName(r.month);
			i+=4;
		}
		else if(format[i]=='d' && format[i+1]=='a' && format[i+2]=='y'){
			printf(1,"%d",r.day);
			i+=2;
		} 
		else if(format[i]=='y' && format[i+1]=='e' && format[i+2]=='a' && format[i+3]=='r'){
			printf(1,"%d",r.year);
			i+=3;
		}
		else if(format[i]=='H' && format[i+1]=='H'){
			int h = r.hour;
			if(h<10) printf(1,"0%d",r.hour);
			else printf(1,"%d",r.hour);
			i++;
		}
		else if(format[i]=='M' && format[i+1]=='M'){
			int m = r.minute;
			if(m<10) printf(1,"0%d",r.minute);
			else printf(1,"%d",r.minute);
			i++;
		}
		else if(format[i]=='S' && format[i+1]=='S'){
			int s = r.second;
			if(s<10) printf(1,"0%d",r.second);
			else printf(1,"%d",r.second);
			i++;
		}
		else if(format[i]=='"' || format[i]=='-' ||format[i]=='s'){
			continue;
		}
		else{
			printf(1,"%c",format[i]);
		}
	}
}

void yesterday(){
  struct rtcdate r;
	if (date(&r)) {
		printf(2, "date failed\n");
		exit();
	}

	// maret
	if(r.month == 3){
		if(kabisat(r.year)){
			if(r.day==1){
				r.month -= 1; r.day = 29;
			}
			else r.day -= 1;
		}
		else{
			if(r.day==1){
				r.month -= 1; r.day = 28;
			}
			else	r.day -= 1;
		}
	}

	//1 jan
	else if((r.day==1)&&(r.month==1)){
		r.month = 12;
		r.day = 31;
		r.year -= 1;
	}

	else{
		if(r.month<9){
			if(r.month%2==0){
				if(r.day==1){
					r.month -= 1; r.day = 31;
				}
				else	r.day -= 1;
			}
			else{
				if(r.day==1){
					r.month -= 1; r.day = 30;
				}
				else	r.day -= 1;
			}
		}
		else{
			if(r.month%2==1){
				if(r.day==1){
					r.month -= 1; r.day = 31;
				}
				else	r.day -= 1;
			}
			else{
				if(r.day==1){
					r.month -= 1; r.day = 30;
				}
				else	r.day -= 1;
			}
		}
	}
	dayName(r.year,r.month,r.day);  
	monthName(r.month); 
	printf(1," %d",r.day);  
	time();  
	printf(1," WIB");
	printf(1," %d\n",r.year);
}

void tomorrow(){
  struct rtcdate r;
	if (date(&r)) {
		printf(1, "failed\n");
		exit();
  }
	if(r.month == 2){ //bulan feb
		if(kabisat(r.year)){
			if(r.day == 29){
				r.month += 1; r.day = 1;
			}
			else r.day += 1;
		}
		else{
			if(r.day == 28){
				r.month += 1; r.day = 1;
			}
			else r.day += 1;
		}
	}
	else if((r.day==31)&&(r.month==12)){ //31st Dec
		r.month = 1; r.day = 1; r.year += 1;
	}
	else{
		if(r.month<8){
			if(r.month%2==1){
				if(r.day==31){
					r.month += 1; r.day = 1;
				}
				else r.day += 1;
			}
			else{
				if(r.day==30){
					r.month += 1; r.day = 1;
				}
				else r.day += 1;
			}
		}
		else{
			if(r.month%2==1){
				if(r.day==30){
					r.month += 1; r.day = 1;
				}
				else r.day += 1;
			}
			else{
				if(r.day==31){
					r.month += 1; r.day = 1;
				}
				else r.day += 1;
			}
		}
	}
	dayName(r.year,r.month,r.day); 
	monthName(r.month); 
	printf(1," %d",r.day);  
	time();  
	printf(1," WIB");
	printf(1," %d\n",r.year);  
}

//date -d
void getDate(const char * day){
  if(strcmp(day,"today")==0){
    currentDate();
  }
  else if(strcmp(day,"yesterday")==0){
    yesterday();
  }
  else if(strcmp(day,"tomorrow")==0){
    tomorrow();
  }
  else{
    currentDate();
  }
}

//date -r
void getModificationDate(const char *fileName, int length){
	
}

int main(int argc, char *argv[]){
  if(argc==1){
    currentDate();
    exit();
  }
  else if(argc >= 2){
    const char *temp = argv[1];
    if(temp[0]=='+'){
      for(int i=1;i<argc;i++){
        getDateByFormat(argv[i],strlen(argv[i]));
        printf(1," ");
      }
      printf(1,"\n");
      exit();
    }
	if(temp[0]=='-' && temp[1]=='s'){
	  for(int i=1;i<argc;i++){
    	getDateByString(argv[i],strlen(argv[i]));
    	printf(1," ");
      }
      printf(1,"\n");
      exit();
	}
	if(temp[0]=='-' && temp[1]=='r'){
	  getModificationDate(argv[2],strlen(argv[2]));
	  printf(1,"\n");
	  exit();
	}
    if(temp[0]=='-' && temp[1]=='d'){
      getDate(argv[2]);
	  exit();
    }
  }
  exit();
}

