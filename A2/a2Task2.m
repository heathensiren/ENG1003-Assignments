clc; 
clear all; 

ProjectPath = pwd;
ROW = 128; COL = 128;

IMG_5704 = strcat(ProjectPath,'\IMG_5704.jpg');
IMG_5703 = strcat(ProjectPath,'\IMG_5703.jpg');
IMG_5702 = strcat(ProjectPath,'\IMG_5702.jpg');
IMG_5701 = strcat(ProjectPath,'\IMG_5701.jpg');
IMG_5700 = strcat(ProjectPath,'\IMG_5700.jpg');
IMG_5699 = strcat(ProjectPath,'\IMG_5699.jpg');
IMG_5698 = strcat(ProjectPath,'\IMG_5698.jpg');
imgDark = strcat(ProjectPath,'dark.png');

img1 = double(imresize(imread("IMG_5704.JPG"),[ROW COL]));
img2 = double(imresize(imread("IMG_5703.JPG"),[ROW COL]));
img3 = double(imresize(imread("IMG_5702.JPG"),[ROW COL]));
img4 = double(imresize(imread("IMG_5701.JPG"),[ROW COL]));
img5 = double(imresize(imread("IMG_5700.JPG"),[ROW COL]));
img6 = double(imresize(imread("IMG_5699.JPG"),[ROW COL]));
img7 = double(imresize(imread("IMG_5698.JPG"),[ROW COL]));
imgDark = double(imresize(imread("dark.png"),[ROW COL]));

figure,
subplot(2,4,1); imshow(uint8(img1)); title('IMG 5704');
subplot(2,4,2); imshow(uint8(img2)); title('IMG 5703');
subplot(2,4,3); imshow(uint8(img3)); title('IMG 5702');
subplot(2,4,4); imshow(uint8(img4)); title('IMG 5701');
subplot(2,4,5); imshow(uint8(img5)); title('IMG 5700');
subplot(2,4,6); imshow(uint8(img6)); title('IMG 5699');
subplot(2,4,7); imshow(uint8(img7)); title('IMG 5698');

figure, 
meanimage = (img1 + img2 +img3+ img4+ img5 +img6+img7)/7; 
subplot(1,3,1); imshow(uint8(meanimage)); title ('Mean Image');
size(imgDark);
Subtractedimage = abs(meanimage - imgDark); 
subplot(1,3,2); imshow(uint8(Subtractedimage)); title('Subtracted Image'); 

Thresh_R = graythresh(Subtractedimage(:,:,1)); 
Thresh_G = graythresh(Subtractedimage(:,:,2));
Thresh_B = graythresh(Subtractedimage(:,:,3));

BW_R = im2bw(Subtractedimage(:,:,1), Thresh_R);
BW_G = im2bw(Subtractedimage(:,:,2), Thresh_G);
BW_B = im2bw(Subtractedimage(:,:,3), Thresh_B);

BW = cat(3, BW_R, BW_G, BW_B);
subplot(1,3,3); imshow(uint8(BW)); title('Thresholded Image'); 
