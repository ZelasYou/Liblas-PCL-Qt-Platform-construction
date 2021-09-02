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
	Q_OBJECT//��
public:
	PCLVisualizer(QWidget *parent = 0);
	~PCLVisualizer();

private:
	Ui::PCLVisualizerClass ui;
	//Ui::PCLVisualizerClass ui;
	//�������ݴ洢
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	pcl::PointCloud<pcl::PointXYZI>::Ptr las;//����ǿ��ֵ��las����
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

	//��ʼ��vtk����
	void initialVtkWidget();

	private slots:
	//�����򿪲�
	void onOpenpcd();//��pcd
	void exit();//�˳�
	void Openlas();//��las
	void Opentxt();//��txt
	void Openbin();//��bin
	//void Clear();
	//void setcolor();
};

#endif // PCLVISUALIZER_H
