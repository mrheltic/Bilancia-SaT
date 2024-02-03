clc
clear
close all

%instrfind
%instrreset;

%Choose a sample weigth that is about 1/3 of the FSR
measures = zeros(5, 1);

prompt = ['Insert the weight in grams of the object and' ...
    ' press enter: '];
while true
      T = input(prompt);
      if isnumeric(str2double(T)) && ~isempty(T) && ~isnan(T)
          known_weigth = T;
          break
      else
          disp('Error, plese enter a correct value!')
      end
end

prompt = ['Place the object in the' ...
    ' middle of the scale and then press enter: '];

s = serial('COM12', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"
 
end

for i = 1 : 5
    if i == 2
        prompt = ['Place the object in the' ...
            ' bottom left corner of the scale and then press enter: '];
    elseif i == 3
        prompt = ['Place the object in the' ...
            ' top left corner of the scale and then press enter: '];
    elseif i == 4
        prompt = ['Place the object in the' ...
            ' top rigth corner of the scale and then press enter: '];
    elseif i == 5
        prompt = ['Place the object in the' ...
            ' bottom rigth corner of the scale and then press enter: '];
    end
    input(prompt);
    fprintf(s, 'a');
    measures(i) = fscanf(s, '%f'); %converts the reading in a float number
    fprintf('Serial value: %f\n', measures(i));
end

fclose(s);
delete(s);
%instrreset;

mean = mean(measures);
standard_deviation = std(measures);
error = known_weigth - measures;

%save the data:
T = table(measures, error, 'VariableNames', {'Measured weight', 'Error'});
writetable(T, 'eccentricity.txt');
writetable(T, 'eccentricity.csv');
