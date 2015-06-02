var sequence50 = [];
var sequence30 = [];
var count = 0;




setInterval(function() {
    count++;
    sequence50.push({
        x: PoissonProcess.sample(50),
        y: count
    });
    sequence30.push({
        x: PoissonProcess.sample(30),
        y: count
    });

    var chart = new CanvasJS.Chart("chartContainer", {
        animationEnabled: true,
        animationDuration: 1500,
        legend: {
            horizontalAlign: "left", // "center" , "right"
            verticalAlign: "center", // "top" , "bottom"
            fontSize: 15
        },
        title: {
            text: "Request distribution"
        },
        data: [{
        	showInLegend: true,
        	legendText: "Mean equal to 30",
            type: "scatter",
            dataPoints: sequence30
        }, {
        	showInLegend: true,
        	legendText: "Mean equal to 50",
            type: "scatter",
            dataPoints: sequence50
        }]
    });
    chart.render();
}, 2500);
