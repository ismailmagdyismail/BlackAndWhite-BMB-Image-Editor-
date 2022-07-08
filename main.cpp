// Assignment 3 
// Name:Ismail Magdy Ismail , ID=20210069 , Group:A , Section:25/26
// Name:Abdallah Khaled     , ID=20210216 , Group:A , Section:25/26
// Name:Basel Ayman Saleh   , ID=20210084 , Group:A , Section:25/26


// Final Phase (12 Filters): 

// black and white Images    

// 1-Black & White Filter
// 2-Invert Filter
// 3-Flip Image
// 4-Rotate Image
// 5-Mirror Image
// 6-Shuffle Image
// 7-Blur Image
// 8-Enlarge Image
// 9-detect Edges

//---------------------------------------

#include <iostream>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

// replacing unsigned char with unchar (Macros)ß
#define unchar unsigned char


unchar image[SIZE][SIZE];


// (Control / Menu)  functions 

void save_image();
void menu();
void check_choice();
void load_image(unchar image[SIZE][SIZE]);



// Filters main Functions 
void black_and_white(unchar image[SIZE][SIZE]);
void invert_filter(unchar image[SIZE][SIZE]);
void flip_image(unchar image[SIZE][SIZE]);
void rotate_image(unchar  image[SIZE][SIZE]);
void mirror_image(unchar  image[SIZE][SIZE]);
void shuffle_image(unchar  image[SIZE][SIZE]);
void blur_image(unchar  image[SIZE][SIZE]);
void enlarge_image(unchar  image[SIZE][SIZE]);
void detect_edges(unchar  image[SIZE][SIZE]);
void darken_or_lighten(unchar  image[SIZE][SIZE]);
void merge_image(unchar  image[SIZE][SIZE]);
void shrink_image(unchar  image[SIZE][SIZE]);


// sub Functions (2d Array Manipulation / Kernels)
void transpose(unchar image[SIZE][SIZE]);
void copy_left(unchar image[SIZE][SIZE]);
void copy_right(unchar image[SIZE][SIZE]);
void copy_upper(unchar image[SIZE][SIZE]);
void copy_down(unchar image[SIZE][SIZE]);
void quarters(unchar q1[SIZE/2][SIZE/2],unchar q2[SIZE/2][SIZE/2],
unchar q3[SIZE/2][SIZE/2],unchar q4[SIZE/2][SIZE/2]);
void rearrange(unchar array[SIZE/2][SIZE/2],const int& current_quarter);
void kernel_sum(const int& row ,const int& coulmn,unchar copy[256][256]);
void quarter(unsigned char array[SIZE/2][SIZE/2],const int& order);
void repeat_pixels(unchar quarter[SIZE/2][SIZE/2]);
void laplacian(const int& row,const int& coulmn,unchar copy[256][256]);
void reduce_image(unchar image[SIZE][SIZE],const int& ratio);



int main()
{
    while(true)
    {
    load_image(image);
    menu();
    check_choice();
    }
}

//---------------------------------------

void load_image(unchar array[SIZE][SIZE])
{
    // Adding extinstion .bmp to the picture (file) name
    char file_name[100];
    cout<<"Enter the name of the Black and white (uncolored) picture  : ";
    cin>>file_name;

    strcat(file_name,".bmp");
   readGSBMP(file_name, array);
}

//---------------------------------------

void save_image()
{
    //adding ".bmp" and saving picture
    char file_name[100];
    cout<<"Enter the target image file name:";
    cin>>file_name;
    strcat(file_name,".bmp");
    writeGSBMP(file_name, image);
}

//---------------------------------------

