#include "pclvisualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);//���岢����Ӧ�ó���
	PCLVisualizer w;//���岢��������
	w.show();//��ʾ����
	return a.exec();//Ӧ�ó�������
}