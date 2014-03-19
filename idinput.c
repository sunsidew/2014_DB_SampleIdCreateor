#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define M 1000000 // 작업 횟수 설정 (1000000)
#define len 10 // 문자열 길이값
#define R_MAX 100 // 랜덤 증가 인자 범위 설정
#define POS 35 // 진수(자리수) 설정

void setStart(int data[]);
void sum36Func(int data[], int plusNum);
void idPrint(int data[], FILE *);

int main(void)
{
	int i, increment;
	int idData[len];
	
	srand(time(NULL)); // 랜덤 세팅
	setStart(idData);

	FILE *fp = fopen("output.csv","w");
	
	for(i = 1 ; i <= M ; i++)
	{
		increment = rand()%R_MAX+1; // 다음 순서 ID 생성을 위한 랜덤 증가값 설정
		
		sum36Func(idData, increment);
		idPrint(idData, fp);
	}
	
	fclose(fp);

	return 0;
}

void setStart(int data[])
{
	int i;
	for(i = 0 ; i < len ; i++) // 아이디 초기값 랜덤 인자로 설정
	{
		data[i] = rand()%POS;
	}
}

void sum36Func(int data[], int plusNum)
{
	int i;
	for(i = len-1 ; i >= 0 ; i--) // 36진수(0-9 + a-z) 덧셈 직접 구현
	{
		data[i] += plusNum%POS;
		if(data[i] >= POS)
		{				
			data[i-1] += data[i]/POS;
			data[i] %= POS;
		}
		plusNum /= POS;
	}
}

void idPrint(int data[], FILE *fp)
{
	int i;
	for(i = 0 ; i < len ; i++)
	{
		if(data[i] >= 10) // 'a-z' == 10~35
		{
			fprintf(fp,"%c",'a'+data[i]-10);
		}
		else fprintf(fp,"%d",data[i]);

		fprintf(fp,"[%d] ",data[i]);
	}
	fprintf(fp,"\n");
}