void menu()
{
    // display filters list
    cout<<"Choose The filter you want to add\n";
    cout<<"1-Black & White Filter\n";
    cout<<"2-Invert Filter\n";
    cout<<"3-Flip Image\n";
    cout<<"4-Rotate Image\n";
    cout<<"5-Mirror Image\n";
    cout<<"6-Shuffle Image\n";
    cout<<"7-Blur Image\n";
    cout<<"8-Enlarge Image\n";
    cout<<"9-Detect Edges in Image\n";
    cout<<"10-Darken OR lighten Image\n";
    cout<<"11-Merge With another Image\n";
    cout<<"12-Shrink Image\n";
    cout<<"0-Exit\n";
}

//---------------------------------------

void black_and_white(unchar image[SIZE][SIZE])
{
    // make all the pixels white and black only
    // if the pixel is dark then we change it to a darker pixel
    // if the pixel is light then we change it to lighter pixel 
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
           if(image[i][j]>127)
            {
                if(image[i][j]+90<=255)
                    image[i][j]+=90;
                else
                    image[i][j]=255;
            }
            else
            {
                if(image[i][j]-20>=0255)
                    image[i][j]-=20;
                else
                    image[i][j]=10;
            }
        }
        
    }
    
}

//---------------------------------------

void  invert_filter(unchar image[SIZE][SIZE])
{
    // change the blacks to whites and the whites to blacks
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            image[i][j]=255-image[i][j];
        }        
    }
    
}

//---------------------------------------

void flip_image(unchar image[SIZE][SIZE])
{
    int choice ;
    cout<<"choose the filter you want to add\n";
    cout<<"1-horizontally\n";
    cout<<"2-vertically\n";
    cin>>choice; 
    // check if the user input is valid
    while (choice!=1&&choice!=2)
    {
      cout<<"invalid option , choose  again:";
      cin>>choice;
    }

    // flipping verically by swapping the first pixel with the last pixel and so on..

    if(choice==2)
    {
        for (int i = 0; i < 256; i++)
        {
           for (int j = 0; j < 256/2; j++)
           {
               swap(image[i][j],image[i][255-j]) ;
           }
           
        }
    }

    // flipping horizonatlly by swapping the top pixel with the bottom pixel and so on..

    else if(choice==1)
    {
        for (int i = 0; i < 256/2; i++)
        {
           for (int j = 0; j < 256; j++)
           {
                swap(image[i][j],image[255-i][j]);
           }
        }
    }
}

//---------------------------------------

void rotate_image(unchar image[SIZE][SIZE])
{
    int choice ;
    cout<<"1-Rotate 90º\n";
    cout<<"2-Rotate 180º\n";
    cout<<"3-Rotate 270º\n";
    cin>>choice;

    // check if the user input is valid

    while(choice!=1&&choice!=2&&choice!=3)
    {
        cout<<"Invalid choice ,Choose again\n";
        cin>>choice;
    }
    // Rotating image by 90º or 180 or 270.

    if(choice==1)
    {
       transpose(image);
    }
    else if(choice==2)
    {
        for (int i = 0; i < 2; i++)
        {
            transpose(image);
        }
        
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
           transpose(image);
        }
        
    }
}

//---------------------------------------

void mirror_image(unchar image[SIZE][SIZE])
{
    int choice ;
    cout<<"Choose the side your want to mirror:\n";
    cout<<"1-Left Side\n";
    cout<<"2-Right Side\n";
    cout<<"3-Upper Side\n";
    cout<<"4-Down Side\n";
    cin>>choice;

    // check if the user input is valid

    while(choice!=1&&choice!=2&&choice!=3&&choice!=4)
    {
        cout<<"Invalid side , Choose another one:";
        cin>>choice;
    }

    // mirror the left side or Right side or upper or lower

    if(choice==1)
    {
        copy_left(image);
    }
    else if(choice==2)
    {
        copy_right(image);
    }
    else if(choice==3)
    {
        copy_upper(image);
    }
    else
    {
        copy_down(image);
    }
    
}

//---------------------------------------

