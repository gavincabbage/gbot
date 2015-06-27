var express = require('express');
var path = require('path');
var fs = require('fs');
var mustache = require('mustache');
var redis = require('redis');

var redisClient = redis.createClient(4290, '127.0.0.1', {});

redisClient.on("error", function (err) {
    console.log("Redis error " + err);
});

// need for web
// port
// route

// redisClient.get("web.enabled", function(err, reply) {
//     if (err !== null) {
//         console.log(err);
//     }
//     console.log("web.enabled: ", reply);
// });

// redisClient.get("web.port", function(err, reply) {
//     if (err) {
//         console.log(err);
//     }
//     console.log("web.port: ", reply);
// });
    
    
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
    var view = {
        "test": "this is a test value",
        "feed_url": "/feed"
    };
    redisClient.get("web.port", function(err, reply) {
        if (err) {
            console.log(err);
        }
        console.log("web.port: ", reply);
        view.port = reply;
    });
    var template = fs.readFileSync('templates/index.html', 'utf8')
    var output = mustache.to_html(template, view);
    res.write(output);
    res.end();
});

var app = express();
app.use(express.static(path.join(__dirname, 'static')));
app.use('/', router);
module.exports = app;
