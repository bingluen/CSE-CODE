var aloha = function(hostNum, packetNum, next) {

    var result = {};

    result.trafficLoad = [];
    result.throughput = [];

    /* number of host must big than or equal to 2 */
    if (hostNum < 2) {
        console.log("Error: number of host must big than or equal to 2.");
        return;
    }

    for (var hosts = 2; hosts <= hostNum; hosts++) {
        /* 產生隨機時間點 */
        randomTimePoint = timePointMartixGenerator(packetNum, hosts);

        /**
         * 決定ALOHA觀察時間長度
         * 取上面產生的矩陣當中的最後一列之第一項
         * array index從0開始orz
         */
        observedTimeLength = randomTimePoint[packetNum - 1][0];

        //console.log(observedTimeLength);

        /**
         * 把剛剛的randomTimePoint 拉成一維，並且排序
         */

        sequence = matirx2DTo1D(randomTimePoint);

        //console.log(sequence);

        /* 從小排到大形成時間軸 */
        sequence = sequence.sort();

        //console.log(sequence);


        /* 統計資料初始化 */
        var totalPacket = 0;
        var successPacket = 0;

        /* 設定frameLength */
        var frameLength = 0.004;

        /* 產生interval （把sequence微分） */
        var interval = diff1DMatirx(sequence);

        //console.log(interval);


        for (var i = 0; i < hosts * packetNum - 1; i++) {
            if (sequence[i+1] > observedTimeLength)
                continue;

            /* totalPacket ++ */
            totalPacket++;

            if (i == 0 || i == hosts * packetNum - 1) {
                if (interval[i] >= frameLength)
                    successPacket++;
            } else if (interval[i] >= frameLength && interval[i - 1] >= frameLength) {
                successPacket++;
            }

            result.trafficLoad[hosts - 2] = frameLength * totalPacket / observedTimeLength;
            result.throughput[hosts - 2] = frameLength * successPacket / observedTimeLength;
        }

    }
    console.log(result);

    next(result);
}


var slotted_aloha = function(hostNum, packetNum, next) {

    var result = {};

    /* 設定frameLength */
    var frameLength = 0.004;

    result.trafficLoad = [];
    result.throughput = [];

    /* number of host must big than or equal to 2 */
    if (hostNum < 2) {
        console.log("Error: number of host must big than or equal to 2.");
        return;
    }

    for (var hosts = 2; hosts <= hostNum; hosts++) {
        /* 產生隨機時間點 */
        randomTimePoint = timePointMartixGeneratorSlotted(packetNum, hosts, frameLength);

        /**
         * 決定ALOHA觀察時間長度
         * 取上面產生的矩陣當中的最後一列之第一項
         * array index從0開始orz
         */
        observedTimeLength = randomTimePoint[packetNum - 1][0];

        //console.log(observedTimeLength);

        /**
         * 把剛剛的randomTimePoint 拉成一維，並且排序
         */

        sequence = matirx2DTo1D(randomTimePoint);

        //console.log(sequence);

        /* 從小排到大形成時間軸 */
        sequence = sequence.sort();

        //console.log(sequence);


        /* 統計資料初始化 */
        var totalPacket = 0;
        var successPacket = 0;

        

        /* 產生interval （把sequence微分） */
        var interval = diff1DMatirx(sequence);

        //console.log(interval);


        for (var i = 0; i < hosts * packetNum - 1; i++) {
            if (sequence[i+1] > observedTimeLength)
                continue;

            /* totalPacket ++ */
            totalPacket++;

            if (interval[i] >= frameLength)
                successPacket++;

            result.trafficLoad[hosts - 2] = frameLength * totalPacket / observedTimeLength;
            result.throughput[hosts - 2] = frameLength * successPacket / observedTimeLength;
        }

    }
    console.log(result);

    next(result);
}



