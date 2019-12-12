% sim('sltank',100)
% open_system('sltank/Comparison')
x = [1, 2, 3];
% a seguir definir um dominio X Y
[X, Y]= meshgrid(1:5,1:5); % note o ;
% índice de X no eixo x, índice de Y no eixo y
mesh(x) % só 1 argumento, p/ o eixo Z