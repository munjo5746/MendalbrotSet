#include "mainwindow.h"

void MainWindow::draw_sse(QImage &image,int max_iter){
    //__int64 start = 0, end = 0, freq = 0;
    int width = 0, height = 0, x_max = 2, x_min = -2, y_min = -1, y_max = 1,x_len = 0, y_len;
    QImage window(600,600,QImage::Format_RGB32);
    QColor color;
    window.fill(Qt::white);
    width = window.width();
    height = window.height();
    x_len = x_max - x_min;
    y_len = y_max - y_min;
    bool is_in1 = true, is_in2 = true, is_in3 = true, is_in4 = true;
    int x = 0, y = 0;
    __m128 c_re, c_im, z_re, z_im, z_re2, z_im2, scalar;
    scalar = _mm_set_ps1(2.0);
    QPainter paint;
    paint.begin(&window);
    //QueryPerformanceCounter((LARGE_INTEGER *) &start);
    for(x = 0; x < width; x += 4){
        c_re = _mm_set_ps(x_min+(x_len*(x+3))/float(width),x_min+(x_len*(x+2))/float(width),x_min+(x_len*(x+1))/float(width),x_min+(x_len*x)/float(width));
        for(y = 0; y < height; y++){
            c_im = _mm_set_ps1(y_max-(y_len*y)/float(height));

            z_re = c_re;
            z_im = c_im;
            is_in1 = true, is_in2 = true, is_in3 = true, is_in4 = true;
            for(int n = 0; n < max_iter; n++){
                z_re2 = _mm_mul_ps(z_re,z_re);
                z_im2 = _mm_mul_ps(z_im,z_im);

                //color.setRed(n);
                //color.setGreen(n);
                //color.setBlue(n);
                //paint.setPen(color);

                if(is_in1 == false && is_in2 == false && is_in3 == false && is_in4 == false){
                    break;
                }
                if(z_re2.m128_f32[0]+z_im2.m128_f32[0] > 4 && is_in1){
                    //paint.drawPoint(x,y);
                    is_in1 = false;
                }
                if(z_re2.m128_f32[1] + z_im2.m128_f32[1] > 4 && is_in2){
                    //paint.drawPoint(x+1,y);
                    is_in2 = false;
                }
                if(z_re2.m128_f32[2] + z_im2.m128_f32[2] > 4 && is_in3){
                    //paint.drawPoint(x+2,y);
                    is_in3 = false;
                }
                if(z_re2.m128_f32[3] + z_im2.m128_f32[3] > 4 && is_in4){
                    //paint.drawPoint(x+3,y);
                    is_in4 = false;
                }
                z_im = _mm_mul_ps(scalar,z_im);
                z_im = _mm_mul_ps(z_im,z_re);
                z_im = _mm_add_ps(z_im,c_im);
                z_re = _mm_sub_ps(z_re2,z_im2);
                z_re = _mm_add_ps(z_re,c_re);
            }

            color.setRed(0);
            color.setGreen(0);
            color.setBlue(0);
            paint.setPen(color);

            if(is_in1){
                paint.drawPoint(x,y);
            }
            if(is_in2){
                paint.drawPoint(x+1,y);
            }
            if(is_in3){
                paint.drawPoint(x+2,y);
            }
            if(is_in4){
                paint.drawPoint(x+3,y);
            }

        }
    }
    paint.end();
    image = window;
    //cout<<"setting here"<<endl;
    //screen = window;
    //label->setPixmap(QPixmap::fromImage(screen));
    //cout<<"setting here"<<endl;
    //QLabel label;
    //label.setPixmap(QPixmap::fromImage(window));
    //label.show();
    //update();
}
void MainWindow::draw_norm(QImage &image,int max_iter){
    int width = 0, height = 0, x_max = 2, x_min = -2, y_min = -1, y_max = 1;
    double c_re = 0.0, c_im = 0, z_re2 = 0.0, z_im2 = 0.0, z_re = 0.0, z_im = 0.0;
    QImage window(600,600,QImage::Format_RGB32);
    QColor color;

    window.fill(Qt::white);
    width = window.width();
    height = window.height();
    QPainter paint;
    bool is_in = false;

    paint.begin(&window);
    //QueryPerformanceCounter((LARGE_INTEGER *) &start);
    for(int x = 0; x < width; x++){
        c_re = x_min + (double((x_max-x_min))*x)/width;
        for(int y = 0; y < height; y++){
            c_im = y_max - (double((y_max-y_min))*y)/height;
            z_re = c_re, z_im = c_im;
            is_in = true;
            for(int i = 0; i < max_iter; i++){
                z_re2 = z_re*z_re;
                z_im2 = z_im*z_im;
                //z_re2 = pow(z_re,3);
                //z_im2 = pow(z_im,3);
                if(z_re2 + z_im2 > 4){
                    is_in = false;
                    break;
                }
                z_im = 2*z_re*z_im + c_im;
                z_re = z_re2 - z_im2 + c_re;
                //z_re = pow(z_re,3)-3*pow(z_im,2)*z_re+c_re;
                //z_im = 3*pow(z_re,2)*z_im-pow(z_im,3)+c_im;
            }

            if(is_in){
                color.setRed(0);
                color.setGreen(0);
                color.setBlue(0);
                paint.setPen(color);
                paint.drawPoint(x,y);
            }

        }
        z_re = 0.0;
        z_im = 0.0;
    }
    paint.end();
    image = window;
    /*
    QueryPerformanceCounter((LARGE_INTEGER *) &end);
    QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
    cout<<(end-start)*1.0/freq<<endl;
    QLabel label;
    label.setPixmap(QPixmap::fromImage(window));
    label.show();
    */
}
