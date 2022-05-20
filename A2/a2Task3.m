clc; 

reduced = double(imread("output.png"));

s = size(reduced);
row = 2:s(1)-1;
col = 2:s(2)-1;

blurredPic(row,col,:) = (reduced(row,col,:) + reduced(row-1,col,:) + reduced(row,col-1,:) + ... 
    reduced(row,col+1,:))/5;

figure,
subplot(2,2,1); imshow(uint8(reduced)); title('IMG 5704');

subplot(2,2,3); imshow(uint8(blurredPic)); title('Blurred Image');

y = reduced - blurredPic;
y = y*10;

output = y + reduced;

subplot(2,2,2); imshow(uint8(output)); title('Output');
subplot(2,2,4); imshow(uint8(y)); title ('Y intensity');