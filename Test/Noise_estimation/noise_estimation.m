clc
clear
close all

%instrreset;

N = 100;
n = zeros(N, 1);

s = serial('COM7', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"

end

for i = 1 : N
    fprintf(s, 'a');
    n(i) = fscanf(s, '%f'); %converts the reading in a float number 
    fprintf('Serial value: %f\n', n(i));
end

fclose(s);
delete(s);
%instrreset;

%save the data:
T = table(n, 'VariableNames', {'Noise'});
writetable(T, 'noise.txt');
writetable(T, 'noise.csv');

%dft = fft(n);
%f = abs(dft(1:100))*2/100;
%h = 0:1:N-1;

bar(h, f);

mean = mean(n);
var = std(n);