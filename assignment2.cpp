#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const float pi = 3.141592;

int main() {

    char header[12];
    int* n;   n = (int*)header;  *n = 200;
    float* f; f = (float*)(header + 4); *f = 1000;
    short* a; a = (short*)(header + 8); *a = 100;
    short* p; p = (short*)(header + 10); *p = 12;
    float* data1; data1 = new float[*n];
    float* data2; data2 = new float[*n];

    float dt = 1. / f[0] / 20.0;
    for (int i = 0; i < n[0]; i++) {
        data1[i] = float(a[0] * sin(2.0 * pi * f[0] * i * dt));
    }

    ofstream aa("a.dat", ios::binary | ios::out);
    if (!aa) return 666;
    aa.write(header, 12 * sizeof(char));
    aa.write((char*)data1, n[0] * sizeof(float));
    aa.close();

    char header1[12];

    ifstream bb("a.dat", ios::binary | ios::in);
    if (!bb) return 666;
    bb.read(header1, 12 * sizeof(char));
    bb.close();

    *f = 200;
    dt = 1. / 1000. / 20.0;
    for (int i = 0; i < n[0]; i++) {
        data2[i] = float(a[0] * sin(2.0 * pi * f[0] * i * dt));
    }

    ofstream cc("b.dat", ios::binary | ios::out);
    if (!cc) return 666;
    cc.write(header1, 12 * sizeof(char));
    cc.write((char*)data2, n[0] * sizeof(float));
    cc.close();

    ofstream dd("c.txt");
    if (!dd) return 666;
    for (int i = 0; i < n[0]; i++) {
        dd << i * dt << " " << data1[i] << " " << data2[i] << endl;
    }
    dd.close();
}