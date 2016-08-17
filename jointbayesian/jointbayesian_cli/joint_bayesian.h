#pragma once
#ifndef LX_DLL_CLASS_EXPORTS
#define LX_DLL_CLASS __declspec(dllexport)
#else
#define LX_DLL_CLASS __declspec(dllimport)
#endif


#include<Eigen/Dense>
#include<iostream>
#include<fstream>
using namespace Eigen;
using namespace std;



class LX_DLL_CLASS JointBayesian{
public:

	JointBayesian(){};
	void jointbayesian_train(double* train_dataset,int* train_label,int M,int N);
	void jointbayesian_test(double* test_dataset, int* test_label, int M, int N);
	void jointbayesian_performance(double threshold_start, double threshold_end, double step);


private:
	Matrix<double, Dynamic, Dynamic>dataset,testset;
	Matrix<int, Dynamic, 1>label,testlabel;
	Matrix<double, Dynamic, Dynamic>A, G;//�洢ѵ��ģ��
	Matrix<double, 1, Dynamic>ratio;//�洢���Ա���

	double cov(Matrix<double, Dynamic, Dynamic>&xi, Matrix<double, Dynamic, Dynamic>&xj);
	void ToMatrix(double* tdataset, int* tlabel, int M, int N,int flag);
	void write_to_dat(Matrix<double, Dynamic, Dynamic>&mat, char* filename);
	void read_from_dat(Matrix<double, Dynamic, Dynamic>&mat, char* filename);
};