clc
clear
close all

%instrfind
%instrreset;

N = 5; %number of readings
measures = zeros(N, 1);
known_weight = input(['Insert the weight in grams of the object and' ...
    ' press enter: ']);
prompt = ['Place the object in the' ...
    ' middle of the scale and then press enter: '];

s = serial('/dev/cu.usbserial-10', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"
 
end

for i = 1 : N
    if i == 2
        prompt = ['Place the object in the' ...
            ' bottom left corner of the scale and then press enter: '];
    elseif i == 3
        prompt = ['Place the object in the' ...
            ' top left corner of the scale and then press enter: '];
    elseif i == 4
        prompt = ['Place the object in the' ...
            ' top right corner of the scale and then press enter: '];
    elseif i == 5
        prompt = ['Place the object in the' ...
            ' bottom right corner of the scale and then press enter: '];
    end
    input(prompt);
    fprintf(s, '\n');
    readData = fscanf(s)
    measures(i) = sscanf(readData, '%f'); %converts the reading in a float number 
end

fclose(s);
delete(s);
%instrreset;

mean = mean(measures);
standard_deviation = std(measures);
error = known_weight - measures;

%save the data:
T = table(measures, error, 'VariableNames', {'Measured weight', 'Error'});
writetable(T, 'eccentricity.txt');
writetable(T, 'eccentricity.csv');