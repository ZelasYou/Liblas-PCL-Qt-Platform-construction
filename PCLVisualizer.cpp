#include <QFileDialog>
#include <iostream>
#include <vtkRenderWindow.h>
#include "pclvisualizer.h"
#include <QColorDialog>
#include <liblas\liblas.hpp>//测试成功添加liblas库

#include <boost/thread/thread.hpp>//为读取txt文件做准备
#pragma execution_character_set("utf-8")

using namespace std;//为string准备的
using namespace pcl;

PCLVisualizer::PCLVisualizer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//初始化
	initialVtkWidget();
	//连接信号和槽
	//QObject::connect()
	connect(ui.actionOpenpcd, &QAction::triggered, this, &PCLVisualizer::onOpenpcd);//连接打开pcd
	connect(ui.actionExit, &QAction::triggered, this, &PCLVisualizer::exit);//连接关闭软件
	connect(ui.actionOpenlas,&QAction::triggered, this, &PCLVisualizer::Openlas);//连接打开las
	connect(ui.actionOpentxt, &QAction::triggered, this, &PCLVisualizer::Opentxt);//连接打开txt
	connect(ui.actionOpenbin, &QAction::triggered, this, &PCLVisualizer::Openbin);//连接打开bin
	//connect(ui.actionClear, &QAction::triggered, this, &PCLVisualizer::Clear);//清空界面

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


//读取文本型和二进制型点云数据
void PCLVisualizer::onOpenpcd()
{
	//只能打开PCD文件 设置打开窗口
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
//自己加的打开las
void PCLVisualizer::Openlas()
{
	//QString dataPath;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("打开las点云"), ".",
		tr("Open las files(*.las)"));
	if (fileName == "")   return;//判断是否添加成功
	std::string file_name = fileName.toStdString();//字符串类型传递
	std::ifstream ifs(file_name, std::ios::in | std::ios::binary); // 打开las文件

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs); // 读取las文件

	unsigned long int nbPoints = reader.GetHeader().GetPointRecordsCount();//获取las数据点的个数

	//pcl::PointCloud<pcl::PointXYZI> cloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	cloud->width = nbPoints;	//保证与las数据点的个数一致	
	cloud->height = 1;
	cloud->is_dense = false;
	cloud->points.resize(cloud->width * cloud->height);

	int i = 0;

	while (reader.ReadNextPoint())
	{
		// 获取las数据的x，y，z,I信息
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
//读取txt格式文件的点云
//打开txt格式点云的函数

void CreateCloudFromTxt(const std::string& file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
	std::ifstream file(file_path.c_str());//c_str()：生成一个const char*指针，指向以空字符终止的数组。
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
//显示txt点云的函数
void PCLVisualizer::Opentxt()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("打开txt点云"), ".",
		tr("Open txt files(*.txt)"));
	if (fileName == "")   return;//判断是否添加成功
	std::string file = fileName.toStdString();  //fileName为文件名，QString型数据 字符串类型传递
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	CreateCloudFromTxt(file, cloud);
	//显示点云
	viewer->updatePointCloud(cloud, "cloud");
	viewer->resetCamera();
	ui.qvtkWidget->update();
}
//打开bin格式点云的函数
void PCLVisualizer::Openbin() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("打开bin点云"), ".",
		tr("Open las files(*.bin)"));
	if (fileName == "")   return;//判断是否添加成功
	std::string file_name = fileName.toStdString();//字符串类型传递
	//开始正式处理bin
	fstream input(file_name.c_str(), ios::in | ios::binary);
	input.seekg(0, ios::beg);
	pcl::PointCloud<PointXYZ>::Ptr points(new pcl::PointCloud<PointXYZ>);

	int i;
	for (i = 0; input.good() && !input.eof(); i++) {
		PointXYZ point;
		input.read((char *)&point.x, 3 * sizeof(float));
		//input.read((char *)&point.intensity, sizeof(float));//暂时还没学会用点云的强度值显示
		points->push_back(point);
	}
	input.close();
	//显示点云
	viewer->updatePointCloud(points, "cloud");
	viewer->resetCamera();
	ui.qvtkWidget->update();

}
//清空当前界面
/*
void PCLVisualizer::Clear() {

	viewer->resetCamera();
	viewer->removeAllPointClouds();
	

}*/