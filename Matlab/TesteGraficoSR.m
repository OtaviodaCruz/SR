% sim('sltank',100)
% open_system('sltank/Comparison')
x = [1, 2, 3];
% a seguir definir um dominio X Y
[X, Y]= meshgrid(1:5,1:5); % note o ;
% �ndice de X no eixo x, �ndice de Y no eixo y
mesh(x) % s� 1 argumento, p/ o eixo Z