void shuffle_image(unchar image[SIZE][SIZE])
{
    // Taking the new order of quarters
    int choice[4];
    cout<<"Enter the New order of quarters ? ";
    for (int i = 0; i < 4; i++)
    {
       cin>>choice[i];

       //validating the users new order of quarters

       while (choice[i]>4||choice[i]<1)
        {
            cout<<"invalid order/quarter ,input should be numbers from[1-4] only , Enter a valid order:";
            cin>>choice[i];
        }
    }
    unchar quarter1[128][128];
    unchar quarter2[128][128];
    unchar quarter3[128][128];
    unchar quarter4[128][128];
    // making 4 arrays storing each storing a quarter
    quarters(quarter1,quarter2,quarter3,quarter4);

    // counter that keeps track of the current quarter to copy to
    int current_quarter=1;

    for (int i = 0; i <4; i++)
    {
        if(choice[i]==1)
        {
            rearrange(quarter1,current_quarter);
        }
        else if(choice[i]==2)
        {
            rearrange(quarter2,current_quarter);
        }
        else if(choice[i]==3)
        {
            rearrange(quarter3,current_quarter);
        }
        else
        {
            rearrange(quarter4,current_quarter);
        }

        // counter that keeps track of which quarter to copy to
        current_quarter++;
    }
    
}

//---------------------------------------

void blur_image(unchar image[SIZE][SIZE])
{
    // using the AVG  blur teqchniue to blur each pixel

    // Making a copy to hold the pixels weights temporarily to be copied later to the original image

    unsigned char copy[SIZE][SIZE];

    for (int i = 0; i < 256; i++)
    {
       for (int j = 0; j < 256; j++)
       {
          kernel_sum(i,j,copy);
       }
       
    }

    // Copying the Wights of each pixel to the Orignal Image

    for (int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            image[i][j]=copy[i][j];
        }
    }
    
}

//---------------------------------------

void enlarge_image(unchar image[SIZE][SIZE])
{
    cout<<"choose The quarter you Want to Enlarge {1,2,3,4} :";
    int choice ;cin>>choice;

    //validating user's input

    while(choice<0||choice>4)
    {
        cout<<"Invalid quarter choose a quarter from [1-4] :";
        cin>>choice;
    }

    unsigned char  enlarged_quarter[128][128];

    if(choice==1)
    {
        quarter(enlarged_quarter,1);
        repeat_pixels(enlarged_quarter);
    }
    else if(choice==2)
    {
        quarter(enlarged_quarter,2);
        repeat_pixels(enlarged_quarter);
    }
    else if(choice==3)
    {
        quarter(enlarged_quarter,3);
        repeat_pixels(enlarged_quarter);
    }
    else
    {
        quarter(enlarged_quarter,4);
        repeat_pixels(enlarged_quarter);
    }
}

//---------------------------------------

void detect_edges(unchar image[SIZE][SIZE])
{

    unchar copy[256][256];

    // using laplacian technique to detect edges  and copying values to an extranal array 

    for (int i = 0; i < 256; i++)
    {
      for(int j = 0; j < 256; j++)
      {
          laplacian(i,j,copy);
      }
    }
    
    // Copying the Wights of each pixel to the Orignal Image
    
    for (int i = 0; i < 256; i++)
    {
      for(int j = 0; j < 256; j++)
      {
          image[i][j]=copy[i][j];
      }
    }

    // using the Invert filter to revert the image 

    invert_filter(image);

    // darkining the edges to be more Visible

    for(int i=0; i < 256; i++)
    {
        for (int j = 0; j< 256; j++)
        {
            if(image[i][j]<125)
                image[i][j]=0;
        }
        
    }
}

//---------------------------------------

