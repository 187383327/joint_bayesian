#joint_bayesian����ʶ��
		C++ʵ��joint bayesian����ʶ���㷨
		C++/CL��װ

##ƽ̨��������
		VS2013      
		eigen3      

##����

###jointbayesian_Csharp

VS2013C#���̣�����C++/CLI��װ��dll�ļ�����ѵ��������

###joingbayesian_cli

��C++�㷨��C++/CLI��װ



##ʹ��

ʵ����JointbBayesian_CLI�࣬�ṩ��4���ӿں�����C#����<br>

* ѵ����bool train_jointbayesian(array<double,2>^ train_dataset,array<int>^train_label,int M,int N)<br>
�����������룺train_dataset:ѵ��������άM*N����<br>
��������      train_label:ѵ������ǩ��һάM*1����<br>
������������������ģ�;���A,G,���洢Ϊdat�ļ���ѵ���ɹ�����true<br>

* �������ԣ�void test_jointbayesian(array<double, 2>^ test_dataset, array<int>^test_label, int M, int N)<br>
		�������룺test_dataset�����Լ�����άM*N����<br>
		����      test_label:���Լ���ǩ��һάM*1����<br>
		    �������������Լ���ratio,�洢�����У���performance_jointbayesian����ʹ��<br>
* ���ܼ��㣺double performance_jointbayesian(double threshold_start, double threshold_end, double step��<br>
        ���룺threshold_start����ֵ��ʼֵ <br>
              threshold_end:��ֵ����ֵ<br>
              step:��������<br>
				�������ǰ���Լ��µ������ֵ�����ش�ֵ
* ����ͼƬ���ԣ�bool testpair_jointbayesian((array<double, 2>^ test_pair,double threshold,int M,int N)
				���룺test_pair��һ�Բ���ͼƬ<br>
							threshold:�� performance_jointbayesian()������������ֵ
				������ж�����ͼƬ����ͬһ�ˣ�����true�����򣬷���false
ѵ���׶Σ�����train_jointbayesian����<br>
�������Խ׶Σ�����test_jointbayesian��performance_jointbayesian����<br>


