%vertices labeled as v#; vertex one is v1, etc
clear
clc
r1 =  0.5;%cylinder radius
r2 = 1;%boundary region radius
lf = 3;%half length, or shortest distance from region edge to origin
lr = 5; % d outlet to  origin
fd = '(20 20 1)'; %far block density
nd = '(20 20 1)'; %boundary block density
fg = 'simpleGrading (1.0 1.0 1.0)'; %far block grading
ng = 'simpleGrading (2.0 1.0 1.0)'; %near grading


v = zeros(64,3);
n = 1;
for theta = 0: pi/4: (7/4) * pi
    sol = [cos(theta), sin(theta)];
    v(n, 1:2) = r1 * sol;
    v(n+8,1:2) = r2*sol;
    n = n + 1;
end

v(17, 1:2) = [lr, 0];
v(18, 1:2) = [lr, r2*sin(pi/4)];
v(19, 1:2) = [lr, lf];
v(20, 1:2) = [r2*cos(pi/4), lf];
v(21, 1:2) = [0, lf];
v(22, 1:2) = [r2*cos(3*pi/4), lf];
v(23, 1:2) = [-lf, lf];
v(24, 1:2) = [-lf, r2*sin(3*pi/4)];
v(25, 1:2) = [-lf, 0];
v(26, 1:2) = [-lf, -r2*sin(pi/4)];
v(27, 1:2) = [-lf, -lf];
v(28, 1:2) = [-r2*cos(pi/4), -lf];
v(29, 1:2) = [0, -lf];
v(30, 1:2) = [-r2*cos(3*pi/4), -lf];
v(31, 1:2) = [lr, -lf];
v(32, 1:2) = [lr, -cos(pi/4)];

%visual confirmation of correct vertex placement
%  hold on
%  for h = 1:32
%      scatter(v(h,1), v(h, 2))
%  end

%Makes duplicate points with z = 1, for "3D" grid
v(33:64, 1:2) = [v(1:32, 1:2)];
v(33:64, 3) = 1;


%Generating Blocks (6 vertices)
%block 0
b0 = 'hex (0 8 9 1 32 40 41 33)';
c0 = nd;
g0 = ng;

%block 1
b1 = 'hex (1 9 10 2 33 41 42 34)';
c1 = nd;
g1 = ng;

%block 2
b2 = 'hex (2 10 11 3 34 42 43 35)';
c2 = nd;
g2 = ng;

%block 3
b3 = 'hex (3 11 12 4 35 43 44 36)';
c3 = nd;
g3 = ng;

%block 4
b4 = 'hex (4 12 13 5 36 44 45 37)';
c4 = nd;
g4 = ng;

%block 5
b5 = 'hex (5 13 14 6 37 45 46 38)';
c5 = nd;
g5 = ng;

%block 6
b6 = 'hex (6 14 15 7 38 46 47 39)';
c6 = nd;
g6 = ng;

%block 7
b7 = 'hex (7 15 8 0 39 47 40 32)';
c7 = nd;
g7 = ng;

%block 8
b8 = 'hex (8 16 17 9 40 48 49 41)';
c8 = fd;
g8 = fg;

%block 9
b9 = 'hex (9 17 18 19 41 49 50 51)';
c9 = fd;
g9 = fg;

%block 10
b10 = 'hex (10 9 19 20 42 41 51 52)';
c10 = fd;
g10 = fg;

%block 11
b11 = 'hex (11 10 20 21 43 42 52 53)';
c11 = fd;
g11 = fg;

%block 12
b12 = 'hex (23 11 21 22 55 43 53 54)';
c12 = fd;
g12 = fg;

%block 13
b13 = 'hex (24 12 11 23 56 44 43 55)';
c13 = fd;
g13 = fg;

%block 14
b14 = 'hex (25 13 12 24 57 45 44 56)';
c14 = fd;
g14 = fg;

%block 15
b15 = 'hex (26 27 13 25 58 59 45 57)';
c15 = fd;
g15 = fg;

%block 16
b16 = 'hex (27 28 14 13 59 60 46 45)';
c16 = fd;
g16 = fg;

%block 17
b17 = 'hex (28 29 15 14 60 61 47 46)';
c17 = fd;
g17 = fg;

%block 18 
b18 = 'hex (29 30 31 15 61 62 63 47)';
c18 = fd;
g18 = fg;

%block 19
b19 = 'hex (15 31 16 8 47 63 48 40)';
c19 = fd;
g19 = fg;

%Def'ing curved edges
e = zeros(32,3);
 for i = 1:8
    e(i, 1) = r1*cos((2*i-1)*pi/8);
    e(i,2) = r1*sin((2*i-1)*pi/8);
    e(i,3) = 0;    
    e(i+8, :) = r2*cos((2*i-1)*pi/8);
    e(i+8,2) = r2*sin((2*i-1)*pi/8);
    e(i+8,3) = 0;   
    e(i+16, :) = r1*cos((2*i-1)*pi/8);
    e(i+16,2) = r1*sin((2*i-1)*pi/8);
    e(i+16,3) = 1;
    e(i+24, :) = r2*cos((2*i-1)*pi/8);
    e(i+24,2) = r2*sin((2*i-1)*pi/8);
    e(i+24,3) = 1;
 end

