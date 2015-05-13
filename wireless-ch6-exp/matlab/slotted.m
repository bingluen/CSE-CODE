% tp 是回傳值..XD slotted才是function Name %
function tp = slotted(M, frameLength)
	%{ 
		data 應該是指單一Frame的時間長度 
		M 為要被處理的 Cumulative Distribution Function 形成的 Array (因為這裡是dicrete)

	%}

	% 計算 Array M的長度 %
	s = size(M)
	%{
		因為matlab 是 Matrix Lab...所以長度是二維的
		ex
			┌            ┐
			│ 20  30  70 │
			│ 40  50  70 │
			└            ┘
		會回傳 [ 2 3 ] 表示 Row = 2  Colum =3

		Array取值不是用"["和"]"，而是使用"("和")"
		例如 s = [ 2 3 ]
		s(1) 會取得 2
		s(2) 會取得 3
		Index從1開始算
	%}

	% 宣告一個 和 M 一樣大的 Array 且初始化為0
	tp = zeros(s(1), s(2));

	for i = 1:s(2)
	    for j = 1:s(1)
	    	%{
	    		做時間分割，以每一列為單位
	    		（在host數目固定時，ALOHA會使用同一列的時間資料作為 觀察時間）
				
				M(j, i) 是時間軸上的某一點 data
				
				M(j, i)/frameLength == floor(M(j, i)/frameLength 表示不被整除
				（我也不知道為什麼matlab要寫這麼醜的條件）

				只有恰好在Frame長度整數倍的時間點，進行slotted才有意義

	    	%}
	        if M(j, i)/frameLength ~= floor(M(j, i)/frameLength)
	            tp(j, i) = (floor(M(j, i)/frameLength)+1)*frameLength;
	        end
	     end
	end