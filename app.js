var arduino = require('duino');

var board = new arduino.Board({
	baudrate: 9600,
	debug: true,
	device: "usbmodemfa131"
});

board.on('ready', function(){
	console.log("ready");

	var rfReceiver = new arduino.RFReceiver({
		board: board,
		pin: '02'
	});

	rfReceiver.on('read', function(err, data){
		console.log("data", data);
	});
});