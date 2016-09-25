/*
 * Discrete CMAC code
 * Author: Aditya Earanky
 * UID:114355997
 */
 
#include <iostream>
#include <cmath>
#include <fstream>

#define pi 3.14

void init_X(float data[100]); //void init_X(float& ret); - Passes a value by reference
void update_W(float input[100],float weights[104],int g, int &count);
void test_Y(float data[100], float weights[104], int g);
void error_metric(float arr[50], int g);

int main()
{
	float _data[100] = {0};
	int g=3;
	float _weights[116] = {0}; //104 for g=5
	int _count;
	
	init_X(_data);
		
	for(int i=0; i<10; i++)
	{
		_count = 0;
		std::cout<<"--------------For the Training data----------\n";
		std::cout<<"Generalization window Size: "<<g;
		update_W(_data, _weights, g,_count);
		std::cout<<"\nIterations required to converge: "<<_count<<std::endl;
		test_Y(_data, _weights, g);
		g=g+2;	
	}
	return 0;
}

void init_X(float data[100])
{
	for(int i=0;i<100;i++) 
		//data[i] = i;
		data[i] = sin((2*pi/100)*i);
}

void update_W(float data[100],float weights[116],int g, int &count)
{
	int start_w = (g-1)/2;
	float Y[50] = {0};
	float des_Y;
	float err[50];
	float add_w;
	float avg_err=100;
	float sum_err=0;
	count=0;

	while(std::abs(avg_err)>0.00001) //Set the error margin here
	{
		count++;
		sum_err = 0;
		for(int i=0; i<100; i=i+2) //For 100 Samples
		{			
			des_Y = data[i];
		
			//Find out the output to compare with the desired output
			int j=i/2;
			Y[j] = 0;
			for(int n=-(g-1)/2; n<(g+1)/2; n++) //g=5
				Y[j] = Y[j] + weights[i+start_w+n];
				
			//Check the error and update the local weights for the current window
			if (Y[j]!=des_Y)
			{
				err[j] = des_Y - Y[j];
				add_w = err[j]/g;
			
				for(int n=-(g-1)/2; n<(g+1)/2; n++) //For g=5
				{
					weights[i+start_w+n] = weights[i+start_w+n] + add_w;
				}
			}
			
			//else std::cout<<"\n";			
	
			//ERROR ARRAY				
			sum_err = sum_err + err[j];
			avg_err = sum_err/50; //For 50 input samples
		}
	}
	std::cout<<"\nAverage Error for the training samples: "<<std::abs(avg_err);
	
	//----------------------SENDING COUNT DATA TO FILE-----------------------
	std::ofstream outfile;
	outfile.open("CountVsG_Dsin.txt", std::ios_base::app);
	outfile <<g<<" ";
	outfile<<count<<"\n"; 
	outfile.close();
	
}

void test_Y(float data[100], float weights[116], int g)
{
	int start_w = (g-1)/2;
	float Output[50] = {0};
	int j;
	float des_Y;
	float err[50] = {0};
	float sum_err=0;
	float avg_err=0;
	
	std::cout<<"\n--------------For the test data-------------";
		
	for (int i=1;i<101;i=i+2)
	{	
		j=i/2;
		for(int n=-(g-1)/2; n<(g+1)/2; n++)
			Output[j] = Output[j]+weights[i+start_w+n];
			
		des_Y = data[i];
		err[j] = des_Y - Output[j];
		std::cout<<"\nDesired: "<<des_Y<<"\tOutput: "<<Output[j] <<"\tError: "<<err[j];
		
		
		//ERROR ARRAY				
		sum_err = sum_err + err[j];
		avg_err = sum_err/50; //For 50 test samples
	}
	std::cout<<"\n\nAverage Error for the test data: "<<std::abs(avg_err) << "\n";
	
	//-------------------SENDING ERROR METRIC DATA TO FILES--------------------------
	error_metric(err, g);	
	
	//-------------------SENDING OUTPUT DATA TO FILES--------------------------
	std::ofstream myfile1 ("expected_sin.txt");
	for (int k=1;k<100;k=k+2) // For 50 samples
	{
		j=k/2;
		if (myfile1.is_open())
		{
			myfile1<<k<<" "<<data[k]<<std::endl;
		}
	}
	myfile1.close();
	
	switch(g) 
	{
		case 3:
		{
			std::ofstream myfile2 ("actual_g_3.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 5:
		{
			std::ofstream myfile2 ("actual_g_5.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 7:
		{
			std::ofstream myfile2 ("actual_g_7.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 9:
		{
			std::ofstream myfile2 ("actual_g_9.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 11:
		{
			std::ofstream myfile2 ("actual_g_11.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 13:
		{
			std::ofstream myfile2 ("actual_g_13.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 15:
		{
			std::ofstream myfile2 ("actual_g_15.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 17:
		{
			std::ofstream myfile2 ("actual_g_17.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 19:
		{
			std::ofstream myfile2 ("actual_g_19.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		case 21:
		{
			std::ofstream myfile2 ("actual_g_21.txt");
			for (int k=1;k<100;k=k+2) // For 50 samples
			{	
				j=k/2;
				if (myfile2.is_open())
				{
					myfile2<<k<<" "<<Output[j]<<std::endl;
				}
			}
			myfile2.close();
		}
		
	}
}

void error_metric(float err[50],int g)
{
	float Sum_Sqr_err;
	float norm2;	
		
	for (int i=0; i<50; i++)
		Sum_Sqr_err = Sum_Sqr_err + pow(err[i],2);
	
	norm2 = sqrt(Sum_Sqr_err);
	std::cout<<"Norm2 : "<<norm2<< "\tWindow size: "<<g <<"\n\n";
	
	std::ofstream outfile;
	outfile.open("Norm2VsG_Dsin.txt", std::ios_base::app);
	outfile <<g<<" ";
	outfile<<norm2<<"\n"; 
	outfile.close();
}
