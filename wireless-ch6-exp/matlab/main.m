%Config%

HostNum = 200;
PacketNum = 200;

%
close all;
%clear all;
clc;

% 計�?資�? %
[trafficLoad1, thoughtput1] = aloha(HostNum, PacketNum);

[trafficLoad2, thoughtput2] = slotted_aloha(HostNum, PacketNum);

% ?��? Prue ALOHA ?��??? Slotted ALOHA?��???%
plot(trafficLoad1, thoughtput1, 'r', trafficLoad2, thoughtput2, 'b');
title('Pure ALOHA V.S. Slotted ALOHA');
legend('Pure ALOHA', 'Slotted ALOHA');
xlabel('Traffic Load');
ylabel('Throughput');

grid on;