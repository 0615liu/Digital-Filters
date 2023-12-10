#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define FS 48000.0f
#define FL 1500.0f   //lower frequency be 1500
#define FH 3500.0f   //higher frequency be 3500
#define PI 3.141592653589793f

typedef struct wave   
{
    char chunkID[4];
    int  ChunkSize;
    char Format[4];
    char SubChunk1ID[4];
    int SubChunk1Size;
    short AudioFormat;
    short numChannels;
    int SampleRate;
    int ByteRate;
    short BlockAlign;
    short BitsPerSample;
    char SubChunk2ID[4];
    int SubChun2Size;
} Headerwav;


// float low_pass(int m, int n)
// {
// 	float wc = 2*PI*FL/FS;
// 	if(n==m) {// L'Hopital's Rule
// 		return wc/PI;
// 	}
// 	else {
// 		return sinf(wc*((float)(n-m)))/PI/((float)(n-m)) * hamming(2*m+1, n);
// 	}
// }

/* hamming: for n=0,1,2,...N, length of N+1 */
float hamming(int N, int n)
{
    return 0.54 - 0.46 * cosf(2 * PI * ((float)(n)) / ((float)N));
}

float band_pass(int m, int n)  
{
    float wh = 2 * PI * FH / FS;  
    float wl = 2 * PI * FL / FS;  
    if (n == m) //when comes to 0                 
    {   // L'Hopital's Rule
        return 2.0 * (wh / PI - wl / PI);
    }
    else if(n!=m)
    {
        return 2.0 * (sinf(wh * ((float)(n - m))) - sinf(wl * ((float)(n - m)))) / PI / ((float)(n - m)) * hamming(2 * m + 1, n);
    }
}

struct RIfunction
{
    double realpart;
    double imaginepart;
};

float BANDSTOP(int m, int n) // bandstop and bandpass in freq domain sigma will be 1
{
    float wh = 2 * PI * FH / FS;
    float wl = 2 * PI * FL / FS; 
    if (n == m) // n=0
    {
        return 1.0- (wh / PI - wl / PI); // inverse fourier transform if 1 is delta
    }
    else // n unequal to 0
    {
        return -(sinf(wh * ((float)(n - m))) - sinf(wl * ((float)(n - m)))) / PI / ((float)(n - m)) * hamming(2 * m + 1, n);
    }
}



struct RIfunction adder(struct  RIfunction x, struct RIfunction y);
struct RIfunction multipler(struct RIfunction x, struct RIfunction y); //x for real y for imagine part 
double absfunction(struct RIfunction x);

void discreteforuiertransform(struct RIfunction* x, int N) 
{
    struct RIfunction* result = calloc(N, sizeof(struct RIfunction));
    if (result == NULL) 
    {
        printf("Memory distribute failed.\n");
    }

    for (int i = 0; i <= N-1; i++) 
    {
        for (int j = 0; j <= N-1; j++) 
        {
            double phase = -2 * (PI * i * j )/ N;
            struct RIfunction cs;
            cs.imaginepart = sin(phase);
            cs.realpart = cos(phase);
            result[i] = adder(result[i], multipler(x[j], cs));
        }
    }

    for (int i = 0; i <=N-1; i++) 
    {
        x[i] = result[i];
    }
    free(result);
}

