clc
clear
close all

%instrreset;

N = 5; %at least 5 measures per object should be done
%Choose a sample weigth that is as close as possible to the FSR
measures = zeros(N, 1);
input('Remove any object from the scale. ')

s = serial('COM12', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"

end

for i = 1 : N
    fprintf(s, 't');
    input('Place the object on the scale. ')
    fprintf(s, 'a');
    measures(i, 1) = fscanf(s, '%f');
    fprintf('Serial value: %f\n', measures(i, 1));
    input('Remove the object from the scale. ')
end

fclose(s);
delete(s);
%instrreset;

%save the data:
T = table(measures, 'VariableNames', {'Measures'});
writetable(T, 'repeatability.txt');
writetable(T, 'repeatability.csv');

mean = mean(measures);
standard_dev = std(measures);
