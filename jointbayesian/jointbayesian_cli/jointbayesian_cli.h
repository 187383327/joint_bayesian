// jointbayesian_cli.h
//���Ƕ�jointbayesian C++ʵ�ֵ�C++/CLI��װ
#pragma once

using namespace System;
//using namespace System::xml;

#include "joint_bayesian.h"

namespace jointbayesian_cli {

	public ref class JointbBayesian_CLI
	{
	public:
		JointbBayesian_CLI();
		~JointbBayesian_CLI();

		void train_jointbayesian(array<double,2>^ train_dataset,array<int>^train_label,int M,int N);//C#�ӿڣ�ѵ��ģ��
		void test_jointbayesian(array<double, 2>^ test_dataset, array<int>^test_label, int M, int N);//����ģ��
		void performance_jointbayesian(double threshold_start, double threshold_end, double step);//ģ�;���


	private:
		JointBayesian* jointbayesian;
	};
}
