var fs          = require('fs');
var app         = require('express')();
var server;
if (process.env.ENABLE_SSL) {
    server      = require('https').Server({
	key:  fs.readFileSync('server.key'),
	cert: fs.readFileSync('server.crt'),
	ca:   fs.readFileSync('ca.crt'),
	requestCert: true,
	rejectUnauthrized: false
    }, app);
    console.log('enable ssl');

} else {
    server      = require('http').Server(app);
}
var io          = require('socket.io')(server);

server.listen(8000);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket) {

    socket.on('join', function(data) {
		socket.join(data.type);
		socket.session = {
		    name: data.name
		}
		console.log('join:', data.name);
    });

    socket.on('run', function(data) {
		data.from = socket.session.name;
		socket.broadcast.emit('run', data);
		console.log('run(' + data.from + '):' + data.command);
    });

    socket.on('reply', function(data) {
		data.from = socket.session.name;
		io.to('browser').emit('reply', data);
		console.log('reply(' + data.from + '):' + data.output);
    });
});
