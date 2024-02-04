clc
clear
close all

%instrreset;

N = 5; %number of readings
measures = zeros(2*N, 1);
x = measures;

<<<<<<< HEAD
s = serial('COM12', 'BaudRate', 115200);
=======
s = serial('/dev/cu.usbserial-110', 'BaudRate', 115200);
>>>>>>> 9e51e6668c2561d67ad62db9130715a009b0cddb
fopen(s);

while fscanf(s) ~= "Setup done"

end

prompt = ['Insert known weight in grams, place the object ' ...
    'on the scale and press enter (ascending order): '];

for i = 1 : 2 * N
    fprintf('\n');
    if i == (1 + N)
        prompt = ['Insert known weight in grams, place the object ' ...
            'on the scale and press enter (descending order): '];
    end
            while true
                T = input(prompt);
                if isnumeric(str2double(T)) && ~isempty(T)
                  x(i) = T;
                  break
                else
                  disp('Error, plese enter a correct value!')
                end
            end
    fprintf(s, 'a');
    measures(i) = fscanf(s, '%f'); %converts the reading in a float number
    fprintf('Serial value: %f\n', measures(i));
end

fclose(s);
delete(s);
%instrreset;

y = measures;

ascending = measures(1:N);
descending = measures((N+1):end);

%save the data:
T = table(x, y, 'VariableNames', {'Known weight', 'Measured weight'});
writetable(T, 'hysteresis.txt');
writetable(T, 'hysteresis.csv');

%Hysteresis:
plot(x(1:N), ascending, 'o', x(N+1:end), descending, '*')
title('Hysteresis');
xlabel('X (valore vero)');
ylabel('Y (indicazione)');
legend('Data', 'Resulting line')
legend();

%Non-linearity:
<<<<<<< HEAD
non_linearity = ascending' - fliplr(descending');
=======
non_linearity = ascending' - fliplr(descending');
>>>>>>> 9e51e6668c2561d67ad62db9130715a009b0cddb
