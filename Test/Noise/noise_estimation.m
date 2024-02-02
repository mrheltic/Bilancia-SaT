clc
clear
close all

%instrreset;

N = 100;
n = zeros(N, 1);

s = serial('/dev/cu.usbserial-10', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"

end

for i = 1 : N
    fprintf(s, '\n');
    readData = fscanf(s);
    n(i) = sscanf(readData, '%f'); %converts the reading in a float number 
end

fclose(s);
delete(s);
%instrreset;

%save the data:
T = table(n, 'VariableNames', {'Noise'});
writetable(T, 'noise.txt');
writetable(T, 'noise.csv');

fft(n);

mean = mean(n);
var = std(n);
