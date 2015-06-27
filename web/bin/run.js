#!/usr/bin/env node

var app = require('../app');
var http = require('http');

var port = process.env.PORT || '3000';
app.set('port', port);
app.set('host', process.env.HOST)

var server = http.createServer(app);
server.listen(port);