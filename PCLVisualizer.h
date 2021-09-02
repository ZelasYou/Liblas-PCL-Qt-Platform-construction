#ifndef PCLVISUALIZER_H
#define PCLVISUALIZER_H

#include <vtkAutoInit.h> 
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <QtWidgets/QMainWindow>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "ui_pclvisualizer.h"
/*
typedef struct tagPOINT_3D
{
	double x;  //mm world coordinate x  
	double y;  //mm world coordinate y  
	double z;  //mm world coordinate z  
	double r;
}POINT_WORLD;
*/
class PCLVisualizer : public QMainWindow
{
	Q_OBJECT//宏
public:
	PCLVisualizer(QWidget *parent = 0);
	~PCLVisualizer();

private:
	Ui::PCLVisualizerClass ui;
	//Ui::PCLVisualizerClass ui;
	//点云数据存储
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	pcl::PointCloud<pcl::PointXYZI>::Ptr las;//带有强度值的las数据
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

	//初始化vtk部件
	void initialVtkWidget();

	private slots:
	//创建打开槽
	void onOpenpcd();//打开pcd
	void exit();//退出
	void Openlas();//打开las
	void Opentxt();//打开txt
	void Openbin();//打开bin
	//void Clear();
	//void setcolor();
};

#endif // PCLVISUALIZER_H
