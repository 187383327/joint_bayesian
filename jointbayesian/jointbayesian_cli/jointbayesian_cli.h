// jointbayesian_cli.h
//���Ƕ�jointbayesian C++ʵ�ֵ�C++/CLI��װ
#pragma once

using namespace System;
using namespace Runtime::InteropServices;
#include<time.h>
#include "joint_bayesian.h"

namespace jointbayesian_cli {

	public ref class JointbBayesian_CLI
	{
	public:
		JointbBayesian_CLI(bool falg,String^ A_path,String^ G_path);
		~JointbBayesian_CLI();

		double train_jointbayesian(array<double,2>^ train_dataset,array<int>^train_label,int trainM,int trainN,\
									 array<double, 2>^ test_dataset, array<int>^test_label, int testM, int testN,\
									 double threshold_start, double threshold_end, double step);//ѵ��ģ�ͣ����Բ����������ֵ
		bool testPair_jointbayesian(array<double, 2>^ test_pair, double threshold, int M, int N);//���Ե���ͼƬ

	private:
		JointBayesian* jointbayesian;
	};
}