%Writing to file
fileID = fopen('blockMeshDict.txt', 'w');
fprintf(fileID, 'FoamFile \n{\n\tversion  2.0;\n\tformat   ascii;\n\tclass    dictionary;\n\tobject   blockMeshDict;\n}');
fprintf(fileID, '\n\nconvertToMeters 1.0;\n');

fprintf(fileID, '\nvertices\n(\n');
for i=1:length(v)
  fprintf(fileID, '        ( %f %f %f)//%i\n', v(i,1), v(i,2), v(i,3), i-1); 
end
fprintf(fileID, '\n );');

fprintf(fileID, '\nblocks\n(\n');
fprintf(fileID, '\t%s %s %s \n', b0, c0, g0);
fprintf(fileID, '\t%s %s %s \n', b1, c1, g1);
fprintf(fileID, '\t%s %s %s \n', b2, c2, g2);
fprintf(fileID, '\t%s %s %s \n', b3, c3, g3);
fprintf(fileID, '\t%s %s %s \n', b4, c4, g4);
fprintf(fileID, '\t%s %s %s \n', b5, c5, g5);
fprintf(fileID, '\t%s %s %s \n', b6, c6, g6);
fprintf(fileID, '\t%s %s %s \n', b7, c7, g7);
fprintf(fileID, '\t%s %s %s \n', b8, c8, g8);
fprintf(fileID, '\t%s %s %s \n', b9, c9, g9);
fprintf(fileID, '\t%s %s %s \n', b10, c10, g10);
fprintf(fileID, '\t%s %s %s \n', b11, c11, g11);
fprintf(fileID, '\t%s %s %s \n', b12, c12, g12);
fprintf(fileID, '\t%s %s %s \n', b13, c13, g13);
fprintf(fileID, '\t%s %s %s \n', b14, c14, g14);
fprintf(fileID, '\t%s %s %s \n', b15, c15, g15);
fprintf(fileID, '\t%s %s %s \n', b16, c16, g16);
fprintf(fileID, '\t%s %s %s \n', b17, c17, g17);
fprintf(fileID, '\t%s %s %s \n', b18, c18, g18);
fprintf(fileID, '\t%s %s %s \n', b19, c19, g19);

fprintf(fileID, ');'); %including formatting marks

fprintf(fileID, '\nedges\n(\n');
for m = 0:3
   for i = 0:7
       n = m;
       if (m == 2 || m == 3)
           n = m+2;
       end   
    j = i+1;
    if (j==8 || j == 16 || j == 40 || j == 48)
        j = 0;
    end
    fprintf(fileID, '\tarc %i %i (%f %f %f)\n', (i+n*8), (j+n*8), e(i+1 + m*8,1), e(i+1 + m*8,2), e(i+1 + m*8,3));    
   end
end
fprintf(fileID, ');\n');      

%Boundaries are constant for this application (the same face, regardless of size, serves as the boundary of the domain)

fprintf(fileID, '\nboundary\n(\n\n');
fprintf(fileID, '\tinlet\n\t{\n\t\ttype patch;\n\t\tfaces\n\t\t(\n');


fprintf(fileID, '\t\t(23 22 54 55)\n');
fprintf(fileID, '\t\t(24 23 55 56)\n');
fprintf(fileID, '\t\t(25 24 56 57)\n');
fprintf(fileID, '\t\t(26 25 57 58)\n');

fprintf(fileID, '\t\t);\n\t}\n\n\toutlet\n\t{\n\t\ttype patch;\n\t\tfaces\n\t\t(\n');


fprintf(fileID, '\t\t(17 49 50 18)\n');
fprintf(fileID, '\t\t(16 48 49 17)\n');
fprintf(fileID, '\t\t(31 63 48 16)\n');
fprintf(fileID, '\t\t(30 62 63 31)\n');

fprintf(fileID, '\t\t);\n\t}\n\n\tcylinder\n\t{\n\t\ttype wall;\n\t\tfaces\n\t\t(\n');


fprintf(fileID, '\t\t(0 1 33 32)\n');
fprintf(fileID, '\t\t(1 2 34 33)\n');
fprintf(fileID, '\t\t(2 3 35 34)\n');
fprintf(fileID, '\t\t(3 4 36 35)\n');
fprintf(fileID, '\t\t(4 5 37 36)\n');
fprintf(fileID, '\t\t(5 6 38 37)\n');
fprintf(fileID, '\t\t(6 7 39 38)\n');
fprintf(fileID, '\t\t(7 0 32 39)\n');

fprintf(fileID, '\t\t);\n\t}\n\n\ttop\n\t{\n\t\ttype symmetryPlane;\n\t\tfaces\n\t\t(\n');


fprintf(fileID, '\t\t(22 21 53 54)\n');
fprintf(fileID, '\t\t(21 20 52 53)\n');
fprintf(fileID, '\t\t(20 19 51 52)\n');
fprintf(fileID, '\t\t(19 18 50 51)\n');

fprintf(fileID, '\t\t);\n\t}\n\n\tbottom\n\t{\n\t\ttype symmetryPlane;\n\t\tfaces\n\t\t(\n');


fprintf(fileID, '\t\t(30 29 61 62)\n');
fprintf(fileID, '\t\t(29 28 60 61)\n');
fprintf(fileID, '\t\t(28 27 59 60)\n');
fprintf(fileID, '\t\t(27 26 58 59)\n');

fprintf(fileID, '\t\t);\n\t}\n\n);\n');

fclose(fileID);
disp('done!');
