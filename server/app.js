'use strict';

/*
  Example by Víctor Díaz.
 */
const express = require('express');
const bodyParser = require('body-parser'); // Body request parser

const PORT = 3000; // Server port

const app  = express(); // Make server app

// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }));

// parse application/json
app.use(bodyParser.json());

// Index get route
app.get('/', function(req, res) {
  res.send('<h1> Hello arduino. I listened your GET request. </h1>')
});

// Index post route
app.post('/', function(req, res) {
  let msg = '<h1> Hello arduino. I listened your POST request </h1>';

  if(req.body.msg) {
    msg += '<p> Your message "' + req.body.msg + '". </p>';
  } else {
    msg += '<p> You didn\'t send a message. </p>';
  }

  res.send(msg);
});

// Run server
app.listen(PORT, function() {
  console.log('Server running on port: ' + PORT);
});
