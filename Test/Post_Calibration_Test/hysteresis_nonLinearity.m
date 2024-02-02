clc
clear
close all

%instrreset;

N = 5; %number of readings
measures = zeros(2*N, 1);
x = measures;

s = serial('/dev/cu.usbserial-10', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"

end

prompt = ['Insert known weight in grams, place the object ' ...
    'on the scale and press enter (ascending order): '];
for i = 1 : 2*N
    if i == (1 + N)
        prompt = ['Insert known weight in grams, place the object ' ...
            'on the scale and press enter (descending order): '];
    end
    x(i) = input(prompt);
    fprintf(s, '\n');
    readData = fscanf(s)
    measures(i) = sscanf(readData, '%f'); %converts the reading in a float number 
end

fclose(s);
delete(s);
%instrreset;

y = measures;

%save the data:
T = table(x, y, 'VariableNames', {'Known weight', 'Measured weight'});
writetable(T, 'hysteresis.txt');
writetable(T, 'hysteresis.csv');

%non-linearity:
x = [x, -x];
y = [y, -y];
plot(x, y)
