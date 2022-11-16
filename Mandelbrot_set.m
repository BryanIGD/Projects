% Mandelbrot set
%
% This program plots the Mandelbrot set fractal as surface and contour
% plots. It is contained in the range [-2, 1] for the real part and [-1.5,
% 1.5] for the imagynary part.
%
% Made by BG

clear all 
clear

% n is the dimensions of the grid (number of points)
n = 200;

% Declare the x and y arrays for the grid
realC = linspace(-2,1,n);
imC = linspace(-1.5,1.5,n);

% Initialize the C and M matrices for eficiency 
C = zeros(n,n);
M = zeros(n,n);

% Populate the C matrix with imaginary numbers
for i=1:n
    for j=1:n
        C(i,j) = realC(i) + 1i*imC(j);
    end
end

% Calculate the numbers that belong to the Mandelbrot set
for i=1:n
    for j=1:n
        z = 0;
        cont = 0;
        zMagnitude = 0;
        for k=1:150
            z = z^2 + C(i,j);
            zMagnitude = abs(z);
            cont = cont + 1;
            if zMagnitude > 2
                break
            end
        end
        M(i,j) = cont;
    end
end

% Plot the results
figure(1);
subplot(1,2,1);
surf(realC,imC,M)
title("Surface plot")
xlabel("Real")
ylabel("Imaginary")

subplot(1,2,2);
contour(realC,imC,M)
title("Contour plot")
xlabel("Real")
ylabel("Imaginary")

figure(2);
meshc(realC,imC,M)
title("Surface and Contour plot")
xlabel("Real")
ylabel("Imaginary")
