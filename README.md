#joint_bayesian����ʶ��
		C++ʵ��joint bayesian����ʶ���㷨
		C++/CLI��װ����C#�ɵ���dll�ļ�

##ƽ̨��������
-------------
		VS2013      
		eigen���������        

##����

###jointbayesian_Csharp

VS2013��C#���̣�����dll�ļ�����ѵ�������

###joingbayesian_cli

VS2013��CLR���̣���C++ʵ��joint bayesian�㷨������joint bayesian�㷨����C++/CLI��װ������C#�ɵ��õ�dll�ļ�



##ʹ��

###jointbayesian_cli

ʵ����JointbBayesian_CLI�࣬�ṩ��3���ӿں�����C#����<br>

* ѵ����void train_jointbayesian(array<double,2>^ train_dataset,array<int>^train_label,int M,int N)<br>
�����������룺train_dataset:ѵ��������άM*N����<br>
��������      train_label:ѵ������ǩ��һάM*1����<br>
������������������ģ�;���A,G,���洢Ϊdat�ļ�

* ���ԣ�void test_jointbayesian(array<double, 2>^ test_dataset, array<int>^test_label, int M, int N)<br>
		�������룺test_dataset�����Լ�����άM*N����<br>
		����      test_label:���Լ���ǩ��һάM*1����<br>
		    �������������Լ���ratio<br>
* ���ܼ��㣺void performance_jointbayesian(double threshold_start, double threshold_end, double step��<br>
        ���룺threshold_start����ֵ��ʼֵ <br>
              threshold_end:��ֵ����ֵ<br>
              step:��������<br>
ѵ���׶Σ�����train_jointbayesian����<br>
���Խ׶Σ�����test_jointbayesian��performance_jointbayesian����<br>