void darken_or_lighten(unchar image[SIZE][SIZE])
{
    int choice;
    cout<<"1-Darken\n";
    cout<<"2-Lighten\n";
    cout<<"Enter your choice :";
    cin>>choice;
    
    //validating user's input

    while (choice>2||choice<1)
    {
        cout<<"invalid choice ,choose  another one [1 OR 2]:";
    }


    int factor ;
    // Detirmne whether to lighten or darken the pixels according to input 
    if(choice==1)
    {
        factor=-1;
    }
    else
    {
        factor=1;
    }
    

        for (int i = 0; i < 256; i++)
        {
            for (int j= 0; j < 256; j++)
            {
                if(image[i][j]+(65*factor)>=0&&image[i][j]+(65*factor)<256)
                {
                    image[i][j]+=(65*factor);
                }
                else
                {
                    if(image[i][j]<0)
                    {
                        image[i][j]=0;
                    }
                    else if(image[i][j]>255)
                    {
                        image[i][j]=255;
                    }
                    
                }
                
            }
            
        }
}

//---------------------------------------

void merge_image(unchar image[SIZE][SIZE])
{
    // loading the other Image to Merge With.
   unchar array[SIZE][SIZE];
    load_image(array);
    for (int i = 0; i < 256; i++)
    {
        for(int j=0 ; j<256; j++)
        {
            image[i][j] =(image[i][j]+array[i][j])/2;
        }

    }
    
}

//---------------------------------------

void shrink_image(unchar image[SIZE][SIZE])
{
    int choice = 0;
    // getiing tha ratio to shrink with

    cout<<"Shrink to (1/2) or (1/3) or (1/4)\n";
    cout<<"1-(1/2)\n";
    cout<<"2-(1/3)\n";
    cout<<"3-(1/4)\n";
    cout<<"Enter your choice :";
    cin>>choice;
    
    //validating input

    while(choice>4||choice<1)
    {
        cout<<"invalid input,choose again :";
    }

    if(choice==1)
    {
        reduce_image(image,2);
    }
    else if(choice==2)
    {
        reduce_image(image,3);
    }
    else
    {
        reduce_image(image,4);
    }
}

//---------------------------------------

void check_choice()
{
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;

    // check if the user input is valid

    while (choice < 0||choice > 12)
    {
        cout<<"invalid filter choice , try another :";
        cin>>choice;
    }

    //call the function that performs this filter function

    if(choice == 0)
    {
        exit(0);
    }
    else if(choice == 1)
    {
        black_and_white(image);
        save_image();
    }
    else if(choice == 2)
    {
        invert_filter(image);
        save_image();
    }
    else if(choice == 3)
    {
        flip_image(image);
        save_image();
    }
    else if(choice == 4)
    {
        rotate_image(image);
        save_image();
    }
    else if(choice == 5)
    {
        mirror_image(image);
        save_image();
    }
    else if(choice == 6)
    {
        shuffle_image(image);
        save_image();	
    }
    else if(choice == 7)
    {
        blur_image(image);
        save_image();
    }
    else if(choice == 8)
    {
        enlarge_image(image);
        save_image();
    }
    else if(choice == 9)
    {
        detect_edges(image);
        save_image();
    }
    else if(choice == 10)
    {
        darken_or_lighten(image);
        save_image();
    }
    else if(choice == 11)
    {
        merge_image(image);
        save_image();
    }
    else if(choice == 12)
    {
        shrink_image(image);
        save_image();
    }
    
    
}

//---------------------------------------

void transpose(unchar image[SIZE][SIZE])
{
    // switch each row of pixels with each coulmn 

    unchar array[SIZE][SIZE];
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j <256 ; j++)
        {
            array[255-j][255-i]=image[i][255-j];
        }
        
    }
    for (int i = 0; i < 256; i++)
    {
       for (int j = 0; j < 256; j++)
       {
           image[i][j]=array[i][j];
       }
       
    }
    
    
}

//---------------------------------------

void copy_left(unchar image[SIZE][SIZE]) 
{
    // copying Left side to Right side

    for (int i = 0; i <256; i++)
    {
        for (int j = 0; j < 256/2; j++)
        {
            image[i][255-j]=image[i][j];
        }
        
    }
    
}