int main(int argc, char *argv[])
{                                                              
    int M = atoi(argv[1]); 
    int k;
    int n = 0;
    
    /*produce hL and hR.txt*/
    char *hL_txt = argv[2];  
    char *hR_txt = argv[3]; 
    /*produce YL and YR.txt*/
    char *YL_txt = argv[4];  
    char *YR_txt = argv[5];
    /*blue-giant-fragment.wav*/
    char *fn_in = argv[6];
    /*output.wav*/   
    char *fn_out = argv[7]; 
    float y = 0;
    float *h_L = (float *)malloc(sizeof(float) * 2 * M + 1);
    float *h_R = (float *)malloc(sizeof(float) * 2 * M + 1);
   
    
    FILE *fp;
    Headerwav MMSP;
    fp = fopen(fn_in, "rb");
    //read the file
    fread(MMSP.chunkID, sizeof(char), 4, fp);
    fread(&MMSP.ChunkSize, sizeof(int), 1, fp);
    fread(MMSP.Format, sizeof(char), 4, fp);
    fread(MMSP.SubChunk1ID, sizeof(char), 4, fp);
    fread(&MMSP.SubChunk1Size, sizeof(int), 1,fp);
    fread(&MMSP.AudioFormat, sizeof(short), 1, fp);
    fread(&MMSP.numChannels, sizeof(short), 1, fp);
    fread(&MMSP.SampleRate, sizeof(int), 1, fp);
    fread(&MMSP.ByteRate, sizeof(int), 1, fp);
    fread(&MMSP.BlockAlign, sizeof(short), 1,fp);
    fread(&MMSP.BitsPerSample, sizeof(short), 1, fp);
    fread(MMSP.SubChunk2ID, sizeof(char), 4, fp);
    fread(&MMSP.SubChun2Size, sizeof(int), 1,fp); 
   //read the file
    fseek(fp, 44, SEEK_SET);
    int N = (MMSP.ChunkSize )/ 2-18;
    N /= 2;
    int filter;
    int bandpassfilter;
    int bandstopfilter;
    short *rightChannelin = malloc(sizeof(short) * N);
    short *rightChannelout = malloc(sizeof(short) * N);
    short *leftChannelin = malloc(sizeof(short) * N);
    short *leftChannelout = malloc(sizeof(short) * N);

    for (int i = 0; i <= N-1; i++)
    {
        fread(&rightChannelin[i], sizeof(short), 1, fp);
        fread(&leftChannelin[i], sizeof(short), 1,fp);
    }
  
    for (n = 0; n < (2 * M + 1); n++)
    {
        h_L[n] = band_pass(M, n);
        h_R[n] = BANDSTOP(M, n);
    }

    for (n = 0; n <=N-1; n++)
    {
        y = 0;
        for (k = 0; k < (2 * M + 1); k++)
        {
            if ((n - k) >= 0)
                y = y + h_L[k] * ((float)(leftChannelin[n - k]));
        }
        leftChannelout[n] = (short)(roundf(y));

        y = 0;
        for (k = 0; k < (2 * M + 1); k++)
        {
            if ((n - k) >= 0)
                y = y + h_R[k] * ((float)(rightChannelin[n - k]));
        }
        rightChannelout[n] = (short)(roundf(y));
    }

    FILE *fptr;

    fptr = fopen(fn_out, "wb");
    if (!fptr)
    {
        fprintf(stderr, "no saving for the data %s\n", fn_out);
        return 0;
    }
    fwrite(&MMSP.chunkID, sizeof(char), 4, fptr);
    fwrite(&MMSP.ChunkSize, sizeof(int), 1,  fptr);
    fwrite(&MMSP.Format, sizeof(char), 4, fptr);
    fwrite(&MMSP.SubChunk1ID, sizeof(char), 4,  fptr);
    fwrite(&MMSP.SubChunk1Size, sizeof(int), 1, fptr);
    fwrite(&MMSP.AudioFormat, sizeof(short), 1,  fptr);
    fwrite(&MMSP.numChannels, sizeof(short), 1, fptr);
    fwrite(&MMSP.SampleRate, sizeof(int), 1,  fptr);
    fwrite(&MMSP.ByteRate, sizeof(int), 1, fptr);
    fwrite(&MMSP.BlockAlign, sizeof(short), 1,  fptr);
    fwrite(&MMSP.BitsPerSample, sizeof(short), 1,  fptr);
    fwrite(&MMSP.SubChunk2ID, sizeof(char), 4,  fptr);
    fwrite(&MMSP.SubChun2Size, sizeof(int), 1, fptr); // in order to write the file
    
    for (int i = 0; i <= N-1; i++)
    {
        fwrite(&leftChannelout[i], sizeof(short), 1,  fptr);
        fwrite(&rightChannelout[i], sizeof(short), 1,  fptr);
    }

    FILE *hLtxt;  
    hLtxt = fopen(hL_txt, "w");
    for (int i = 0; i < 2 * M + 1; i++)
    {
        fprintf(hLtxt, "%.15e\n", h_L[i]);
    }
    fclose(hLtxt);
    int hLcoefficient;
    int hRcoefficient;

    FILE *hRtxt;  
    hRtxt = fopen(hR_txt, "w");
    for (int i = 0; i < 2 * M + 1; i++)
    {
        fprintf(hRtxt, "%.15e\n", h_R[i]);
    }
    fclose(hRtxt);

    struct RIfunction *DFTleftoutput = malloc(sizeof(struct RIfunction) * 1200);
    struct RIfunction *DFTrightoutput = malloc(sizeof(struct RIfunction) * 1200);
    //we will dft the time to spectro
    //1200 sampling
    for (int i = 962880; i < 964080; i++)  
    {
        DFTleftoutput[i - 962880].imaginepart = 0;
        DFTrightoutput[i - 962880].imaginepart = 0;
    }

    for (int i = 962880; i < 964080; i++) 
    {
        DFTleftoutput[i - 962880].realpart = leftChannelout[i];
        DFTrightoutput[i - 962880].realpart = rightChannelout[i];
    }
  
    discreteforuiertransform( DFTleftoutput, 1200); 
    discreteforuiertransform( DFTrightoutput, 1200);    
    // if(!discreteforuiertransform(DFTleftoutput, 1200))
    // {
    //     printf("save");
    // }

    FILE *YLtxt;  
    YLtxt = fopen(YL_txt, "w");
    //produce YLtxt
    //produce YRtxt
    FILE *YRtxt;  
    YRtxt = fopen(YR_txt, "w");
    for(int i=0;i<600;i++) //owing 0 to 599 and 600 to 1200 is same
    {
     double strength = absfunction(DFTleftoutput[i]);
     double strengthsize = 20*log(strength);
     fprintf(YLtxt,"%.15e\n", strengthsize);  
    }
    fclose(YLtxt);
//two times for loop for YL YR
    for(int i=0;i<600;i++) //owing 0 to 599 and 600 to 1200 is same
    {
     double strength = absfunction(DFTrightoutput[i]);
     double strengthsize = 20*log(strength);
      fprintf(YRtxt,"%.15e\n", strengthsize);
    }
    fclose(YRtxt);
}

double absfunction(struct RIfunction x) 
{
    return sqrt( x.imaginepart * x.imaginepart + x.realpart * x.realpart);  //square roots to calculate the abs
}

// in order to real imagine multipler and sigma
struct RIfunction adder(struct  RIfunction x, struct RIfunction y) 
{
    struct RIfunction cmp;
    cmp.realpart = x.realpart + y.realpart;
    cmp.imaginepart = x.imaginepart + y.imaginepart;
    //cmp.sigma=x.real+ y.real + x.imagine + y.imagine;
    return cmp;
}

//create real imagine part
struct RIfunction multipler(struct RIfunction x, struct RIfunction y) //x for real y for imagine part
{
    struct RIfunction cmp;
    cmp.realpart = x.realpart * y.realpart - x.imaginepart * y.imaginepart;
    cmp.imaginepart = x.realpart * y.imaginepart + x.imaginepart * y.realpart;
    //cmp.sigma=x.real* y.real * x.imagine * y.imagine;
    return cmp;
}


