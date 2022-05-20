%This is for the variables 
function y = a2Task1(k,f,t)

%Equation
y = (1-exp(-k*t)).*cos(2*pi*f*t);
figure;

%Sketching the plot 
plot(t,y);

%Graphing labels 
xlabel('Time (s)');
ylabel('Voltage(V)');
title('Transient');