//---------------------------------------

void copy_right(unchar image[SIZE][SIZE]) 
{
    // copying Right side to Left side

    for (int i = 0; i < 256; i++)
    {
        for (int j = 255; j>=128; j--)
        {
            image[i][255-j]=image[i][j];
        }
        
    }
    
}

//---------------------------------------

void copy_upper(unchar image[SIZE][SIZE])
{
    // copying Upper side to Lower side

    for (int i = 0; i < 256/2; i++)
    {
       for (int j = 0; j < 256; j++)
       {
           image[255-i][j]=image[i][j];
       }
       
    }
    
}

//---------------------------------------

void copy_down(unchar image[SIZE][SIZE])
{
    // copying down side to upper side

    for (int i = 255; i >= 127; i--)
    {
       for (int j = 0; j < 256; j++)
       {
           image[255-i][j]=image[i][j];
       }
       
    }
    
}

//---------------------------------------

void quarters(unchar q1[SIZE/2][SIZE/2],unchar q2[SIZE/2][SIZE/2],
unchar q3[SIZE/2][SIZE/2],unchar q4[SIZE/2][SIZE/2])
{
    // making an array for eahc quarter of the orignal imaged to be shuffled and re-arranged 
    int row=0,coulmn=0;
    for (int i = 0; i <256/2; i++)
    {
        coulmn=0;
        for (int j = 0; j < 256/2; j++)
        {
            q1[row][coulmn] = image[i][j];
            coulmn++;
        }
        row++;
    }
    row=0,coulmn=0;
    for (int i = 0; i < 256/2; i++)
    {
        coulmn=0;
        for (int j = 128; j < 256; j++)
        {
            q2[row][coulmn] = image[i][j];
            coulmn++;
        }
        row++;
    }
    row=0,coulmn=0;
    for (int i = 128; i < 256; i++)
    {
        coulmn=0;
        for (int j = 0; j < 256/2; j++)
        {
            q3[row][coulmn] = image[i][j];
            coulmn++;
        }
        row++;
    }
    row=0,coulmn=0;
    for (int i = 128; i < 256; i++)
    {
        coulmn=0;
        for (int j = 128; j <256; j++)
        {
            q4[row][coulmn] =image[i][j];
            coulmn++;
        }
        row++;
    }
}

//---------------------------------------

void rearrange(unchar array[SIZE/2][SIZE/2],const int& current_quarter)
{
    //shuffling the arrays that was storing each quarter and copying them back to the orignal image in the new specifed order by the user

    int row=0,coulmn=0;
    if(current_quarter ==1)
    {
        row=0,coulmn=0;
        for (int i = 0; i < SIZE/2; i++)
        {
            coulmn=0;
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j] = array[row][coulmn];
                coulmn++;
            }
            row++;
        }
    }
    else if(current_quarter ==2)
    {
        row=0,coulmn=0;
        for (int i = 0; i < SIZE/2; i++)
        {
            coulmn=0;
            for (int j = 128; j <256; j++)
            {
                image[i][j] = array[row][coulmn];
                coulmn++;
            }
            row++;
        }
    }
    else if(current_quarter==3)
    {
        row=0,coulmn=0;
       for (int i = 128; i < SIZE; i++)
        {
            coulmn=0;
            for (int j = 0; j <SIZE/2; j++)
            {
                image[i][j] = array[row][coulmn];
                coulmn++;
            }
            row++;
        } 
    }
    else
    {
        row=0,coulmn=0;
        for (int i = 128; i < 256; i++)
        {
            coulmn=0;
            for (int j = 128; j <256; j++)
            {
                image[i][j] = array[row][coulmn];
                coulmn++;
            }
            row++;
        } 
    }
}

//---------------------------------------

