#include "joint_bayesian.h"


JointBayesian::JointBayesian(bool flag, char* Apath, char* Gpath){
	A_path = Apath;
	G_path = Gpath;
	if (flag){
		read_from_dat(A, A_path);
		read_from_dat(G, G_path);
	}
	//read_from_dat(A,)
}

bool JointBayesian::jointbayesian_train(double* train_dataset, int* train_label, int M, int N){
	cout << "**********train jointbayes***********" << endl;
	ToMatrix(train_dataset, train_label, M, N,1);
	int n_dim = dataset.cols();//ͼƬά��
	int n_image = dataset.rows();//ͼƬ����
	cout << "image:" << n_image << ' ' << "dim:" << n_dim << endl;
	int everyclasscount[20000] = { 0 };//��¼ÿ������ͼƬ��
	int withcount = 0;
	int n_class = 1, cnt = 1;//n_class�������� cnt��ÿ�����������
	int numberbuf[10000] = { 0 };
	int maxnumber = cnt;
	for (int i = 0; i < n_image-1; i++){//����ͼƬ�����������ж��ٸ���ͬ���ˣ��Լ�ÿ��ͼƬ�ĸ�����
		if (label(i, 0) != label(i + 1, 0)){
			if (cnt > 1)withcount += cnt;
			maxnumber = maxnumber > cnt ? maxnumber : cnt;
			if (numberbuf[cnt] == 0)numberbuf[cnt] = 1;
			everyclasscount[n_class - 1] = cnt;
			n_class++;
			cnt = 1;
			continue;
		}
		cnt++;
	}
	if (cnt > maxnumber)maxnumber = cnt;
	cout << "maxnumber" << maxnumber << endl;
	everyclasscount[n_class - 1] = cnt;//���һ�������ͼƬ����
	if (cnt > 1)withcount += cnt;
	cout <<"class:"<< n_class << ',' <<endl;
	Matrix<double, Dynamic, Dynamic>u,e;
	u.setZero(n_dim, n_class);
	e.setZero(n_dim, withcount);
	Matrix<double, Dynamic, Dynamic>ui,ei;
	ui.setZero(n_dim, 1);
	ei.setZero(n_dim, 1);
	cout << "cal u,e" << endl;
	//��ʼ��u��e�������ڳ�ʼ��Su��Sw
	for (int i = 0,count=0,count1=0; i < n_class; i++){
		for (int j = 0; j < everyclasscount[i]; j++)ui += dataset.row(count1 + j).transpose();
		ui = ui / everyclasscount[i];
		u.col(i) = ui;
		if (everyclasscount[i] > 1){
			for (int j = 0; j < everyclasscount[i]; j++)e.col(count + j) = dataset.row(count + j).transpose() - ui;
			count += everyclasscount[i];
		}
		count1 += everyclasscount[i];
	}
	Matrix<double, Dynamic, Dynamic>Su, Sw,oldSw;
	Su.setZero(n_dim,n_dim);
	Sw.setZero(n_dim, n_dim);
	cout << "cal Su,Sw" << endl;
	//��ʼ��Su��Sw
	for (int i = 0; i < u.rows(); i++)
		for (int j = 0; j < u.rows(); j++){
			Matrix<double, Dynamic, Dynamic>xi, xj;
			xi = u.row(i);
			xj = u.row(j);
			Su(i, j) = cov(xi, xj);
			xi = e.row(i);
			xj = e.row(j);
			Sw(i, j) = cov(xi, xj);
		}
	oldSw = Sw;
	double convergence = 1, min_convergence = 1;
	Matrix<double, Dynamic, Dynamic>F,Sg,Sui,Sei;
	cout << "iterate start"<<endl;
	//��ʼ����
	for (int l = 0; l < 5000; l++){
		cout << "**********iter" << l <<"**********" <<endl;
		F = Sw.inverse();
		cout << "cal u,e" << endl;	
		//����u��e����
		Matrix<Matrix<double,Dynamic, Dynamic>, 1000, 1>SwG, SuFG;
		for (int mi = 0; mi < maxnumber + 1; mi++){
			if (numberbuf[mi] == 1){
				G = -((mi*Su + Sw).inverse()*Su*Sw.inverse());
				SuFG[mi] = Su*(F + mi*G);
				SwG[mi] = Sw*G;
			}
		}
		for (int i = 0,count=0,count1=0; i < n_class; i++){
			ui.setZero(n_dim, 1);
			ei.setZero(n_dim, 1);
			for (int j = 0; j < everyclasscount[i]; j++)ui += SuFG(everyclasscount[i])*(dataset.row(count1 + j).transpose());
			u.col(i) = ui;
			count1 += everyclasscount[i];
			if (everyclasscount[i]>1){
				for (int k = 0; k < everyclasscount[i]; k++){
					ei += SwG(everyclasscount[i])*(dataset.row(count + k).transpose());
					e.col(count + k) = dataset.row(count + k).transpose() + ei;
				}
				count += everyclasscount[i];
			}
		}
		cout << "cal Su,Sw" << endl;
		//����Su,Sw����
		for (int i = 0; i < u.rows(); i++)
			for (int j = 0; j < u.rows(); j++){
				Matrix<double, Dynamic, Dynamic>xi, xj;
				xi = u.row(i);
				xj = u.row(j);
				Su(i, j) = cov(xi, xj);
				xi = e.row(i);
				xj = e.row(j);
				Sw(i, j) = cov(xi, xj);
			}
		//�ж�Sw�Ƿ�������������ֹͣ������ѵ������
		convergence = (Sw - oldSw).norm() / Sw.norm();
		cout << "convergence: "<<  convergence << endl;
		if (convergence < 0.000001)break;
		oldSw = Sw;
	}
	cout << "iter end" << endl;
	//����ģ��A,G
	F = Sw.inverse();
	G = -((2 * Su + Sw).inverse())*Su*(Sw.inverse());
	A = ((Su + Sw).inverse()) - (F + G);
	write_to_dat(A, A_path);
	write_to_dat(G, G_path);
	cout << "***********train complete***********" << endl;
	return true;
}

