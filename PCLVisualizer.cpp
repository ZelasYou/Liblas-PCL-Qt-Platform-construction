#include <QFileDialog>
#include <iostream>
#include <vtkRenderWindow.h>
#include "pclvisualizer.h"
#include <QColorDialog>
#include <liblas\liblas.hpp>//���Գɹ����liblas��

#include <boost/thread/thread.hpp>//Ϊ��ȡtxt�ļ���׼��
#pragma execution_character_set("utf-8")

using namespace std;//Ϊstring׼����
using namespace pcl;

PCLVisualizer::PCLVisualizer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//��ʼ��
	initialVtkWidget();
	//�����źźͲ�
	//QObject::connect()
	connect(ui.actionOpenpcd, &QAction::triggered, this, &PCLVisualizer::onOpenpcd);//���Ӵ�pcd
	connect(ui.actionExit, &QAction::triggered, this, &PCLVisualizer::exit);//���ӹر����
	connect(ui.actionOpenlas,&QAction::triggered, this, &PCLVisualizer::Openlas);//���Ӵ�las
	connect(ui.actionOpentxt, &QAction::triggered, this, &PCLVisualizer::Opentxt);//���Ӵ�txt
	connect(ui.actionOpenbin, &QAction::triggered, this, &PCLVisualizer::Openbin);//���Ӵ�bin
	//connect(ui.actionClear, &QAction::triggered, this, &PCLVisualizer::Clear);//��ս���

}

PCLVisualizer::~PCLVisualizer()
{

}

void PCLVisualizer::initialVtkWidget()
{
	cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	viewer->addPointCloud(cloud, "cloud");

	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();
}


//��ȡ�ı��ͺͶ������͵�������
void PCLVisualizer::onOpenpcd()
{
	//ֻ�ܴ�PCD�ļ� ���ô򿪴���
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open PointCloud"), ".",
		tr("Open PCD files(*.pcd)"));

	if (!fileName.isEmpty())
	{
		std::string file_name = fileName.toStdString();
		//sensor_msgs::PointCloud2 cloud2;
		pcl::PCLPointCloud2 cloud2;
		//pcl::PointCloud<Eigen::MatrixXf> cloud2;
		Eigen::Vector4f origin;
		Eigen::Quaternionf orientation;
		int pcd_version;
		int data_type;
		unsigned int data_idx;
		int offset = 0;
		pcl::PCDReader rd;
		rd.readHeader(file_name, cloud2, origin, orientation, pcd_version, data_type, data_idx);

		if (data_type == 0)
		{
			pcl::io::loadPCDFile(fileName.toStdString(), *cloud);
		}
		else if (data_type == 2)
		{
			pcl::PCDReader reader;
			reader.read<pcl::PointXYZ>(fileName.toStdString(), *cloud);
		}

		viewer->updatePointCloud(cloud, "cloud");
		viewer->resetCamera();
		ui.qvtkWidget->update();
	}
}
void PCLVisualizer::exit()
{
	this->close();
}
//�Լ��ӵĴ�las
void PCLVisualizer::Openlas()
{
	//QString dataPath;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("��las����"), ".",
		tr("Open las files(*.las)"));
	if (fileName == "")   return;//�ж��Ƿ���ӳɹ�
	std::string file_name = fileName.toStdString();//�ַ������ʹ���
	std::ifstream ifs(file_name, std::ios::in | std::ios::binary); // ��las�ļ�

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs); // ��ȡlas�ļ�

	unsigned long int nbPoints = reader.GetHeader().GetPointRecordsCount();//��ȡlas���ݵ�ĸ���

	//pcl::PointCloud<pcl::PointXYZI> cloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	cloud->width = nbPoints;	//��֤��las���ݵ�ĸ���һ��	
	cloud->height = 1;
	cloud->is_dense = false;
	cloud->points.resize(cloud->width * cloud->height);

	int i = 0;

	while (reader.ReadNextPoint())
	{
		// ��ȡlas���ݵ�x��y��z,I��Ϣ
		cloud->points[i].x = (reader.GetPoint().GetX());
		cloud->points[i].y = (reader.GetPoint().GetY());
		cloud->points[i].z = (reader.GetPoint().GetZ());
		//cloud->points[i].intensity = (reader.GetPoint().GetIntensity());
		i++;
	}
	viewer->updatePointCloud(cloud, "cloud");
	viewer->resetCamera();
	ui.qvtkWidget->update();
	
}
//��ȡtxt��ʽ�ļ��ĵ���
//��txt��ʽ���Ƶĺ���

void CreateCloudFromTxt(const std::string& file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
	std::ifstream file(file_path.c_str());//c_str()������һ��const char*ָ�룬ָ���Կ��ַ���ֹ�����顣
	std::string line;
	pcl::PointXYZ point;
	while (getline(file, line)) {
		std::stringstream ss(line);
		ss >> point.x;
		ss >> point.y;
		ss >> point.z;
		cloud->push_back(point);
	}
	file.close();
}
//��ʾtxt���Ƶĺ���
void PCLVisualizer::Opentxt()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("��txt����"), ".",
		tr("Open txt files(*.txt)"));
	if (fileName == "")   return;//�ж��Ƿ���ӳɹ�
	std::string file = fileName.toStdString();  //fileNameΪ�ļ�����QString������ �ַ������ʹ���
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	CreateCloudFromTxt(file, cloud);
	//��ʾ����
	viewer->updatePointCloud(cloud, "cloud");
	viewer->resetCamera();
	ui.qvtkWidget->update();
}
//��bin��ʽ���Ƶĺ���
void PCLVisualizer::Openbin() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("��bin����"), ".",
		tr("Open las files(*.bin)"));
	if (fileName == "")   return;//�ж��Ƿ���ӳɹ�
	std::string file_name = fileName.toStdString();//�ַ������ʹ���
	//��ʼ��ʽ����bin
	fstream input(file_name.c_str(), ios::in | ios::binary);
	input.seekg(0, ios::beg);
	pcl::PointCloud<PointXYZ>::Ptr points(new pcl::PointCloud<PointXYZ>);

	int i;
	for (i = 0; input.good() && !input.eof(); i++) {
		PointXYZ point;
		input.read((char *)&point.x, 3 * sizeof(float));
		//input.read((char *)&point.intensity, sizeof(float));//��ʱ��ûѧ���õ��Ƶ�ǿ��ֵ��ʾ
		points->push_back(point);
	}
	input.close();
	//��ʾ����
	viewer->updatePointCloud(points, "cloud");
	viewer->resetCamera();
	ui.qvtkWidget->update();

}
//��յ�ǰ����
/*
void PCLVisualizer::Clear() {

	viewer->resetCamera();
	viewer->removeAllPointClouds();
	

}*/