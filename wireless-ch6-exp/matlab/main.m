%Config%

HostNum = 200;
PacketNum = 200;

%
close all;
%clear all;
clc;

% 計算資料 %
[trafficLoad1, thoughtput1] = aloha(HostNum, PacketNum);

[trafficLoad2, thoughtput2] = slotted_aloha(HostNum, PacketNum);

% 畫圖 Prue ALOHA 用紅色  Slotted ALOHA用藍色 %
plot(trafficLoad1, thoughtput1, 'r', trafficLoad2, thoughtput2, 'b');
title('Prue ALOHA V.S. Slotted ALOHA');
legend('Prue ALOHA', 'Slotted ALOHA');
xlabel('Traffic Load');
ylabel('Thoughput');