var timePointMartixGenerator = function(packetNum, hosts) {
    var randomFactor = 1; /* Magic Number?! */

    /* 2-D的Matrix */
    /**
     * 分佈長相 PacketNum × hosts
     *     ┌                           ┐
     *     │ 0.8507 0.7368 .... 0.6925 │
     *     │ 1.4113 1.3246 .... 1.2492 │
     *     │    ¦      ¦     ＼    ¦   │
     *     │13.6273 11.6090 .... 9.8195│
     *     └                           ┘
     */

    /**
     * 先產生 隨機數的Matrix 在改成上面的累加
     *     ┌                           ┐
     *     │ 0.8507 0.7368 .... 0.6925 │
     *     │ 0.5606 0.5860 .... 0.5567 │
     *     │    ¦      ¦     ＼    ¦   │
     *     │ 0.8452 0.2094 .... 0.9430 │
     *     └                           ┘
     */

    var matrix = [];

    for (var i = 0; i < packetNum; i++) {
        var row = [];
        for (var j = 0; j < hosts; j++) {
            row.push(randomFactor * Math.random());
        }
        //console.log('row' + i + ':' + row);
        matrix.push(row);
    }
    /**
     * 轉換成累加的
     *     ┌                           ┐
     *     │ 0.8507 0.7368 .... 0.6925 │
     *     │ 1.4113 1.3246 .... 1.2492 │
     *     │    ¦      ¦     ＼    ¦   │
     *     │13.6273 11.6090 .... 9.8195│
     *     └                           ┘
     */

    for (var i = 1; i < packetNum; i++) {
        for (var j = 0; j < hosts; j++) {
            matrix[i][j] = matrix[i][j] + matrix[i - 1][j];
        }
        //console.log('row' + i + ':' + matrix[i]);
    }

    return matrix;
}


var timePointMartixGeneratorSlotted = function(packetNum, hosts, frameLength) {
    var randomFactor = 1; /* Magic Number?! */

    /* 2-D的Matrix */
    /**
     * 分佈長相 PacketNum × hosts
     *     ┌                           ┐
     *     │ 0.8507 0.7368 .... 0.6925 │
     *     │ 1.4113 1.3246 .... 1.2492 │
     *     │    ¦      ¦     ＼    ¦   │
     *     │13.6273 11.6090 .... 9.8195│
     *     └                           ┘
     */

    /**
     * 先產生 隨機數的Matrix 在改成上面的累加
     *     ┌                           ┐
     *     │ 0.8507 0.7368 .... 0.6925 │
     *     │ 0.5606 0.5860 .... 0.5567 │
     *     │    ¦      ¦     ＼    ¦   │
     *     │ 0.8452 0.2094 .... 0.9430 │
     *     └                           ┘
     */

    var matrix = [];

    for (var i = 0; i < packetNum; i++) {
        var row = [];
        for (var j = 0; j < hosts; j++) {
            row.push(randomFactor * Math.random());
        }
        //console.log('row' + i + ':' + row);
        matrix.push(row);
    }

    /**
     * 先做Slotted在累加
     * 程式實質上run的時候只是把資料變成frameLength的整數倍...
     */
    
    for(var i = 0; i < packetNum; i++) {
        for(var j = 0; j < hosts; j++)
        {
            if(matrix[i][j] % frameLength != 0)
                matrix[i][j] = (Math.floor(matrix[i][j]/frameLength)+1)*frameLength;
        }
    }

    /**
     * 轉換成累加的
     *     ┌                           ┐
     *     │ 0.8507 0.7368 .... 0.6925 │
     *     │ 1.4113 1.3246 .... 1.2492 │
     *     │    ¦      ¦     ＼    ¦   │
     *     │13.6273 11.6090 .... 9.8195│
     *     └                           ┘
     */

    for (var i = 1; i < packetNum; i++) {
        for (var j = 0; j < hosts; j++) {
            matrix[i][j] = matrix[i][j] + matrix[i - 1][j];
        }
        //console.log('row' + i + ':' + matrix[i]);
    }

    return matrix;
}

var matirx2DTo1D = function(matrix) {
    var array = [];

    for (var i = 0; i < matrix.length; i++) {
        array = array.concat(matrix[i]);
    }

    return array;
}

var diff1DMatirx = function(matrix) {
    var diffResult = [];
    for (var i = 1; i < matrix.length; i++) {
        diffResult.push(matrix[i] - matrix[i - 1]);
    }

    return diffResult;
}

var init = function()
{
    aloha(200, 200, drawChart);
    console.log('分隔');
    slotted_aloha(200, 200, drawChart);
}

google.setOnLoadCallback(init);