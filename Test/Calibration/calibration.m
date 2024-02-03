clc
clear all
close all

%instrfind
%instrreset

N = 11; %number of sample weigths
measures = zeros(N, 5); %5 positions per every object
x = zeros(N, 1);
y = x;

s = serial('COM7', 'BaudRate', 115200);
fopen(s);

while fscanf(s) ~= "Setup done"
 
end

for i = 1 : N
    fprintf('\n');
    for j = 1 : 5
        if j == 1
            prompt = ['Insert known weight in grams, place the object in the' ...
                ' middle of the scale and then press enter: '];
            while true
                T = input(prompt);
                if (isempty(T)) || ~isnumeric(str2double(T))
                    disp('Error, plese enter a correct value!')
                else
                    x(i)=T;
                    break
                end
            end
            fprintf('\n');
        elseif j == 2
            prompt = ['Place the object in the' ...
                ' bottom left corner of the scale and then press enter: '];
            input(prompt);
        elseif j == 3
            prompt = ['Place the object in the' ...
                ' top left corner of the scale and then press enter: '];
            input(prompt);
        elseif j == 4
            prompt = ['Place the object in the' ...
                ' top right corner of the scale and then press enter: '];
            input(prompt);
        elseif j == 5
            prompt = ['Place the object in the' ...
                ' bottom right corner of the scale and then press enter: '];
            input(prompt);
        end
        fprintf(s, 'a');
        measures(i, j) = fscanf(s, '%f'); %converts the reading in a float number
        fprintf('Serial value: %f\n', measures(i, j));
    end
end

fclose(s);
delete(s);
%instrreset

for i = 1 : N
    y(i) = mean(measures(i, :));
end

%save the data:
T = table(x, y, 'VariableNames', {'Known weight', 'Measured weight'});
writetable(T, 'calibration.txt');
writetable(T, 'calibration.csv');

%linear regression:
coeff = polyfit(x, y, 1);
calibration_factor = coeff(1);
offset = coeff(2);
z = polyval(coeff, x);
err = z - x;
err2 = norm(z - x, 2);
fprintf('\nError (linear regression): %1.2e \n', err2);
figure(1)
clf;
plot(x, y, 'go', 'LineWidth' , 1, ... 
    'MarkerEdgeColor', 'k', ...
    'MarkerFaceColor', 'g' ,...
    'MarkerSize', 10);
hold on;
plot(x, z); 
title('Linear regression');
xlabel('X');
ylabel('Y');
legend('Data', 'Resulting line')
legend();
hold off;