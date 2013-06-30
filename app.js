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
		console.log("receiver data", data);
	});
});

var tboard = new arduino.Board({
	baudrate: 9600,
	debug: true,
	device : "usbserial-A601EMRF"
});

tboard.on('ready', function(){
	console.log("ready");

	var rfTransmitter = new arduino.RFTransmitter({
		board: tboard,
		pin: '06'
	})

	setInterval(function() {
	  rfTransmitter.send("hey there");
	}, 2000);
});