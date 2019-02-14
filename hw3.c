#include "img_pro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int matrix_multiply3x3(unsigned char **img1,int  img2[3][3])
{
	int i,j,x,y=0,sum=0;

			for(x=0;x<3;x++)
			{	
			   for(i=0;i<3;i++)
				{
	            	sum= sum+img1[x][i]*img2[x][i];
                }
            }


	return sum;
}


unsigned char **apply_filter(unsigned char **img,int filter[3][3], int NR, int NC)
{
	unsigned char **img_edge,**small_img;
    img_edge=alloc_img(NR,NC);
	small_img=alloc_img(3,3);
	int i,j,x,y;

	for(i=0; i<(NR-9) ;i++) 
	{
		for(j=0; j<(NC-9) ;j++)
		{
			for(x=0;x<3;x++)
			{	for(y=0;y<3;y++)
				{ 
				 
				  small_img[x][y]=img[i+x][y+j];
				}
			}

		    img_edge[i][j]=matrix_multiply3x3(small_img,filter);


		}
				
	}

	return img_edge;

}

unsigned char **edge_detect(unsigned char **img,int NR,int NC)
{
	int i,j,x,y;
	unsigned char **img_edge,**small_img;
	img_edge=alloc_img(NR,NC);
    small_img=alloc_img(3,3);
	int lap[3][3] = {0,1,0,1,-4,1,0,1,0};
	int Gx[3][3]  = {-1,0,1,-2,0,2,-1,0,1};
	int Gy[3][3]  = {1,2,1,0,0,0,-1,-2,-1};

	img_edge = apply_filter(img,lap,NR, NC);

	free_img(small_img);
	return (img_edge);

	

}



int main(int argc, char *argv[])
{  

   char FileName[20]; 

   if( argc == 2 ) {

      printf("Your pgm file is %s \n", argv[1]);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("Example : ./hw3 [.pgm file]  \n");
	  exit(0);
   }


    unsigned int x,y,i,j,NR=300,NC=300;

    unsigned char **img,**img_det;
   
    strcpy(FileName, argv[1]);

	img=alloc_img(NR,NC);
	img_det=alloc_img(NR,NC);
	img=pgm_file_to_img(FileName,&NR,&NC);


	img_det=edge_detect(img,NR,NC);



    img_to_pgm_file(img_det,"edge_detection.pgm",NR,NC);  //new file
    printf("The new file has been saved as edge_detection.pgm \n");

	free_img(img);



}
