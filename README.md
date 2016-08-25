#joint_bayesian人脸识别
		C++实现joint bayesian人脸识别算法
		C++/CLI封装生成C#可调用dll文件

##平台及依赖项
		VS2013      
		eigen矩阵运算库        

##介绍

###jointbayesian_Csharp

VS2013的C#工程，调用dll文件进行训练与测试

###joingbayesian_cli

VS2013的CLR工程，用C++实现joint bayesian算法，并对joint bayesian算法进行C++/CLI封装，生成C#可调用的dll文件



##使用

实现了JointbBayesian_CLI类，提供了3个接口函数供C#调用<br>

<<<<<<< HEAD
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
=======
* 训练：void train_jointbayesian(array<double,2>^ train_dataset,array<int>^train_label,int M,int N)<br>
　　　　输入：train_dataset:训练集，二维M*N数组<br>
　　　　　　　 train_label:训练集标签，一维M*1数组<br>
　　　　输出：计算出模型矩阵A,G,并存储为dat文件

* 测试：void test_jointbayesian(array<double, 2>^ test_dataset, array<int>^test_label, int M, int N)<br>
　　　　输入：test_dataset：测试集，二维M*N数组组<br>
　　　　　　　test_label:训练集标签，一维M*N数组<br>
　　　　输出：计算出测试集的ratio<br>
* 性能计算：void performance_jointbayesian(double threshold_start, double threshold_end, double step）<br>
　　　　输入：threshold_start：阈值起始值 <br>
　　　　　　　threshold_end:阈值结束值<br>
　　　　　　　step:步进长度<br>
　　　　输出：最高正确率和对应阈值<br>
训练阶段，调用train_jointbayesian函数<br>
测试阶段，调用test_jointbayesian和performance_jointbayesian函数<br>
>>>>>>> origin/master