//����ģ�ͣ�����ratio
double* JointBayesian::jointbayesian_test(double* test_dataset, int* test_label, int M, int N){
	cout << "**********test jointbayes***********" << endl;
	//�������ݾ��󣬱�ǩ����
	ToMatrix(test_dataset, test_label, M, N,0);
	int n_pair = testset.rows() / 2;
    ratio.setZero(1, n_pair);
	Matrix<double, 1, 1>res;
	for (int i = 0,j=0; i <testset.rows(); i+=2){
		res = testset.row(i)*A*testset.row(i).transpose() + testset.row(i+1)*A*testset.row(i+1).transpose() - 2 * testset.row(i)*G*testset.row(i + 1).transpose();
		ratio(0,j++) = res(0, 0);
	}
}

//����ģ��׼ȷ�ʣ�Ѱ�����������ֵ
double JointBayesian::jointbayesian_performance(double t_s, double t_e, double step){
	cout << "**********find best threshhold**********"<<endl;
	int n_pair = testset.rows() / 2;
	//����Ѱ�������ֵ
	double accuracy = 0, bestaccuracy = 0, bestthreshold = t_s;
	for (double z = t_s; z <= t_e; z += step){
		int score = 0, y;
		for (int j = 0; j < n_pair; j++){
			if (ratio(0,j) >= z)y = 1;
			else y = 0;
			if (testlabel(j, 0) == y)score++;
		}
		accuracy = (double)score / n_pair;
		if (accuracy > bestaccuracy){
			bestaccuracy = accuracy;
			bestthreshold = z;
		}
	}
	cout << "best threshold:" << bestthreshold << endl;
	cout << "best accuracy:" << bestaccuracy << endl;
	return bestthreshold;
}
//���Ե���ͼƬ
bool JointBayesian::jointbayesian_testPair(double* test_pair, double threshold, int M, int N){
	//�������ݾ���
	Matrix<double, 1, Dynamic>x1, x2;
	x1.setZero(1, N);
	x2.setZero(1, N);
	for (int i = 0; i < N; i++){
		x1(0, i) = test_pair[i];
		x2(0, i) = test_pair[N + i];
	}
	Matrix<double, 1, 1>res;
	//����ratio
	res = x1*A*x1.transpose() + x2*A*x2.transpose() - 2 * x1*G*x2.transpose();
	if (res(0, 0) >= threshold)return true;
	else return false;
}

//����������֮��Э������ΪЭ��������е�һ��Ԫ��
double JointBayesian::cov(Matrix<double, Dynamic, Dynamic>&xi, Matrix<double, Dynamic, Dynamic>&xj){
	int n = xi.cols();
	double mean_xi = xi.sum() / n;
	double mean_xj = xj.sum() / n;
	double covm = 0;
	for (int i = 0; i < n; i++)covm += (xi(0, i) - mean_xi)*(xj(0, i) - mean_xj);
	covm /= (n - 1);
	return covm;
}

//�������������飬��ǩ����ת��Ϊ��Ӧ�ľ�����ʽ
void JointBayesian::ToMatrix(double* tdataset, int* tlabel, int M, int N, int flag){
	if (flag){
		dataset.setZero(M, N);
		label.setZero(M, 1);
	}
	else {
		testset.setZero(M, N);
		testlabel.setZero(M / 2, 1);
	}
	for (int i = 0; i < M; i++){
		if (flag)label(i, 0) = tlabel[i];
		else if(i<M/2)testlabel(i, 0) = tlabel[i];
		for (int j = 0; j < N; j++){
			if (flag)dataset(i, j) = tdataset[i*N + j];
			else testset(i, j) = tdataset[i*N + j];
		}
	}
}

void JointBayesian::write_to_dat(Matrix<double, Dynamic, Dynamic>&mat, char* filename){
	ofstream file;
	file.open(filename, ios::trunc);
	file << mat.rows()<<" "<<mat.cols()<<" "<<"\n";
	for (int i = 0; i < mat.rows(); i++){
		for (int j = 0; j < mat.cols(); j++)file << mat(i, j) << ' ';
		file << "\n";
	}
	file.close();
}

void JointBayesian::read_from_dat(Matrix<double, Dynamic, Dynamic>&mat, char* filename){
	ifstream file;
	file.open(filename, ios::in);
	double temp;
	int M, N;
	file >> M >> N;
	mat.setZero(N, N);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++){
			file >> temp;
			mat(i, j) = temp;
		}
}