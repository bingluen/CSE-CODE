var drawChart = function(data) {
    var charData = [];
    var title = ['Traffic load', 'Pure ALOHA'];
    charData.push(title);

    for (var i = 0; i < data.trafficLoad.length; i++) {
        var row = [];
        row.push(data.trafficLoad[i]);
        row.push(data.throughput[i]);
        charData.push(row);

        console.log(row);
    }

    var options = {
        title: 'ALOHA',
        curveType: 'function',
        legend: {
            position: 'right'
        }
    };

    var dataToDraw = google.visualization.arrayToDataTable(charData);

    var chart = new google.visualization.LineChart(document.getElementById('graphCanvas'));

    chart.draw(dataToDraw, options);
}
