%Pure ALOHA 模擬

%G = traffic load, S = throughput，兩個都是array

function [G, S] = aloha(HostNum, PacketNum)

	% 所謂host就是 互相傳資料的point數量，小於2的話是要傳給鬼喔%

	if(HostNum < 2)
		error('Error: number of host must big than or equal to 2.')
	end

	factor = 1; % Magic Number for random number (ΦωΦ)　% 

	for hosts = 2:HostNum

		% 產生隨機時間點 %
		randTimePoint = cumsum(factor* rand(PacketNum, hosts));

		%{ 
			cusum 是 產生 Cumulative Distribution Function 的 function
			第k項會等於 前k項和
		%}


		% ALOHA 的觀察時間點 %
		observedTimePoint = randTimePoint(PacketNum, 1);

		% 把randTimePoint 的資料改寫成 1-D array%
		sequence = zeros(1, hosts*PacketNum);
		for i = 1:PacketNum
			sequence(1, (i-1) * hosts+1:i*hosts) = randTimePoint(i, :);
		end

		% 重新排序 %
		sequence = sort(sequence);

		% 統計資料 %
		totalFrame = 0; % 總傳輸 Time Frame %
		successFrame = 0; % 沒有遇到碰撞的 Time Frame 數目 %
		frameTime = 0.004 % 每一個Frame長度 （佔用的時間） 這裡也是個magic Number 不知道為什麼給這個值 % 

		% Frame之間的時間間隔 %
		interval = diff(sequence); % 把剛剛 sequence 微分 %

		%{
			所謂的 array 微分呢...即：
			將 Cumulative Distribution Function 
			還原成
			Probability Density Function 的概念...

			最初在產生 randTimePoint時為了產生出時間軸上的點，

			透過cumsum函數 把產生的隨機數進行累加來形成時間軸，

			在此透過微分還原他
		%}



		% 模擬不同的host數和封包數搭配的狀況 %
		for i = 1:hosts*PacketNum - 1
			% 只在 剛剛選定ALOHA觀察時間內進行觀察 %
			if sequence(i+1) > observedTimePoint
				continue;
			end

			% Frame 累加 %
			totalFrame = totalFrame + 1;

			% 第一個&最後一個Frame 只要發送時間點大於等於應該等待間隔時，就算成功 %
			if ( i == 1 || i = hosts*PacketNum ) && interval(1, i) >= frameTime 
				successFrame = successFrame +1;
			end

			% 非最開始及最後的case，則要顧慮前後的間隔是否足夠，足夠才算成功 %
			if i ~= 1 && i ~= hosts*PacketNum && interval(1, i) >= frameTime && interval(1, i-1) >= frameTime
				successFrame = successFrame +1;
			end

			%計算在此case下（特定的host數目和packet數目）traffic load 和 throughput
			G(hosts-1) = frameTime/observerdTime*totalFrame;
			S(hosts-1) = frameTime/observerdTime*successFrame;
		end
	end




