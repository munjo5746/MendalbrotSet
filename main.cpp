#include "mainwindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    __int64 st = 0, ed = 0, freq = 0;
    MainWindow main;
    QImage sse_image,norm_image;
    QLabel sse_label,norm_label;
    int loop_num = 0;
    ofstream sse,normal;
    cout<<"SSE test begin!!"<<endl;
    sse.open("sse_result.txt",ios::out);
    for(int count = 1; count <= 5;count++){
        sse_image.fill(Qt::white);
        loop_num += 50;
        QueryPerformanceCounter((LARGE_INTEGER *) &st);
        main.draw_sse(sse_image,loop_num);
        QueryPerformanceCounter((LARGE_INTEGER *) &ed);
        QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
        sse<<loop_num<<','<<((ed-st)*1.0/freq)<<endl;
        st = 0, ed = 0, freq = 0;
    }
    sse.close();
    cout<<"SSE test end!!"<<endl;
    st = 0, ed = 0, freq = 0;
    loop_num = 0;
    cout<<"Normal test begin!!"<<endl;
    normal.open("normal_result.txt",ios::out);
    for(int count = 1; count <= 5;count++){
        norm_image.fill(Qt::white);
        loop_num += 50;
        QueryPerformanceCounter((LARGE_INTEGER *) &st);
        main.draw_norm(norm_image,loop_num);
        QueryPerformanceCounter((LARGE_INTEGER *) &ed);
        QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
        normal<<loop_num<<','<<((ed-st)*1.0/freq)<<endl;
        st = 0, ed = 0, freq = 0;
    }
    normal.close();
    cout<<"Normal test end!!"<<endl;
    norm_label.setPixmap(QPixmap::fromImage(norm_image));
    norm_label.show();
    sse_label.setPixmap(QPixmap::fromImage(sse_image));
    sse_label.show();

    return a.exec();
}
