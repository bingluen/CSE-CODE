var getErlangs = function(lambda, holdingTime) {
    return lambda * holdingTime / 3600;
}

var getErlangsB = function(numChannels, erlangs) {
    var numerator = getPower(erlangs, numChannels) / getFactorial(numChannels);
    var denominator = 0;
    for (var i = 0; i <= numChannels; i++) {
        denominator += getPower(erlangs, i) / getFactorial(i);
    }

    return numerator / denominator;
}

var getErlangsC = function(numChannels, erlangs) {
    var numerator = getPower(erlangs, numChannels) / getFactorial(numChannels - 1) / (numChannels - erlangs);
    var denominator = numerator
    for (var i = 0; i < numChannels; i++) {
        denominator += getPower(erlangs, i) / getFactorial(i);
    }

    return numerator / denominator;
}

var getFactorial = function(n) {
    if (n <= 0)
        return 1;
    else if (n == 1)
        return 1;
    else
        return n * getFactorial(n - 1);
}

var getPower = function(base, square) {
    if (square == 0)
        return 1;
    else if (square == 1)
        return base;
    else
        return base * getPower(base, square - 1);

}

var generatingErlangBData = function(numChannels, arrivalRate, arrivalOffset, holdingTime, holdingOffset) {
    var datas = [];

    for (var i = holdingTime.lowerBound; i <= holdingTime.upperBound; i += holdingOffset) {
        var data = {};
        data.holdingTime = i;
        data.blockingProbability = [];
        for (var j = arrivalRate.lowerBound; j <= arrivalRate.upperBound; j += arrivalOffset) {
            var blockingProbability = {};
            blockingProbability.arrivalRate = j;
            blockingProbability.value = getErlangsB(numChannels, getErlangs(i, j));
            data.blockingProbability.push(blockingProbability);
        }
        datas.push(data);
    }

    return datas;
}

var generatingErlangCData = function(numChannels, arrivalRate, arrivalOffset, holdingTime, holdingOffset) {
    var datas = [];

    for (var i = holdingTime.lowerBound; i <= holdingTime.upperBound; i += holdingOffset) {
        var data = {};
        data.holdingTime = i;
        data.queueProbability = []
        for (var j = arrivalRate.lowerBound; j <= arrivalRate.upperBound; j += arrivalOffset) {
            var queueProbability = {};
            queueProbability.arrivalRate = j;
            queueProbability.value = getErlangsC(numChannels, getErlangs(i, j));
            data.queueProbability.push(queueProbability);
        }
        datas.push(data);
    }

    return datas;
}

var doPrint = function() {

    var arrivalRate = {};

    var holdingTime = {};

    var arrivalOffset = Number($('#arrivalRateStep').val()) > 0 ? Number($('#arrivalRateStep').val()) : 1;

    var holdingOffset = Number($('#holdingTimeStep').val()) > 0 ? Number($('#holdingTimeStep').val()) : 1;

    arrivalRate.lowerBound = Number($('#arrivalRateLowerBound').val()) > 0 ? Number($('#arrivalRateLowerBound').val()) : 1;
    arrivalRate.upperBound = Number($('#arrivalRateUpperBound').val()) > arrivalRate.lowerBound ? Number($('#arrivalRateUpperBound').val()) : arrivalRate.lowerBound + arrivalOffset;

    holdingTime.lowerBound = Number($('#holdingTimeLowerBound').val()) > 0 ? Number($('#holdingTimeLowerBound').val()) : 1;
    holdingTime.upperBound = Number($('#holdingTimeUpperBound').val()) > holdingTime.lowerBound ? Number($('#holdingTimeUpperBound').val()) : holdingTime.lowerBound + holdingOffset;

    var numChannels = Number($('#numChannel').val()) > 0 ? Number($('#numChannel').val()) : 1;

    var ErlangBData = generatingErlangBData(numChannels, arrivalRate, arrivalOffset, holdingTime, holdingOffset);

    var ErlangCData = generatingErlangCData(numChannels, arrivalRate, arrivalOffset, holdingTime, holdingOffset)

    console.log(ErlangBData);

    console.log(ErlangCData);

    /* draw Erlang B  */

    var ErlangBDrawData = [];
    var title = [];
    title.push('Holding Time');
    for (var j = 0; j < ErlangBData[0].blockingProbability.length; j++) {
        title.push('Arrival Rate = ' + ErlangBData[0].blockingProbability[j].arrivalRate);
    }
    ErlangBDrawData.push(title);
    for (var i = 0; i < ErlangBData.length; i++) {
        var data = [];
        data.push(ErlangBData[i].holdingTime);
        for (var j = 0; j < ErlangBData[i].blockingProbability.length; j++) {
            data.push(ErlangBData[i].blockingProbability[j].value);
        }

        ErlangBDrawData.push(data);
    }

    console.log(ErlangBDrawData);


    var data = google.visualization.arrayToDataTable(ErlangBDrawData);

    var options = {
        title: 'Erlang B',
        titleTextStyle: {
            fontSize: 18
        },
        width: 1080,
        curveType: 'function',
        legend: {
            position: 'right'
        },
        hAxis: 
        {
            title: 'Holding Time'
        },
        vAxis:
        {
            title: 'Blocking Probability'
        }
    };

    var ErlangsBGraph = new google.visualization.LineChart(document.getElementById('ErlangsBGraph'));

    ErlangsBGraph.draw(data, options);

    var ErlangCDrawData = [];
    var title = [];
    title.push('Holding Time');
    for (var j = 0; j < ErlangCData[0].queueProbability.length; j++) {
        title.push('Arrival Rate = ' + ErlangCData[0].queueProbability[j].arrivalRate);
    }
    ErlangCDrawData.push(title);
    for (var i = 0; i < ErlangCData.length; i++) {
        var data = [];
        data.push(ErlangCData[i].holdingTime);
        for (var j = 0; j < ErlangCData[i].queueProbability.length; j++) {
            data.push(ErlangCData[i].queueProbability[j].value);
        }

        ErlangCDrawData.push(data);
    }

    console.log(ErlangCDrawData);


    var dataC = google.visualization.arrayToDataTable(ErlangCDrawData);

    var optionsC = {
        title: 'Erlang C',
        titleTextStyle: {
            fontSize: 18
        },
        width: 1080,
        curveType: 'function',
        legend: {
            position: 'right'
        },
        hAxis: 
        {
            title: 'Holding Time'
        },
        vAxis:
        {
            title: 'Delayed Probability'
        }
    };

    var ErlangsCGraph = new google.visualization.LineChart(document.getElementById('ErlangsCGraph'));

    ErlangsCGraph.draw(dataC, optionsC);


}

var initialize = function() {
    $('#printButton').click(function() {
        if(!($('#graph').is(":visible"))) {
            $('#graph').toggle(1500, null);
        }
        doPrint();
    });
    $('#calculateMinChannel').click(function() {
        $('#minChannel').text(getMinChannels(Number($('#getChannelBolcingProbability').val()), Number($('#getChannelArrivalRate').val()), Number($('#getChannelServiceTime').val())));
    });
}

google.setOnLoadCallback(initialize);


var getMinChannels = function (blockingProbability, arrivalRate, holdingTime) {
    for (var i = 0; ; i++) {
        if (getErlangsB(i, getErlangs(arrivalRate, holdingTime)) <= blockingProbability)
            return i;
    }
}