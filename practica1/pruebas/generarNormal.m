## Copyright (C) 2019 Rankern
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} generarNormal (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Rankern <rankern@rankern-HP-Notebook>
## Created: 2019-06-07

function [retval] = generarNormal ()

a = ['../ficherosPrueba/prueba1.pr';'../ficherosPrueba/prueba2.pr'; '../ficherosPrueba/prueba3.pr'; '../ficherosPrueba/prueba4.pr';'../ficherosPrueba/prueba5.pr';'../ficherosPrueba/prueba6.pr';'../ficherosPrueba/prueba7.pr';'../ficherosPrueba/prueba8.pr';'../ficherosPrueba/prueba9.pr'];
b = [1000, 1000,  1500,2000, 2500, 2500, 5000, 10000, 10000]
for i = 1:9
  f = fopen (a(i,:), "w+");
  ale = randn(1, 256) .^2 * b(i);
  total = 0
  for j = 1:256
   escribir(1,1:ale(j)) = j-1;
   total += fwrite(f, escribir, "uchar");
 endfor
 total
endfor

endfunction
