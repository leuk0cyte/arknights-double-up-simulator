// written by leuk0cyte, 2020
// ������ּ��ģ���ȡ���շ���˫up��
// ����ļ��е�ÿһ�����ִ���һ����ͬ������ڼ��뱾��up���������ǵĹ�����
//  �ó����ܼƳ�ȡ�Ĵ���
// �������㹻��һ�ڴ���һ����β��Խ����������֮���ڣ���Ƶ�������ڸ���
// ���ݴ�����ʹ��matlab
// ���к�Ŀ¼�л�����һ��logfile����һ���ǳ�ȡ����
//  �ڶ����Ǹó�ȡ���µ������Ŀ�����������ۼƷֲ�����
// ����ʹ��gcc����

// v2 ˵����
//  v2 ��ÿһ�β��Ժ�ֱ�ӽ���ͳ�ƣ��Կ�һ��
// v3 ˵���� 2020��4��25��
//  v3 �ڳ��������������˵�������������ԡ�

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// #include <omp.h>
#include <time.h>

FILE * logfile;

bool randtest(double ptrue) {
	double randfloat = (double)rand() / RAND_MAX;
	if (randfloat >= ptrue)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//������Ժ���������Ϊ��ĸ��ʣ�����һ��������ԵĽ���Ƿ�Ϊ��

int main(char argc,char** argv){
	printf("written by leuk0cyte, 2020\n\n\
	������ּ��ģ���ȡ���շ���˫up��\n\
	ԭ���Ǽ����ģ���ڳ����ڽ��г鿨���ӵ�1�鿪ʼ������Ϊֹ����¼�´�ʱ�ĳ�ȡ�����ظ�n��\n\
	nĬ����һ����Σ����Թ��õ�Ҳ����ͨ�����뱾������������������n��ֵ\n\
	���ڱ�Ŀ¼������PowerShell����סShift�����ļ��������ı�Ŀ¼�а�����Ҽ��������롰./�����������.exe 1e9�������趨nΪʮ��\n\
	����ʵһ����ε�����Ҳ�㹻��һ�ڴ���һ����β��Խ����������֮���ڣ���Ƶ�������ڸ���\n\
	���б���������Ŀ¼�²���logfile.txt����ʹ��excel������ļ�\n\
	��һ�Ŵ����ȡ�������ڸó��ӱ��׼�����Ϊ0������¿�ʼ��ȡ���ȡ�Ĵ���\n\
	�ڶ��Ŵ����ڸó�ȡ���³�������up���ǵ��������\n\
	�����Ŵ���ó�ȡ������Ӧ�ġ�xx���ڳ����������ǡ�����¼����ۼƷֲ�������ֵ\n\
	Please have fun!\n\n\n\
	���س����������桭��\
	");
	getchar();
	printf("������\n\n\n");

	uint64_t TEST_TIMES;
	if (argc>1)
	{
		TEST_TIMES = strtod(argv[1],NULL);
	}else
	{
		TEST_TIMES = 1e6;
	}//Ĭ�ϲ��Դ���һ�����
	
	double run_time;
	clock_t time_start, time_stop;
	time_start = clock();

	if ((logfile=fopen("logfile.txt", "w")) == NULL)
	{
		printf("û�в���logfile�ļ���Ȩ�ޣ������Թ���Ա���,���߰ѳ�����ڱ�ĵط�������\n");
		goto a;
	}
	double p0 = 0.02;
	// ������ǵ�ԭʼ����
	double p1 = 0.02;
	// 50���ĸ��ʲ���
	double p2 = 0.7;
	// ���up�����ǵĸ���
	double p3 = 0.5;
	// up�У���ĸ���
	double p4 = 1 - p3;
	// up�У����ĸ���

	srand((unsigned)time(NULL));//���������������

	double p[99];
	for (int i = 0; i < 49; i++)
	{
		p[i] = p0;
	}
	for (int i = 49; i < 99; i++)
	{
		p[i] = p0 + p1 * (i - 49);
	}

	//��ʼ����
	uint64_t* const X = (uint64_t*)malloc(sizeof(uint64_t) * TEST_TIMES);
	//Ҫ����ռ䣬������Խ��

    int ylen = 3000;
    uint64_t Y[3001];
    memset(Y,0,3001);


	for (uint64_t i = 0; i < TEST_TIMES; i++)
	{
		bool flag[2] = { 1,1 };
		int k = 0;
        int xlabel = 0;
		while (flag[0] || flag[1])
		{
			for (int j = 0; j < 99; j++)
			{
				if (randtest(p[j]))
				{
					k += j + 1;
					if (randtest(p2))
					{
						if (randtest(p3))
						{
							flag[0] = 0;
							break;
						}
						else
						{
							flag[1] = 0;
							break;
						}
					}
				}
			}
		}
		if (k<=ylen)
        {
            Y[k]++;
        }else
        {
            X[xlabel] = k;
            xlabel++;
        }  
	}

	// for (size_t i = 0; i < TEST_TIMES; i++)
	// {
	// 	fprintf(logfile, "%llu\t", X[i]);
	// }//���һ����д��Ӳ�̣�һ�ڴβ��Բ����������ļ�Լ360MB

	
	double Z[3001];
	Z[2] = (double)Y[2]/TEST_TIMES;
	for (size_t i = 3; i < ylen + 1; i++)
	{
		Z[i] = Z[i-1] + (double)Y[i]/TEST_TIMES;
	}

	for (size_t i = 2; i < 3000 + 1; i++)
	{
		fprintf(logfile, "%li\t", i);
	}// ���ô���
	fprintf(logfile, "\n");
	for (size_t i = 2; i < ylen + 1; i++)
	{
		fprintf(logfile, "%lu\t", Y[i]);
	}// �ô����µ�����
	fprintf(logfile, "\n");
	for (size_t i = 2; i < ylen + 1; i++)
	{
		fprintf(logfile, "%e\t", Z[i]);
	}// �ۼƷֲ�
    fprintf(logfile, "\n");
    for (size_t i = 0; i < TEST_TIMES; i++)
    {
        if (X[i]==0)
        {
            break;
        }else
        {
            fprintf(logfile, "%lu\t", X[i]);
        }  
    }//��������
	// ¼���ļ�
	

a:
    time_stop = clock();	//��ʱ����
	run_time = (double)(time_stop - time_start)/CLOCKS_PER_SEC * 1e3;
	//
	printf("run_time: %fms\n",run_time);
	printf("�����ѽ�������ȷ��Ŀ¼�����ɵ�logfile.txt\n\
	���س����˳�������\
	");
	getchar();

	return 0;
}