void kernel_sum(const int& row,const int& coulmn,unchar copy[256][256])
{
    // Making a kernel of size 3X3 to get the weighted Avg of the pixels

    int kernel[3][3];

    int kernel_row=0,kernel_col=0;
    int coulmn_move=coulmn-1+3;
    int row_move=row-1+3;

    for (int i = row-1; i <row_move; i++)
    {
        for (int j = coulmn-1; j <coulmn_move; j++)
        {
            if(i>=0&&i<=255&&j>=0&&j<=255)
            {
                kernel[kernel_row][kernel_col]=image[i][j]*4;
            }
            kernel_col++;
        }
        kernel_col=0;
       kernel_row++;
    }

    //Finding the weighted AVG for every Pixel
    long long sum = 0;
    for (int i = 0; i < 3; i++)
    {
       for (int j = 0; j < 3; j++)
       {
           sum += kernel[i][j];
       }
    }
    double wighted_avg=ceil(sum/36.0);
    copy[row][coulmn] =  wighted_avg;
    
}

//---------------------------------------

void quarter(unchar array[SIZE/2][SIZE/2],const int& order)
{
    if(order == 1)
    {
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
               array[i][j] =image[i][j];
            }
            
        }
    }
    else if(order ==2)
    {
        int row=0,coulmn=0;
        for (int i = 0 ; i < 128; i++)
        {
            coulmn=0;
            for (int j = 128; j < 256; j++)
            {
               array[row][coulmn] = image[i][j];
               coulmn++;
            }
            row++;
        }
    }
    else if(order ==3)
    {
        int row=0,coulmn=0;
        for (int i = 128 ; i < 256; i++)
        {
            coulmn=0;
            for (int j = 0; j < 128; j++)
            {
               array[row][coulmn] = image[i][j];
               coulmn++;
            }
            row++;
        }
    }
    else
    {
        int row=0,coulmn=0;
        for (int i = 128 ; i < 256; i++)
        {
            coulmn=0;
            for (int j = 128; j < 256; j++)
            {
               array[row][coulmn] = image[i][j];
               coulmn++;
            }
            row++;
        }
    }
}

//---------------------------------------

void repeat_pixels(unchar quarter[SIZE/2][SIZE/2])
{
    // repeat Each pixel four times (square shape 2x2) to enlarge a certain quarter

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            for (int k= ((i+1)*2)-2; k <= (i+1)*2-1; k++)
            {
               for (int l = ((j+1)*2)-2 ; l<=(j+1)*2-1 ; l++)
               {
                   image[k][l]=quarter[i][j];
               }
               
            }
            
        }
        
    }
    
}

//---------------------------------------

void laplacian(const int& row,const int& coulmn,unchar copy[256][256])
{
    // Making a kernel of size 3X3 to get the Laplacian weights of the pixels
    int delta_pos_x=0;
    int delta_neg_x=0;
    int delta_pos_y=0;
    int delta_neg_y=0;
    int center=4*image[row][coulmn];
    if(coulmn+1<256)
    {
        delta_pos_x=image[row][coulmn+1];
    }
    if(coulmn-1>=0)
    {
        delta_neg_x=image[row][coulmn-1];
    }
    if(row+1<256)
    {
        delta_pos_y=image[row+1][coulmn];
    }
    if(row-1>=0)
    {
        delta_neg_y=image[row-1][coulmn];
    }

    int laplace=abs(delta_pos_y+delta_neg_y+delta_pos_x+delta_neg_x-center);
    copy[row][coulmn]=laplace;

}

//---------------------------------------

void reduce_image(unchar image[SIZE][SIZE],const int& ratio)
{
    unchar copy[SIZE][SIZE];
    // making an extrnal array  w making all it's pixels white
    for (int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            copy[i][j] = 255;
        }
    }
    // copying the orignal image into the extrnal array according to the shrink ratio 
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            copy[i/ratio][j/ratio] =image[i][j];
        }
    }
    //returning back the content to original image
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            image[i][j] =copy[i][j];
        }
    }
}

//---------------------------------------
