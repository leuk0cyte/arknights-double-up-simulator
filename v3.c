// written by leuk0cyte, 2020
// 本程序旨在模拟抽取明日方舟双up池
// 输出文件中的每一个数字代表一个不同的玩家在集齐本次up的两个六星的过程中
//  该池中总计抽取的次数
// 样本数足够大（一亿次与一百万次测试结果相差在万分之五内），频率趋近于概率
// 数据处理建议使用matlab
// 运行后目录中会生成一个logfile，第一排是抽取数，
//  第二排是该抽取数下的玩家数目，第三排是累计分布函数
// 建议使用gcc编译

// v2 说明：
//  v2 在每一次测试后直接进行统计，稍快一点
// v3 说明： 2020年4月25日
//  v3 在程序内添加了文字说明，增加易用性。

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
//随机测试函数，输入为真的概率，返回一次随机测试的结果是否为真

int main(char argc,char** argv){
	printf("written by leuk0cyte, 2020\n\n\
	本程序旨在模拟抽取明日方舟双up池\n\
	原理是计算机模拟在池子内进行抽卡，从第1抽开始，抽齐为止，记录下此时的抽取数，重复n次\n\
	n默认是一百万次，电脑够好的也可以通过给与本程序启动参数来增加n的值\n\
	如在本目录下启动PowerShell（按住Shift键在文件管理器的本目录中按鼠标右键），输入“./本程序的名字.exe 1e9”，来设定n为十亿\n\
	但其实一百万次的样本也足够大（一亿次与一百万次测试结果相差在万分之五内），频率趋近于概率\n\
	运行本程序后会在目录下产生logfile.txt，请使用excel打开这个文件\n\
	第一排代表抽取数，即在该池子保底计数器为0的情况下开始抽取后抽取的次数\n\
	第二排代表在该抽取数下抽齐两个up六星的试验次数\n\
	第三排代表该抽取数所对应的“xx抽内抽齐两个六星”这个事件的累计分布函数的值\n\
	Please have fun!\n\n\n\
	按回车键启动仿真……\
	");
	getchar();
	printf("启动！\n\n\n");

	uint64_t TEST_TIMES;
	if (argc>1)
	{
		TEST_TIMES = strtod(argv[1],NULL);
	}else
	{
		TEST_TIMES = 1e6;
	}//默认测试次数一百万次
	
	double run_time;
	clock_t time_start, time_stop;
	time_start = clock();

	if ((logfile=fopen("logfile.txt", "w")) == NULL)
	{
		printf("没有产生logfile文件的权限！试试以管理员身份,或者把程序放在别的地方启动？\n");
		goto a;
	}
	double p0 = 0.02;
	// 获得六星的原始概率
	double p1 = 0.02;
	// 50抽后的概率补偿
	double p2 = 0.7;
	// 抽出up的六星的概率
	double p3 = 0.5;
	// up中，年的概率
	double p4 = 1 - p3;
	// up中，阿的概率

	srand((unsigned)time(NULL));//重设随机数计数器

	double p[99];
	for (int i = 0; i < 49; i++)
	{
		p[i] = p0;
	}
	for (int i = 49; i < 99; i++)
	{
		p[i] = p0 + p1 * (i - 49);
	}

	//开始测试
	uint64_t* const X = (uint64_t*)malloc(sizeof(uint64_t) * TEST_TIMES);
	//要个大空间，储存测试结果

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
	// }//结果一次性写入硬盘，一亿次测试产生的数据文件约360MB

	
	double Z[3001];
	Z[2] = (double)Y[2]/TEST_TIMES;
	for (size_t i = 3; i < ylen + 1; i++)
	{
		Z[i] = Z[i-1] + (double)Y[i]/TEST_TIMES;
	}

	for (size_t i = 2; i < 3000 + 1; i++)
	{
		fprintf(logfile, "%li\t", i);
	}// 所用次数
	fprintf(logfile, "\n");
	for (size_t i = 2; i < ylen + 1; i++)
	{
		fprintf(logfile, "%lu\t", Y[i]);
	}// 该次数下的人数
	fprintf(logfile, "\n");
	for (size_t i = 2; i < ylen + 1; i++)
	{
		fprintf(logfile, "%e\t", Z[i]);
	}// 累计分布
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
    }//究极非酋
	// 录入文件
	

a:
    time_stop = clock();	//计时结束
	run_time = (double)(time_stop - time_start)/CLOCKS_PER_SEC * 1e3;
	//
	printf("run_time: %fms\n",run_time);
	printf("仿真已结束！请确认目录下生成的logfile.txt\n\
	按回车键退出本程序。\
	");
	getchar();

	return 0;
}