/************************************************
* FFT code from the book Numerical Recipes in C *
* Visit www.nr.com for the licence.             *
************************************************/

// The following line must be defined before including math.h to correctly define M_PI
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI  3.14159265358979323846
#define TWOPI   (2.0*PI)

/*

 Inputs:
    data[] : array of complex* data points of size 2*NFFT+1.
        data[0] is unused,
        * the n'th complex number x(n), for 0 <= n <= length(x)-1, is stored as:
            data[2*n+1] = real(x(n))
            data[2*n+2] = imag(x(n))
        if length(Nx) < NFFT, the remainder of the array must be padded with zeros

    nn : FFT order NFFT. This MUST be a power of 2 and >= length(x).
    isign:  if set to 1,
                computes the forward FFT
            if set to -1,
                computes Inverse FFT - in this case the output values have
                to be manually normalized by multiplying with 1/NFFT.
 Outputs:
    data[] : The FFT or IFFT results are stored in data, overwriting the input.
*/

void four1(float data[], int nn, int isign)
{
    int n, mmax, m, j, istep, i;
    float wtemp, wr, wpr, wpi, wi, theta;
    float tempr, tempi;

    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
        tempr = data[j];     data[j] = data[i];     data[i] = tempr;
        tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
        }

        m = n >> 1;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax = 2;
    while (n > mmax) {
    istep = 2*mmax;
    theta = TWOPI/(isign*mmax);
    wtemp = sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    for (m = 1; m < mmax; m += 2) {
        for (i = m; i <= n; i += istep) {
        j =i + mmax;
        tempr = wr*data[j]   - wi*data[j+1];
        tempi = wr*data[j+1] + wi*data[j];
        data[j]   = data[i]   - tempr;
        data[j+1] = data[i+1] - tempi;
        data[i] += tempr;
        data[i+1] += tempi;
        }
        wr = (wtemp = wr)*wpr - wi*wpi + wr;
        wi = wi*wpr + wtemp*wpi + wi;
    }
    mmax = istep;
    }
}

void four2(unsigned char data[], int nn, int isign)
{
    int n, mmax, m, j, istep, i;
    unsigned char wtemp, wr, wpr, wpi, wi, theta;
    unsigned char tempr, tempi;

    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
        tempr = data[j];     data[j] = data[i];     data[i] = tempr;
        tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
        }

        m = n >> 1;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax = 2;
    while (n > mmax) {
    istep = 2*mmax;
    theta = TWOPI/(isign*mmax);
    wtemp = sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    for (m = 1; m < mmax; m += 2) {
        for (i = m; i <= n; i += istep) {
        j =i + mmax;
        tempr = wr*data[j]   - wi*data[j+1];
        tempi = wr*data[j+1] + wi*data[j];
        data[j]   = data[i]   - tempr;
        data[j+1] = data[i+1] - tempi;
        data[i] += tempr;
        data[i+1] += tempi;
        }
        wr = (wtemp = wr)*wpr - wi*wpi + wr;
        wi = wi*wpr + wtemp*wpi + wi;
    }
    mmax = istep;
    }
}



