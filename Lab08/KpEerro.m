close all;
clc;
Kp = 0:0.1:50;
Vi = 3.3;
Vo = (10e3 .* Kp .* Vi)./(10e3 .* ( 1 + Kp));
subplot(2,1,1)
plot(Kp, Vo);
hold on;
plot(Kp, Vo+10);
title('Vo (V) x Kp');
ylabel('Vo (V)'); xlabel('Kp (adm)');
% ylim([0 Vi+0.1]);
% xlim([-1 51]);
grid on
erroRegime =  100 .* (3.3 - (3.3 .* 10e3.*Kp)./( 3.3 .* 10e3.*(1 + Kp)));
%figure;
subplot(2,1,2)
plot(Kp,erroRegime);
title('Erro (%) x Kp - Ea(s) = 1/s');
ylabel('Erro (%)'); xlabel('Kp (adm)');
grid